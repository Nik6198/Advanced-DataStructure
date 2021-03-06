// niket doke sy h 2

#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctime>
using namespace std;

typedef struct student
{
    int roll_no;
    string name;
    int marks;
    int phone_no;
}student;

typedef struct skip_ll
{
    int key;
    struct skip_ll* nxt;
    bool flag;
    int no;
    union
    {
        struct skip_ll* dwn;
        student* s_dwn;
    }u;
}skip_ll;


student* set(int roll_no)
{
    student* node=new student();
    string name;
    int marks,phone;
    cin>>name>>marks>>phone;
    node->roll_no=roll_no;
    node->name=name;
    node->marks=marks;
    node->phone_no=phone;
    return node;
}




skip_ll* initialise(int key,student* node=NULL,bool flag=true) // flag 1 for skip_ll and 0 for student
{
    skip_ll* temp=new skip_ll();
    temp->key=key;
    temp->flag=flag;
    temp->no=0;
    if(flag)
        temp->u.dwn=NULL;
    else
    {
        temp->u.s_dwn=node;
    }    
    temp->nxt=NULL;
    return temp;
}

skip_ll* insert(skip_ll *start,int key,student* node)
{
    int max_level=0,cur_level=0;
    //cout<<rand();
    int r;
    skip_ll* new_node=initialise(key,node,false),*temp=NULL;
    // cout<<level<<new_node->key<<endl; 
     
    do
    {
        //cout<<"why";
        //if(level==2)
        //{
        temp=initialise(key);
        temp->u.dwn=new_node;
        new_node=temp;
        cur_level++;
       // cout<<cur_level;}
        r=rand();
       //cout<<r<<endl;
    }while((r%2)==0);
    
    temp=start;
    
    while(temp->flag)
    {
        max_level++;
        temp=temp->u.dwn;
    }
    
    int temp_level=max_level;
    
    while(temp_level++ < cur_level)
    {
        temp=initialise(-1);
        temp->u.dwn=start;
        start=temp;
    }
    
    temp=start;
   
    while( temp->flag )
    {
        //cout<<"temp nxt"<<temp->key;
        while(temp->nxt != NULL && new_node->key > temp->nxt->key )
        {
            temp=temp->nxt;
            //temp->no+=no; 
            //(temp->no)++; 
            //cout<<"why not"; 
        }
        //cout<<max_level<<" "<<cur_level<<" "<<temp->key;
        if(max_level-- <= cur_level)
        {
            //cout<<temp->key;
            new_node->nxt=temp->nxt;
            temp->nxt=new_node;
            
            new_node=new_node->u.dwn;
        }
        temp=temp->u.dwn;
        //cout<<endl<<temp->key<<" flag "<<temp->flag;
    }
    
 
    //cout<<"temp"<<temp->key;
    new_node->nxt=temp->nxt;
    temp->nxt=new_node;
     int no=0;
    temp=start;
    while(temp->flag)
    {
        temp=temp->u.dwn;
    }
    
    while(temp->key!=key)
    {
      no++;
      temp=temp->nxt;
    }
    //cout<<temp->key<<"has no "<<no<<endl;
    temp->no=no;
    
    while(temp!=NULL)
    {
        skip_ll* t=start;
        
        while(t->flag)
        {
            while(t->nxt!=NULL && temp->key >= t->nxt-> key)
               t=t->nxt;
            //cout<<"t->key "<<t->key<<endl;
            if (temp->key == t->key)
                break;
            t=t->u.dwn;
        }
        
        while(t->flag)
        {
            t->no=no;
            t=t->u.dwn;
        }
        t->no=no;
        no++;
        temp=temp->nxt;
    }
    
    
    
    
    return start;
}

void print(skip_ll* t)
{
    if(t!=NULL)
    {
        skip_ll* p=t;
        while(p!=NULL)
        {
            cout<<p->key<<" "<<p->no<<"  ";
            p=p->nxt;
        }            
        cout<<endl;
        if(t->flag)
        print(t->u.dwn);
        else
        print(NULL);
    }
}

