#include "helper.h"
#include <cassert>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

// Writer
Writer::Writer() {
    offset = 0;
}

Writer::Writer(string file_name) : Writer() {
    open(file_name);
    offset = 0;
}

void Writer::open(string file_name) {
    out.open(file_name);
}

void Writer::close() {
    out.close();
}

int Writer::getOffset() {
    return offset;
}

void Writer::vwrite(int x) {
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

void Writer::swrite(string s) {
    out << s;
}

void Writer::vwriteList(int tid, const vector<Doc>& list) {
    vwrite(tid);
    int number = (int) list.size();
    vwrite(number);
    for (int i = 0; i < number; i += BLOCK) {
        for (int j = 0; j < BLOCK && i + j < number; j++) {
            vwrite(list[i + j].uid);
        }
        for (int j = 0; j < BLOCK && i + j < number; j++) {
            vwrite(list[i + j].freq);
        }
    }
}

// Reader

Reader::Reader() {

}

Reader::Reader(string file_name) {
    open(file_name);
}

void Reader::open(string file_name) {
    in.open(file_name);
}

void Reader::close() {
    in.close();
}

vector<int> Reader::vread(int start, int end) {
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

vector<Doc> Reader::vreadList(int tid, int start, int end, int number) {
    auto list = vread(start, end);
    // for (auto v : list) {
    //     cout << v << " ";
    // }
    // cout << endl;
    int n = (int) list.size();
    assert (tid == list[0]);
    assert (number == list[1]);
    // cout << "n : " << n << endl;
    assert (number == (n - 2) / 2);
    assert (n % 2 == 0);
    vector<Doc> docs(number);
    int cnt = 0;
    for (int i = 2; i < n; i += 2 * BLOCK) {
        int len = min((n - i) / 2, BLOCK);
        for (int j = 0; j < len; j++) {
            docs[(i - 2) / 2 + j] = Doc(list[i + j], list[i + len + j]);
            cnt++;
        }
    }
    // for (auto d : docs) {
    //     cout << d.first << "," << d.second << endl;
    // }
    assert (cnt == number);
    return docs;
}

// string getNext(const string& s, int& pos) {
//     string t = "";
//     while (pos < (int) s.size() && s[pos] == ' ') pos++;
//     while (pos < (int) s.size() && s[pos] != ' ') t += s[pos++];
//     return t;
// }

vector<Url> Reader::urlread() {
    vector<Url> urls;
    string line = "";
    while (getline(in, line)) {
        stringstream ss(line);
        int uid, length;
        string url;
        ss >> uid >> url >> length;
        // urls[uid] = Url(uid, url, length);
        urls.emplace_back(uid, url, length);
    }
    return urls;
}

vector<Term> Reader::termread() {
    vector<Term> terms;
    string line = "";
    while (getline(in, line)) {
        stringstream ss(line);
        int tid;
        string term;
        ss >> tid >> term;
        // terms[tid] = Term(tid, term);
        terms.emplace_back(tid, term);
    }
    return terms;
}

vector<Index> Reader::indexread() {
    vector<Index> indexes;
    string line = "";
    while (getline(in, line)) {
        stringstream ss(line);
        int tid, start, end, number;
        ss >> tid >> start >> end >> number;
        // indexes[tid] = Index(tid, start, end, number);
        indexes.emplace_back(tid, start, end, number);
    }
    return indexes;
}

// VByte Reader
// VByteReader::VByteReader(string file_name) : Reader(file_name) {}

// int VByteReader::getNext(int& start) {
//     int val = 0;
//     while (true) {
//         int x = read(start, start + 1)[0];
//         start++;
//         val = (val << 7) | (x & 127);
//         if ((x & 128) == 0) {
//             break;
//         } 
//     }
//     return val;
// }

// vector<int> VByteReader::read(int start, int end) {
//     in.seekg(start);
//     int len = end - start;
//     string s;
//     s.resize(len);
//     in.read(&s[0], len);
//     vector<int> arr;
//     for (int i = 0; i < len; ) {
//         int val = 0;
//         int j = i;
//         while (j < len) {
//             int ch = (unsigned char)s[j++];
//             val = val * 128 + (ch & 127);
//             if (ch <= 127) break;
//         }
//         i = j;
//         arr.push_back(val);
//     }
//     return arr;
// }

// vector<pair<int, int>> VByteReader::read(int tid, int start, int end, int number) {
//     auto list = read(start, end);
//     for (auto v : list) {
//         cout << v << " ";
//     }
//     cout << endl;
//     int n = (int) list.size();
//     assert (tid == list[0]);
//     assert (number == list[1]);
//     cout << "n : " << n << endl;
//     assert (number == (n - 2) / 2);
//     assert (n % 2 == 0);
//     vector<pair<int, int>> docs(number);
//     int cnt = 0;
//     for (int i = 2; i < n; i += 2 * BLOCK) {
//         int len = min((n - i) / 2, BLOCK);
//         for (int j = 0; j < len; j++) {
//             docs[(i - 2) / 2 + j] = make_pair(list[i + j], list[i + len + j]);
//             cnt++;
//         }
//     }
//     for (auto d : docs) {
//         cout << d.first << "," << d.second << endl;
//     }
//     assert (cnt == number);
//     return docs;
// }
// // Reader

// Reader::Reader(string file_name) {
//     open(file_name);
// }

// void Reader::open(string file_name) {
//     in.open(file_name, ios::binary | ios::ate);
// }

// int Reader::getFileSize() {
//     return in.tellg();
// }

// void Reader::close() {
//     in.close();
// }

// TextWriter
// TextWriter::TextWriter(string file_name) : Writer(file_name) {}

// void TextWriter::write(int key, const vector<string>& list) {
//     out << key;
//     for (auto val : list) {
//         out << " " << val;
//     }
//     out << endl;
// }

// TextReader
// TextReader::TextReader(string file_name) : Reader(file_name) {}

// string TextReader::getNext(const string& s, int& pos) {
//     string term = "";
//     while (pos < (int) s.size() && s[pos] == ' ') pos++;
//     while (pos < (int) s.size() && s[pos] != ' ') {
//         term += s[pos++];
//     }
//     return term;
// }
// map<int, vector<string>> TextReader::read() {
//     map<int, vector<string>> mp;
//     string line = "";
//     while (getline(in, line)) {
//         stringstream ss(line);
//         int key;
//         string val;
//         ss >> key;
//         while (ss >> val) {
//             mp[key].push_back(val);
//         }
//     }
//     return mp;
// }

// VByte Writer
// VByteWriter::VByteWriter(string file_name) : Writer(file_name) {
//     offset = 0;
// }

// int VByteWriter::getOffset() {
//     return offset;
// }

// void VByteWriter::writeList(int tid, const vector<pair<int, int>>& list) {
//     write(tid);
//     int number = (int) list.size();
//     write(number);
//     for (int i = 0; i < number; i += BLOCK) {
//         for (int j = 0; j < BLOCK && i + j < number; j++) {
//             write(list[i + j].first);
//         }
//         for (int j = 0; j < BLOCK && i + j < number; j++) {
//             write(list[i + j].second);
//         }
//     }
// }

// void VByteWriter::write(int x) {
//     cout << "write x: " << x << endl;
//     vector<int> digits;
//     digits.push_back((x % 128));
//     x /= 128;
//     while (x) {
//         digits.push_back(128 | (x % 128));
//         x /= 128;
//     }
//     int len = (int) digits.size();
//     for (int i = len - 1; i >= 0; i--) {
//         out << (unsigned char)(digits[i]);
//     }
//     offset += len;
// }

// // VByte Reader
// VByteReader::VByteReader(string file_name) : Reader(file_name) {}

// // int VByteReader::getNext(int& start) {
// //     int val = 0;
// //     while (true) {
// //         int x = read(start, start + 1)[0];
// //         start++;
// //         val = (val << 7) | (x & 127);
// //         if ((x & 128) == 0) {
// //             break;
// //         } 
// //     }
// //     return val;
// // }

// vector<int> VByteReader::read(int start, int end) {
//     in.seekg(start);
//     int len = end - start;
//     string s;
//     s.resize(len);
//     in.read(&s[0], len);
//     vector<int> arr;
//     for (int i = 0; i < len; ) {
//         int val = 0;
//         int j = i;
//         while (j < len) {
//             int ch = (unsigned char)s[j++];
//             val = val * 128 + (ch & 127);
//             if (ch <= 127) break;
//         }
//         i = j;
//         arr.push_back(val);
//     }
//     return arr;
// }

// vector<pair<int, int>> VByteReader::read(int tid, int start, int end, int number) {
//     auto list = read(start, end);
//     for (auto v : list) {
//         cout << v << " ";
//     }
//     cout << endl;
//     int n = (int) list.size();
//     assert (tid == list[0]);
//     assert (number == list[1]);
//     cout << "n : " << n << endl;
//     assert (number == (n - 2) / 2);
//     assert (n % 2 == 0);
//     vector<pair<int, int>> docs(number);
//     int cnt = 0;
//     for (int i = 2; i < n; i += 2 * BLOCK) {
//         int len = min((n - i) / 2, BLOCK);
//         for (int j = 0; j < len; j++) {
//             docs[(i - 2) / 2 + j] = make_pair(list[i + j], list[i + len + j]);
//             cnt++;
//         }
//     }
//     for (auto d : docs) {
//         cout << d.first << "," << d.second << endl;
//     }
//     assert (cnt == number);
//     return docs;
// }