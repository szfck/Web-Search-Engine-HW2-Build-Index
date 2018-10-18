#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

const string URL_TABLE = "url_table.txt";
struct Doc {
    string url;
    int size;
    Doc() {}
    Doc(string url, int size) : url(url), size(size) {}
};

unordered_map<string, int> urls;
vector<Doc> docs; 

string getTerm(const string& s, int& pos) {
    string term = "";
    while (pos < (int)s.size() && s[pos] == ' ') pos++;
    while (pos < (int)s.size() && s[pos] != ' ') {
        term += s[pos++];
    }
    return term;
}

void readPage(const string& s, ofstream& out, ofstream& url_table, map<string, vector<pair<int, int>>>& mp) {
    int pos = 0;
    string url = getTerm(s, pos);
    int page_size = stoi(getTerm(s, pos));
    if (urls.find(url) != urls.end()) {
        return;
    }
    int docId = (int)docs.size();
    urls[url] = docId;
    docs.emplace_back(url, page_size);
    url_table << docId << " " << url << " " << page_size << endl;
    string term = "";
    map<string, int> cnt;
    while ((term = getTerm(s, pos)) != "") {
        cnt[term]++;
    }
    for (auto& p : cnt) {
        string term = p.first;
        int freq = p.second;
        mp[term].emplace_back(docId, freq);
    }
} 

void read(ifstream& in, ofstream& out, ofstream& url_table) {
    map<string, vector<pair<int, int>>> mp;
    string str;
    while (getline(in, str)) {
        readPage(str, out, url_table, mp);
    }
    for (auto& p : mp) {
        string term = p.first;
        auto& list = p.second;
        string str = term;
        for(auto& pa : list) {
            int docId = pa.first;
            int freq = pa.second;
            str += " (" + to_string(docId) + "," + to_string(freq) + ")";
        }
        out << str << endl;
    }
}
int main() {
    ofstream url_table; 
    url_table.open ("url_table.txt");
    for (int i = 0; i < 100; i++) {
        string num = to_string(i);
        while ((int)num.size() < 5) num = '0' + num;
        ifstream input_file;
        ofstream output_file;
        input_file.open("intermediate-output-1/" + num + ".txt");
        output_file.open("intermediate-output-2/" + num + ".txt");
        read(input_file, output_file, url_table);
    }
    url_table.close();
    return 0;
}