void print_data(skip_ll* t)
{
    while(t->flag)
        t=t->u.dwn;
    
    t=t->nxt;
    while(t!=NULL)
    {
        student* node=t->u.s_dwn;
        
        cout<<node->name<<endl<<"roll_no "<<node->roll_no<<"  marks "<<node->marks<<"  phone "<<node->phone_no<<endl;
        t=t->nxt;
    }
}


bool search(skip_ll* t,int key)
{
    while(t->flag)
    {
        while(t->nxt!=NULL && key >= t->nxt-> key)
            t=t->nxt;
        if (key == t->key)
            break;
        t=t->u.dwn;
    }
    if(t->key==key)
        return true;
    else
        return false;
}


skip_ll* delete_ll(skip_ll* t,int key)
{
    skip_ll* temp=t,*temp2,*start=t;
    int max_level=0,cur_level=0;
    bool flag1=true;
    
    while(temp->flag)
    {
        max_level++;
        temp=temp->u.dwn;
    }
    
    while(temp->key!=key)
    {
        temp=temp->nxt;
    }
    temp=temp->nxt;
    
    while(temp!=NULL)
    {
        skip_ll* t=start;
        
        while(t->flag)
        {
            while(t->nxt!=NULL && temp->key >= t->nxt-> key)
               t=t->nxt;
            //cout<<"t->key "<<t->key<<endl;
            if (temp->key == t->key)
                break;
            t=t->u.dwn;
        }
        
        while(t->flag)
        {
            (t->no)--;
            t=t->u.dwn;
        }
        (t->no)--;
        //no++;
        temp=temp->nxt;
    }
    
    
    
    //cout<<t->nxt;
    //cout<<"c1\n";
    while(t->flag)
    {
        while(t->nxt!=NULL && key > t->nxt-> key)
        {
            //if(t->key==-1)
             // {start=t;//cout<<t->key;
              //}
              
            t=t->nxt;
           // cout<<t->nxt<<" ";
            
        }
        if (t->nxt!=NULL && key == t->nxt->key)
        {
            
            if(flag1)
            {
                temp=t;
                while(temp->flag)
                {
                    cur_level++;
                    temp=temp->u.dwn;
                }
                flag1=false;
            }
            //if(key==12)
            //cout<<t->key;
            if(t->key==-1 && max_level==cur_level && t->nxt->nxt==NULL) // overall level decreases
            {
                //cout<<"why";
                temp=t->nxt;
                max_level--;
                cur_level--;
                temp2=t;
                t=t->u.dwn;
                start=t;
                //cout<<(t->key)<<endl;
                delete(temp2);
                delete(temp);
                continue;
            }
            
            temp2=t->nxt;
            t->nxt=t->nxt->nxt;
            delete(temp2);
            
        }
        
        t=t->u.dwn;
       
    }
    
    temp2=t->nxt;
    student* node=temp2->u.s_dwn;
    delete(node);
    t->nxt=t->nxt->nxt;
    delete(temp2);
    
   // cout<<start->key;
    return start;
}


student* find_n_smallest(skip_ll* t,int n)
{
    while(t->flag)
    {
        while(t->nxt!=NULL && n >= t->nxt-> no)
            t=t->nxt;
        if (n == t->no)
            break;
        t=t->u.dwn;
    }
    if(t->no==n)
    {
        while(t->flag)
            t=t->u.dwn;
        return t->u.s_dwn;
       // student* node=t->u.s_dwn;
        //cout<<node->name<<endl<<"roll_no "<<node->roll_no<<"  marks "<<node->marks<<"  phone "<<node->phone_no<<endl;
    }
    else
        return NULL;
}

