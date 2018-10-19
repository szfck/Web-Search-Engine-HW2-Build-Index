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

        // get current offset
        int getOffset();

        // wirte long long int to a binary file with varbyte encoding
        void write(long long x);

        // close file
        void close();
};

class VByteReader {
    private:
        ifstream in;
    public:
        VByteReader(string file_name);

        // read bytes from binary file in range [start, end)
        // and decode to long long vector
        vector<long long> read(int start, int end);

        // close file
        void close();
};