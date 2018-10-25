echo "Start"
cd ../build/
cmake .
make
echo "Finished making"

cp  ./Sanntid_miniproject/Sanntid_miniproject /export/nfs/

cd ../miniproject-files 

echo "Starting server"
./miniproject-server
echo "Finished main.sh!"

