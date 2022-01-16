#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

struct _BinTree;
typedef struct _BinTree* Point;
typedef struct _BinTree{
    int X;
    Point L;
    Point R;
}BinTree;

struct _Stog;
typedef struct _Stog* pt;
typedef struct _Stog{
    int n;
    pt next;
}Stog;

int Menu(Point pRoot);
Point CreateEl(int n);
Point Insert(Point p, Point newEl);
int Replace(Point p);
Point CreateTree(Point pRoot);
int DeleteAll(Point p);
int InorderToStog(Point p, pt a);
int PrintInorder(Point p);
int PrintInFile(char* fName, pt frs);
pt CreateElStog(int n);
int DeleteStog(pt head);
int InsertAfter(pt p, pt newEl);
pt FindLast(pt head);
int AddAtEnd(int n, pt head);

int main()
{
    Point pRoot = NULL;
    pRoot = CreateTree(pRoot);
    Menu(pRoot);
    
    return 0;
}

int Menu(Point pRoot)
{
    int option = 0;
    
    while(1)
    {
        printf("\nEnter number coresponding to action you want to perform:\n"
                "1 -> Add a new element to the tree\n"
                "2 -> Print inorder\n"
                "3 -> Replace all elements with the sum of their branches\n"
                "4 -> Print inorder in file\n"
                "5 -> Generate new tree\n"
                "6 -> Exit\n");
                
        scanf(" %d", &option);
        
        switch(option)
        {
            case 1:
            {
                int n;
                printf("\nEnter the value you would like to add to the tree:\n");
                scanf(" %d", &n);
                pRoot = Insert(pRoot, CreateEl(n));
                option = 0;
                
                break;
            }
            
            case 2:
            {
                printf("\n");
                PrintInorder(pRoot);
                printf("\n");
                option = 0;
                
                break;
            }
            
            case 3:
            {
                printf("\n");
                Replace(pRoot);
                printf("\n");
                option = 0;
                 
                break;
            }
            
            case 4:
            {
                Stog head = {.n = 0, .next = NULL};
                pt h = &head;
                char s[20] = "0";
                
                printf("Enter the name of the .txt file you wish to write in:\n");
                scanf(" %s", s);
                strcat(s, ".txt");
                InorderToStog(pRoot, h);
                PrintInFile(s, h->next);
                printf("\n");
                
                option = 0;
                break;
            }
            
            case 5:
            {
                printf("\n");
                DeleteAll(pRoot);
                pRoot = NULL;
                pRoot = CreateTree(pRoot);
                printf("\n");
                
                option = 0;
                break;
            }
            
            case 6:
            {
                DeleteAll(pRoot);
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
}

Point CreateTree(Point pRoot)
{
    int i = 0;
    Point temp = NULL;
    
    srand(time(0));
    
    for(i = 0; i < 10; i++)
    {
        temp = CreateEl(rand() % 79 + 11);
        if(!temp)
            return NULL;
        pRoot = Insert(pRoot, temp);
    }
    
    return pRoot;
}

Point CreateEl(int n)
{
    Point newEl = NULL;
    newEl = (Point)malloc(sizeof(BinTree));
    
    if(!newEl){
        printf("Memory allocation failed.");
        return NULL;
    }
    
    newEl->X = n;
    newEl->L = NULL;
    newEl->R = NULL;
    return newEl;
}

Point Insert(Point p, Point newEl)
{
    if(p == NULL)
        return newEl;
    else if(p->X < newEl->X)
        p->L = Insert(p->L, newEl);
    else if(p->X > newEl->X)
        p->R = Insert(p->R, newEl);
        
    return p;
}

int PrintInorder(Point p)
{
    if(!p)
        return 0;
    
    PrintInorder(p->L);
    printf("%d", p->X);
    PrintInorder(p->R);
    return 0;
}

int Replace(Point p)
{
    int temp = 0;
    
    if(p == NULL)
        return 0;
    else{
        temp = p->X;
        p->X = Replace(p->R) + Replace(p->L);
        return p->X + temp;
    }
}

int DeleteAll(Point p)
{
    if(!p)
        return 0;
    if(!p->L && !p->R)
        free(p);
    else{
        if(p->L)
            DeleteAll(p->L);
        if(p->R)
            DeleteAll(p->R);
            
        free(p);
    }
    
    return 0;
}

pt CreateElStog(int n)
{
    pt newEl = NULL;
    newEl = (pt)malloc(sizeof(Stog));
    
    if(!newEl){
        printf("Memory allocation failed.");
        return NULL;
    }
    
    newEl->n = n;
    newEl->next = NULL;
    return newEl;
}

int InsertAfter(pt p, pt newEl)
{
    newEl->next = p->next;
    p->next = newEl;
    return 0;
}

pt FindLast(pt head)
{
    pt last = head;
    while(last -> next){
        last = last -> next;
    }
    return last;
}

int AddAtEnd(int n, pt head)
{
    pt newEl = NULL;
    newEl = CreateElStog(n);
    
    if(!newEl)
        return -1;
        
    InsertAfter(FindLast(head), newEl);
    return 0;
}

int InorderToStog(Point p, pt a)
{
    if(!p)
        return 0;
    InorderToStog(p->L, a);
    AddAtEnd(p->X, a);
    InorderToStog(p->R, a);
    
    return 0;
}

int PrintInFile(char* fName, pt frs)
{
    pt temp = frs;
    FILE* f = NULL;
    
    f = fopen(fName, "w");
    if(f == NULL){
        printf("File failed to open.\n");
        return -1;
    }
    
    for(temp; temp; temp = temp->next)
        fprintf(f, "%d ", temp->n);
        
    fclose(f);
    return 0;
}

int DeleteStog(pt head)
{
    pt temp = NULL;
    
    while(head->next != NULL){
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }
    
    return 0;
}
