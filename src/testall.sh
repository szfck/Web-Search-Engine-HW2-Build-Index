make build_index
rm ../output/term_table.txt
rm ../output/url_table.txt

# test ==== [1000, 1002)
time ./build_index 1000 1005
# run ===== [0, 10)
# time ./build_index 0 10

make merge
# test ==== [1000, 1002) -> 1000
time ./merge 1 1000 1005 1000
# run ====== [0, 10) -> 0
# time ./merge 1 0 10 0

make test

ID=01000
BIN=../output/intermediate-output-3/index-$ID.merge1.bin
TXT=../output/intermediate-output-3/index-$ID.merge1.txt
time ./test "$BIN" "$TXT"