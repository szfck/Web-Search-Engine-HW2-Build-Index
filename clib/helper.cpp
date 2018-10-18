#include <iostream>
using namespace std;

class Helper{
    public:
        void hello(){
            cout << "Hello" << endl;
        }
        void read(char* doc_) {
            string doc(doc_);
            // char* p = doc;
            cout << doc << endl;
            cout << doc.size() << endl;
            cout << "hahaha" << endl;
            // while (p != '\0') {
            //     printf("%c", *p++);
            // }
            // puts("");
        }
};

// interface to python
extern "C" {
    Helper* Helper_new(){ return new Helper(); }
    void hello(Helper* helper){ helper->hello(); }
    void read(Helper* helper, char* doc){ helper->read(doc); }
}