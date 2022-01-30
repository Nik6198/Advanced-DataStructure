#include<iostream>
using namespace std;


typedef struct bt
{
  int key;
  int degree;
  struct bt* parent;
  struct bt* sibling;
  struct bt* left;
}bt;


bt* reverse(bt*);
bt* merge(bt*,bt*);
void link(bt*,bt*);
bt* print(bt*,int);
bt* union_bt(bt*,bt*);
bt* create(int);
int min(bt*);
int extract_min(bt** head);
int decrease_key(bt*,int,int);
void delete_key(bt** head,int key);


int main()
{
 
  int n;
  cin>>n;
  int k;
  bt* head=NULL;
  for(int i=0;i<n;i++)
  {
  	cin>>k;
  	bt* t=create(k);
  	head=union_bt(head,t);

  }
  cout<<"binomial heap is \n";
  print(head,0);
  cout<<endl<<endl;
 // while(head!=NULL)
  {

  cout<<"min is "<<extract_min(&head)<<endl;
  
  print(head,0);

  }
  cout<<"decrease key 80 to 3\n";
  decrease_key(head,80,3);
  print(head,0);
  cout<<"delete 2 \n";
  delete_key(&head,2);
   print(head,0);
  cout<<"delete 21 \n"; 
  delete_key(&head,21);
  print(head,0);
  return 0;
}

bt* reverse(bt* t)
{
  bt* p=t;
  bt* q=t->sibling;
  bt* r=NULL;
  if(t->sibling!=NULL)
    r=t->sibling->sibling;
  
  p->sibling=NULL; 
  while(q!=NULL)
  {
    
  	q->sibling=p;
  	p=q;
  	q=r;
  	if(r!=NULL)
  	  r=r->sibling;
  }
  
  return p;
}



bt* merge(bt* h1,bt* h2)
{
  bt* new_head=NULL,*temp=NULL;
  
  if(h1==NULL)
  {
    new_head=h2;
    return new_head;
  }
  
  if(h1->degree<h2->degree)
  {
    new_head=temp=h1;
    h1=h1->sibling;
    temp->sibling=NULL;
  }
  else
  {
    new_head=temp=h2;
    h2=h2->sibling;
    temp->sibling=NULL;
  }
  
  while(h1!=NULL && h2!=NULL)
  {
    if(h1->degree<h2->degree)
    {
      temp->sibling=h1;
      temp=temp->sibling;
      h1=h1->sibling;
      temp->sibling=NULL;
    }
    else
    {
      temp->sibling=h2;
      temp=temp->sibling;
      h2=h2->sibling;
      temp->sibling=NULL;
    }
  }
  
  while(h1!=NULL)
  {
    temp->sibling=h1;
    temp=temp->sibling;
    h1=h1->sibling;
    temp->sibling=NULL;
  }
  
  while(h2!=NULL)
  {
    temp->sibling=h2;
    temp=temp->sibling;
    h2=h2->sibling;
    temp->sibling=NULL;
  }

  return new_head;
}

void link(bt* h1,bt* h2)
{
  bt* head=NULL,*child=NULL;
  if(h1->key > h2->key)
  {
    head=h2;
    child=h1;
  }
  else
  {
    head=h1;
    child=h2;
  }
  
  child->sibling=head->left;
  child->parent=head;
  head->left=child;
  head->degree++;
  
  
}


bt* print(bt* t,int key)  //used for traversal and searching with key as flag : flag=0-print flag!=0-search
{
  static bt* r=NULL;
  if(t!=NULL)
  {
     if(key==0)
       cout<<t->key<<" \""<<t->degree<<"\" "<<endl;
     else
     {
      // cout<<key;
       if(t->key==key)
         r=t;
     }  
     
     print(t->left,key);
     print(t->sibling,key);
    // cout<<endl;
  }
  return r;
}

