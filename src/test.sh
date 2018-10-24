make read_test
ID=01002
BIN=../output/intermediate-output-3/index-$ID.merge1.bin
TXT=../output/intermediate-output-3/index-$ID.merge1.txt
time ./read_test "$BIN" "$TXT"
# time ./build_index 1001 1002
