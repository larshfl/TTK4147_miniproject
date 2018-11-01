from sys import stdin

i =0
for line in stdin :
    i+=1
    print(i, line.strip().split("dt:")[1])