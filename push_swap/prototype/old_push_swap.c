#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct anode
{
  int number;
  struct anode *next;
}              anode;
void swap(anode *head)
{
  int i;

  i = head->number;
  if(head->next != NULL)
  {
    head->number = head->next->number;
    head->next->number = i;
  }
}
void rotate(anode *head)
{
  int i;
  anode *current;

  current = head;
  i = head->number;
  while(current->next != NULL)
  {
    current->number = current->next->number;
    current = current->next;
  }
  current->number = i;
}
void revrotate(anode *head)
{
  anode *current;
  int i;
  int aux;
  current = head;
  while(current->next != NULL)
    current = current->next;
  i = current->number;
  current = head;
  while(current != NULL)
  {
    aux=current->number;
    current->number = i;
    i=aux;
    current=current->next;
  }
}
void printlist(anode *head)
{
  anode *current;
  current = head;
  while(current != NULL)
  {
    printf("%i\n", current->number);
    current = current->next;
  }
}
void push(anode **heada, anode **headb)
{
  anode *nextitem;
  anode *first;
  int val;
  val = (*heada)->number;
  nextitem = (*heada)->next;
  free(*heada);
  *heada = nextitem;
  if(*headb == NULL)
  {
    *headb = malloc(sizeof(anode));
    (*headb)->number = val;
    (*headb)->next = NULL;
  }
  else
  {
    first = malloc(sizeof(anode));
    first->number = val;
    first->next = *headb;
    *headb = first;
  }
}
int ordelements(anode *head)
{
  anode *current;
  int count;
  current = head;
  count = 0;
  if(head == NULL)
    return(-1);
  while (current->next != NULL)
  {
    if(current->number > (current->next)->number)
      break;
    current = current->next;
    count++;
  }
  return(count);
}

int revordelements(anode *head)
{
  anode *current;
  int count;
  current = head;
  count = 0;
  if(head == NULL)
    return(-1);
  while (current->next != NULL)
  {
    if(current->number < (current->next)->number)
      break;
    current = current->next;
    count++;
  }
  return(count);
}
int numberelements(anode *head)
{
  anode *current;
  int i;
  i = 0;
  current = head;

  if(head == NULL)
    return(0);
  while(current != NULL)
  {
    current = current->next;
    i++;
  }
  return(i);
}

