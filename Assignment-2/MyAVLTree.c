#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like
char* strtok_r(char *str,const char *delim,char **nextp)
{
 char *ret;
 if (str == NULL)str = *nextp;
 str += strspn(str, delim);
 if (*str == '\0')return NULL;
 ret = str;
 str += strcspn(str, delim);
 if (*str)*str++ = '\0';
 *nextp = str;
 return ret;
}
int max(int a, int b)
{
    return (a > b)? a : b;
}
// data type for avl tree nodes
typedef struct AVLTreeNode
{
	int key; //key of this item
	int  value;  //value (int) of this item
	int height; //height of the subtree rooted at this node
	struct AVLTreeNode *parent; //pointer to parent
	struct AVLTreeNode *left; //pointer to left child
	struct AVLTreeNode *right; //pointer to right child
} AVLTreeNode;
AVLTreeNode *FindMin(AVLTreeNode *node)
{
 if(node!=NULL)
 {
  while(node->left)
  {
   node = node->left;
  }
 }
 return node;
}
int height(AVLTreeNode *N)
{
 if (N == NULL)
  return 0;
 return N->height;
}
//data type for AVL trees
typedef struct AVLTree
{
	int  size;      // count of items in avl tree
	AVLTreeNode *root; // root
} AVLTree;
// create a new AVLTreeNode
AVLTreeNode *newAVLTreeNode(int k, int v )
{
	AVLTreeNode *new;
	new = malloc(sizeof(AVLTreeNode));
	assert(new != NULL);
	new->key = k;
	new->value = v;
	new->height = 0; // height of this new node is set to 0
	new->left = NULL; // this node has no child
	new->right = NULL;
	new->parent = NULL; // no parent
	return new;
}
// create a new empty avl tree
AVLTree *newAVLTree()
{
	AVLTree *T;
	T = malloc(sizeof (AVLTree));
	assert (T != NULL);
	T->size = 0;
	T->root = NULL;
	return T;
}
AVLTreeNode *single_rotate_with_left(AVLTreeNode *k)
{
	assert(k!=NULL);
	AVLTreeNode *k1;

	k1 = k->left;
	k1->parent = k->parent;
	k->left = k1->right;
	k1->right =k;
	k->parent = k1;
	k->height = max(height(k->left),height(k->right))+1;
	k1->height = max(height(k1->left),k->height)+1;

	return k1;
}
AVLTreeNode *single_rotate_with_right(AVLTreeNode *k)
{
	assert(k!=NULL);
	AVLTreeNode *k1;
	k1 = k->right;
	k1->parent = k->parent;
	k->right = k1->left;
	k1->left =k;
	k->parent = k1;
	k->height = max(height(k->left),height(k->right))+1;
	k1->height = max(height(k1->right),k->height)+1;

	return k1;
}
AVLTreeNode *double_rotate_with_left(AVLTreeNode *k)
{
 assert(k!=NULL);
 k->left = single_rotate_with_right(k->left);
 return single_rotate_with_left(k);
}
AVLTreeNode *double_rotate_with_right(AVLTreeNode *k)
{	assert(k!=NULL);
	k->right = single_rotate_with_left(k->left);
	return single_rotate_with_right(k);
}
void Balance(AVLTree *T,AVLTreeNode *neuw)
{
 AVLTreeNode *parent;
 parent = neuw->parent;

 while (parent!=NULL)
 {
  parent->height = max(height(parent->left),height(parent->right))+1;
  int Pparent = height(parent->left) - height(parent->right);
  if (Pparent == 0) break;
  else if (Pparent == 1 || Pparent == -1)
  {
   neuw = parent;
   parent = parent->parent;
  }
  else
  {
   int node = height(neuw->left) - height(neuw->right);
   if (Pparent== 2)
   {
    if (node == -1)
    {
     if (parent->parent == NULL) T->root = double_rotate_with_left(parent);
     else parent->parent->right = double_rotate_with_left(parent);
    }
    else
    {
     if (parent->parent == NULL) T->root = single_rotate_with_left(parent);
     else
     {
      if (parent->key > (parent->parent->key))
      (parent->parent->right)=single_rotate_with_left(parent);
       else (parent->parent->left)=single_rotate_with_left(parent);
     }
    }
   }

   else
   {
    if(node == -1)
    {
     if (parent->parent == NULL) T->root = single_rotate_with_right(parent);
     else parent->parent->right = single_rotate_with_right(parent);
    }
    else
    {
     if (parent->parent == NULL) T->root = double_rotate_with_right(parent);
     else
     {
      if (parent->key > (parent->parent->key))
      parent->parent->right = double_rotate_with_right(parent);
      else parent->parent->left = double_rotate_with_right(parent);
     }
    }
   }
    parent = parent->parent;
  }
 }
}

