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

char ch;
string getTerm(ifstream& in) {
    string str = "";
    while (true) {
        str += ch;
        in.get(ch);
        if (ch == ' ' || ch == '\n') return str;
    }
}
// string getTerm(const string& s, int& pos) {
//     string term = "";
//     while (pos < (int)s.size() && s[pos] == ' ') pos++;
//     while (pos < (int)s.size() && s[pos] != ' ') {
//         term += s[pos++];
//     }
//     return term;
// }

string getNum(int x) {
    string num = to_string(x);
    while ((int)num.size() < 5) num = '0' + num;
    return num;
}

struct Term {
    string str;
    int start, end;
    int number;
    Term() {}
    Term(string str, int start, int end, int number) : str(str), start(start), end(end), number(number) {}
};

int start;
void outVByte(int x, ofstream& out) {
    vector<int> digits;
    if (x == 0) {
        digits.push_back(0);
    }
    while (x > 0) {
        digits.push_back(x % 128);
        x /= 128;
    }
    // cout << x << endl;
    for (int i = (int)digits.size() - 1; i > 0; i--) {
        // cout << digits[i] << endl;
        out << (unsigned char)(128 | digits[i]);
        start++;
    }
        // cout << digits[0] << endl;
    out << (unsigned char)(digits[0]);
    start++;
}
int main() {
    ifstream input_file;
    string input_filename = "intermediate-output-3/" + getNum(0) + ".merge4.txt";
    // string input_filename = "intermediate-output-3/test.txt";
    input_file.open(input_filename);
    ofstream term_table, index;
    term_table.open("term_table.txt");
    index.open("index.bin");

    int BLOCK = 128;

    string line = "";
    int term_id = -1;
    start = 0;

    // if (!input_file.get(ch)) {
    //     return 0;
    // }
    // while (getline(input_file, line)) {
        int T = 0;
    while (true) {
        if (!input_file.get(ch)) {
            break;
        }
        // if (T++ > 1) break;
        vector<int> docid;
        vector<int> freq;
        string str = "";

            // cout << ch << endl;
        string term = getTerm(input_file);
        // cout << term << endl;
        if (term == "") break;
        // cout << line << endl;
        term_id++;
        int pos = 0;
        // input_file.get(ch);
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
            // int d = stoi(str.substr(0, p));
            // int f = stoi(str.substr(p + 1));
            docid.push_back(stoi(docIdStr));
            freq.push_back(stoi(freqStr));
            input_file.get(ch);
        }
        // while ((term = getTerm(line, pos)) != "") {
        //     str = str.substr(1, (int)str.size() - 2);
        //     int p = str.find(',');
        // }
        int number = (int)docid.size();
        // cout << term << " " << term_id << endl;
        // cout << number << endl;
        // term_id {docid...} {freq...}
        int startByte = start;
        // cout << "!" << endl;
        outVByte(term_id, index);
        for (int i = 0; i < number; i += BLOCK) {
            for (int j = 0; j < BLOCK && i + j < number; j++) {
                outVByte(docid[i + j], index);
            }
            for (int j = 0; j < BLOCK && i + j < number; j++) {
                outVByte(freq[i + j], index);
            }
        }
        outVByte(number, index);

        int endByte = start - 1;
        // cout << term << endl;
        term_table << term_id << " " << term << " " << startByte << " " << endByte << " " << number << endl;
    }
    return 0;
}