bt* union_bt(bt* h1,bt* h2)
{
  bt* h=merge(h1,h2);
  
  bt *prev=NULL,*x=h,*next=h->sibling;
  bt *left=NULL,*head=NULL;
  while(next!=NULL)
  {

    if(x->degree == next->degree && next->sibling!=NULL && x->degree == next->sibling->degree)
  	{
   	 prev=x;
   	 x=next;
   	 next=next->sibling; 
  	}
  	else if(x->degree == next->degree)
  	{
   	 if(x->key> next->key)
   	 {
   	   left=x;
   	   head=next;
   	   x=next;
       left->sibling=NULL;
   	 }
  	  else
  	  {
   	   left=next;
   	   head=x;
  	    x->sibling=next->sibling;
  	    left->sibling=NULL;
   	 }
    
   	 if(prev!=NULL)
  	  {
   	   prev->sibling=head;
   	 }
   	 else
  	  {
   	   h=head;
   	 }
   
   	  
  	  link(left,head);
  	  next=head->sibling;

  	}
  	else
  	{
  	  prev=x;
  	  x=next;
  	  next=next->sibling;
  	  	
  	}

  }

  return h;
}


bt* create(int key)
{
  bt* t=new bt();
  t->key=key;
  t->parent=NULL;
  t->left=NULL;
  t->sibling=NULL;
  t->degree=0;
  return t;
}

int min(bt* head)
{
	int min=999999;
	
	while(head!=NULL)
	{
		if(min>head->key)
		  min=head->key;
		head=head->sibling;
	}
	return min;
}

int extract_min(bt** head)
{
  bt* t=*head; // point to min
	bt* pre_h=NULL; // point to prev of min
	bt* h1=*head;
	bt* prev=NULL; 
	int min;
	
	while(h1!=NULL)
	{
		if(t->key > h1->key)
		{
		  pre_h=prev;
		  t=h1;
		}
		prev=h1;
		h1=h1->sibling;
	}
	min=t->key;	
	
	if(t==*head)
	{
	  *head=t->sibling;
	  t->sibling=NULL;
	}
	else
	{
	  pre_h->sibling=t->sibling;
	  t->sibling=NULL;
	}
	int degree=t->degree;
	bt* temp=t->left;
	
	t->left=NULL;
	delete(t);
	
	

	if(temp!=NULL)
	{
		
  	temp=reverse(temp);  
  	*head=union_bt(*head,temp);

  }
	return min;
}


int decrease_key(bt* head,int x,int key)
{
  if(key>x)
  {
    cout<<"error";
    return 0;
  }
  bt* q=NULL;
  bt* t=head;

   
  q=print(head,x);
  
  if(q==NULL)
  {
    cout<<"key not present\n";
    return 0;
  }
  
  q->key=key;
  bt* p=q->parent;
  
  while(p!=NULL)
  {
    if(q->key<p->key)
    {
      int temp=q->key;
      q->key=p->key;
      p->key=temp;
    }
    
    p=p->parent;
    q=q->parent;
  }
  
  return 1;
}


void delete_key(bt** head,int key)
{
	int new_key=-999;
	if(decrease_key(*head,key,new_key))
    extract_min(head);
}


/*///////////////////////////////////////////////////////////////////////////////////////////////////////////

input

13
10
15
20
5
3
2
100
-2
60
75
80
12
90

output

binomial heap is 
90 "0" 
12 "2" 
60 "1" 
75 "0" 
80 "0" 
-2 "3" 
5 "2" 
10 "1" 
15 "0" 
20 "0" 
2 "1" 
3 "0" 
100 "0" 


min is -2
2 "2" 
90 "1" 
100 "0" 
3 "0" 
5 "3" 
12 "2" 
60 "1" 
75 "0" 
80 "0" 
10 "1" 
15 "0" 
20 "0" 
decrease key 80 to 3
2 "2" 
90 "1" 
100 "0" 
3 "0" 
3 "3" 
5 "2" 
60 "1" 
75 "0" 
12 "0" 
10 "1" 
15 "0" 
20 "0" 
delete 2 
3 "0" 
90 "1" 
100 "0" 
3 "3" 
5 "2" 
60 "1" 
75 "0" 
12 "0" 
10 "1" 
15 "0" 
20 "0" 
delete 21 
90 "1" 
100 "0" 
3 "3" 
5 "2" 
60 "1" 
75 "0" 
12 "0" 
10 "1" 
15 "0" 
20 "0" 


*/////////////////////////////////////////////////////////////////////////////////////////////////////////

