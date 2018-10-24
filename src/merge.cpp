#include <iostream>
#include <unordered_map>
#include <string>
#include "helper.h"
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

struct Node {
    int tid, fid;
    Node(int tid, int fid) : tid(tid), fid(fid) {}
    Node() {}
    bool operator < (const Node& o) const {
        return tid > o.tid;
    }
};

// add term to priority queue
void addToQue(int fid, priority_queue<Node>& pq, map<int, vector<pair<int, int>>>& mp, VByteReader& input_file, int& start, int& end) {
    int tid = input_file.getNext(start);
    int number = input_file.getNext(start);
    auto list = input_file.read(tid, start - 2, start + number, number);
    // string line = "";
    // if (getline(input_file, line)) {
    //     int pos = 0;
    //     string term = getTerm(line, pos);
    //     string str = "";
    //     while ((str = getTerm(line, pos)) != "") {
    //         str = str.substr(1, (int)str.size() - 2);
    //         int p = str.find(',');
    //         string docId = str.substr(0, p);
    //         string freq = str.substr(p + 1);
    //         mp[term].emplace_back(stoi(docId), stoi(freq));
    //     }
    pq.push(Node(tid, fid));
    // }
}

void output(int tid, map<int, vector<pair<int, int>>>& mp, VByteWriter& output_file) {
    output_file.writeList(tid, mp[tid]);
}

// n way merge 
void nway_merge(VByteReader input_file[], int n, VByteWriter& output_file) {
    priority_queue<Node> pq;
    map<int, vector<pair<int, int>>> mp; // term_id [(doc_id, freq) ..]
    vector<int> start(n, 0);
    vector<int> end(n);
    for (int i = 0; i < n; i++) {
        end[i] = input_file[i].getFileSize();
    }
    for (int i = 0; i < n; i++) {
        addToQue(i, pq, mp, input_file[i], start[i], end[i]);
    }
    while (pq.size()) {
        auto cur = pq.top();
        // string term = cur.term;
        int tid = cur.tid;

        // output merged list for term 
        output(tid, mp, output_file);

        while (pq.size() && tid == pq.top().tid) {
            int fid = pq.top().fid;
            pq.pop();
            addToQue(fid, pq, mp, input_file[fid]);
        }

        mp.erase(tid);
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
    // ifstream input_file[number];
    // ofstream output_file;
    VByteReader input_file[number];
    for (int j = 0; j < number; j++) {
        if (step == 1) {
            input_file[j].open("../intermediate-output-2/" + getNum(start + j) + ".bin");
            // input_file[j].open("../intermediate-output-2/" + getNum(start + j) + ".bin");
        } else {
            input_file[j] = VByteReader("../intermediate-output-3/" + getNum(start + j) + ".merge" + to_string(step - 1) + ".bin");
            // input_file[j].open("../intermediate-output-3/" + getNum(start + j) + ".merge" + to_string(step - 1) + ".bin");
        }
    }
    // output_file.open("../intermediate-output-3/" + getNum(target) + ".merge" + to_string(step) + ".txt");
    VByteWriter output_file("../intermediate-output-3/" + getNum(target) + ".merge" + to_string(step) + ".bin");

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