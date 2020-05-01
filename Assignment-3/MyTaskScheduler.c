#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct HeapNode
{
	int key;
	int TaskName;
	int Etime;
	int Rtime;
	int Dline;
    struct HeapNode *parent;
	struct HeapNode *left;
	struct HeapNode *right;
} HeapNode;

typedef struct BinomialHeap
{
	int  size;
    HeapNode *LastNode;
	HeapNode *root;
} BinomialHeap;

HeapNode *newHeapNode(int k, int n, int c, int r, int d, HeapNode *L, HeapNode *R, HeapNode *P)
{
	HeapNode *neuw;
	neuw = malloc(sizeof(HeapNode));
	assert(neuw != NULL);
	neuw->key = k;
	neuw->TaskName = n;
	neuw->Etime = c;
	neuw->Rtime = r;
	neuw->Dline = d;
    neuw->left = L;
	neuw->right = R;
	neuw->parent = P;
	return neuw;
}

BinomialHeap *newHeap()
{
	BinomialHeap *T;
	T = malloc(sizeof(BinomialHeap));
	assert (T != NULL);
    T->size = 0;
	T->LastNode=NULL;
	T->root = NULL;
	return T;
}

 HeapNode *InsertLastNode(HeapNode *node)
{
	HeapNode *p,*neuw;
	p = node->parent;
	if(p!= NULL)
    {
     while(p!=NULL && p->left!=node)
     {
      node = node->parent;
      p = p->parent;
     }
     if(p==NULL) neuw=node;
     else neuw = p->right;
     if (neuw==NULL)  return p;
     while (neuw->left!=NULL)  neuw = neuw->left;
     return neuw;
	}
	neuw = node;
	return neuw;
 }

 HeapNode *RemoveLastNode(HeapNode *node)
 {
 	HeapNode *p,*neuw;
 	p = node->parent;
 	if(p!= NULL)
    {
     while(p!=NULL && p->right!=node)
     {
      p = p->parent;
      node = node->parent;
     }
     if(p== NULL) neuw=node;
     else neuw = p->left;
     while (neuw->right!=NULL) neuw = neuw->right;
     return neuw;
	}
	neuw = node;
	return neuw;
 }

// put the time complexity analysis for Insert() here
// Time Complexity: O(logN)

void Insert(BinomialHeap *T, int k, int n, int c, int r, int d)
{
  HeapNode *p,*neuw,*g,*lefts,*rights,*last;
  if (T->size ==0)
  {
    neuw = newHeapNode(k,n,c,r,d,NULL,NULL,NULL);
    T->root = neuw;
    T->LastNode = T->root;
    T->size =1;
    return;
  }
  last = InsertLastNode(T->LastNode);
  neuw = newHeapNode(k,n,c,r,d,NULL,NULL,last);
  if (last->left == NULL)last->left =neuw;
  else last->right = neuw;
  T->size +=1;

  if (neuw->key >= last->key)
  {
    T->LastNode = neuw;
    return;
  }
   p = last;

  while (p!=NULL && neuw->key < p->key )
  {
   if(p->parent==NULL)
   {
    neuw->parent = NULL;
    T->root = neuw;
   }
   else
   {
    g = p->parent;
    if(g->right == p)  g->right = neuw;
    else g->left =neuw;
    neuw->parent = g;
   }

   rights= neuw->right;
   lefts= neuw->left;
   if(p->right == neuw)
   {
    neuw->right =p;
    if (p->left !=NULL)
    {
     neuw->left = p->left;
     p->left->parent = neuw;
    }
   }
   else
   {
    neuw->left = p;
    if (p->right !=NULL)
    {
     neuw->right = p->right;
     p->right->parent = neuw;
    }
   }

  p->left = lefts;
  p->right = rights;
  if (rights!=NULL) rights->parent = p;
  if (lefts!=NULL) lefts->parent = p;
  p->parent = neuw;
  p = neuw->parent;
 }
 T->LastNode = last;
}

void Print(HeapNode *node)
{
 if (node!=NULL)
 {
  printf(" %d%d ",node->TaskName,node->key);
  Print(node->left);
  Print(node->right);
 }
}

// put your time complexity for RemoveMin() here
// Time Complexity: O(logN)

