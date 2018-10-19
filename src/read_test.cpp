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
    // this is a test : decode info from binarry file and check value
    VByteReader reader("../index.bin");
    int start = 106717567, end = 106717579;
    int num = 10858;
    auto list = reader.read(start, end);
    cout << list[0] << endl;
    cout << list.back() << endl;
    return 0;
}