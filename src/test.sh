make test
ID=01002
BIN=../output/intermediate-output-3/index-$ID.merge1.bin
TXT=../output/intermediate-output-3/index-$ID.merge1.txt
time ./test "$BIN" "$TXT"
# time ./build_index 1001 1002
