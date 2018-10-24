make build_index
rm ../output/term_table.txt
rm ../output/url_table.txt
time ./build_index 1000 1001
time ./build_index 1001 1002
