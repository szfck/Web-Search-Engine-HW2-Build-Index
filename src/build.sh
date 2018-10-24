make build_index
rm ../output/term_table.txt
rm ../output/url_table.txt

# test ==== [1000, 1002)
time ./build_index 1000 1002
# ==========

# time ./build_index 0 10

