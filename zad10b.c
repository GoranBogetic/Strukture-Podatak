#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (1024)

struct _list;
typedef struct _list* Point;
typedef struct _list{
    Point next;
    char name[128];
    int pop;
}list;

struct _tree;
typedef struct _tree* Pos;
typedef struct _tree{
    Pos L;
    Pos R;
    char name[128];
    Point next;
}tree;



int Menu(Pos pRoot);
Point CreateCity(char* name, int pop);
Pos CreateCountry(char* name);
Point InsertCity(Point p, Point newEL);
Pos InsertCountry(Pos head, Pos newEl);
int ReadCountry(char* fName, Pos p);
Pos ReadCity(char* fName, Pos p);
int PrintCities(Point p);
int PrintAll(Pos p);
int DeleteList(Point first);
int DeleteAll(Pos p);
Pos FindCountry(char* name, Pos p);
int PrintInCountryBiggerThan(Pos country, int n);
int PrintCitiesBiggerThan(Point p, int n);

int main()
{
    tree root = {.next = NULL, .name = {0}, .L = NULL, .R = NULL};
    Pos pRoot = &root;
    
    return Menu(pRoot);
}

int Menu(Pos pRoot)
{
    int option = 0;
    
    while(1)
    {
        printf("\nEnter number coresponding to action you want to perform:\n"
                "1 -> Read from file\n"
                "2 -> Print everything\n"
                "3 -> Print cities in country with population larger than n\n"
                "4 -> Delete everything\n"
                "5 -> Exit\n");
                
        scanf(" %d", &option);
        
        switch(option)
        {
            case 1:
            {
                char s[30] = "0";
                printf("Enter the name of text file you want to read from:\n");
                scanf(" %s", s);
                if(strlen(s) > 4 && strcmp(&s[strlen(s) - 4], ".txt"))
                    strcat(s, ".txt");
                ReadCountry(s, pRoot);
                
                option = 0;
                break;
            }
            
            case 2:
            {
                PrintAll(pRoot);
                
                option = 0;
                break;
            }
            
            case 3:
            {
                char s[30] = "0";
                int n = 0;
                printf("Enter the name of the country and the minimum population:\n");
                scanf(" %s %d", s, &n);
                PrintInCountryBiggerThan(FindCountry(s, pRoot), n);
                
                option = 0;
                break;
            }
            
            case 4:
            {
                DeleteAll(pRoot->L);
                DeleteAll(pRoot->R);
                strcpy(pRoot->name, "0");
                pRoot->L = NULL;
                pRoot->R = NULL;
                
                break;
            }
            
            case 5:
            {
                DeleteAll(pRoot->L);
                DeleteAll(pRoot->R);
                
                return 0;
            }
            
            default:
            {
                printf("\nIncorrect input. Try again.\n");
                
                option = 0;
                break;
            }
        }
    }
    
    return -1;
}

Point CreateCity(char* name, int pop)
{
    Point newCity = NULL;
    newCity = (Point)malloc(sizeof(list));
    
    if(!newCity){
        printf("Memory allocation failed.");
        return NULL;
    }
    
    strcpy(newCity->name, name);
    newCity->next = NULL;
    newCity->pop = pop;
   
    return newCity;
}

Pos CreateCountry(char* name)
{
    Pos newCountry = NULL;
    newCountry = (Pos)malloc(sizeof(tree));
    
    if(!newCountry){
        printf("Memory allocation failed.");
        return NULL;
    }
    
    strcpy(newCountry->name, name);
    newCountry->next = NULL;
    newCountry->R = NULL;
    newCountry->L = NULL;
    return newCountry;
}

Point InsertCity(Point p, Point newEl)
{
    Point temp = NULL;
    
    if(!p)
        return newEl;
        
    temp = p;
    while(1)
    {
        if(temp->next != NULL && (temp->next->pop < newEl->pop || temp->next->pop == newEl->pop && strcmp(temp->next->name, newEl->name) < 0))
            temp = temp->next;
        else 
            break;
    }
    
    if(temp->next == NULL)
        temp->next = newEl;
    else if(strcmp(newEl->name, temp->next->name) == 0){
        free(newEl);
        return NULL;
    }
    else{
        newEl->next = temp->next;
        temp->next = newEl; 
    }
    
    return NULL;
}

