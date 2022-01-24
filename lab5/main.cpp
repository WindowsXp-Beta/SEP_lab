#include <iostream>
#include <string>
using namespace std;

#include "cuckoo.h"

int main() {
//    freopen("../test.in", "r", stdin);
    int M;
    cin >> M;
    string cmd;
    CuckooHashTable cuckooHashTable(8);
    for (int i = 0; i < M; i++) {
        cin >> cmd;
        if (cmd == "Insert") {
            int key, value;
            cin >> key >> value;
            cuckooHashTable.insert(key, value);
//            cuckooHashTable.print_table();
        } else if (cmd == "Lookup") {
            int key;
            cin >> key;
            cuckooHashTable.lookup(key);
        } else if (cmd == "Delete") {
            int key;
            cin >> key;
            cuckooHashTable.delete_(key);
        } else {
            throw "cmd Not Defined";
        }
    }
    return 0;
}
