import random
from time import time
a=[]
start=time()
for i in range(10**8):
    a.append(random.randint(1,10**8))
a.sort()
stop=time()
print stop-start,"seconds"
