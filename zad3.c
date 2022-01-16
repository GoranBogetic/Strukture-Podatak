#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthyear;
    Position next;
}Person;

Position createNewPerson(char* name, char* surname, int birthyear)
{
    Position newPerson = NULL;
    newPerson = (Position) malloc (sizeof(Person));
    
    if(!newPerson){
        printf("Couldn't allocate memory.\n");
        return NULL;
    }
    
    strcpy (newPerson -> name, name);
    strcpy (newPerson -> surname, surname);
    newPerson -> birthyear = birthyear;
    newPerson -> next = NULL;
    return newPerson;
}

int InsertAfter (Position newPerson, Position p)
{
    newPerson -> next = p -> next;
    p -> next = newPerson;
    return 0;
}

int AddAtFront (char* name, char* surname, int birthyear, Position head)
{
    Position newPerson = NULL;
    newPerson = createNewPerson (name, surname, birthyear);
    
    if(!newPerson)
        return -1;
    
    InsertAfter(newPerson, head);
    return 0;
}



int Print (Position frs)
{
    Position temp = frs;
    
    if(!temp)
        printf("Empty list.\n\n");
    else
        printf("Name\tSurname\t\tBirth year\n");    
        
    for(temp; temp; temp = temp -> next)
        printf("%s\t%s\t\t%d\n", temp -> name, temp -> surname, temp -> birthyear);
        
    return 0;
}

Position FindLast (Position head)
{
    Position last = head;
    while(last -> next){
        last = last -> next;
    }
    return last;
}

int AddAtBack (char* name, char* surname, int birthyear, Position head)
{
    Position newPerson = NULL;
    Position last = NULL;
    newPerson = createNewPerson (name, surname, birthyear);
    
    if(!newPerson)
        return -1;
        
    last = FindLast(head);
    InsertAfter(newPerson, last);
    return 0;
}



Position FindBySurname (char* surname, Position frs)
{
    Position temp = frs;
    for(temp; temp; temp = temp -> next)
        if(strcmp(temp -> surname, surname) == 0)
            return temp;
            
    if(!temp)
        printf("No %s was found in the list.\n\n", surname);
    return temp;    
}

int Delete (char* surname, Position head)
{
    Position temp = head;
    Position toDelete = NULL;
    
    for(temp; temp -> next; temp = temp -> next)
        if(strcmp(temp -> next -> surname, surname) == 0)
            break;
    toDelete = temp -> next;
    temp -> next = toDelete -> next;
    free(toDelete);
    return 0;
}

int DeleteAll (Position head)
{
    Position temp = NULL;
    while(head -> next != NULL){
        temp = head -> next;
        head -> next = temp -> next;
        free(temp);
    }
    return 0;
}

Position FindPrevious (char* surname, Position head)
{
    Position temp = head;
    for(temp; temp -> next; temp = temp -> next)
        if(strcmp(temp -> next -> surname, surname) == 0)
                return temp;
                
    return temp;
}

int AddBehind (char* name, char* surname, int birthyear, char* behind, Position head)
{
    Position temp = NULL;
    Position newPerson = NULL;
    
    temp = FindBySurname(behind, head -> next);
    if(!temp)
        return -1;
        
    newPerson = createNewPerson(name, surname, birthyear);
    if(!newPerson)
        return -1;
    
    InsertAfter(newPerson, temp);
    return 0;
}

int AddBefore (char* name, char* surname, int birthyear, char* before, Position head)
{
    Position temp = NULL;
    Position newPerson = NULL;
    
    temp = FindPrevious(before, head);
    if(!temp)
        return -1;
    
    newPerson = createNewPerson(name, surname, birthyear);
    if(!newPerson)
        return -1;
    
    InsertAfter(newPerson, temp);
    return 0;
}

int AddSorted (char* name, char* surname, int birthyear, Position head)
{
    Position temp = head;
    Position newPerson = NULL;
    for(temp; temp -> next; temp = temp -> next){
        if(strcmp(surname, temp -> next -> surname) == 0){
            if(strcmp(name, temp -> next -> name) < 0)
                break;
                
            if(strcmp(name, temp -> next -> name) == 0)
                if(birthyear < temp -> next -> birthyear)
                    break;
        }
        
        if(strcmp(surname, temp -> next -> surname) < 0)
            break;
    }
    
    newPerson = createNewPerson(name, surname, birthyear);
    if(!newPerson)
        return -1;
        
    InsertAfter(newPerson, temp);
    return 0;
}

int WriteInFile (char* fName, Position frs)
{
    Position temp = frs;
    FILE* f = NULL;
    
    f = fopen(fName, "w");
    if(f == NULL){
        printf("Otvaranje datoteke je neuspjesno.\n");
        return -1;
    }
    
    fprintf(f, " Name       Surname     Birth year");
    for(temp; temp; temp = temp -> next)
        fprintf(f, "\n %s %s %d", temp -> name, temp -> surname, temp -> birthyear);
        
    printf("\n");
    
    fclose(f);
    return 0;
}

