#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

const int BLOCK = 128;
class Writer {
    protected:
        int offset;
        ofstream out;
    public:
        Writer();
        Writer(string file_name);
        void open(string file_name);
        void close();
        int getOffset();
        void vwrite(int x);
        void swrite(string s);
        void vwriteList(int tid, const vector<pair<int, int>>& list);
};

struct Url {
    string url;
    int uid, length;
    Url() {}
    Url(int uid, string url, int length) : uid(uid), url(url), length(length) {}
};

struct Term {
    int tid;
    string term;
    Term() {}
    Term(int tid, string term) : 
        tid(tid), term(term) {}
};

struct Index {
    int tid, start, end, number;
    Index() {}
    Index(int tid, int start, int end, int number) : 
        tid(tid), start(start), end(end), number(number) {}
};

struct Doc {
    int uid, freq;
    Doc() {}
    Doc(int uid, int freq) : uid(uid), freq(freq) {}
};

class Reader {
    protected:
        ifstream in;
    public:
        Reader();
        Reader(string file_name);
        void open(string file_name);
        void close();

        vector<int> vread(int start, int end);
        vector<Doc> vreadList(int tid, int start, int end, int number);
        vector<Url> urlread();
        vector<Term> termread();
        vector<Index> indexread();

};

// class TextWriter : public Writer {
//     public:
//         TextWriter() {};
//         TextWriter(string file_name);

//         void write(int key, const vector<string>& list);
// };

// class TextReader : public Reader {
//     public:
//         TextReader() {};
//         TextReader(string file_name);
//         map<int, vector<string>> read();
// };

// const int BLOCK = 128;
// class VByteWriter : public Writer {
//     private:
//         // ofstream out;
//         int offset;
//         // const int BLOCK = 128;
//     public:
//         VByteWriter() {};
//         VByteWriter(string file_name);

//         // get current offset
//         int getOffset();

//         // wirte long long int to a binary file with varbyte encoding
//         void write(int x);

//         // write tid with list of (docId, freq) pair
//         void writeList(int tid, const vector<pair<int, int>>& list);

//         // close file
//         // void close();
// };

// class VByteReader : public Reader {
//     private:
//         int offset;
//         // read bytes from binary file in range [start, end)
//         // and decode to long long vector
//         // const int BLOCK = 128;
//     public:
//         VByteReader() {};
//         VByteReader(string file_name);

//         int getOffset();

//         // int getNext(int& start);
//         vector<int> read(int start, int end);
//         vector<pair<int, int>> read(int tid, int start, int end, int number);

//         // // close file
//         // void close();
// };