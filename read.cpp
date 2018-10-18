#include <iostream>
#include <unordered_map>
#include <assert.h>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

int readInt(ifstream& in) {
    char ch;
    if (!in.get(ch)) return -1;
    int value = 0;

    cout << (int)ch << endl;
    while (ch > 127) {
        value *= 128;
        value += (ch & 127);
        in.get(ch);
    }
    value *= 128;
    value += (ch & 127);
    return value;
}
int main() {
    ifstream in("index.txt", ifstream::binary);
    // string input_filename = ;
    // input_file.open(input_filename);
    // ofstream term_table, index;
    // term_table.open("term_table.txt");
    // index.open("index.bin");
    int start = 134737, end = 134792, number = 14;
    // int start = 0, end = 100, number = 14;
    // 135055
    in.seekg(start);
    std::string s;
    s.resize(end - start);
    in.read(&s[0], end - start);

    for (int i = 0; i < 10; i++) {
        cout << (int)(unsigned char)(s[i]) << endl;
    }

    // in.seekg(start);
    // int term_id = readInt(in);
    // cout << term_id << endl;

    // cout << readInt(in) << endl;
    // for (int i = 0; i < 14; i++) {
    //     cout << readInt(in) << endl;
    // }
    // for(int i=0;i<NUMBER_OF_BYTES_TO_READ;i++) { 
    //     if(in.get(ch))
    //         out << ch;
    //     else
    //         break;
    // }

    int BLOCK = 128;

    return 0;
}