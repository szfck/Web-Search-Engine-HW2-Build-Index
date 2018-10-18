#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

class Helper{
    private:
        bool isStop(char ch) {
            if (ch == ' ' || ch == '.' || ch == ',' || ch == ':' || ch == '/') return true;
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) return false;
            if (ch >= '0' && ch <= '9') return false;
            return true;
        }
        void parse(const string& str) {
            int len = str.size();
            unordered_map<string, int> word_count;
            for (int i = 0; i < len; ) {
                while (i < len && isStop(str[i])) {
                    i++;
                }
                if (i >= len) break;
                int j = i;
                string word = "";
                while (j < len && !isStop(str[j])) {
                    word += str[j++];
                }
                word_count[word] += 1;
                i = j;
            }
            for (auto ptr : word_count) {
                cout << ptr.first << " " << ptr.second << endl;
            }
        }
    public:
        void hello(){
            cout << "Hello" << endl;
        }
        void read(char* doc_) {
            string doc(doc_);
            parse(doc);
        }
};

// interface to python
extern "C" {
    Helper* Helper_new(){ return new Helper(); }
    void hello(Helper* helper){ helper->hello(); }
    void read(Helper* helper, char* doc){ helper->read(doc); }
}