// put your time complexity analysis of CreateAVLTree() here
// Time Complexity - O(NLogN)
AVLTree *CreateAVLTree(const char *filename)
{
 AVLTree *T;
 T = newAVLTree();
 int a,b,c;
 char StringLine[1000];
 int k,v;
 char *str,*temp;
 char *delim = " ;\n";
 char* pSave = NULL;
 str = malloc(100);
 temp = malloc(100);
 if (strcmp(filename,"stdin")==0)
 {
  while(strlen(gets(StringLine))!=0)
  {
   str = strtok_r(StringLine,delim,&pSave);
   while(str!=NULL)
   {
    strcpy(temp,str);
    int len = strlen(temp);
    if (len<5)
    {
     printf("invalid input\n");
     exit(1);
    }
    temp= strtok(temp,"(");
    if (strlen(temp)==len)
    {
     printf("no (");
     exit(1);
    }
    int len1 = strlen(temp);
    temp = strtok(temp,",");
    if (strlen(temp)==len1)
    {
     printf("no ,");
     exit(1);
    }
    k = atoi(temp);
    if (k==0 && *temp!='0')
    {
     printf("not integer");
     exit(1);
    }
    temp = strtok(NULL,")");
    int len2 = strlen(temp);
    if(len-len1-2==len2)
    {
    printf("invalid input\n");
    return T;
    }
    v=atoi(temp);
    if (v==0 && *temp!='0')
    {
     printf("not integer");
     exit(1);
    }

    a = InsertNode(T,k,v);
    if (a == 0)
    {
     printf("error");
     return NULL;
    }
    str=strtok_r(NULL,delim,&pSave);
   }
  }
 }
 else
 {
  FILE *fp = fopen(filename,"r");
  if (fp==NULL)
  {
   printf("File could not be opened?");
   exit(1);
  }

  while(!feof(fp))
  {
   fscanf(fp,"(%d,%d)\n",&b,&c);
   a = InsertNode(T,b,c);
   if (a == 0)
   {
    printf("Value could not be inserted. \n");
    return NULL;
   }
  }
  fclose(fp);
 }
}

void UnionList(int arrayA[],int arrayB[],int arrayC[],int a, int b)
{
 	int i=0,j=0,k=0;
 	while(i<a && j<b)
    {
 		if(arrayA[i]<arrayB[j]) arrayC[k++]=arrayA[i++];
 		else arrayC[k++]=arrayB[j++];
 	}
 	while(i<a)
    {
 		arrayC[k++]=arrayA[i++];
 	}
 	while(j<b)
    {
 		arrayC[k++]=arrayB[j++];
 	}
 }

// put your time complexity for ALVTreesUnion() here
// Time Complexity - O(M+N)
AVLTree *AVLTreesUnion(AVLTree *T1, AVLTree *T2)
{
  	AVLTree *T3;
 	T3 = newAVLTree();
 	int m=T1->size,n=T2->size;

 	int arrayAkey[m],arrayAvalue[m];
 	int i =0;
 	TreeArray(T1->root,arrayAkey,arrayAvalue,&i);

 	int arrayBkey[n],arrayBvalue[n];
 	int j =0;
 	TreeArray(T2->root,arrayBkey,arrayBvalue,&j);

 	int arrayCkey[n+m],arrayCvalue[n+m];
 	UnionList(arrayAkey,arrayBkey,arrayCkey,m,n);
 	UnionList(arrayAvalue,arrayBvalue,arrayCvalue,m,n);

 	for(int i=0;i<m+n;i++)
 	{
 		j = InsertNode(T3,arrayCkey[i],arrayCvalue[i]);
 		if(j==0) printf("Error: node could be inserted");
 	}
 	return T3;
}

