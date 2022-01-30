import _fib_heap
import random
import time 
import matplotlib.pyplot as plt
class graph:

  def __init__(self,n):
    self.graph=[]
    
    for i in range(n):
      temp=[random.randint(0,1001) for i in range(n)]
      temp[i]=0
      self.graph.append(temp)
      
  
  def accept(self):
    for i in range(len(self.graph)):
      m=int(input())
      n=int(input())
      for j in range(n):
        dest=int(input())
        cost=int(input())
        self.graph[m-1][dest-1]=cost 
    
  def dij_array(self,source,n):
    start=time.time()
    dist=self.graph[source-1].copy()
    #print(dist)
    vis=[False for i in range(len(self.graph))]
    vis[source-1]=True
    
    
    for i in range(len(self.graph)-1):
      min=9999999
      v=None
      for i in range(len(self.graph)):
      
        if not vis[i]  and min>dist[i]:
          v=i
          min=dist[i]
          
      if v is None:
        break
      vis[v]=True
      min=dist[v]
      for i in range(len(self.graph)):
        if not vis[i] and dist[i]>dist[v]+self.graph[v][i]:
          dist[i]=dist[v]+self.graph[v][i]
      #print(min,v,dist,vis)
    t=abs(start-time.time())
    plt.plot([n],[t],'bo')  
    print("time taken for array",t,n)
    return dist

  def dij_heap(self,source,n):
    
    h1=_fib_heap.fib()
    
    for i in range(len(self.graph)):
      if i is not (source-1):
        h1.insert(key=self.graph[source-1][i],vertex=i)
    dist=self.graph[source-1].copy()
    dist1=dist.copy()
    #print(dist)
    #h1.print1()
    #print("**")
    #vis=[False for i in range(len(self.graph))]
    #vis[source-1]=True
    start=time.time()
    for i in range(len(self.graph)-1):
      min=h1.extract_min()
      #print(min[0],min[1])
      #if h1.min is not None:
        #print("***")
        #h1.print1()
        #print("***")
      list1=[]
      
      for k in h1.hash.keys():
        #print(h1.hash.keys(),"hi",h1.hash[k],"bye")
        #list1=list(h1.hash.values())
        #print(k,list1[0].key[1])
      
        if h1.hash[k].key[1] > dist[min[0]]+self.graph[min[0]][k]:
          h1.decrease_key(k,dist1[k],dist[min[0]]+self.graph[min[0]][k])
          dist[k]=dist[min[0]]+self.graph[min[0]][k]
    t=abs(start-time.time())
    plt.plot(n,[t],'ro')  
    print("time taken is for heap",t,n)
    
    return dist  
#h1=fib()
n=0
while n<=5000:
    n+=100
#n=int(input())
    g=graph(n)
#print(g.graph[0])
#g.accept()

#for i in g.graph:
 # print(i)
  

    g.dij_heap(1,n)
    g.dij_array(1,n)
plt.show()
