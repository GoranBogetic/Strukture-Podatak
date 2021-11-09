#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct _polinom;
typedef struct _polinom* point;
typedef struct _polinom{
    int koef;
    int expo;
    point next;
}polinom;

int ReadFile(point head1, point head2);
point FindPrevExpo(int expo, point head);
point CreateEl(int koef, int expo);
int DeleteAfter(point p);
int DeleteAll(point p);
int InsertAfter(point p, point newEl);
int SortInsert(point newEl, point head);
int PoliPrint(point f);
int ElPrint(point temp);
int PoliSuma(point f1, point f2, point suma);
int PoliProdukt(point f1, point f2, point product);


int main()
{
    polinom head1 = {.koef = 0, .expo = 0, .next = NULL};
    point p1 = &head1;
    polinom head2 = {.koef = 0, .expo = 0, .next = NULL};
    point p2 = &head2;
    polinom suma = {.koef = 0, .expo = 0, .next = NULL};
    point psuma = &suma;
    polinom product = {.koef = 0, .expo = 0, .next = NULL};
    point pprodukt = &product;
    
    ReadFile(p1, p2);
    
    PoliPrint(p1->next);
    PoliPrint(p2->next);
    
    PoliSuma(p1->next, p2->next, psuma);
    PoliPrint(psuma->next);
    
    PoliProdukt(p1->next, p2->next, pprodukt);
    PoliPrint(pprodukt->next);
    
    DeleteAll(p1);
    DeleteAll(p2);
    DeleteAll(psuma);
    DeleteAll(pprodukt);
    return 0;
}

point FindPrevExpo(int ex, point head)
{
    point p = head;
    
    while(p->next != NULL && p->next->expo < ex){
        p = p->next;
    }
    
    return p;
}

point CreateEl(int koef, int expo)
{
    point newEl = NULL;
    newEl = (point)malloc(sizeof(polinom));
    if(!newEl){
        printf("Greska pri alokaciji memorije.\n");
        return NULL;
    }    
    newEl->koef = koef;
    newEl->expo = expo;
    newEl->next = NULL;
    return newEl;
}

int DeleteAfter(point p)
{
    point Del = NULL;
    
    Del = p->next;
    p->next = Del->next;
    free(Del);
    return 0;
}

int DeleteAll(point head)
{
    point Del = NULL;
    
    while(head->next != NULL){
		Del = head->next;
		head->next = Del->next;
		free(Del);
	}
    return 0;
}

int InsertAfter(point p, point newEl)
{
    newEl->next = p->next;
    p->next = newEl;
    return 0;
}

int SortInsert(point newEl, point head)
{
    point temp = NULL;
    temp = FindPrevExpo(newEl->expo, head);
    
    if(temp->next == NULL || newEl->expo < temp->next->expo){
        if(newEl->expo == 0)
            return 0;
        InsertAfter(temp, newEl);
    }
    else{
        if(temp->next->koef + newEl->koef == 0)
            DeleteAfter(temp);
        else
            temp->next->koef += newEl->koef;
        free(newEl);
    }
    return 0;
}

int ElPrint(point temp)
{
    if(temp->koef == 1);
    else if(temp->koef == 1 && temp->expo == 0)
        printf(" 1");
    else if(temp->koef < 0)
        printf(" %d", temp->koef * (-1));
    else
        printf(" %d", temp->koef);
        
    if(temp->expo == 0);
    else if(temp->expo > 0)
        printf(" x^%d", temp->expo);
    else
        printf(" x^(%d)", temp->expo);
        
    return 0;
    
}

int PoliPrint(point f)
{
    point temp = f;
    
    if(temp->koef < 0)
        printf(" -");
    
    for(temp; temp; temp = temp->next)
    {
        ElPrint(temp);
        if(temp->next->koef < 0)
            printf(" -");
        else if(temp->next->koef >= 0)
            printf(" +");
        else
            printf("\n");
    }
    return 0;
}

int ReadFile(point head1, point head2)
{
    point p = NULL;
    FILE* f = NULL;
    char buffer[1024] = {0};
    char t[30] = {0};
    int br = 0;
    int koef = 0;
    int expo = 0;
    int n = 0;
    point newEl = NULL;
    
    while(1){
        printf("Unesite ime datoteke (ukljucujuci i nastavak .txt) iz koje zelite citati podatke:\n");
        scanf(" %s", t);
        f = fopen(t, "r");
        
        if(!f)
            printf("Otvaranje datoteke nije uspjelo! Pokusajte ponovno.\n");
        else
            break;
    }
    
    fgets(buffer, 1024, f);
    
    while(buffer[br] != '\0'){
        if(sscanf(&buffer[br], " %d %d %n", &koef, &expo, &n) == 2){
            p = FindPrevExpo(head1, expo);
            newEl = CreateEl(koef, expo);
            SortInsert(p, newEl);
        }
        
        else{
            printf("Doslo je do pogreske.");
            return -1;
        }
        
        br += n;
    }
    
    br = 0;
    
    while(buffer[br] != '\0'){
        if(sscanf(&buffer[br], " %d %d %n", &koef, &expo, &n) == 2){
            p = FindPrevExpo(head2, expo);
            newEl = CreateEl(koef, expo);
            SortInsert(p, newEl);
        }
        
        else{
            printf("Doslo je do pogreske.");
            return -1;
        }
        
        br += n;
    }
    
    fclose(f);
    return 0;
}

int PoliSuma(point f1, point f2, point suma)
{
    point pSuma = suma;
    point p1 = f1;
    point p2 = f2;
    point newEl = NULL;
    
    while(p1 != NULL && p2 != NULL){
        if(p1->expo == p2->expo){
            newEl = CreateEl(p1->koef + p2->koef, p1->expo);
            SortInsert(pSuma, newEl);
            p1 = p1->next;
            p2 = p2->next;
        }
        else if(p1->expo < p2->expo){
            newEl = CreateEl(p1->koef, p1->expo);
            SortInsert(pSuma, newEl);
            p1 = p1->next;
        }
        else{
            newEl = CreateEl(p2->koef, p2->expo);
            SortInsert(pSuma, newEl);
            p2 = p2->next;
        }
    }
        if(p2 == NULL);
        else p1 = p2;
        
    while(p1 != NULL){
        newEl = CreateEl(p1->koef, p1->expo);
        SortInsert(pSuma, newEl);
        p1 = p1->next;
    }
    return 0;
}

int PoliProdukt(point f1, point f2, point product)
{
    point pProdukt = product;
    point p1 = f1;
    point p2 = f2;
    point newEl = NULL;
    
    while(p1){
        while(p2){
            newEl = CreateEl(p1->koef * p2->koef, p1->expo + p2->expo);
            SortInsert(pProdukt, newEl);
            p2 = p2->next;
        }
        p2 = f2;
        p1 = p1->next;
    }
    return 0;
}














