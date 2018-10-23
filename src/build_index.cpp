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

const string END = "===============";
const string OUTPUT = "../output/"; // output dir
const string URL_TABLE_PATH = OUTPUT + "url_table.txt";
const string TERM_TABLE_PATH = OUTPUT + "term_table.txt";
map<string, int> url_map;
int ucnt;
map<string, int> term_map;
int tcnt;
vector<string> terms;
vector<pair<string, int>> urls;

void addTerm(int id, string term) {
    assert (id == (int) terms.size());
    terms.emplace_back(term);
}

void addUrl(int id, string url, int length) {
    assert (id == (int) urls.size());
    urls.emplace_back(url, length);
}

//get next term from ifstream
string getTerm(string& s, int& pos) {
    string str = "";
    while (pos < (int) s.size()) {
        char ch = s[pos++];
        if (ch >= 'A' && ch <= 'Z') {
            str += ch - 'A' + 'a';
        } else if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) {
            str += ch;
        } else {
            if (str != "") return str;
            continue;
        }
    }
    return str;
}

//get num with leading 0s
string getNum(int x) {
    string num = to_string(x);
    while ((int)num.size() < 5) num = '0' + num;
    return num;
}

string str(int x) {
    return to_string(x);
}

void build(int id) {
    string id_str = getNum(id);
    string input_filename = OUTPUT + "intermediate-output-1/" + id_str + ".txt";
    ifstream input_file;
    input_file.open(input_filename);

    string line = "";
    string url = "";
    map<int, vector<pair<int, int>>> words; 
    while (getline(input_file, line)) {
        if (line == "") continue;
        //get url
        url = line;
        if (url_map.find(url) == url_map.end()) {
            url_map[url] = ucnt++;
        } else {
            // while (getline(input_file, line) && line != END);
            // getline(input_file, line);
            // break;
        }
        int uid = url_map[url];

        map<int, int> freq; // for this doc
        // read doc
        while (getline(input_file, line)) {
            if (line == END) {
                string len;
                getline(input_file, len);
                int length = 0;
                try {
                    length = stoi(len);
                } catch (const std::exception& e) {
                    cout << url << " " << e.what() << endl;
                    break;
                }
                addUrl(uid, url, length);
                // url_table.write(uid, {url, str(length)});
                for (auto p : freq) { // in uid
                    int tid = p.first, fre = p.second;
                    words[tid].emplace_back(uid, fre);
                }
                break;
            }

            int pos = 0;
            string term = "";
            while ((term = getTerm(line, pos)) != "") {
                if (term_map.find(term) == term_map.end()) {
                    addTerm(tcnt, term);
                    // terms.push_back(term);
                    term_map[term] = tcnt++;
                    // assert ((int) terms.size() == tcnt);
                }
                int tid = term_map[term];
                freq[tid]++;
            }

        }
    }

    VByteWriter index_list(OUTPUT + "intermediate-output-2/" + "index-" + id_str + ".bin");
    TextWriter index_term(OUTPUT + "intermediate-output-2/" + "index-" + id_str + ".txt");
    for (auto& word : words) {
        int start = index_list.getOffset();
        int tid = word.first;
        auto& list = word.second;
        int number = (int) list.size();
        index_list.writeList(tid, list);
        int end = index_list.getOffset();

        // tid start end #doc
        index_term.write(tid, {str(start), str(end), str(number)});
    }
    index_list.close();
    index_term.close();
    input_file.close();
}

void init_url_and_term_table() {
    cout << "init url table ..." << endl;
    TextReader url_table(URL_TABLE_PATH);
    auto url_map_ = url_table.read();
    url_map.clear();
    urls.clear();
    for (auto p : url_map_) {
        // id url length
        int id = p.first;
        string url = p.second[0];
        int length = stoi(p.second[1]);
        url_map[url] = id;
        addUrl(id, url, length);
    }
    url_table.close();

    cout << "init term table ..." << endl;
    TextReader term_table(TERM_TABLE_PATH);
    auto term_map_ = term_table.read();
    term_map.clear();
    terms.clear();
    for (auto p : term_map_) {
        // id term
        int id = p.first;
        string term = p.second[0];
        term_map[term] = id;
        addTerm(id, term);
    }
    term_table.close();
    ucnt = (int) url_map.size();
    tcnt = (int) term_map.size();
    cout << "ucnt: " << ucnt << " tcnt: " << tcnt << endl;
}

int main(int argc, char *argv[]) {
    int lower = atoi(argv[1]), upper = atoi(argv[2]);
    init_url_and_term_table();
    int total = 100;

    cout << "start build index for file " << lower << " to " << upper - 1 << endl;
    for (int i = lower; i < upper; i++) {
        build(i);
    }

    cout << "write back to url_table..." << endl;
    // write to url_table
    // uid url length
    TextWriter url_table(URL_TABLE_PATH);
    for (int i = 0; i < (int) urls.size(); i++) {
        url_table.write(i, {urls[i].first, str(urls[i].second)});
    }
    url_table.close();

    cout << "write back to term_table..." << endl;
    // write to term table
    // tid term_str
    TextWriter term_table(TERM_TABLE_PATH);
    for (int i = 0; i < (int) terms.size(); i++) {
        term_table.write(i, {terms[i]});
    }
    term_table.close();
    return 0;
}
