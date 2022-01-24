#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>

#include "Tree.h"

using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/

TreeNode::TreeNode(int x, int y) : left(nullptr), right(nullptr) {
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
    TreeNode *&node = root;
    while (true) {
        if (!node) {
            node = new TreeNode(x, y);
            break;
        }
        int val = (level % 2) ? y : x;
        int node_val = (level % 2) ? node->getY() : node->getX();
        if (val > node_val) node = node->right;
        else if (val < node_val) node = node->left;
        else {
            int other_dim = node_val == node->getX() ? 0 : 1;
            int inserting_other_dim = val == x ? y : x;
            node->data[other_dim] = inserting_other_dim;
            return;
        }
        level++;
    }
}

istream &operator>>(istream &in, BinaryDimonTree &tree) {
    int M;
    in >> M;
    for (int i = 0; i < M; i++) {
        int x, y;
        in >> x >> y;
        tree.insert(x, y);
    }
}
