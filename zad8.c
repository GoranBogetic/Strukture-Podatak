#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX 128

struct _BinTree;
typedef struct _BinTree* Point;
typedef struct _BinTree
{
    int X;
    Point L;
    Point R;
}BinTree;

Point Insert(Point p, Point newEl);
Point CreateEl(int n);
int PrintInorder(Point p);
int PrintPreorder(Point p);
int PrintPostorder(Point p);
int PrintLevelorder(Point p);
int PrintLevel(Point p, int lv, int current);
int MaxLvl(Point p, int lv);
int Find(Point p, int n);
Point Delete(Point p, int n);
int DeleteAll(Point p);
int Menu(Point pRoot);

int main()
{
    Point pRoot = NULL;
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
                "3 -> Print preorder\n"
                "4 -> Print postorder\n"
                "5 -> Print level order\n"
                "6 -> Find element\n"
                "7 -> Delete element\n"
                "8 -> Exit\n");
                
        scanf("%d", &option);
        
        switch(option)
        {
            case 1:
            {
                int n = 0;
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
                PrintPreorder(pRoot);
                printf("\n");
                option = 0;
                
                break;
            }
            
            case 4:
            {
                printf("\n");
                PrintPostorder(pRoot);
                printf("\n");
                option = 0;
                
                break;
            }
            
            case 5:
            {
                printf("\n");
                PrintLevelorder(pRoot);
                printf("\n");
                option = 0;
                
                break;
            }
            
            case 6:
            {
                int n = 0;
                printf("\nEnter the value you would like to check for:\n");
                scanf(" %d", &n);
                if(Find(pRoot, n))
                    printf("The value %d exists in the tree.\n", n);
                else
                    printf("The value %d doesn't exist in the tree.\n", n);
                    
                option = 0;
                break;
            }
            
            case 7:
            {
                int n = 0;
                printf("\nEnter the value you would like to delete:\n");
                scanf(" %d", &n);
                if(!Find(pRoot, n));
                else
                    Delete(pRoot, n);
                    
                option = 0;
                break;
            }
            
            case 8:
            {
                DeleteAll(pRoot);
                break;
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

int Find(Point p, int n)
{
    if(!p)
        return 0;
    if(p->X == n)
        return n;
    else if(p->X < n)
        return Find(p->R, n);
    else if(p->X > n)
        return Find(p->L, n);
    else
        return 0;
}

Point Delete(Point p, int n)
{
    Point temp = NULL;
    if(!p)
        return NULL;
    if(p->X == n){
        if(p->L){
            temp = p->L;
            while(temp->R){
                temp = temp->R;
            }
            temp->L = p->L;
            temp->R = p->R;
        }
        else if(p->R){
            temp->R;
            while(temp->L){
                temp = temp->L;
            }
            temp->L = p->L;
            temp->R = p->R;
        }
        p->L = NULL;
        p->R = NULL;
        free(p);
        return temp;
    }
    else if(p->X < n)
        p->R = Delete(p->R, n);
    else
        p->L = Delete(p->L, n);
        
    return p;
}

int DeleteAll(Point p)
{
    if(!p)
        return 0;
    if(!p->L && p->R)
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
        p->R = Insert(p->R, newEl);
    else if(p->X > newEl->X)
        p->L = Insert(p->L, newEl);
    else{
        free(newEl);
        return p;
    }
    
    return p;
}

int PrintInorder(Point p)
{
    if(!p || p->X == INT_MAX)
        return 0;
    PrintInorder(p->L);
    printf("%d", p->X);
    PrintInorder(p->R);
    return 0;
}

int PrintPreorder(Point p)
{
    if(!p || p->X == INT_MAX)
        return 0;
    printf("%d", p->X);
    PrintPreorder(p->L);
    PrintPreorder(p->R);
    return 0;
}

int PrintPostorder(Point p)
{
    if(!p || p->X == INT_MAX)
        return 0;
    PrintPostorder(p->L);
    PrintPostorder(p->R);
    printf("%d", p->X);
    return 0;
}

int MaxLvl(Point p, int lv)
{
    int k = 0;
    lv++;
    if(p->L)
        lv = MaxLvl(p->L, lv);
    if(p->R){
        lv = MaxLvl(p->R, lv);
        if(k > 1)
            lv = k;
    }
    return 1;
}

int PrintLevel(Point p, int lv, int current)
{
    if(!p || p->X == INT_MAX)
        return 0;
    if(lv == current)
        printf("%d", p->X);
    PrintLevel(p->L, lv, current+1);
    PrintLevel(p->R, lv, current+1);
    return 0;
}

int PrintLevelorder(Point p)
{
    int lv = MaxLvl(p, -1);
    int i;
    for(i = 0; i <= 1; i++)
    {
        printf("\n");
        PrintLevel(p, i, 0);
    }
    
    return 0;
}