void range_query(skip_ll* start,int l1,int l2 )
{
    
    for(int key=l1;key<=l2;key++)
    {
        skip_ll* t=start;
        while(t->flag)
        {
            while(t->nxt!=NULL && key >= t->nxt-> key)
                t=t->nxt;
            if (key == t->key)
                break;
            t=t->u.dwn;
        }
        if(t->key==key)
        {
            while(t->flag)
                t=t->u.dwn;
            
            student* node=t->u.s_dwn;
            cout<<node->name<<endl<<"roll_no "<<node->roll_no<<"  marks "<<node->marks<<"  phone "<<node->phone_no<<endl;
        }
    }

}


int main()
{
    skip_ll* start=initialise(-1,NULL,false);
    srand(time(0));
    
    int n;
    cout<<"enter no of records\n";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int roll_no;
        cin>>roll_no;
        student* node=set(roll_no);
        start=insert(start,roll_no,node);
        //print(start);
        
    }  
    cout<<"skip list is \n";
    print(start);
    cout<<"skip list data is\n";
    print_data(start);  
    /*print(start);
    start=insert(start,5,3);
    print(start);
    start=insert(start,8,1);
    print(start);
    start=insert(start,12,4);
    print(start);*/
    cout<<"searching for 12 "<<search(start,12)<<endl;
    cout<<"searching for 5 "<<search(start,5)<<endl;
    cout<<"searching for 8 "<<search(start,8)<<endl;
    cout<<"searching for 10 "<<search(start,10)<<endl;
    cout<<"searching for 11 "<<search(start,11)<<endl;
    
    student* node=find_n_smallest(start,2);
    cout<<"2nd smallest record is \n";
    if (node!=NULL)
        cout<<node->name<<endl<<"roll_no "<<node->roll_no<<"  marks "<<node->marks<<"  phone "<<node->phone_no<<endl;
    else
        cout<<"no data available\n";
    //cout<<start->nxt;
    cout<<"all records in range 5-10\n";
    range_query(start,5,10);
    cout<<"\ndeleting 10 \n";
    start=delete_ll(start,10);cout<<endl;
    print(start);
    cout<<"\ndeleting 5 \n";
    start=delete_ll(start,5);cout<<endl;
    print(start);
    cout<<"\ndeleting 8 \n";
    start=delete_ll(start,8);cout<<endl;
    print(start);
    cout<<"\ndeleting 12 \n";
    start=delete_ll(start,12);cout<<endl;
    //cout<<start->key;
    
    print(start);
    return 0;
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////


input

4
10
niket
99
23428975
5
rahul
43
23542345
8
tirumal
66
24234324
12
piyush
98
23525353

output

enter no of records
skip list is 
-1 0  8 2  
-1 0  8 2  
-1 0  5 1  8 2  10 3  12 4  
-1 0  5 1  8 2  10 3  12 4  
skip list data is
rahul
roll_no 5  marks 43  phone 23542345
tirumal
roll_no 8  marks 66  phone 24234324
niket
roll_no 10  marks 99  phone 23428975
piyush
roll_no 12  marks 98  phone 23525353
searching for 12 1
searching for 5 1
searching for 8 1
searching for 10 1
searching for 11 0
2nd smallest record is 
tirumal
roll_no 8  marks 66  phone 24234324
all records in range 5-10
rahul
roll_no 5  marks 43  phone 23542345
tirumal
roll_no 8  marks 66  phone 24234324
niket
roll_no 10  marks 99  phone 23428975

deleting 10 

-1 0  8 2  
-1 0  8 2  
-1 0  5 1  8 2  12 3  
-1 0  5 1  8 2  12 3  

deleting 5 

-1 0  8 1  
-1 0  8 1  
-1 0  8 1  12 2  
-1 0  8 1  12 2  

deleting 8 

-1 0  12 1  
-1 0  12 1  

deleting 12 

-1 0  




*///////////////////////////////////////////////////////////////////////////////////////////////////////////////
