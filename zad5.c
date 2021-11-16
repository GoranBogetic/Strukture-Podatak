#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _stackEl;
typedef struct _stackEl* Point;
typedef struct _stackEl{
    double num;
    Point next;
}stackEl;

Point CreateEl(double num);
int InsertAfter(Point p, Point newEl);
int DeleteAfter(Point p);
int DeleteAll(Point head);
int Push(double num, Point head);
int Pop(double* resultDestination, Point head);
int PerformOp(char op, Point head);
int CalculatePostfixFromFile(double* resultDestination);
int ReadPostfixFromFile(char** buffer);


int main()
{
    
    return 0;
}

Point CreateEl(double num)
{
    Point newEl = NULL;
    newEl = (Point)malloc(sizeof(stackEl));
    
    if(!newEl){
        perror("Memory allocation failed.");
        return NULL;
    }
    
    newEl->num = num;
    newEl->next = NULL;
    return newEl;
}

int InsertAfter(Point p, Point newEl)
{
    newEl->next = p->next;
    p->next = newEl;
    return 0;
}

int DeleteAfter(Point p)
{
    Point Del = NULL;
    
    Del = p->next;
    p->next = Del->next;
    free(Del);
    return 0;
}

int DeleteAll(Point head)
{
    Point Del = NULL;
    
    while(head->next != NULL){
		Del = head->next;
		head->next = Del->next;
		free(Del);
	}
    return 0;
}

int Push(double num, Point head)
{
    Point newEl = NULL;
    
    newEl = CreateEl(num);
    if(!newEl){
        return -1;
    }
    
    InsertAfter(head, newEl);
    return 0;
}

int Pop(double* resultDestination, Point head)
{
    Point first = head->next;
    
    if(!first){
        perror("Invalid postfix, check your file");
        return -1;
    }
    
    *resultDestination = first->num;
    DeleteAfter(head);
    return 0;
}

int PerformOp(char op, Point head)
{
    double op1 = 0;
    double op2 = 0;
    double res = 0;
    
    if(Pop(&op2, head) != 0)
        return -1;
    
    if(Pop(&op1, head) != 0)
        return -2;
        
    switch(op)
    {
        case '+':
            res = op1 + op2;
            break;
        case '-':
            res = op1 - op2;
            break;
        case '*':
            res = op1 * op2;
            break;
        case '/':
            if(op2 == 0){
                printf("Can't divide with zero!");
                return -3;
            }
            res = op1 / op2;
        default:
            printf("Operation %c not supported. But for only $69.00 we can implementi it for you.\n", op);
            return -4;
    }
    
    return Push(res, head);
}

int CalculatePostfixFromFile(double* resultDestination)
{
    char* buffer = NULL;
    char* currentBuffer = NULL;
    int nBytes = 0;
    int status = 0;
    double num = 0;
    char op = 0;
    stackEl head = {.next = NULL, .num = 0};
    
    status = ReadPostfixFromFile(&buffer);
    if(!status)
        return -2;
        
    currentBuffer = buffer;
    while(strlen(currentBuffer) > 0){
        status = sscanf(currentBuffer, " %lf %n", &num, &nBytes);
        if(status == 1){
            status = Push(num, &head);
            if(status){
                free(buffer);
                DeleteAll(&head);
                return -3;
            }
            currentBuffer += nBytes;
        }
        
        else{
            sscanf(currentBuffer, " %c %n", &op, &nBytes);
            status = PerformOp(op, &head);
            if(status){
                free(buffer);
                DeleteAll(&head);
                return -4;
            }
            currentBuffer += nBytes;
        }
    }
    
    free(buffer);
    
    status = Pop(resultDestination, &head);
    if(status){
        DeleteAll(&head);
        return -5;
    }
    
    if(head.next){
        DeleteAll(&head);
        printf("Invalid postfix, check your file");
        return -6;
    }
    
    return 0;
}

int ReadPostfixFromFile(char** buffer)
{
    FILE* f = NULL;
    int fLength = 0;
    char temp[50] = {0};
    
    while(1){
        printf("Enter file name (including .txt) from which you want to read from:\n");
        scanf("%s", temp);
        f = fopen(temp, "r");
        if(!f)
            printf("Couldn't open file. Try again.\n");
        else 
            break;
    }
    
    while(fgetc(f) != EOF)
        fLength++;
        
    *buffer = (char*)calloc(fLength + 1, sizeof(char));
    
    if(!(*buffer)){
        perror("Memory allocation failed");
        return -2;
    }
    
    rewind(f);
    fread(*buffer, sizeof(char), fLength, f);
    fclose(f);
    return 0;
}
