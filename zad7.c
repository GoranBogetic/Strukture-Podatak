#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 128

struct _Directory;
typedef struct _Directory* Point;
typedef struct _Directory{
    char* name[MAX];
    Point sibling;
    Point child;
}Directory;

Point Insert(Point current, Point newDirectory);
Point CreateDirectory(char name[MAX]);
int Print(Point p, int i);
int FindParent(Point* current, Point parent, Point p, char name[MAX]);
int FindByName(Point* current, Point p, char name[MAX]);
int Delete(Point p);

int main()
{
    Directory root = {.name = "..", .sibling = NULL, .child = NULL};

    return 0;
}

Point Insert(Point current, Point newDirectory)
{
    if(current == NULL)
        return newDirectory;
    else if(strcmp(current->name, newDirectory->name) > 0){
        newDirectory->sibling = current;
        return newDirectory;
    }
    else if(strcmp(current->name, newDirectory->name) < 0){
        current->sibling = Insert(current->sibling, newDirectory);
        free(newDirectory);
        return current;
    }
    else{
        printf("File or directory with such name already exists.\n");
        free(newDirectory);
        return current;
    }
}

Point CreateDirectory(char name[MAX])
{
    Point newDirectory = NULL;
    newDirectory = (Point)malloc(sizeof(Directory));
    
    if(!newDirectory){
        printf("Memory allocation failed.");
        return NULL;
    }
    
    strcpy(newDirectory->name, name);
    newDirectory->sibling = NULL;
    newDirectory->child = NULL;
    return newDirectory;
}

int Print(Point p, int i)
{
    int j;
    printf("\n");
    
    for(j = 0; j < i; j++)
        printf("  ");
    printf(" %s", p->name);
    if(p->child)
        Print(p->child, i+1);
    if(p->sibling)
        Print(p->sibling, i);

    return 0;
}

int FindParent(Point* current, Point parent, Point p, char name[MAX])
{
    if(strcmp(p->name, name) == 0)
        *current = parent;
    if(p->child)
        FindParent(current, p, p->child, name);
    if(p->sibling)
        FindParent(current, parent, p->sibling, name);
        
    return 0;
}

int FindByName(Point* current, Point p, char name[MAX])
{
    if(strcmp(p->name, name) == 0)
        *current = p;
    if(p->child)
        FindByName(current, p->child, name);
    if(p->sibling)
        FindByName(current, p->sibling, name);
        
    return 0;
}

int Delete(Point p)
{
    if(!p)
        return 0;
    else if(!p->sibling && !p->child){
        free(p);
        return 0;
    }
    else{
        if(p->child){
            Delete(p->child);
            p->child = NULL;
        }
        if(p->sibling){
            Delete(p->sibling);
            p->sibling = NULL;
        }
        free(p);
    }
    
    return 0;
}




