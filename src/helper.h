#include <string>
#include <fstream>
#include <vector>
using namespace std;

class VByteWriter {
    private:
        ofstream out;
        int offset;
    public:
        VByteWriter(string file_name);

        int getOffset();

        void write(long long x);
        void close();
};

class VByteReader {
    private:
        ifstream in;
    public:
        VByteReader(string file_name);

        vector<long long> read(int start, int end);
        void close();
};