#include <iostream>
#include <unordered_map>
#include <assert.h>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <queue>
#include "helper.h"

using namespace std;

int main() {
    VByteReader reader("../index.bin");
    int start = 106717567, end = 106717579;
    // int start = 0, end = 76179;
    // int start = 116738, end = 133473;
    int num = 10858;
    auto list = reader.read(start, end);
    // for (auto v : list) {
    //     cout << v << " ";
    // }
    cout << list[0] << endl;
    cout << list.back() << endl;

    return 0;
}