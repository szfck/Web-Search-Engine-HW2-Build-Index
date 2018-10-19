#include "helper.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

VByteWriter::VByteWriter(string file_name) {
    out.open(file_name);
    offset = 0;
}

int VByteWriter::getOffset() {
    return offset;
}

void VByteWriter::close() {
    out.close();
}

void VByteWriter::write(long long x) {
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

VByteReader::VByteReader(string file_name) {
    in.open(file_name);
}

void VByteReader::close() {
    in.close();
}

vector<long long> VByteReader::read(int start, int end) {
    in.seekg(start);
    int len = end - start;
    string s;
    s.resize(len);
    in.read(&s[0], len);
    vector<long long> arr;
    for (int i = 0; i < len; ) {
        long long val = 0;
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


