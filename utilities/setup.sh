SPAWN="gnome-terminal -x"


Inet_Address=$( ifconfig | grep  addr | python2 getInet.py)

# Inet_Address=${GET_Inet_Address}
echo ${Inet_Address}
echo ${Inet_Address} | python2 insertIP.py

