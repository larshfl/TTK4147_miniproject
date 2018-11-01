echo "Start"
cd ../build/
cmake .
make
echo "Finished making"

cp  ./Sanntid_miniproject/Sanntid_miniproject /export/nfs/

cd ../miniproject-files 

echo "Starting server"
./miniproject-server
cp /export/nfs/OUTPUT.txt ../utilities/BOARD_DATA.txt

rm plot5.png
gnuplot plot5
feh plot5.png
cd ../utilities
cat BOARD_DATA.txt | translate_to_plotable.py > results.dat
gnuplot testGnuplot
echo "Finished main.sh!"

