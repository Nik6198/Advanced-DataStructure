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


int fact(int n)
{
  int fact=1;
  
  for(int i=1;i<=n;i++)
  {
  	fact*=i;
  }
  
  return fact;
}


int nCr(int n,int r)
{
  int c=(fact(n))/(fact(n-r)*fact(r));
  return c;
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
 /* head=h2;
  child=h1;
  head->degree++;
  //child->degree++;  
  bt* c_last=NULL,*h=NULL,*h_last=NULL;
  
  h=head->left;
  //child->sibling=head->left;
  head->left=child;
  child->parent=head;
 // cout<<head->key<<child->key;

  while(child!=NULL)
  {
    c_last=child;
    while(c_last!=NULL && c_last->sibling!=NULL)
    {
      c_last->degree++;
      c_last=c_last->sibling;
    }
    if(c_last!=NULL)
    {
      c_last->degree++;
      c_last->sibling=h;
    }
    h_last=h;

    while(h_last!=NULL)
    {
      h_last->degree++;
      h_last=h_last->sibling;
    }
   

    if(h!=NULL)
      h=h->left;
    child=child->left;
  }
 // cout<<"link done\n";
  //return head;*/
  
  child->sibling=head->left;
  child->parent=head;
  head->left=child;
  head->degree++;
  
  
}
/*void print(bt* t)
{
  while(t!=NULL)
  {
    cout<<t->key<<" \""<<t->degree<<"\" \n";
    bt* l=t->left;
    while(l!=NULL)
    {
    	bt* r=l;
   	  //cout<<t->key<<" "<<t->degree<<" ";
    	while(r!=NULL)
    	{
    		cout<<r->key<<" \""<<r->degree<<"\" ";
    		r=r->sibling;
    	}
    	cout<<endl;
    	l=l->left;
  	}
  	cout<<endl;
  	t=t->sibling;
  }
}*/

bt* print(bt* t,int key)
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
  //cout<<"hi\n";
  //print(h);
  //cout<<"hi\n";
  
  bt *prev=NULL,*x=h,*next=h->sibling;
  bt *left=NULL,*head=NULL;
  while(next!=NULL)
  {
    //cout<<"x "<<x->key<<" next "<<next->key<<endl;
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
  	 // cout<<"bye";
  	 // break;
  	}
  	else
  	{
  	  prev=x;
  	  x=next;
  	  next=next->sibling;
  	  	
  	}
  	//cout<<"-------\n";
  	//print(h);
  	//cout<<"-------\n";
  }
  //print(head);
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
	min=t->key;	//cout<<pre_h<<endl;
	//cout<<min<<endl;
	//cout<<(*head)->sibling<<endl;
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
	//cout<<pre_h<<endl;
	//cout<<(*head)->sibling<<endl;
	t->left=NULL;
	delete(t);
	
	
	//int i=1;
	if(temp!=NULL)
	{
		/*bt* k=temp;
		while(k->sibling!=NULL)
		{
			k->parent=NULL;
			k=k->sibling;	
		}
		k->sibling=NULL;
		t=temp;
	
		while(t!=NULL)
  	{
    //cout<<t->key<<" "<<t->degree<<" \n";
    	t->degree=degree-i;
   	  int i_1=1;
   	  bt* l=t->left;
    	while(l!=NULL)
    	{
    		bt* r=l;
    		int no=nCr(t->degree,i_1);
   	  	//cout<<t->key<<" "<<t->degree<<" ";
    		while(no-->0)
    		{
    			//cout<<r->key<<" "<<r->degree<<" ";
    			r->degree=degree-i;
    			if(no!=0)
    			  r=r->sibling;
    			else
    				r->sibling=NULL;
    		}
    		//cout<<endl;
    		l=l->left;
    		i_1++;
  		}	
  		//cout<<endl;
  		t=t->sibling;
  		i++;
  	}		*/
	
  	temp=reverse(temp);
   // print(temp);
  	//print(*head);
  	//head=merge(head,temp);
  
  	*head=union_bt(*head,temp);
		//print(*head);
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
 /* while(t!=NULL)
  {
    //cout<<t->key<<" \""<<t->degree<<"\" \n";
    if(t->key==x)
      q=t;
    bt* l=t->left;
    while(l!=NULL)
    {
    	bt* r=l;
   	  //cout<<t->key<<" "<<t->degree<<" ";
    	while(r!=NULL)
    	{
    		//cout<<r->key<<" \""<<r->degree<<"\" ";
    		if(r->key==x)
    		  q=r;
    		r=r->sibling;
    	}
    //	cout<<endl;
    	l=l->left;
  	}
  	//cout<<endl;
  	t=t->sibling;
  }*/
 // cout<<q->key;
   
  q=print(head,x);
  //cout<<q->key<<endl;
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
  	//head=insert(head,t);
  	head=union_bt(head,t);
  	print(head,0);
  	cout<<endl<<endl;
  }
 //while(head!=NULL)
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
