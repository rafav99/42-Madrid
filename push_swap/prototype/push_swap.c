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

int minimum(anode *head)
{
  int num;
  anode *current;

  current = head;
  num = current->number;
  while(current != NULL)
  {
    if(current->number < num)
      num = current->number;
    current = current->next;
      
  }
  return(num);
}
int maximum(anode *head)
{
  int num;
  anode *current;

  current = head;
  num = current->number;
  while(current != NULL)
  {
    if(current->number > num)
      num = current->number;
    current = current->next;
      
  }
  return(num);
}
int position(anode *head, int mynumber)
{
    int pos;

    anode *current;
    current = head;
    pos = 0;
    while(current != NULL)
    {
        pos++;
        if(current->number == mynumber)
            return(pos);
        current = current->next;
    }
    return(-1);
}

int revposition(anode *head, int position)
{
  int numb;
  int i;

  anode *current;
  current = head;
  i = 1;
  if(head == NULL)
    return(-1);
  while(i < position)
  {
    if(current->next != NULL)
      current = current->next;
    i++;
  }
    return(current->number);
}
int checkspot(anode *auxlist, int mynumber)
{
    int pos;

    anode *current;
    current = auxlist;
    pos = 0;
    if(auxlist == NULL)
      return(-1);
    if(auxlist->number < mynumber && revposition(auxlist, numberelements(auxlist)) > mynumber)
      return(0);
    if(mynumber > maximum(auxlist))
      return(position(auxlist,maximum(auxlist)) - 1);
    while(current->next != NULL)
    {
      pos++;
      if(current->number > mynumber && current->next->number < mynumber) 
        return(pos);
        current = current->next;
    }
    return(-1);
}

int checkfor(anode *head, int bottom, int top)
{
  int i;
  anode *current;
  current = head;
  while(current != NULL)
  {
    if(current->number >= bottom && current->number < top)
      return(current->number);
    current = current->next;
  }
  return(-1);
}

int checkforev(anode *head, int bottom, int top)
{
  int i;

  i =numberelements(head);
  while(i > i/2)
  {
    if(revposition(head, i) >= bottom && revposition(head, i) < top)
      return(i);
    i--;
  }
  return(-1);
}
int ft_atoi(char *cnumb)
{
    int i;
    int number;

    i = 0;
    number = 0;
    while(cnumb[i] != '\0')
    {
        number = number + cnumb[i] - 48;
        i++;
    }
    return(number);
}
int main(int argc, char *argv[])
{
    int i;
    int n;
    int l;
    int top;
    int s;
    int r;
    int p;
    int chunks;
    anode *head;
    anode *current;
    anode *auxlist;

    head = malloc(sizeof(anode));
   // auxlist = malloc(sizeof(anode));
    head->next = NULL;
    auxlist = NULL;
    current = head;
    i = 1;
    while(argv[i] != NULL)
    {
        current->number = ft_atoi(argv[i]);
        if(argv[i+1] != NULL)
        {
            current->next = malloc(sizeof(anode));
            current = current->next;
        }
        else
            current->next=NULL;
        i++;        
    }
    l = numberelements(head);
    chunks = minimum(head);
    top = 0;
    printlist(head);
    while(numberelements(head)> 0)
    {
        while(position(head, checkfor(head, chunks, l/5 + chunks)) != -1)
        {
         
          n = position(head, checkfor(head, chunks, l/5 + chunks));
          s = checkspot(auxlist, revposition(head,n));
          printf("Chunks es %i, l/5 es %i, n es %i, s es %i, revpos es %i\n", chunks, l/5, n, s, revposition(head, n));
          i = 0;
          p = checkforev(head, chunks, l/5 + chunks);
          if (p < n)
          {
            while(i < p - 1)
            {
              revrotate(head);
              printf("rra\n");
              i++;
            }
          }
          else
            while(i < n - 1)
            {
              rotate(head);
              printf("ra\n");
              i++;
            }
          i = 0;
          while(i < s && numberelements(auxlist) > 1)
          {
            rotate(auxlist);
            printf("rb\n");
            i++;
          }
          push(&head, &auxlist);
          printf("pa\n");
          printf("lista a \n");
          printlist(head);
          printf("lista b \n");
          printlist(auxlist);
        }
        chunks = chunks + l/5;
         top++;
    }
  
    n = position(auxlist, maximum(auxlist));
    if(n < numberelements(auxlist)/2)
    {
      while(i < n)
      {
        rotate(auxlist);
        printf("rb\n");
        i++;
      }
    }
    else
    {
      i = 0;
      while(i <= numberelements(auxlist) - n)
      {
        revrotate(auxlist);
        i++;
      }
    }
    printf("lista b\n");
    printlist(auxlist);
    i = 0;
    while(i <l)
    {
      push(&auxlist, &head);
      i++;
    }
    printf("lista a \n");
    printlist(head);
   
}