#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define St struct  state
#define islist struct stateList
#define tr struct  transition
#define loop for(int i=0;i<1000000;i++);

struct state
{
  char final;
  int value;
  struct transition *transList;
};
 
struct stateList
{
  int value;
  struct state *statePtr;
  struct stateList *next;
};
 
struct transition
{
  char symbol;
  struct state *statePtr;
  struct transition *next;
};
 
int dfa(char * input, struct state *s);
void freemem(struct stateList * sList);
int main()
{
  islist *sList = NULL, *sListPtr=NULL, *tmpListPtr = NULL;
  St *sPtr, *tmpStatePtr;
  tr *tPtr,*tmpTransPtr;
  int stateNo;
  char final='N';
  char symbol=' ';
  loop
  char input[80];
  do
  {
    printf("Enter the number corresponding to the state(Press 0 to exit)");
    scanf("%d",&stateNo);
    getchar();
    if(stateNo != 0)
    {
      printf("Final State ? Give answer as (Y?N) ");
      scanf("%c",&final);
      if(sList == NULL)
      {
        sList = (islist*) malloc(sizeof(islist));
        sList -> value = stateNo;
        sList -> statePtr = (St *) malloc (sizeof(St));
        sList -> statePtr -> value = stateNo;
        sList -> statePtr -> final = final;
        sList -> statePtr -> transList = NULL;
        sList -> next= NULL;
        loop
      }
      else
      {
        sListPtr = sList;
        while(sListPtr -> next != NULL)
        {
          sListPtr = sListPtr->next;
        }
        sListPtr->next = (islist*) malloc(sizeof(islist));
        sListPtr = sListPtr->next;
        sListPtr -> value = stateNo;
        sListPtr -> statePtr = (St *) malloc (sizeof(St));
        sListPtr -> statePtr -> value = stateNo;
        sListPtr -> statePtr -> final = final;
        loop
        sListPtr -> statePtr -> transList = NULL;
        sListPtr -> next= NULL;
      }
    }
  }while(stateNo != 0);
   
  sListPtr = sList;
  while(sListPtr != NULL)
  {
    printf("\n\ngive transitions from state %d \n",sListPtr->value);
    printf("To the State (press 0 to Quit) : ");
    scanf("%d",&stateNo);
    while(stateNo != 0)
    {
      tmpListPtr = sList;
      while(tmpListPtr != NULL)
      {
        if(tmpListPtr-> value == stateNo)
        {
          break;
        }
        tmpListPtr = tmpListPtr ->next;
      }
 
 
      if(tmpListPtr == NULL)
      {
        printf("The given state is invalid\n");
      }
      else
      {
        getchar();
        printf("Enter the symbol for which it occurred");
        scanf("%c",&symbol);
        sPtr = sListPtr -> statePtr;
     
        if(sPtr->transList == NULL)
        {
          sPtr->transList = (tr *) malloc (sizeof (tr));
          tPtr = sPtr->transList;
        }
        else
        {
          tPtr = sPtr->transList;
          while(tPtr->next != NULL)
          {
          tPtr = tPtr->next;
          }
          tPtr -> next = (tr *) malloc (sizeof (tr));
          tPtr = tPtr ->next;  
        }
        tPtr -> symbol = symbol;
        tPtr -> statePtr = tmpListPtr->statePtr;
        tPtr -> next = NULL;
        loop
      }
      printf("\nTo the State (press 0 to Quit) : ");
      scanf("%d",&stateNo);
    }
    sListPtr = sListPtr -> next;
  }
  loop
  if(sList != NULL)
  {
    printf("\nEnter the String to be checked : ");
    scanf("%s",input);
    while(strcmp(input,"q") != 0)
    {
      if( dfa(input,sList->statePtr ))
      {
      printf("The given String is Accepted.");
      }
      else
      {
      printf("The given String is Not accepted!!! . ");
      }
      printf("\nEnter the String to be checked (press q to Quit): ");
      scanf("%s",input);
    }
  }  
   
  freemem(sList);
}
 
int dfa(char * input, struct state *s)
{
  tr * t;
  int accept =0;

  if(s == NULL)
  {
    return 0;
  }
  else
  {
    t = s -> transList;
    if(input[0] == '\0' && s -> final == 'Y')
    {
    return 1;
    }
     
    while( t != NULL && accept ==0)
    {
   
      if(t -> symbol == input[0])
      {
     
        accept= dfa(input+1,t->statePtr);
      }
      t = t -> next;
    }
  }loop
  return accept;
}
 
void freemem(struct stateList * sList)
{
  islist *tsList;
  St * tstate;
  tr *trans, *trans2;
  while(sList != NULL)
  {
    tsList = sList->next;
     
    tstate = sList -> statePtr;
    trans = tstate -> transList;
    while(trans != NULL)
    {
      trans2 = trans->next;
      free(trans);
      trans = trans2;
    }
    free(tstate);
    free(sList);
    sList = tsList;
  }
}
