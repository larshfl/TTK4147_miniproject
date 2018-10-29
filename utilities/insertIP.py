from sys import stdin

def main():
    for line in stdin: 
        IP = line.strip()
    f= open("../src/main.c", "r")
    lines = [i for i in f]
    f.close()
    f = open("../src/main.c", "w")
    for line in lines: 
        if "#define IP_ADDR" in line:
            f.write("#define IP_ADDR "+ '"'+IP+'"'+ "\n")
        else:
            f.write(line)
    


main() 