int checkrepeat(anode *head, int n)
{
    anode *currentdos;
    currentdos = head;
   while(currentdos != NULL)
    { 
      if (n == currentdos->number)
      return(0);
        currentdos = currentdos->next;
    }
    return(1);
}
int countorder(anode *head, int min, int max)
{
  int i;
  anode *current;

  current = head;
  i = 0;
  while(head->next != NULL && head->number < head->next->number)
  {
    if(head->next->number < min || head->next->number > max)
      break;
    i++;
  }
  return(i);
}
int checkfor(anode *head, int mid)
{
  int i;
  anode *current;

  current = head;
  while(current != NULL)
  {
    if(current->number < mid)
      return(1);
    current = current->next;
  }
  return(0);
}
int ordlist(anode **list, int minimum)
{
  int i, n, x, a;

    while(revordelements((*list)) != numberelements(*list) - 1)
  {
    i = 0;
    n = revordelements(*list);
    a = numberelements(*list);
    if(n <= a/2)
    {
      i = 0;
      while(i < n)
      {
          if ((*list)->next->number > (*list)->number)
            break;
          rotate(*list);
          i++;
      }
    }
    else
    {
      i = 0;
      while(i < a - n - 1)
      {
        revrotate(*list);
        i++;
        x++;  
      }
    }
      if((*list)->number != minimum && (*list)->next->number > (*list)->number)
      {
        swap(*list);
        x++;
      }
      else if((*list)->number == minimum)
      {
        rotate(*list);
         x++;
      }
    
  }
      return(0);
}
int main(int arc,char *argv[])
{
  srand(time(NULL));
  anode *head;
  anode *auxlist;
  anode *current;

  int i, n, x, a, minimum, maximum, minmid, maxmid, mid, count, pos, moves, media, b, top;
 
 
  media = 0;
  moves = 0;
  i = 0;
   b = 0;
   top = 0;
  head = malloc(sizeof(anode));
  auxlist = (malloc(sizeof(anode)));
  head->number=-1;
  head->next = NULL;
  auxlist->next = NULL;
  auxlist->number = -1;
  current = head;

  while(1)
  {
     
    n = rand()%100;
    while(checkrepeat(head, n) != 1)
    {
      n = rand()%100;
    }
    current->number = n;
    if(i ==98)
      break;
    current->next=malloc(sizeof(anode));
    current = current->next;
    i++;
  }
  current->next = NULL;
  auxlist = NULL;
  printlist(head);
  a = 0;
  current = head;
  minimum = current->number;
  maximum = current->number;
  while(current != NULL)
  {
    if(minimum > current->number)
      minimum = current->number;
    if(maximum < current->number)
      maximum = current->number;
    current=current->next;
  }
  mid = (minimum+maximum)/2;
  minmid = (minimum + mid)/2;
  maxmid = (maximum + mid)/2;
  /*printf("el minimo es %i \n", minimum);
  printf("el maximo es %i \n", maximum);
  printf("el mid es %i \n", mid);*/
  current = head;
 
  x = 0;
  while(ordelements(head) != numberelements(head) - 1)
  {
    i = 0;
    n = ordelements(head);
    a = numberelements(head);
    if(n <= a/2)
    {
      while(i < n)
      {
        while(head->number < mid)
        {
          push(&head, &auxlist);
          x++;
          printf("lista a\n");
          printlist(head);
          printf("lista b\n");
          printlist(auxlist);
          printf("push h-a, ordelements: %i , numberelements: %i, moves: %i\n", ordelements(head), numberelements(head), x);
        }
          if (head->next->number < head->number)
            break;
          rotate(head);
           x++;  
          printf("lista a\n");
          printlist(head);
          printf("lista b\n");
          printlist(auxlist);   
          printf("rotate, ordelements: %i , numberelements: %i, moves: %i\n", ordelements(head), numberelements(head), x);
          i++;
      }
    }
    else
    {
      i = 0;
      while(i < a - n - 1)
      {
        revrotate(head);
        i++;
           x++;  
          printf("lista a\n");
          printlist(head);
          printf("lista b\n");
          printlist(auxlist);   
          printf("revrotate, ordelements: %i , numberelements: %i, moves: %i\n", ordelements(head), numberelements(head), x);
      }
    }
      if(head->number != maximum && head->next->number < head->number)
      {
        swap(head);
        printf("lista a\n");
        printlist(head);
        printf("lista b\n");
        printlist(auxlist);
        x++;
        printf("Swap head, ordelements: %i , numberelements: %i, moves: %i\n", ordelements(head), numberelements(head), x);
        if(numberelements(auxlist) > 1)
        {
          if(auxlist->number < auxlist->next->number)
            swap(auxlist);
        }
      }
      else if(head->number == maximum)
      {
        rotate(head);
        x++;
      }
     /*if(numberelements(auxlist)> 1)
      ordlist(&auxlist, minimum);*/
    
     if(revordelements(auxlist) == numberelements(auxlist) - 1 && ordelements(head) == numberelements(head) - 1  && numberelements(auxlist) > 0)
     {  
        if(head->number < mid)
        {
          n = head->number;
          rotate(head);
          while(auxlist != NULL && auxlist->number > n )
            push(&auxlist,&head);
          revrotate(head);
        }

          n = numberelements(auxlist);
          i = 0;
          while(i < n)
          {
            push(&auxlist, &head);
            i++;
            x++;
          }

      }
 
     
      printf("lista a\n");
      printlist(head);
      printf("lista b\n");
      printlist(auxlist);
       printf("ordelements: %i , numberelements: %i, moves: %i\n", ordelements(head), numberelements(head), x);
    //}
    
  }
}