Pos InsertCountry(Pos p, Pos newEl)
{
    if(p == NULL)
        return newEl;
    else if(strcmp(p->name, "0") == 0){
        strcpy(p->name, newEl->name);
        p->L = newEl->L;
        p->R = newEl->R;
        p->next = newEl->next;
        free(newEl);
    }
    else if(strcmp(p->name, newEl->name) > 0)
        p->L = InsertCountry(p->L, newEl);
    else if(strcmp(p->name, newEl->name) < 0)
        p->R = InsertCountry(p->R, newEl);
    else 
        free(newEl);
        
    return p;
}

int ReadCountry(char* fName, Pos p)
{
    Pos temp = NULL;
    FILE* f = NULL;
    char buffer[MAX] = {0};
    char name[128] = {0};
    char fN[128] = {0};

    f = fopen(fName, "r");
    if(f == NULL){
        printf("Failed to open the file.");
        return -1;
    }
    
    while(!feof(f))
    {
        fgets(buffer, MAX, f);
        if(sscanf(buffer, " %s %s", name, fN) == 2){
            temp = CreateCountry(name);
            ReadCity(fN, temp);
            InsertCountry(p, temp);
        }
    }
    
    fclose(f);
    return 0;
}

Pos ReadCity(char* fName, Pos p)
{
    FILE* f = NULL;
    char buffer[MAX] = {0};
    char name[128] = {0};
    int pop = 0;
    
    f = fopen(fName, "r");
    if(f == NULL){
        printf("Failed to open the file.");
        return NULL;
    }
    
    while(!feof(f))
    {
        fgets(buffer, MAX, f);
        if(sscanf(buffer, " %s %d", name, &pop) == 2){
            Point temp = CreateCity(name, pop);
            if(!p->next)
                p->next = temp;
            else if(p->next->pop > temp->pop){
                temp->next = p->next;
                p->next = temp;
            }
            else if(p->next->pop == temp->pop && strcmp(p->next->name, name) > 0){
                temp->next = p->next;
                p->next = temp;
            }
            else
                InsertCity(p->next, temp);
        }
    }
    
    fclose(f);
    
    return NULL;
}

int PrintAll(Pos p)
{
    if(!p || strcmp(p->name, "0") == 0)
        return 0;
    PrintAll(p->L);
    printf("%s:\n", p->name);
    PrintCities(p->next);
    PrintAll(p->R);
    
    return 0;
}

int PrintCities(Point p)
{
    if(!p)
        return 0;
        
    printf("\t%s - %d\n", p->name, p->pop);
    PrintCities(p->next);
    
    return 0;
}

Pos FindCountry(char* name, Pos p)
{
    Pos temp = p;
    if(strcmp(temp->name, "0") == 0)
        return NULL;
    else if(strcmp(temp->name, name) == 0)
        return temp;
    else if(strcmp(temp->name, name) < 0)
        temp = FindCountry(name, temp->R);
    else if(strcmp(temp->name, name)>0)
        temp = FindCountry(name, temp->L);
        
    return temp;
}

int PrintInCountryBiggerThan(Pos country, int n)
{
    if(!country){
        printf("There is no such country in the list.");
        return -1;
    }
    
    PrintCitiesBiggerThan(country->next, n);
    return 0;
}

int PrintCitiesBiggerThan(Point p, int n)
{
    if(!p)
        return 0;

    if(p->pop >= n)
        printf("\t%s - %d\n", p->name, p->pop);
    PrintCitiesBiggerThan(p->next, n);
    
    
    return 0;
}

int DeleteList(Point p)
{
    if(!p)
        return 0;
    DeleteList(p->next);
    free(p);
    return 0;
}

int DeleteAll(Pos p)
{
    if(!p)
        return 0;
    DeleteAll(p->L);
    DeleteList(p->next);
    DeleteAll(p->R);
    free(p);
    return 0;
}














