#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <vector>

#include "Tree.h"

using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/

TreeNode::TreeNode(int x, int y) : left(nullptr), right(nullptr) {
//, level_(level) {
    data[0] = x;
    data[1] = y;
}

int TreeNode::getX() {
    return data[0];
}

int TreeNode::getY() {
    return data[1];
}

void BinaryDimonTree::insert(int x, int y) {
    int level = 0;
    TreeNode **node = &root;
    while (true) {
        if (*node == nullptr) {
            *node = new TreeNode(x, y);
            break;
        }
        int val = (level % 2) ? y : x;
        int node_val = (level % 2) ? (*node)->getY() : (*node)->getX();
        if (val < node_val) node = &(*node)->left;
        else node = &(*node)->right;
        level++;
    }
}

ostream &operator<<(ostream &out, const TreeNode &b) {
    out << "x: " << b.data[0] << "\ty: " << b.data[1];
    return out;
}

istream &operator>>(istream &in, BinaryDimonTree &tree) {
    int M;
    in >> M;
    vector<TreeNode *> nodes;
    for (int i = 0; i < M; i++) {
        int x, y;
        in >> x >> y;
//        tree.insert(x, y);
        nodes.push_back(new TreeNode(x, y));
    }
    tree.create(nodes, 0, nodes.size() - 1, &tree.root, 0);
    return in;
}

void BinaryDimonTree::create(vector<TreeNode *> &nodes, int l, int r, TreeNode **parent, int level) {
    if (l >= r) {
        if (l == r) {
            *parent = nodes[l];
        }
        return;
    }
    int dim = level % 2;
    sort(nodes.begin() + l, nodes.begin() + r + 1,
         [=](TreeNode *a, TreeNode *b) { return a->data[dim] < b->data[dim]; } );
    int mid = (l + r) / 2;
    *parent = nodes[mid];

    // recursively create
    level++;
    create(nodes, l, mid - 1, &(*parent)->left, level);
    create(nodes, mid + 1, r, &(*parent)->right, level);
}

BinaryDimonTree::BinaryDimonTree() : root(nullptr) {}

BinaryDimonTree::~BinaryDimonTree() {
    clear(root);
}

long long int BinaryDimonTree::distance(int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

TreeNode *BinaryDimonTree::find_nearest_node(int x, int y) {
    long long int min_distance = LONG_MAX;
    TreeNode *result = nullptr;
    recur_search(root, x, y, min_distance, &result, 0);
    return result;
}

void BinaryDimonTree::recur_search(TreeNode *cur, int x, int y, long long int &min_distance, TreeNode **guess, int level) {
    if (!cur) return;
    long long int dis = distance(cur->getX(), cur->getY(), x, y);
    if (dis < min_distance) {
//        cout << "previous dis: " << min_distance << " now dis: " << dis << endl;
        min_distance = dis;
        *guess = cur;
    } else if (dis == min_distance) {
        if (cur->getX() < (*guess)->getX() ||
            (cur->getX() == (*guess)->getX() &&
             cur->getY() < (*guess)->getY()))
            *guess = cur;
    }
    int dim = level % 2;
    int val = dim ? y : x;
    int node_val = dim ? cur->getY() : cur->getX();
    level++;
    auto next = val < node_val ? cur->left : cur->right;
    auto other = val < node_val ? cur->right : cur->left;
    recur_search(next, x, y, min_distance, guess, level);

    if (abs(val - node_val) < sqrt(min_distance)) {
        recur_search(other, x, y, min_distance, guess, level);
    }
}

void BinaryDimonTree::clear(TreeNode *node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}
