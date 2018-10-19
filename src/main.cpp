#include <iostream>
#include "helper.h"
using namespace std;
int main() {
    vector<int> arr = {100000, 2, 3, 4};
    VByteWriter writer("test.bin");
    for (auto v : arr) {
        writer.write(v);
    }
    cout << writer.getOffset() << endl;
    writer.close();
    VByteReader reader("test.bin");
    auto list = reader.read(0, 6);
    for (auto v : list) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}