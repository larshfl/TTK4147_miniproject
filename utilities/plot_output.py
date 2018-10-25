import matplotlib.pyplot as plt
from sys import stdin

whole_text = "".join( [ i for i in stdin])
relevant_data = [ i.strip() for i in whole_text.split("START")[-1].split("\n") if i.strip() != '']


time = [float( i.split("t:")[-1].strip()) for i in relevant_data if ("t:" in i)]
u = [float(    i.split("u:")[-1].strip()) for i in relevant_data if    ("u:" in i)]
y = [float(    i.split("y:")[-1].strip()) for i in relevant_data if    ("y:" in i)]


# print(time, y)
shortest = min( len(time), len(y))
plt.plot(time[:shortest], y[:shortest])
plt.ylabel('y')
plt.xlabel('t')

plt.show()
