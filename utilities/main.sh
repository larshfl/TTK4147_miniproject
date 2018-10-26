echo "Start"
cd ../build/
cmake .
make
echo "Finished making"

cp  ./Sanntid_miniproject/Sanntid_miniproject /export/nfs/

cd ../miniproject-files 

echo "Starting server"
./miniproject-server

rm plot5.png
gnuplot plot5
feh plot5.png

echo "Finished main.sh!"

