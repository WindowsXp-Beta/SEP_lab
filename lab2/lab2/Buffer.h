#pragma once

#include <string>

using std::string;

struct ListNode {
    string content_;
    ListNode *next_;
    ListNode(string content, ListNode *next) :
            content_(content), next_(next) {}
};

class List {
private:
    ListNode *head_;
    ListNode *at(int lineNumber);
public:
    List() : head_(nullptr) {}
    ~List();
    int insert(const string &text, int lineNumber);
    int deleteLines(int from, int to);
    int showLines(int from, int to);
    void writeToFile(const string &filename) const;
    const string &moveToLine(int lineNumber) ;
};

class Buffer {
private:
    int currentLineNum;
    // TODO: add a List here for storing the input lines
    List *list;
public:
    Buffer();
    ~Buffer();

    void writeToFile(const string &filename) const;

    const string &moveToLine(int idx);

    void showLines(int from, int to);

    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);
};
