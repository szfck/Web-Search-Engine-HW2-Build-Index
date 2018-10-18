cd clib
rm *.o
rm *.so
g++ -c -fPIC helper.cpp -o helper.o
g++ -shared -Wl -o libhelper.so  helper.o