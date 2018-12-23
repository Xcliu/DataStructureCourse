import random
import time
time_start=time.time()
a=[]
for i in range(10**5):
    a.append(random.randint(1,20))


def select_sort(A):
    #print("The origin array:",A)
    list_obj=range(len(A))
    tmp=0
    for j in range(len(A)):
        min_set=A[j]
        index=j
        for i in list_obj[j:len(A)]:
            if A[i]< min_set:
                min_set=A[i]
                index=i
        #print(min_set)
        tmp=A[j]
        A[j]=min_set
        A[index]=tmp
    #print(A)

select_sort(a)

time_end=time.time()
print "Runing time",time_end-time_start
