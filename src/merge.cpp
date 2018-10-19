#include <iostream>
#include <unordered_map>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

// output term's doc ids and freqs to file
void output(string term, map<string, vector<pair<int, int>>>& mp, ofstream& out) {
    auto& list = mp[term];
    string str = term;
    for(auto& pa : list) {
        int docId = pa.first;
        int freq = pa.second;
        str += " (" + to_string(docId) + "," + to_string(freq) + ")";
    }
    out << str << endl;
}

// get next term from string
string getTerm(const string& s, int& pos) {
    string term = "";
    while (pos < (int)s.size() && s[pos] == ' ') pos++;
    while (pos < (int)s.size() && s[pos] != ' ') {
        term += s[pos++];
    }
    return term;
}
struct Node {
    string term;
    int id;
    Node(string term, int id) : term(term), id(id) {}
    Node() {}
    bool operator < (const Node& o) const {
        return term > o.term;
    }
};

// add term to priority queue
void addToQue(int id, priority_queue<Node>& pq, map<string, vector<pair<int, int>>>& mp, ifstream& input_file) {
    string line = "";
    if (getline(input_file, line)) {
        int pos = 0;
        string term = getTerm(line, pos);
        string str = "";
        while ((str = getTerm(line, pos)) != "") {
            str = str.substr(1, (int)str.size() - 2);
            int p = str.find(',');
            string docId = str.substr(0, p);
            string freq = str.substr(p + 1);
            mp[term].emplace_back(stoi(docId), stoi(freq));
        }
        pq.push(Node(term, id));
    }
}

// n way merge 
void nway_merge(ifstream input_file[], int n, ofstream& output_file) {
    priority_queue<Node> pq;
    map<string, vector<pair<int, int>>> mp;
    for (int i = 0; i < n; i++) {
        addToQue(i, pq, mp, input_file[i]);
    }
    while (pq.size()) {
        auto cur = pq.top();
        string term = cur.term;

        // output merged list for term 
        output(term, mp, output_file);

        while (pq.size() && term == pq.top().term) {
            int id = pq.top().id;
            pq.pop();
            addToQue(id, pq, mp, input_file[id]);
        }

        mp.erase(term);
    }
}

// get a number with leading 0s
string getNum(int x) {
    string num = to_string(x);
    while ((int)num.size() < 5) num = '0' + num;
    return num;
}

// merge files in [start, start + number) to a target file
void merge_(int step, int start, int number, int target) {
    cout << "merge step: " << step << " from " << start << " to " << start + number - 1 << endl;
    ifstream input_file[number];
    ofstream output_file;
    for (int j = 0; j < number; j++) {
        if (step == 1) {
            input_file[j].open("../intermediate-output-2/" + getNum(start + j) + ".txt");
        } else {
            input_file[j].open("../intermediate-output-3/" + getNum(start + j) + ".merge" + to_string(step - 1) + ".txt");
        }
    }
    output_file.open("../intermediate-output-3/" + getNum(target) + ".merge" + to_string(step) + ".txt");

    nway_merge(input_file, number, output_file);

    for (int j = 0; j < number; j++) {
        input_file[j].close();
    }
    output_file.close();
}
int main() {
    // [0, 300) -> [0, 30)
    for (int i = 0; i < 300; i += 10) {
        merge_(1, i, 10, i / 10);
    }
    // [0, 30) -> [0, 6)
    for (int i = 0; i < 30; i += 5) {
        merge_(2, i, 5, i / 5);
    }
    // [0, 6) -> [0, 2)
    for (int i = 0; i < 6; i += 3) {
        merge_(3, i, 3, i / 3);
    }
    // [0, 2) -> [0, 1)
    merge_(4, 0, 2, 0);
    return 0;
}