void IntersectionList(int arrayA[],int arrayB[],int arrayC[],int a, int b)
{
 	int i=0,j=0,k=0;
 	while(i<a && j<b)
    {
     if(arrayA[i]<arrayB[j])
       i++;
     else if (arrayB[j]<arrayA[i])
       j++;
     else
     {
       arrayC[k++]=arrayB[j++];
       i++;
     }
 	}
 }

// put your time complexity for ALVTreesIntersection() here
// Time Complexity - O(M+N)
AVLTree *AVLTreesIntersection(AVLTree *T1, AVLTree *T2)
{
  	AVLTree *T3;
 	T3 = newAVLTree();
 	int m=T1->size,n=T2->size;

 	int arrayAkey[m],arrayAvalue[m];
 	int i =0;
 	TreeArray(T1->root,arrayAkey,arrayAvalue,&i);

 	int arrayBkey[n],arrayBvalue[n];
 	int j =0;
 	TreeArray(T2->root,arrayBkey,arrayBvalue,&j);

 	int arrayCkey[n+m],arrayCvalue[n+m];
 	IntersectionList(arrayAkey,arrayBkey,arrayCkey,m,n);
 	IntersectionList(arrayAvalue,arrayBvalue,arrayCvalue,m,n);

 	for(int i=0;i<m+n;i++)
 	{
 		j = InsertNode(T3,arrayCkey[i],arrayCvalue[i]);
 		if(j==0) printf("Error: node could be inserted?");
 	}
 	return T3;
}

// put the time complexity analysis for InsertNode() here
// Time Complexity - O(logN)
int InsertNode(AVLTree *T, int k, int v)
{
  AVLTreeNode *node;
  AVLTreeNode *neuw;
  AVLTreeNode *parent;

  if (T->root == NULL)
  {
   node = newAVLTreeNode(k,v);
   T->root = node;
   T->root->height =1;
   T->size +=1;
   return 1;
  }
  node = T->root;

  while (node!=NULL)
  {
   parent = node;
   if (k < node->key)
   {
    node = node->left;
   }
   else if (k > node->key)
   {
    node = node->right;
   }
   else
   {
    return 0;
   }
  }

  neuw = newAVLTreeNode(k,v);
  T->size +=1;

  if (k > parent->key)
  {
   parent->right = neuw;
   neuw ->parent = parent;
  }
  else
  {
   parent->left = neuw;
   neuw->parent = parent;
  }

  Balance(T,neuw);

  return 1;
}

// put your time complexity analysis for Search() here
// Time Complexity - O(logN)
AVLTreeNode *Search(AVLTree *T, int k, int v)
{
 AVLTreeNode *node;
 node = T->root;
 while(node!=NULL)
 {
  if(k == node->key)
    return node;

  else if(k < node->key)
    node=node->left;

  else node=node->right;
 }
 return NULL;
}
// put your time complexity for DeleteNode() here
// Time Complexity - O(logN)
int DeleteNode(AVLTree *T, int k, int v)
{
 AVLTreeNode *node;
 AVLTreeNode *child;
 AVLTreeNode *parent;
 AVLTreeNode *x;

 if(T->root == NULL) return 0;

 node = Search(T,k,v);
 if (node==NULL) return 0;

 if (node==T->root)
 {
  T->root =NULL;
  return 1;
 }

 parent = node->parent;

 if (node->height == 0)
 {
  if(node->key > parent->key)
  {
    parent->right =NULL;
    child = parent->left;
  }
  else
  {
   parent->left = NULL;
   child = parent->right;
  }
  free(node);
  Balance(T,child);
 }

 else if (node->left==NULL || node->right==NULL)
 {
  if(node->left == NULL)  child = node->right;
  else child = node->left;

  if (parent==NULL)
  {
   T->root = child;
   child->parent = NULL;
   free(node);
  }
  else
  {
   if(node->key > parent->key) parent->right = child;
   else parent->left = child;
   child->parent = parent;
   free(node);
   Balance(T,child);
  }
 }
 else
 {
  x = node;
  node = FindMin(node);
  child = node->right;
  x->key = node->key;
  x->value = node->value;
  parent = node->parent;

  if (parent==x)
  {
   parent->right = child;
  }
  else
  {
   parent->left = child;
  }
  if (child != NULL)  child->parent = parent;
  free(node);
  if(child) Balance(T,child);
  else Balance(T,parent);
 }

 T->size -=1;
 return 1;
}

