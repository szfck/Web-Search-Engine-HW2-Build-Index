#include "helper.h"
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

// Writer
Writer::Writer(string file_name) {
    out.open(file_name);
}

void Writer::close() {
    out.close();
}

// Reader
Reader::Reader(string file_name) {
    in.open(file_name);
}

void Reader::close() {
    in.close();
}

// TextWriter
TextWriter::TextWriter(string file_name) : Writer(file_name) {}

void TextWriter::write(int key, const vector<string>& list) {
    out << key;
    for (auto val : list) {
        out << " " << val;
    }
    out << endl;
}

// TextReader
TextReader::TextReader(string file_name) : Reader(file_name) {}

// string TextReader::getNext(const string& s, int& pos) {
//     string term = "";
//     while (pos < (int) s.size() && s[pos] == ' ') pos++;
//     while (pos < (int) s.size() && s[pos] != ' ') {
//         term += s[pos++];
//     }
//     return term;
// }
map<int, vector<string>> TextReader::read() {
    map<int, vector<string>> mp;
    string line = "";
    while (getline(in, line)) {
        stringstream ss(line);
        int key;
        string val;
        ss >> key;
        while (ss >> val) {
            mp[key].push_back(val);
        }
    }
    return mp;
}

// VByte Writer
VByteWriter::VByteWriter(string file_name) : Writer(file_name) {
    offset = 0;
}

int VByteWriter::getOffset() {
    return offset;
}

void VByteWriter::writeList(int tid, const vector<pair<int, int>>& list) {
    write(tid);
    int number = (int) list.size();
    for (int i = 0; i < number; i += BLOCK) {
        for (int j = 0; j < BLOCK && i + j < number; j++) {
            write(list[i + j].first);
        }
        for (int j = 0; j < BLOCK && i + j < number; j++) {
            write(list[i + j].second);
        }
    }
    write(number);
}

void VByteWriter::write(int x) {
    vector<int> digits;
    digits.push_back((x % 128));
    x /= 128;
    while (x) {
        digits.push_back(128 | (x % 128));
        x /= 128;
    }
    int len = (int) digits.size();
    for (int i = len - 1; i >= 0; i--) {
        out << (unsigned char)(digits[i]);
    }
    offset += len;
}

// VByte Reader
VByteReader::VByteReader(string file_name) : Reader(file_name) {}

vector<int> VByteReader::read(int start, int end) {
    in.seekg(start);
    int len = end - start;
    string s;
    s.resize(len);
    in.read(&s[0], len);
    vector<int> arr;
    for (int i = 0; i < len; ) {
        int val = 0;
        int j = i;
        while (j < len) {
            int ch = (unsigned char)s[j++];
            val = val * 128 + (ch & 127);
            if (ch <= 127) break;
        }
        i = j;
        arr.push_back(val);
    }
    return arr;
}


