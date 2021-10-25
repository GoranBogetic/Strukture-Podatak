#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
}Person;

Position CreateNewPerson (char* name, char* surname, int birthYear)
{
  Position newPerson = NULL;
  
  newPerson = (Position) malloc (sizeof (Person));
  if(!newPerson)
  {
      perror("Couldn't allocate memmory.\n");
      return NULL;
  }
  
  strcpy(newPerson->name,name);
  strcpy(newPerson->surname,surname);
  newPerson->birthYear = birthYear;
  newPerson->next=NULL;
  
  return newPerson;
}

int InsertAfter (Position p, Position newPerson)
{
  newPerson->next = p->next;
  p->next = newPerson;

  return 0;
}

Position FindLast (Position head)
{
  Position last = head;

  while (last->next)
    {
      last = last->next;
    }

  return last;
}

int AddAtStart (Position head, char* name, char* surname, int birthYear)
{
  Position newPerson = NULL;

  newPerson = CreateNewPerson (name, surname, birthYear);
  if (!newPerson)
    return -1;

  InsertAfter (head, newPerson);

  return 0;
}

int AddAtEnd (Position head, char* name, char* surname, int birthYear)
{
  Position newPerson = NULL;
  Position last=NULL;

  newPerson = CreateNewPerson (name, surname, birthYear);
  if (!newPerson)
    return -1;
  
  last=FindLast(head);
  InsertAfter (last, newPerson);

  return 0;
}

int PrintList (Position first)
{
  Position temp = first;
  
  if(!temp)
    printf("The list is empty. :(\n\n");
  for (temp; temp; temp = temp->next)
    printf ("Name: %s\tSurname: %s\tBirthyear: %d\n",
	    temp->name, temp->surname, temp->birthYear);

  return 0;
}

Position FindBySurname (char* surname, Position first)
{
    Position temp = first;
    
    for(temp; temp; temp = temp->next)
        if(strcmp(temp->surname, surname) == 0)
            return temp;
    
    if(!temp)
        printf("There is no %s!\n\n", surname);
    return temp;
}

int DeletePerson(char* surname, Position head)
{
    Position temp = head;
    Position toDeletePerson=NULL;
    
    for(temp;temp->next;temp=temp->next)
        if(strcmp(temp->next->surname,surname) == 0)
            break;
    toDeletePerson = temp->next;
    temp->next = toDeletePerson->next;
    free(toDeletePerson);
    
    return 0;
}

int main ()
{
  Person head = {.name = {0},.surname = {0},.birthYear = 0,.next = NULL };
  Position p = &head;
  
  AddAtStart(&head, "Jure", "Juric", 1991);
  AddAtEnd(&head, "Pero", "Peric", 1985);
  AddAtStart(&head, "Ana", "Anic", 2000);
  
  PrintList(p->next);
  printf("\n");
  
  DeletePerson("Juric", &head);
  DeletePerson("Peric", &head);
  DeletePerson("Anic", &head);
  
  PrintList(p->next);
  
  FindBySurname("Matic", head.next);
  
  AddAtEnd(&head, "Pero", "Peric", 1985);
  AddAtStart(&head, "Jure", "Juric", 1991);
  AddAtEnd(&head, "Ana", "Anic", 2000);
  
  PrintList(p->next);
  
  return 0;
}