void TreeArray(AVLTreeNode *node,int key[],int value[],int *index)
{
 	if(node == NULL) return;
 	TreeArray(node->left,key,value,index);
 	key[*index]= node->key;
 	value[*index] = node->value;
 	(*index)++;
 	TreeArray(node->right,key,value,index);
}

// put your time complexity analysis for CloneAVLTree() here
// Time Complexity - O(n)
AVLTree *CloneAVLTree(AVLTree *T)
{
 AVLTree *T1;
 T1 = newAVLTree();
 if(T==NULL) return T1;
 int arrayA[T->size],arrayB[T->size];
 int i=0,x;
 TreeArray(T->root,arrayA,arrayB,&i);
 for (int i=0;i<T->size;i++)
 {
  x = InsertNode(T1,arrayA[i],arrayB[i]);
  if(x==0) printf("error could not be copied");
 }
 return T1;
}

void PrintOrder(AVLTreeNode *node)
{
	if (node!=NULL)
	{
     PrintOrder(node->left);
     printf("(%d,%d)\n",node->key,node->value);
     PrintOrder(node->right);
	}

}

void FreeAVLTreeNode(AVLTreeNode *node)
{
	if (node==NULL) return;
	FreeAVLTreeNode(node->left);
	FreeAVLTreeNode(node->right);
	free(node);
}

// put your time complexity analysis for freeAVLTree() here
// Time Complexity - O(N)
void FreeAVLTree(AVLTree *T)
{
  if (T==NULL) return;
  FreeAVLTreeNode(T->root);
  free(T);
}

// put your time complexity analysis for PrintAVLTree() here
// Time Complexity - O(N)
void PrintAVLTree(AVLTree *T)
{
 if (T==NULL) return;
 PrintOrder(T->root);
}

//sample main for testing
int main()
{
 int i,j;
 AVLTree *tree1, *tree2, *tree3, *tree4, *tree5, *tree6, *tree7, *tree8;
 AVLTreeNode *node1;

 tree1=CreateAVLTree("stdin");
 PrintAVLTree(tree1);
 FreeAVLTree(tree1);
 // you need to create the text file file1.txt
 // to store a set of items without duplicate items
 tree2=CreateAVLTree("file1.txt");
 PrintAVLTree(tree2);
 tree3=CloneAVLTree(tree2);
 PrintAVLTree(tree3);
 FreeAVLTree(tree2);
 FreeAVLTree(tree3);
 //Create tree4
 tree4=newAVLTree();
 j=InsertNode(tree4, 10, 10);
 for (i=0; i<15; i++)
  {
   j=InsertNode(tree4, i, i);
   if (j==0) printf("(%d, %d) already exists\n", i, i);
  }
  PrintAVLTree(tree4);
  node1=Search(tree4,20,20);
  if (node1!=NULL)
    printf("key= %d value= %d\n",node1->key,node1->value);
  else
    printf("Key 20 does not exist\n");

  for (i=17; i>0; i--)
  {
    j=DeleteNode(tree4, i, i);
	if (j==0)
	  printf("Key %d does not exist\n",i);
    PrintAVLTree(tree4);
  }
 FreeAVLTree(tree4);
 //Create tree5
 tree5=newAVLTree();
 j=InsertNode(tree5, 6, 25);
 j=InsertNode(tree5, 6, 10);
 j=InsertNode(tree5, 6, 12);
 j=InsertNode(tree5, 6, 20);
 j=InsertNode(tree5, 9, 25);
 j=InsertNode(tree5, 10, 25);
 PrintAVLTree(tree5);
 //Create tree6
 tree6=newAVLTree();
 j=InsertNode(tree6, 6, 25);
 j=InsertNode(tree6, 5, 10);
 j=InsertNode(tree6, 6, 12);
 j=InsertNode(tree6, 6, 20);
 j=InsertNode(tree6, 8, 35);
 j=InsertNode(tree6, 10, 25);
 PrintAVLTree(tree6);
 tree7=AVLTreesIntersection(tree5, tree6);
 tree8=AVLTreesUnion(tree5,tree6);
 PrintAVLTree(tree7);
 PrintAVLTree(tree8);
 return 0;
}
