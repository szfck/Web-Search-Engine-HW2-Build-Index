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
    VByteReader reader("../output/intermediate-output-2/index-00000.bin");
    int start = 49018155, end = 49018167;
    int num = 2;
    int id = 1102785;
    auto list = reader.read(start, end);
    cout << list[0] << endl;
    cout << list.back() << endl;
    return 0;
}