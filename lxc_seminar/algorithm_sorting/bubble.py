import random
a=[]
for i in range(10):
    a.append(random.randint(1,20))


def bubble_sort(A):
    k=len(A)-1
    tem_num=0
    print("The origin array:",A)
    for j in range(len(A)):
       index=0
       for i in range(k):
           if A[i]>A[i+1]:
              tem_num=A[i]
              A[i]=A[i+1]
              A[i+1]=tem_num 
           else:
               index=index+1
       if index==k+1:
          break 
       k=k-1
    print(A)
bubble_sort(a)


   
