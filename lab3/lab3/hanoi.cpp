#include "termio.h"
#include <string>
#include <sstream>
#include <cassert>
#include <map>

// Do not delete the following line
char Termio::buffer[Termio::CANVAS_HEIGHT][Termio::CANVAS_WIDTH + 1];
template <typename T> class XPStack;

template<typename T> class XPStack;
template<typename T> void print_tor(int number, const XPStack<T> &s);

template <typename T>
class XPStack {
    friend void print_tor<T>(int number, const XPStack<T> &s);
public:
    XPStack() : top_(nullptr) {}

    ~XPStack() {
        while (top_) {
            pop();
        }
    }

    void push(T value) {
        top_ = new node(value, top_);
    }

    void pop() {
        auto pop_item = top_;
        top_ = top_->next_;
        delete pop_item;
    }

    T top() {
        return top_->value_;
    }

    bool is_empty() {
        return top_ == nullptr;
    }
private:
    struct node {
        T value_;
        node *next_;
        node (T value, node *next) : value_(value), next_(next) {}
    };
    node *top_;
};

map<int, int> index2layer = {
        {1, 9}, {2, 7}, {3, 5}, {4, 3}, {5, 1}
};

map<int, int> index2tor = {
        {1, 5}, {2, 20}, {3, 35}
};

template<typename T> void print_tor(int index, const XPStack<T> &s)  {
    assert(index <= 3 && index >= 1);
    typename XPStack<T>::node *node_array[5];
    int size = 0;
    auto p = s.top_;
    while (p) {
        node_array[size++] = p;
        p = p->next_;
    }
    int x_cord = index2tor.at(index);
    for (int i = 0; i < 10; i++) {
        Termio::buffer[i][x_cord] = '|';
    }
    assert(size <= 5);
    for (int i = size - 1; i >= 0; i--) {
        int y_cord = index2layer.at(size - i);
        Termio::buffer[y_cord][x_cord] = '*';
        for (int j = 1; j <= node_array[i]->value_; j++) {
            Termio::buffer[y_cord][x_cord + j] = '*';
            Termio::buffer[y_cord][x_cord - j] = '*';
        }
    }
}

void print_base() {
    for (int i = 0; i < Termio::CANVAS_WIDTH; i++) {
        Termio::buffer[Termio::CANVAS_HEIGHT - 1][i] = '-';
    }
    for (auto pair : index2tor) {
        Termio::buffer[Termio::CANVAS_HEIGHT - 1][pair.second] = '|';
    }
}

void draw_state(XPStack<int> *stacks) {
    Termio::ResetBuffer();
    for (int i = 1; i <= 3; i++) {
        print_tor(i, stacks[i - 1]);
    }
    print_base();
    Termio::Draw();
}

inline bool in_range(int number) {
    return number <= 3 && number >= 1;
}

void Move(int from, int to, XPStack<int> towers[]) {
    towers[to - 1].push(towers[from - 1].top());
    towers[from - 1].pop();
    draw_state(towers);
}

void hanoi(int n, int from, int to, int buffer, XPStack<int> towers[]) {
    if (n == 1) {
        cout << "Auto moving:"<< from << "->" << to << endl;
        Move(from, to, towers);
        return;
    }
    hanoi(n - 1, from, buffer, to, towers);
    cout << "Auto moving:"<< from << "->" << to << endl;
    Move(from, to, towers);
    hanoi(n - 1, buffer, to, from, towers);
}

void reset(XPStack<pair<int, int>> &operation_stack, XPStack<int> towers[]) {
    while (!operation_stack.is_empty()) {
        auto operation_pair = operation_stack.top();
        cout << "Auto moving:" << operation_pair.second
            << "->" << operation_pair.first << endl;
        Move(operation_pair.second, operation_pair.first, towers);
        operation_stack.pop();
    }
}

int main() {

    // ---- Example: how to use termio.h ----
    // clear screen
//    Termio::Clear();
    // reset buffer
//    Termio::ResetBuffer();
//    write_hi();
//    Termio::Draw();
    // ----------- End of example -----------
    // Your code here
    while (true) {
        string cmd;
        cout << "How many disks do you want? (1 ~ 5)" << endl;
        cin >> cmd;
        if (cmd == "Q") break;
        int disk_number;
        stringstream ss(cmd);
        ss >> disk_number;
        if (disk_number < 1 || disk_number > 5) continue;
        XPStack<int> towers[3];
        for (int i = disk_number; i >= 1; i--) {
            towers[0].push(i);
        }
        draw_state(towers);
        // entering normal mode
        XPStack<pair<int, int>> operation_stack;
        while (true) {
            int from, to;
            cout << "Move a disk. Format: x y" << endl;
            cin >> from >> to;
            if (in_range(from) && in_range(to) &&
                !towers[from - 1].is_empty() &&
                (towers[to - 1].is_empty() || towers[from - 1].top() < towers[to - 1].top())) {
                Move(from, to, towers);
                if (towers[0].is_empty() && towers[2].is_empty()) {
                    cout << "Congratulations! You win!" << endl;
                    break;
                } else {
                    operation_stack.push(make_pair(from, to));
                }
            } else if (from == 0 && to == 0) {
                // entering autoplay mode
                reset(operation_stack, towers);
                hanoi(disk_number, 1, 2, 3, towers);
                cout << "Congratulations! You win!" << endl;
                break;
            } else if (from <= 0 && to <= 0) {
                // entering advanced autoplay mode
                int a = from, b = to, c;
                cin >> c;
                reset(operation_stack, towers);
                if (a + b + c != -disk_number) continue;
                hanoi(-b - c, 1, 2, 3, towers);
                hanoi(-c, 2, 3, 1, towers);
                cout << "Congratulations! You win!" << endl;
                break;
            } else draw_state(towers);
        }
    }

    return 0;
}
