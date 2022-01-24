//
// Created by 魏新鹏 on 2022/1/24.
//

#ifndef LAB5_CUCKOO_H
#define LAB5_CUCKOO_H

class CuckooHashTable {
public:
    explicit CuckooHashTable(int size);
    ~CuckooHashTable();
    void insert(int key, int value);
    void lookup(int key);
    void delete_(int key);
    struct Node {
        int key_;
        int value_;
        explicit Node(int key = -1, int value= 0) : key_(key), value_(value) {}
    };
    void print_table();
private:
    Node kick(int which_table, int key, int value);
    void rehash();
    int hash1(int key) const { return key % size_; }
    int hash2(int key) const { return (key / size_) % size_; }
    int size_;
    Node *hashTables[2];

};
#endif //LAB5_CUCKOO_H
