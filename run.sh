echo 'build clib ...'
cd clib
make all
cd ..
sh ./build-clib.sh
echo 'run python test ...'
echo '==================='
# python test.py
python extract_text.py
