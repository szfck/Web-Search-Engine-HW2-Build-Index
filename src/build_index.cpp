#include <iostream>
#include "helper.h"
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

char ch;

//get next term from ifstream
string getTerm(ifstream& in) {
    string str = "";
    while (true) {
        str += ch;
        in.get(ch);
        if (ch == ' ' || ch == '\n') return str;
    }
}

//get num with leading 0s
string getNum(int x) {
    string num = to_string(x);
    while ((int)num.size() < 5) num = '0' + num;
    return num;
}

int main() {
    ifstream input_file;
    string input_filename = "../intermediate-output-3/" + getNum(0) + ".merge4.txt";
    input_file.open(input_filename);
    ofstream term_table;
    term_table.open("../term_table.txt");
    VByteWriter index("../index.bin");

    int BLOCK = 128; // block size

    string line = "";
    int term_id = -1;
    while (true) {
        // read term's doc ids and freqs from intermediate file
        if (!input_file.get(ch)) {
            break;
        }
        vector<int> docid;
        vector<int> freq;
        string str = "";

        string term = getTerm(input_file);
        if (term == "") break;
        term_id++;
        int pos = 0;
        while (true) {
            if (ch == '\n') break;
            string docIdStr = "";
            string freqStr = "";
            input_file.get(ch);
            assert (ch == '(');
            input_file.get(ch);
            while (ch != ',') {
                docIdStr += ch;
                input_file.get(ch);
            }
            input_file.get(ch);
            while (ch != ')') {
                freqStr += ch;
                input_file.get(ch);
            }
            docid.push_back(stoi(docIdStr));
            freq.push_back(stoi(freqStr));
            input_file.get(ch);
        }
        int number = (int)docid.size();

        // write term's info to binary file
        // term_id {docid...} {freq...}
        int startByte = index.getOffset();

        index.write(term_id);
        for (int i = 0; i < number; i += BLOCK) {
            for (int j = 0; j < BLOCK && i + j < number; j++) {
                index.write(docid[i + j]);
            }
            for (int j = 0; j < BLOCK && i + j < number; j++) {
                index.write(freq[i + j]);
            }
        }
        index.write(number);

        int endByte = index.getOffset();

        // write to term table
        term_table << term_id << " " << term << " " << startByte << " " << endByte << " " << number << endl;
    }
    return 0;
}