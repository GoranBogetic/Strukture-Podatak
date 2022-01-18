#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (1024)

struct _tree;
typedef struct _tree* Pos;
typedef struct _tree{
    Pos L;
    Pos R;
    char name[128];
    int pop;
}tree;

struct _list;
typedef struct _list* Point;
typedef struct _list{
    Point next;
    char name[128];
    Pos root;
}list;

int Menu(Point heads);
Pos CreateCity(char* name, int pop);
Point CreateCountry(char* name);
Pos InsertCity(Pos p, Pos newEL);
int InsertCountry(Point head, Point newEl);
Point ReadCountry(char* fName, Point heads);
Pos ReadCity(char* fName, Point p);
int PrintCities(Pos p);
int PrintAll(Point first);
int DeleteList(Point first);
int DeleteTree(Pos p);
int DeleteAll(Point first);
Point FindCountry(char* name, Point first);
int PrintInCountryBiggerThan(Point country, int n);
int PrintCitiesBiggerThan(Pos p, int n);
int GetHashPos(char* country);

int main()
{
    Point heads = (Point)malloc(11 * sizeof(list));
    int i = 0;
    for(i = 0; i < 11; i++)
    {
        heads[i].next = NULL;
        strcpy(heads[i].name, "0");
        heads[i].root = NULL;
    }
    
    return Menu(heads);
}

int Menu(Point heads)
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
                heads = ReadCountry(s, heads);
                if(!heads)
                    return -1;
                    
                option = 0;
                break;
            }
            
            case 2:
            {
                int i = 0;
                for(i = 0; i < 11; i++)
                    PrintAll(&heads[i]);
                    
                option = 0;
                break;
            }
            
            case 3:
            {
                char s[30] = "0";
                int n = 0;
                int i = 0;
                int t = 0;
                printf("Enter the name of the country and the minimum population:\n");
                scanf(" %s %d", s, &n);
                for(i = 0; i < 11; i++)
                    t += PrintInCountryBiggerThan(FindCountry(s, &heads[i]), n);
                if(t == -11)
                    printf("There is no such country.");
                    
                option = 0;
                break;
            }
            
            case 4:
            {
                int i = 0;
                for(i = 0; i < 11; i++)
                {
                    DeleteAll(heads[i].next);
                    heads[i].next = NULL;
                }
                
                option = 0;
                break;
            }
            
            case 5:
            {
                int i = 0;
                for(i = 0; i < 11; i++)
                {
                    DeleteAll(heads[i].next);
                    heads[i].next = NULL;
                }
                
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

Pos CreateCity(char* name, int pop)
{
    Pos newCity = NULL;
    newCity = (Pos)malloc(sizeof(tree));
    
    if(!newCity){
        printf("Memory allocation failed.");
        return NULL;
    }
    
    strcpy(newCity->name, name);
    newCity->pop = pop;
    newCity->R = NULL;
    newCity->L = NULL;
    return newCity;
}

Point CreateCountry(char* name)
{
    Point newCountry = NULL;
    newCountry = (Point)malloc(sizeof(list));
    
    if(!newCountry){
        printf("Memory allocation failed.");
        return NULL;
    }
    
    strcpy(newCountry->name, name);
    newCountry->next = NULL;
    newCountry->root = NULL;
    return newCountry;
}

Pos InsertCity(Pos p, Pos newEl)
{
    if(p == NULL)
        return newEl;
    else if(p->pop > newEl->pop)
        p->L = InsertCity(p->L, newEl);
    else if(p->pop < newEl->pop)
        p->R = InsertCity(p->R, newEl);
    else if(strcmp(p->name, newEl->name) > 0)
        p->L = InsertCity(p->L, newEl);
    else if(strcmp(p->name, newEl->name) < 0)
        p->R = InsertCity(p->R, newEl);
    else 
        free(newEl);
        
    return p;
}

int InsertCountry(Point head, Point newEl)
{
    Point temp = NULL;
    temp = head;
    
    while(1){
        if(temp->next != NULL && strcmp(temp->next->name, newEl->name) < 0)
            temp = temp->next;
        else
            break;
    }
    
    if(temp->next == NULL)
        temp->next = newEl;
    else if(strcmp(newEl->name, temp->next->name) == 0){
        free(newEl);
        return -1;
    }
    else{
        newEl->next = temp->next;
        temp->next = newEl;
    }
    
    return 0;
}

list* ReadCountry(char* fName, Point heads)
{
    Point temp1 = NULL;
    Point temp2 = NULL;
    FILE* f = NULL;
    char buffer[MAX] = {0};
    char name[128] = {0};
    char fN[128] = {0};
    list pFile[11];
    int i = 0;
    
    f = fopen(fName, "r");
    if(f == NULL){
        printf("Failed to open the file.");
        return NULL;
    }
    
    while(!feof(f))
    {
        fgets(buffer, MAX, f);
        if(sscanf(buffer, " %s %s", name, fN) == 2){
            i = GetHashPos(name);
            InsertCountry(&heads[i], CreateCountry(name));
            ReadCity(fN, heads[i].next);
        }
    }
    
    fclose(f);
    
    return heads;
}

Pos ReadCity(char* fName, Point p)
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
            Pos newCity = NULL;
            
            newCity = CreateCity(name, pop);
            p->root = InsertCity(p->root, newCity);
        }
    }
    
    fclose(f);
    
    return p->root;
}

int PrintCities(Pos p)
{
    if(!p)
        return 0;
        
    PrintCities(p->L);
    printf("\t%s - %d\n", p->name, p->pop);
    PrintCities(p->R);
    
    return 0;
}

int PrintAll(Point first)
{
    Point temp = first;
    while(temp)
    {
        if(strcmp(temp->name, "0") != 0){
            printf("%s:\n", temp->name);
            PrintCities(temp->root);
        }
        
        temp = temp->next;
    }
    
    return 0;
}

int DeleteList(Point first)
{
    if(!first)
        return 0;
    DeleteList(first->next);
    free(first);
    return 0;
}

int DeleteAll(Point first)
{
    if(!first)
        return 0;
    DeleteAll(first->next);
    DeleteTree(first->root);
    free(first);
    return 0;
}

int DeleteTree(Pos p)
{
    if(!p)
        return 0;
    if(!p->L && !p->R)
        free(p);
    else{
        if(p->L)
            DeleteTree(p->L);
        if(p->R)
            DeleteTree(p->R);
        free(p);
    }
    
    return 0;
}

Point FindCountry(char* name, Point first)
{
    Point temp = first;
    while(temp != NULL && strcmp(temp->name, name) != 0)
    {
        temp = temp->next;
    }
    
    return temp;
}

int PrintInCountryBiggerThan(Point country, int n)
{
    if(!country){
        return -1;
    }
    
    PrintCitiesBiggerThan(country->root, n);
    return 0;
}

int PrintCitiesBiggerThan(Pos p, int n)
{
    if(!p)
        return 0;
    PrintCitiesBiggerThan(p->R, n);
    if(p->pop >= n){
        printf("\t%s - %d\n", p->name, p->pop);
        PrintCitiesBiggerThan(p->L, n);
    }
    
    return 0;
}

int GetHashPos(char* country)
{
    int i = 0;
    int key = 0;
    
    for(i = 0; i < strlen(country) && i < 5; i++)
        key += (int)country[i];
        
    key = key % 11;
    return key;
}







