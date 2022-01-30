#include<iostream>
#include<malloc.h>
using namespace std;

typedef struct btree
{
  int m;
  int* key;
  struct btree** child;
  int n;
  struct btree* parent;
  int leaf;
}btree;


btree* insert(btree*,int,btree*);
btree* split(btree*,int,btree*,btree*,int);
void initialise(btree*);
void inorder(btree*,int);
int search(btree*,int);


int main()
{
  btree* head=NULL; 
  int n;
  cin>>n;
  int key;
  for(int i=0;i<n;i++)
  {
    cout<<"enter\n";
    cin>>key;
    head=insert(head,key,NULL);
    cout<<endl;
   inorder(head,0);
  }
  
  cout<<"searching for -3 -"; 
  if(search(head,-3))
  {
    cout<<"present\n";
  }
  else 
  {
    cout<<"not present\n";
  }
  cout<<"searching for 51 -"; 
  if(search(head,51))
  {
    cout<<"present\n";
  }
  else 
  {
    cout<<"not present\n";
  }
  return 0;
}


btree* insert(btree* head,int key,btree* p)
{
  if(head==NULL)
  {
    head=new btree;
    initialise(head);
    head->leaf=1;
    head->key[0]=key;
    (head->n)++;
    return head;
  }
  else
  {
   
     p=head;
    
    while(p!=NULL && p->leaf!=1) // find the node where key is to be inserted
    {
      int i;
      for( i=0;i<p->n;i++)
      {
        if(key<=p->key[i])
          break;
      }
        if(p->leaf==0)
          p=p->child[i];
        else
          break;
 
    }
  
    if(p->n==p->m-1)  // node is full
    {
     
      head=split(p,key,NULL,head,0); // sibling node
    }
    else // not full
    {

      int i;
      for(i=0;i<p->n;i++)
      {
        if(key<p->key[i])
          break;
      }
      if(i!=p->n) //shift the keys
      {  
        for(int j=p->n-1;j>=i;j--)
        {
           p->key[j+1]=p->key[j];
        }
      }
      p->key[i]=key;
      p->n++;
    }
    return head;
  }
}

btree* split(btree* p,int key,btree* q,btree* head,int child)
{
  int temp[p->m];  // for finding median
  int i=0;
  btree* s=NULL;
 


  if(p->n!=p->m-1) // if node is not full
  {
  

    for(i=0;i<p->n;i++)
    {
      if(key<p->key[i])
        break;
      }
   
      if(i!=p->n) //shift the keys
      {  
        for(int j=p->n-1;j>=i;j--)
        {
           p->key[j+1]=p->key[j];
           
        }
        for(int j=p->n;j>=i+1;j--)
        {
          p->child[j+1]=p->child[j];
        }
      }
      p->key[i]=key;
      p->child[i+1]=q;
      p->child[i+1]->parent=p;
      p->n++;

  }
  else  // if the node is full
  {

    if(p->parent==NULL ) // if p is root
    {
      s=new btree;  //cout<<"hi new root"; 
      initialise(s);
      head=s; //update the head
      s->n++;
      p->parent=s;
      s->leaf=0;
      s->child[0]=p; // make first child of s as p
    }


    
    while(p->key[i]<key && i<p->m-1)
    {
      temp[i]=p->key[i];
      i++;
    }
      
    temp[i]=key;
  
    while(i<=p->m-1)
    {
      temp[i+1]=p->key[i];
      i++;
    }
  
    int median=temp[p->m/2];
 
    for(int i=0;i<(p->m/2);i++)
    {
      p->key[i]=temp[i];
    }
    p->n=p->m/2;  //update n
  

  
    btree* z=new btree;
    initialise(z);
    z->parent=s;
    if(p->leaf==0)
      z->leaf=0;
    else
      z->leaf=1;
  
    for(int i=p->m/2+1;i<p->m;i++)
    {
      z->key[i-(p->m/2 + 1)]=temp[i];
    }
    z->n=p->m/2; //update sibling node's n
	   

   if(s!=NULL )
   { 
     
      s->key[0]=median;// put median in new root node
      s->child[1]=z;
 	    
   }                       
   else
   {

     int i;
     for(i=0;i<p->parent->n;i++)
     {
       if(p==p->parent->child[i])
         break;
     }

      head=split(p->parent,median,z,head,i+1);
   }


    if(q!=NULL)
    {

      if(child<=p->m/2)
      {
         for(int i=p->m/2;i<p->m;i++)
         {
           z->child[i-p->m/2]=p->child[i];
           z->child[i-p->m/2]->parent=z;
         }
         for(int i=child;i<p->m/2;i++)
         {
           p->child[i+1]=p->child[i];
         }
         p->child[child]=q;
         q->parent=p;
      }
      else
      {
        for(int i=p->m/2+1;i<child;i++)
        {
          z->child[i-p->m/2-1]=p->child[i];
          z->child[i-p->m/2-1]->parent=z;
         }
         z->child[child-p->m/2-1]=q;
         q->parent=z;
         for(int i=child;i<p->m;i++)
         {
           z->child[i-p->m/2]=p->child[i];
           z->child[i-p->m/2]->parent=z;
         }
      }
    }

  }
  return head;
}


int search(btree* t,int key)
{
  int present=0;
  
  for(int i=0;i<t->n;i++)
  {
    if(t->key[i]==key)
    {
      present=1;
      break;
    }
    else if(t->key[i]>key && t->leaf!=1)
    {
      present=search(t->child[i],key);
      break;
    }
    else if(t->n-1==i && t->leaf!=1)
    {
      present=search(t->child[i+1],key);
    }
    else if(t->leaf==1 && i==t->n-1)
      present=0;
  }
  return present;  
}

void initialise(btree* head)
{
  head->m=3;
  head->parent=NULL;
  head->key=new int[head->m-1];
  head->child=(btree**)malloc(head->m*sizeof(btree*));
  head->leaf=1;
  head->n=0;
  for(int i=0;i<head->m;i++)
  {
    head->child[i]=NULL;
    if(i<head->m-1)
      head->key[i]=0;
  }
}

void inorder(btree* t,int node_no)
{
  int i=0;
  while(t!=NULL && i!=t->n+1 )
  {
    for(i=0;i<=t->n;i++)
    {
      if(i==0) 
        node_no++;
      inorder(t->child[i],node_no);
      if(i<t->n)
      cout<<"("<<node_no<<")"<<t->key[i]<<" "; 
      if(i==t->n)
        cout<<endl;
    }
   
  }
}
