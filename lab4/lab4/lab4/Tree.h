//
// Created by Smile on 2019/4/8.
//

#ifndef C_BINARYDIMEN_TREE_H
#define C_BINARYDIMEN_TREE_H

#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/

class TreeNode {
    friend ostream &operator<<(ostream &out, const TreeNode &b);
    friend class BinaryTree;
    friend class BinaryDimonTree;

private:
    /* data */
    int data[2];

    TreeNode *left;
    TreeNode *right;
//    int level_;

public:
    /* methods */
    explicit TreeNode(int x = 0, int y = 0);
    int getX();  /* DO NOT CHANGE */
    int getY();  /* DO NOT CHANGE */
    ~TreeNode() = default; /* DO NOT CHANGE */
};


class BinaryDimonTree {
    friend istream &operator>>(istream &in, BinaryDimonTree &tree); /* DO NOT CHANGE */

private:
    /* data */
    TreeNode *root;

    void insert(int x, int y);
    long long int distance(int x1, int y1, int x2, int y2);
    void clear(TreeNode *node);
    void create(vector<TreeNode* > &nodes, int l, int r, TreeNode **parent, int level);
public:
    /* methods */
    BinaryDimonTree();          /* DO NOT CHANGE */
    ~BinaryDimonTree();
    TreeNode *find_nearest_node(int x, int y);  /* DO NOT CHANGE */

    void recur_search(TreeNode *cur, int x, int y, long long int &min_distance, TreeNode **guess, int level);

};

#endif //C_BINARYDIMEN_TREE_H