HeapNode *RemoveMin(BinomialHeap *T)
{
 HeapNode *node,*lefts,*rights,*last,*temp,*record;
 node=NULL;

 if (T->size ==1)
 {
  node = T->LastNode;
  T->root=NULL;
  T->LastNode =NULL;
  T->size = 0;
  return node;
 }
 last = T->LastNode;
 node = T->root;
 record = newHeapNode(node->key, node->TaskName, node->Etime, node->Rtime,node->Dline,NULL,NULL,NULL);
 node->key = last->key;
 node->Dline = last->Dline;
 node->Etime = last->Etime;
 node->Rtime = last->Rtime;
 node->TaskName = last->TaskName;
 T->LastNode = RemoveLastNode(last);
 if (last->parent->left == last) last->parent->left =NULL;
 else last->parent->right =NULL;
 last->parent = NULL ;
 T->size -= 1;

 while((node->left!=NULL && node->key > node->left->key) || (node->right!=NULL && node->key > node->right->key ))
 {
  if (node->right==NULL || (node->right!=NULL && node->left->key <= node->right->key))
  {
    temp = node->left;
    lefts =temp->left;
    rights = temp->right;
    temp->right = node->right;

    if (node->right !=NULL)node->right->parent = temp;
    temp->left = node;
   }
   else
   {
    temp = node->right;
    lefts = temp->left;
    rights = temp->right;
    temp->left = node->left;
    if(node->left !=NULL) node->left->parent = temp;
    temp->right = node;
   }
   if (node->parent!=NULL)
   {
    if (node->parent->left==node) node->parent->left = temp;
    else node->parent->right =temp;
   }
   temp->parent = node->parent;
   node->parent = temp;
   node->left = lefts;
   node->right = rights;
   if(lefts!=NULL) lefts->parent = node;
   if(rights!=NULL) rights ->parent = node;
   if (node==T->root)
   {
    T->root = node->parent;
    T->root->parent =NULL;
   }
   if (temp==T->LastNode)
   {
    T->LastNode = node;
   }
  }
 return record;
}

int LateStart(BinomialHeap *T)
{
 if (T->size !=0)
 return T->root->Dline-T->root->Etime;
 else return -1;
}

//returns the smallest key in heap.
//Time Complexity: O(1)

int Min(BinomialHeap *T)
{
 if (T->size !=0)
 return T->root->key;
 else return -1;
}

// put your time complexity analysis for MyTaskScheduler here
// Time Complexity: O(nlogn)

int TaskScheduler(char *f1, char *f2, int m )
{
 int a,b,c,d;
 HeapNode *releasenode, *readynode;
 FILE *fp  = fopen(f1,"r");
 if(fp==NULL)
 {
  printf("File does not exist");
  exit(1);
 }
 BinomialHeap *F;
 F = newHeap();

 while(!feof(fp))
 {
  fscanf(fp,"%d %d %d %d\n",&a,&b,&c,&d);
  Insert(F,c,a,b,c,d);
 }
 fclose(fp);

 FILE *fp2 = fopen(f2,"w");
 int target=0,k=0,j;
 int core[m];

 for (j=0;j<m;j++)
 {
  core[j]=0;
 }

  BinomialHeap *R;
  R = newHeap();

  while(F->size!=0 || R->size!=0 )
  {
   while(F->size!=0 && Min(F)<=k)
   {
    releasenode = RemoveMin(F);
    Insert(R,releasenode->Dline,releasenode->TaskName,releasenode->Etime,releasenode->Rtime,releasenode->Dline);
   }
    for(int j=0;j<m;j++)
    {
     int latestart = LateStart(R);
     if (latestart==-1) break;
     if(R->size!=0 && core[j]<=latestart)
     {
      readynode = RemoveMin(R);
      if( core[j]<readynode->Rtime) core[j]=readynode->Rtime;
      fprintf(fp2,"%d core%d %d\n ",readynode->TaskName,j,core[j]);
      core[j]+=readynode->Etime;
     }
     if (j==0) target =core[j];
     if (core[j]>target) target=core[j];
     }
     if(target>k) k=target;
     else k++;
     if(F->size==0 && k>releasenode->Dline) return 0;
	}
	return 1;
}

int main() //sample main for testing
{ int i;
  i=TaskScheduler("samplefile1.txt", "feasibleschedule1.txt", 4);
  if (i==0) printf("No feasible schedule!\n");
  /* There is a feasible schedule on 4 cores */
  i=TaskScheduler("samplefile1.txt", "feasibleschedule2.txt", 3);
  if (i==0) printf("No feasible schedule!\n");
  /* There is no feasible schedule on 3 cores */
  i=TaskScheduler("samplefile2.txt", "feasibleschedule3.txt", 5);
  if (i==0) printf("No feasible schedule!\n");
  /* There is a feasible schedule on 5 cores */
  i=TaskScheduler("samplefile2.txt", "feasibleschedule4.txt", 4);
  if (i==0) printf("No feasible schedule!\n");
  /* There is no feasible schedule on 4 cores */
  i=TaskScheduler("samplefile3.txt", "feasibleschedule5.txt", 2);
  if (i==0) printf("No feasible schedule!\n");
  /* There is no feasible schedule on 2 cores */
  i=TaskScheduler("samplefile4.txt", "feasibleschedule6.txt", 2);
  if (i==0) printf("No feasible schedule!\n");
  /* There is a feasible schedule on 2 cores */
 return 0;
}
