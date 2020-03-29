// Author: Kazi Swad Abdullah
// Student ID: z5201993
// Platform: Windows

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like

// data structures representing DLList

// data type for nodes

typedef struct DLListNode
{
	int  value;  // value (int) of this list item
	struct DLListNode *prev;
	// pointer previous node in list
	struct DLListNode *next;
	// pointer to next node in list
} DLListNode;

//data type for doubly linked lists
typedef struct DLList
{
	int  size;      // count of items in list
	DLListNode *first;  // first node in list
	DLListNode *last;  // last node in list
} DLList;

// create a new DLListNode
DLListNode *newDLListNode(int it)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);
	new->value = it;
	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLList
DLList *newDLList()
{
	struct DLList *L;
	L = malloc(sizeof (struct DLList));
	assert (L != NULL);
	L->size = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}

// create a DLList from a text file
// put your time complexity analysis for CreateDLListFromFileDlist() here
// O(n).

DLList *CreateDLListFromFileDlist(const char *filename)
{
  DLList *L ;
  L = newDLList();  //generate a new ddlist
  DLListNode *new;  //generate a new node
  DLListNode *next;  //next node
  DLListNode *prev;  //prev node
  next = L->last;   // set next node to the last on on the list
  prev = L->first;  // set prev node to the first on on the list
  int n= 0;
  int num = 0;
  char lineA[10];
  char lineB[10];
  FILE *fr;

  if (filename == "stdin")
  {
     while (fgets(lineA, sizeof(lineA), stdin) != NULL && strcmp(lineA,"end\n") != 0)
    {
      num = atoi(lineA);
      if(L->size ==0)
      {                       //generate first node
       next = newDLListNode(num);
       next->prev = NULL;
       L->first = next;
       L->size++;
      }
      else
      {
       while (next->next!=NULL)
       {
        next = next->next;
       }
       next->next = newDLListNode(num);
       prev = next;
       next = next->next;
       next->prev = prev;
       L->last = next;
       next->next = NULL;
      }
    }
    return L;
  }

  else
  {  //file open
   fr = fopen(filename, "r");

   if(fr == NULL)
   {
    printf("File does not exist...");
    L->first = newDLListNode(0);;
   }

   while (fscanf(fr,"%s", lineB)!=EOF && fr != NULL)
   {
    n = atoi(lineB);
	new = newDLListNode(n);
	if (L->last == NULL)
	{
     new->prev = NULL;
     L->first = L->last = new;
    }
	else
	{
     L->last->next = new;
     new->prev = L->last;
     L->last = new;
     new ->next=NULL;
	}
	L->size++;
   }
    fclose(fr); // close file
  }
  return L;
}

// clone a DLList
// put your time complexity analysis for cloneList() here
// // Time Complexity O(n)

DLList *cloneList(struct DLList *u)
{
    DLList *L;
    L=newDLList();

    if (u == NULL) // if there are no items in list
    {
     L = u;
    }

    DLListNode *nodeinLtemp,*nodeinL, *nodeinu;
    nodeinu = u->first;

    if (nodeinu != NULL) //define first node
    {
        nodeinL = newDLListNode(nodeinu->value);
        L->first = nodeinL;
        nodeinL->prev = NULL;
        nodeinu = nodeinu->next;
    }
    while (nodeinu!=NULL) //define the rest of the nodes
    {
        nodeinL->next = newDLListNode(nodeinu->value);
        nodeinLtemp = nodeinu;
        nodeinL = nodeinL->next;
        nodeinL->prev = nodeinLtemp;
        L->last = nodeinL;
        nodeinu = nodeinu->next;
    }
    return L;
}

// compute the union of two DLLists u and v
// put your time complexity analysis for intersection() here
// Time Complexity O(u*v)

DLList *setUnion(struct DLList *u, struct DLList *v)
{
    DLList *L;
    L = cloneList(u);
    DLListNode* nodeinu;
    nodeinu = L->first;
    DLListNode* nodeinv;
    nodeinv = v->first;
    DLListNode* temp;
    int x = 0;

    while(nodeinv != NULL)
    {
      while (nodeinu->next != NULL)
      {
       if (nodeinv->value == nodeinu->value)
       {
         x = 1;
       }
       nodeinu = nodeinu->next;
      }
      if (x == 0)
      {
        temp = nodeinu;
        nodeinu->next = newDLListNode(nodeinv->value);
        nodeinu = nodeinu->next;
        nodeinu->prev = temp;
      }
      x = 0;
      nodeinv = nodeinv->next;
      nodeinu = L->first;
    }
    return L;
}


// compute the insection of two DLLists u and v
// put your time complexity analysis for intersection() here
// Time Complexity O(u*v)

DLList *setIntersection(struct DLList *u, struct DLList *v)
{
    DLList *L;
    L= newDLList();
    DLListNode* nodeinL;
    nodeinL = L->first;
    DLListNode* nodeinu;
    nodeinu = u->first;
    DLListNode* nodeinv;
    nodeinv = v->first;
    DLListNode* temp;
    int c = 0;

    while(nodeinv ->next != NULL)
    {
     while (nodeinu->next != NULL)
     {
      if (nodeinv->value == nodeinu->value)
      {
       if (c == 0) //first node
       {
        nodeinL = newDLListNode(nodeinv->value);
        L->first = nodeinL;
        nodeinL->prev = NULL;
        nodeinL->next = NULL;
        c++;
       }
       else  //rest of the nodes
       {
        nodeinL->next = newDLListNode(nodeinv->value);
        temp = nodeinL;
        nodeinL = nodeinL->next;
        nodeinL->prev = temp;
       }
      }
      nodeinu = nodeinu->next;
     }
      nodeinu = u->first;
      nodeinv = nodeinv->next;
    }
    nodeinL->next = NULL;
    return L;
}

// free up all space associated with list
// put your time complexity analysis for freeDLList() here
// Time Complexity O(n)

void freeDLList(struct DLList *L)
{
    assert(L != NULL);
    DLListNode *current, *temporary;
    current = L->first;
    while (current != NULL)
    {
	  temporary = current;
	  current = current->next;
	  free(temporary);
    }
    free(L); //free list
}

// display items of a DLList
// put your time complexity analysis for printDDList() here
// Time Complexity O(n)

void printDLList(struct DLList *u)
{
  DLListNode* current;   //generate node current
  current = u->first;

  while (current ->next != NULL)  //while current exist
  {
    printf("The Value of the Node is: %d \n", current->value);  //print current node
    current = current -> next;
  }
  printf("The Value of the Node is: %d \n", current->value);  //print last node
}

//Main Function

int main()
{
 DLList *list1, *list2, *list3, *list4;

 list1=CreateDLListFromFileDlist("File1.txt");
 printDLList(list1);

 list2=CreateDLListFromFileDlist("File2.txt");
 printDLList(list2);

 list3=setUnion(list1, list2);
 printDLList(list3);

 list4=setIntersection(list1, list2);
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 printf("please type all the integers of list1\n");
 list1=CreateDLListFromFileDlist("stdin");

 printf("please type all the integers of list2\n");
 list2=CreateDLListFromFileDlist("stdin");

 list3=cloneList(list1);
 printDLList(list3);
 list4=cloneList(list2);
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 return 0;
}

