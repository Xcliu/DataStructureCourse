import random
a=[]
for i in range(10):
    a.append(random.randint(1,20))
#a=[1,4,3,6,7]

def select_sort(A):
    print("the original array:",A)
    j=1
    tmp=0
    unuse=1
    k=0
    index=0
    while j<len(A):
        if A[j]<A[0]:
            tmp=A[0]
            A[0]=A[j]
            i=j
            while i>=2:
                A[i]=A[i-1]
                i=i-1
            A[1]=tmp 
        elif A[j]>=A[j-1]:
             unuse=1
        else:
            for i in range(j):
                if A[j]>=A[i-1]and A[j]<=A[i]:
                    index=i
            k=j
            tmp=A[k]
            while k>=index+1:
                A[k]=A[k-1]
                k=k-1
            A[index]=tmp
        j=j+1
    print(A)
select_sort(a)
