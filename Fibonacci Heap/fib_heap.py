


#node structure 
class node:
  def __init__(self,key,vertex):
    self.key=[]
    self.key.append(vertex)
    self.key.append(key)
    self.left=self
    self.right=self
    self.child=None
    self.degree=0
    self.parent=None
    self.mark=False
    
#fib heap class  
class fib:
  
  def __init__(self):
    self.N=0
    self.min=None
    self.hash={}
  
    
  #inserts key or directly new_node accordingly whichever is given
  def insert(self,key=None,new_node=None,vertex=None,flag=True,flag2=True):
    #initialise new node
    if new_node is None:
      new_node=node(key,vertex)
    
      dict={}
      dict[key]=new_node
      self.hash[vertex]=dict
    #add this node to list
    if self.min==None:
      self.min=new_node
    else:
      new_node.left=self.min.left
      self.min.left=new_node
      new_node.left.right=new_node
      new_node.right=self.min
      
    #change min if required
    if flag and self.min.key[1]>new_node.key[1] :
      self.min=new_node
    #print("N",self.N)
    if flag2:
      self.N+=1  
    #increase count of no of nodes in list 
    
    #print("N",self.N)
    

  
  def extract_min(self):
    
    z=self.min

    if z is not None:
      #print("BEFORE",self.N)
      self.N=self.N-1
      #print("AFTER",self.N)
      iterate=z.child
      
      #find last node in list
      """last=iterate
      while last.right is not iterate:
        last=last.right
      """
      #remove one node and add to root list
      while iterate is not None and iterate.right is not iterate:
        temp=iterate
        #print("temp is",temp.key)
        iterate=iterate.right
        iterate.left=temp.left
        temp.left.right=iterate
        
        temp.parent=None
        self.insert(new_node=temp,flag2=False,flag=False)
      if iterate is not None:  
        self.insert(new_node=iterate,flag2=False,flag=False)  
      self.min=self.min.right
      self.min.left=z.left
      z.left.right=self.min
      #print("yo",self.min.left.right.key)
      #self.print1()
      
      
      if z.right is z:
        self.min=None
      else:
        self.consolidate()
    
    #print("AFTER",self.N)    
    if z is not None:
      return z.key
    else:
      return None
      
        
  def consolidate(self):
    
    #create aux dictionary
    aux={}    
    
    
    flag=True
    
    while flag:
      x=self.min
      self.min=self.min.right
      self.min.left=x.left
      x.left.right=self.min
      if x.right is x:
        flag=False
      x.left=x.right=x   
      #print("node list after removing x")
      #self.print1()
      #x=temp
      d=x.degree
      #print("dict",aux.get(d))
      #print("before linking")
      #for i in aux.keys():
        #print("key",i,"value",aux[i].key)
      while aux.get(d) is not None:
        y=aux.pop(d)
        #print("x",x.key)
        if x.key[1] > y.key[1] :
          t=x
          x=y
          y=t
        self.fib_heap_link(y,x)
        
        d+=1
      
      aux[d]=x
      #print("after linking")
      #for i in aux.keys():
        #print("key",i,"value",aux[i].key)
      #x=x.right
      
     
      
    self.min=None
    for value in aux.values():
      self.insert(new_node=value,flag2=False)

      
  def fib_heap_link(self,y,x):
    #print(x.key,y.key)
    t=y.right
    t.left=y.left
    y.left.right=t
    #y.left=y.right=y
    
    if x.child is not None:
      temp=x.child
      y.left=temp.left
      temp.left.right=y
      y.right=temp
      temp.left=y
      

    #print(y.child)
    x.child=y
    y.parent=x
    x.degree+=1
    y.mark=False
    #print(h1.min.key,h1.min.left.key,h1.min.right.key,h1.min.child.key)    
  def print1(self):
  
    temp=self.min
    flag1=True
    while flag1:
      print(temp.key[0],temp.key[1])
      t=temp.child
      #print(t)
      while t is not None:
        z=t
        flag2=True
        while flag2:
          print(z.key[0],z.key[1])
          
          if z.right is t:
            flag2=False
          z=z.right
          #break
        t=t.child
        #break
      if temp.right is self.min:
        flag1=False  
      temp=temp.right
      #break     
  
  def decrease_key(self,vertex,key,new_key):
    x=self.hash[vertex][key]
    
    if new_key > key:
      return 
    else:
      x.key[1]=new_key
      y=x.parent
      
      if y is not None and x.key[1] < y.key[1] :
        self.cut(x,y)
        self.cascading_cut(y)
        
        
  def cut(self,x,y):
    if y.child is x:
      if x.right is x:
        y.child=None
      else:
        y.child=x.right
      
    z=x.right
    z.left=x.left
    x.left.right=z
    
    x.left=x.right=x
    x.parent=None
    self.insert(new_node=x,flag2=False)
    
  def cascading_cut(self,y):
    z=y.parent
    
    if z is not None:
      if not y.mark:
        y.mark=True
      else:
        self.cut(y,z)
        self.cascading_cut(z)  
    
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
        
"""h1=fib()
n=int(input("enter no of nodes"))
for i in range(n):
  z=int(input())
  h1.insert(key=z,vertex=i)
  
  #h1.print1()

#h1.insert(key=10)
#h1.insert(key=5)
#h1.insert(key=15)
#print(h1.min.key,h1.min.left.key,h1.min.right.key)  
#print("N",h1.N)

print("min is",h1.extract_min()) 
#print("N",h1.N)

#print(h1.min.key,h1.min.left.key,h1.min.right.key,h1.min.child.key)
print("***")
h1.print1()
print("***")    
#h1.print1()        
h1.decrease_key(8,48,21)
print("***")
h1.print1()
print("***")
        
#while h1.N>0:
  #print("***********MINIMUM is",h1.extract_min(),"*****************")
  #if h1.min is not None:   
   # h1.print1()   
      
#print("N",h1.N)"""      
    
    
  
      
      
      
      
      
