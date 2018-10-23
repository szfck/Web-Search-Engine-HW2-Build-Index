#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class Writer {
    protected:
        ofstream out;
    public:
        Writer(string file_name);

        // close file
        void close();
};

class Reader {
    protected:
        ifstream in;
    public:
        Reader(string file_name);

        // close file
        void close();
};

// class Term {
//     int start, end, number;
//     Term() {}
//     Term(int start, int end, int number) : start(start), end(end), number(number) {}
// };

// class Url {
//     string url;
// }

// template<class T>
class TextWriter : public Writer {
    public:
        TextWriter(string file_name);

        void write(int key, const vector<string>& list);
};

// template<class T>
class TextReader : public Reader {
    // private:
        // string getNext(const string& s, int& pos);
    public:
        TextReader(string file_name);
        map<int, vector<string>> read();
};

class VByteWriter : public Writer {
    private:
        // ofstream out;
        int offset;
        const int BLOCK = 128;
    public:
        VByteWriter(string file_name);

        // get current offset
        int getOffset();

        // wirte long long int to a binary file with varbyte encoding
        void write(int x);

        // write tid with list of (docId, freq) pair
        void writeList(int tid, const vector<pair<int, int>>& list);

        // close file
        // void close();
};

class VByteReader : public Reader {
    // private:
    //     ifstream in;
    public:
        VByteReader(string file_name);

        // read bytes from binary file in range [start, end)
        // and decode to long long vector
        vector<int> read(int start, int end);

        // // close file
        // void close();
};