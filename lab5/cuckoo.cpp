//
// Created by 魏新鹏 on 2022/1/24.
//

#include "cuckoo.h"
#include <iostream>

using namespace std;

CuckooHashTable::CuckooHashTable(int size) : size_(size) {
    hashTables[0] = new Node[size_];
    hashTables[1] = new Node[size_];
}

CuckooHashTable::~CuckooHashTable() {
    delete hashTables[0];
    delete hashTables[1];
}

CuckooHashTable::Node CuckooHashTable::kick(int which_table, int key, int value) {
    int hash_value;
    switch (which_table) {
        case 1:
            hash_value = hash1(key);
            break;
        case 2:
            hash_value = hash2(key);
            break;
        default:
            throw "Only two hash tables";
    }
    Node kicked = hashTables[which_table - 1][hash_value];
    hashTables[which_table - 1][hash_value].key_ = key;
    hashTables[which_table - 1][hash_value].value_ = value;
    if (kicked.key_ != -1) cout << "Kick " << kicked.key_ << " with " << key
        << " in table " << which_table - 1 << ' ' << hash_value << endl;
    return kicked;
}

void CuckooHashTable::lookup(int key) {
    int h1 = hash1(key);
    if (key == hashTables[0][h1].key_) {
        cout << hashTables[0][h1].value_ << endl;
    } else {
        int h2 = hash2(key);
        if (key == hashTables[1][h2].key_) {
            cout << hashTables[1][h2].value_ << endl;
        } else {
            cout << "Key Not Found\n";
        }
    }
}

void CuckooHashTable::delete_(int key) {
    int h1 = hash1(key);
    if (key == hashTables[0][h1].key_) {
        hashTables[0][h1].key_ = -1;
        hashTables[0][h1].value_ = 0;
    } else {
        int h2 = hash2(key);
        if (key == hashTables[1][h2].key_) {
            hashTables[1][h2].key_ = -1;
            hashTables[1][h2].value_ = 0;
        } else {
            cout << "Key Not Found\n";
        }
    }
}

void CuckooHashTable::insert(int key, int value) {
    if (key == -1) return;// just in case
    int h1 = hash1(key);
    int h2 = hash2(key);
    if (hashTables[0][h1].key_ == -1 || hashTables[0][h1].key_ == key) {
        hashTables[0][h1].key_ = key;
        hashTables[0][h1].value_ = value;
    }
    else if (hashTables[1][h2].key_ == -1 || hashTables[1][h2].key_ == key) {
        hashTables[1][h2].key_ = key;
        hashTables[1][h2].value_ = value;
    } else {
        int kick_count = 0;
        int which_table = 1;
        while (true) {
            auto kicked_node = kick(which_table, key, value);
            if (kicked_node.key_ == -1) break;
            if (++kick_count >= 2 * size_) {
                cout << "Loop Detect\n";
                rehash();
                insert(kicked_node.key_, kicked_node.value_);
                break;
            }
            key = kicked_node.key_;
            value = kicked_node.value_;
            which_table = 3 - which_table;
        }
    }
}

void CuckooHashTable::rehash() {
    int old_size = size_;
    size_ *= 2;
    Node *oldHashTables[2] = {hashTables[0], hashTables[1]};
    hashTables[0] = new Node[size_];
    hashTables[1] = new Node[size_];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < old_size; j++) {
            int key = oldHashTables[i][j].key_;
            if (key != -1) {
                insert(key, oldHashTables[i][j].value_);
            }
        }
    }
    delete [] oldHashTables[0];
    delete [] oldHashTables[1];
}

void CuckooHashTable::print_table() {

    for (int i = 0; i < 2; i++) {
        cerr << "table: " << i << '\t';
        for (int j = 0; j < size_; j++) {
            int key = hashTables[i][j].key_;
            if (key != -1) {
                cerr << "index: " << j << " key: " << key
                    << " value: " << hashTables[i][j].value_ << '\t';
            }
        }
    }
}