echo "Start"

cd ../build/
cmake . && \
make && \
echo "Finished making" && \

cp  ./Sanntid_miniproject/Sanntid_miniproject /export/nfs/ && \
cd ../miniproject-files && \
echo "Starting server" && \
./miniproject-server && \
rm plot5.png && \
gnuplot plot5 && \
cp plot5.png ../utilities/y.png && \

cd ../utilities && \
rm -f BOARD_DATA.txt && \
cp /export/nfs/BOARD_DATA.txt BOARD_DATA.txt && \
echo "COPIED" && \
cat BOARD_DATA.txt | python translate_to_plotable.py > results.dat && \
# cat BOARD_DATA.txt | python translate_to_plotable.py > results.dat && \
 echo "TRANSLATED"
 gnuplot testGnuplot 
 
 feh y.png && \
 feh plot5.png
echo "Finished main.sh!"