int ReadFile (char* fName, Position head)
{
    Position temp = head;
    FILE* f = NULL;
    char buffer[MAX_SIZE] = {0};
    char name[MAX_SIZE] = {0};
    char surname[MAX_SIZE] = {0};
    int birthyear = 0;
    
    f = fopen(fName, "r");
    if(f == NULL){
        printf("Otvaranje datoteke je neuspjesno.\n");
        return -1;
    }
    
    while(!feof(f)){
        fgets(buffer, MAX_SIZE, f);
        if(sscanf(buffer, " %s %s %d", name, surname, &birthyear) == 3)
            AddSorted(name, surname, birthyear, temp);
    }
    
    fclose(f);
    return 0;
}

int Sort (Position head)
{
    WriteInFile("Sort.txt", head -> next);
    DeleteAll(head);
    ReadFile("Sort.txt", head);
    return 0;
}

int Menu(Position p)
{
    char fName={0};
    int option=0;
    char name[20]={0};
    char surname[20]={0};
    char s[20]="0";
    int birthYear=0;
    int temp=1;
    int OnOff=1;
    
    while(OnOff)
    {
        printf("\nEnter number coresponding to action you want to perform:\n"
                "1 -> Add a new person to the list\n"
                "2 -> Delete someone from the list\n"
                "3 -> Check if someone is on the list\n"
                "4 -> Print the list\n"
                "5 -> Delete the list\n"
                "6 -> Read list from a file\n"
                "7 -> Sort list\n"
                "8 -> Write list in a file\n"
                "9 -> Exit\n");
                
        scanf("%d", &option);
            
        switch(option)
        {
            case 1:
            {
                while(temp)
                {
                    printf("\n1 -> Add to the beginning\n"
                            "2 -> Add to the end\n"
                            "3 -> Add sorted (this is pointless if the list insn't sorted already)\n"
                            "4 -> Return to previous menu\n");
                            
                    scanf("%d", &option);
                    
                    switch(option)
                    {
                        case 1:
                        {
                            while(1)
                            {
                                printf("Enter in order: name surname birthyear\n");
                                if(scanf("%s %s %d", name, surname, &birthYear) == 3){
                                    AddAtFront(name, surname, birthYear, p);
                                    break;
                                }   
                    
                                else 
                                    printf("Incorrect input. Try again\n");
                            }
                
                            break;
                        }
                    
                        
                        case 2:
                        {
                            while(1)
                            {
                                printf("Enter in order: name surname birthyear\n");
                                if(scanf("%s %s %d", name, surname, &birthYear) == 3){
                                    AddAtBack(name, surname, birthYear, p);
                                    break;
                                }
                    
                                else 
                                    printf("Incorrect input. Try again\n");
                            }
                
                            break;
                        }
            
                        case 3:
                        {
                            while(1)
                            {
                                printf("Enter in order: name surname birthyear\n");
                                if(scanf("%s %s %d", name, surname, &birthYear) == 3){
                                    AddSorted(name, surname, birthYear, p);
                                    break;
                                }
                    
                                else 
                                    printf("Incorrect input. Try again\n");
                            }
                
                            break;
                        }
                        
                        case 4:
                        {
                            temp = 0;
                            break;
                        }
                        
                        default:
                        {
                            printf("Incorrect input. Try again\n");
                            break;
                        }
                    }
                }
                
                break;
            }
            
            case 2:
            {
                printf("Enter the surname of the person you wish to delete\n");
                scanf("%s", s);
                Delete(s, p);
                        
                break;
            }
                    
            case 3:
            {
                printf("Enter the surname of the person you wish to check\n");
                scanf("%s", s);
                if(!FindBySurname(s, p -> next))
                    printf("There is no %s in this list", s);
                else
                    printf("%s is in this list", s);
                            
                break;
            }
                    
            case 4:
            {
                Print(p -> next);
                break;
            }
                    
            case 5:
            {
                DeleteAll(p);
                break;
            }
                    
            case 6:
            {
                DeleteAll(p);
                printf("Enter the name of the .txt file you wish to read from:\n");
                scanf("%s", s);
                strcat(s, ".txt");
                ReadFile(s, p);
                    
                break;
            }
                    
            case 7:
            {
                Sort(p);
                break;
            }
                    
            case 8:
            {
                printf("Enter the name of the .txt file you wish to write in:\n");
                scanf("%s", s);
                strcat(s, ".txt");
                WriteInFile(s, p -> next);
                        
                break;
            }
                    
            case 9:
            {
                OnOff = 0;
                break;
            }
                    
            default:
            {
                printf("Incorrect input. Try again\n");
                break;
            }
                
        }
    }
	return 0;
}

int main()
{
    Person head = {.name = {0}, .surname = {0}, .birthyear = 0, .next = NULL};
    Position p = &head;
    
    Menu(p); 
    
    return 0;
}
