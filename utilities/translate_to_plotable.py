from sys import stdin
print("t", "dt")
i =0
for line in stdin :
	i+=1
	if("dt" in line):
		print i, line.strip().split("dt:")[1]
