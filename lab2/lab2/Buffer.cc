#include <fstream>
#include <iostream>
#include <cassert>
#include "Buffer.h"
#include "error.h"

//TODO: your code here
//implement the functions in ListBuffer

Buffer::Buffer() : list(new List()), currentLineNum(0) {}

Buffer::~Buffer() {
    delete list;
}

void Buffer::writeToFile(const string &filename) const {
    list->writeToFile(filename);
}

void Buffer::showLines(int from, int to) {
    if (from > to && to != -1) throw EdException(EdException::Type::NumberRangeError);
    // to = -1 means last line
    currentLineNum = list->showLines(from, to);
}

void Buffer::deleteLines(int from, int to) {
    if (from > to) throw EdException(EdException::Type::DeleteRangeError);
    currentLineNum = list->deleteLines(from, to);
}

void Buffer::insertLine(const string &text) {
    currentLineNum = list->insert(text, currentLineNum - 1);
}

void Buffer::appendLine(const string &text) {
    currentLineNum = list->insert(text, currentLineNum);
}

const string &Buffer::moveToLine(int idx) {
    auto &line = list->moveToLine(idx);
    currentLineNum = idx;
    return line;
}

List::~List() {
    auto cur = head_;
    while (cur != nullptr) {
        auto next = cur->next_;
        delete cur;
        cur = next;
    }
}

ListNode *List::at(int lineNumber) {
    if (!head_ || lineNumber <= 0) throw EdException(EdException::Type::LineNumberOutOfRange);
    auto cur = head_;
    while (--lineNumber) {
        cur = cur->next_;
        if (cur == nullptr) throw EdException(EdException::Type::LineNumberOutOfRange);
    }
    return cur;
}

// insert the line after lineNumber
int List::insert(const string &text, int lineNumber) {
    if (lineNumber <= 0) {
        head_ = new ListNode(text, head_);
        return 1;
    } else {
        auto cur = at(lineNumber);
        cur->next_ = new ListNode(text, cur->next_);
        return lineNumber + 1;
    }
}

int List::deleteLines(int from, int to) {
    ListNode **start = nullptr;
    if (from == 1)
        start = &head_;
    else if (from > 1)
        start = &at(from - 1)->next_;
    else throw EdException(EdException::Type::DeleteRangeError);
    at(to);
    for (int i = from; i <= to; i++) {
        auto deleting = *start;
        *start = (*start)->next_;
        delete deleting;
    }
    return *start == nullptr ? from - 1 : from;
}

int List::showLines(int from, int to) {
    assert(from <= to || to == -1);
    if (to == -1 && head_ == nullptr) throw EdException(EdException::Type::NumberRangeError);
    auto start = at(from);
    if (to == -1) {
        int i = from;
        for (; start != nullptr; i++, start = start->next_) {
            std::cout << i << '\t' << start->content_ << '\n';
        }
        return i - 1;
    } else {
        at(to); // check if lineNumber out of range
        for (int i = from; i <= to; i++, start = start->next_) {
            assert(start);
            std::cout << i << '\t' << start->content_ << '\n';
        }
        return to;
    }
}

void List::writeToFile(const string &filename) const {
    std::ofstream outFile(filename, std::ofstream::out);
    auto cur = head_;
    while (cur) {
        outFile << cur->content_ << '\n';
        cur = cur->next_;
    }
    std::cout << outFile.tellp() << " byte(s) written\n";
}

const string &List::moveToLine(int lineNumber) {
    return at(lineNumber)->content_;
}
