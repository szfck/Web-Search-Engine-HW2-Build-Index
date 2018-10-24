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

string str(int x) {
    return to_string(x);
}
// add term to priority queue
void addToQue(int fid, priority_queue<Node>& pq, map<int, vector<Doc>>& mp, Reader& indexes, const  vector<Index>& term_index_vec, int& counter) {
    cout << (int) term_index_vec.size() << endl;
    if (counter >= (int) term_index_vec.size()) return;
    cout << "nway merge ........... " << endl;
    int idx = counter++;
    auto index = term_index_vec[idx];
    int tid = index.tid, start = index.start, end = index.end, number = index.number;
    auto docs = indexes.vreadList(tid, start, end, number);
    for (auto doc : docs) {
        mp[tid].push_back(doc);
    }
    // int tid = indexes.getNext(start);
    // int number = indexes.getNext(start);
    // auto list = indexes.read(tid, start - 2, start + number, number);
    pq.push(Node(tid, fid));
}

void output(int tid, map<int, vector<Doc>>& mp, Writer& merged_index, Writer& merged_term_index) {
    // cout << "output : " << tid << endl;
    int start = merged_index.getOffset();
    merged_index.vwriteList(tid, mp[tid]);
    int end = merged_index.getOffset();
    merged_term_index.swrite(str(tid) + " " + str(start) + " " + str(end) + " " + str(mp[tid].size()) + '\n');
}

// n way merge 
void nway_merge(Reader indexes[], Reader term_indexes[], int n, Writer& merged_index, Writer& merged_term_index) {
    priority_queue<Node> pq;
    map<int, vector<Doc>> mp; // term_id [(doc_id, freq) ..]
    vector<Index> term_indexes_vec[n];
    vector<int> counter(n, 0);
    cout << "nway merge " << n << endl;
    for (int i = 0; i < n; i++) {
        term_indexes_vec[i] = term_indexes[i].indexread();
    }
    for (int i = 0; i < n; i++) {
    cout << "nway merge " << n << endl;
        addToQue(i, pq, mp, indexes[i], term_indexes_vec[i], counter[i]);
    }
    while (pq.size()) {
        auto cur = pq.top();
        // string term = cur.term;
        int tid = cur.tid;
        cout << cur.tid << " " << cur.fid << endl;

        // output merged list for term 
        output(tid, mp, merged_index, merged_term_index);

        while (pq.size() && tid == pq.top().tid) {
            int fid = pq.top().fid;
            pq.pop();
            addToQue(fid, pq, mp, indexes[fid], term_indexes_vec[fid], counter[fid]);
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
    Reader indexes[number];
    Reader term_indexes[number];
    for (int j = 0; j < number; j++) {
        string index_path = "";
        string term_index_path = "";
        if (step == 1) {
            index_path = "../output/intermediate-output-2/index-" + getNum(start + j) + ".bin";
            term_index_path = "../output/intermediate-output-2/index-" + getNum(start + j) + ".txt";
        } else {
            index_path = "../output/intermediate-output-3/index-" + getNum(start + j) + ".merge" + to_string(step - 1) + ".bin";
            term_index_path = "../output/intermediate-output-3/index-" + getNum(start + j) + ".merge" + to_string(step - 1) + ".txt";
        }
        cout << index_path << endl;
        cout << term_index_path << endl;
        indexes[j].open(index_path);
        term_indexes[j].open(term_index_path);
        // term_indexes[j].indexrea
        // Reader tmp(term_index_path);
        // tmp.indexread();
    }
    cout << "start merging ... " << endl;
    string merge_index_path = "../output/intermediate-output-3/index-" + getNum(target) + ".merge" + to_string(step) + ".bin";
    string merge_term_index_path = "../output/intermediate-output-3/index-" + getNum(target) + ".merge" + to_string(step) + ".txt";
    cout << merge_index_path << endl;
    cout << merge_term_index_path << endl;
    Writer merged_index(merge_index_path);
    Writer merged_term_index(merge_term_index_path);

    nway_merge(indexes, term_indexes, number, merged_index, merged_term_index);

    cout << "finished .. " << endl;
    for (int j = 0; j < number; j++) {
        indexes[j].close();
        term_indexes[j].close();
    }
    merged_index.close();
    merged_term_index.close();
}
int main() {
    merge_(1, 1000, 2, 1002);
    // [0, 300) -> [0, 30)
    // for (int i = 0; i < 300; i += 10) {
    //     merge_(1, i, 10, i / 10);
    // }
    // // [0, 30) -> [0, 6)
    // for (int i = 0; i < 30; i += 5) {
    //     merge_(2, i, 5, i / 5);
    // }
    // // [0, 6) -> [0, 2)
    // for (int i = 0; i < 6; i += 3) {
    //     merge_(3, i, 3, i / 3);
    // }
    // // [0, 2) -> [0, 1)
    // merge_(4, 0, 2, 0);
    return 0;
}