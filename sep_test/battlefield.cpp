#include "battlefield.h"
#include <cstring>
#include <QQueue>
#include <vector>
#include <QDebug>
using namespace std;

vector< pair<int, int> >  path;//动态数组path用于存储路径
bool flag = true;//用于递归终点返回
int dir[4][2] = {//方向数组
    {- 1, 0},
    {1, 0},
    {0, - 1},
    {0, 1}
};


void BattleField::DFS(int y, int x){
    if(!flag) return;
    if(x == 100){
        path.push_back(make_pair(y,x));
        flag = false;
        return;
    }
    if(maze[y][x] == 1) return;
    //上述判断语句检测是否到达递归终点

    maze[y][x] = 1;//标记已访问
    path.push_back(make_pair(y, x));//将此顶点加入路径当中
    for(int i = 0; i < 4 && flag; i++){//向四个方向继续递归寻找
        DFS(y + dir[i][0], x + dir[i][1]);
    }
    if(flag) path.pop_back();//依据此顶点未找到则退出路径
}

// find path in this function
// you can add other functions to solve this problem
// you should print the path if you can find one
// if you can find one, return true, otherwise false
struct Node{
    int row;
    int column;
    Node(int row = 0, int column = 0):row(row), column(column){}
};

bool BattleField::findPath(){
    for (int i = 0; i < N; i++){//遍历col=0这列
        if(field[0][i]->type != Box::Enemy){
            maze[i + 1][1] = 1;
            path.push_back(make_pair(i + 1, 1));
            for(int k = 0; k < 4; k++){
                qDebug() << maze[1 + dir[k][1]][i + 1 + dir[k][0]];
                DFS(i + 1 + dir[k][0], 1 + dir[k][1]);//递归地对四个方向进行查找
            }
            if(!flag) {
                qDebug() << path.size();
                for(auto it = path.begin(); it != path.end(); it++){
                    qDebug() << it->second - 1 << " " << it->first - 1;
                    field[it->second - 1][it->first - 1]->type = Box::Path;
                }
                return true;
            }
            maze[i + 1][1] = 0;
        }
    }
    return false;
}

BattleField::BattleField(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            field[i][j] = new Box(i, j);
        }
    }
    for(int i = 0; i < N + 2; i++){
        for (int j = 0; j < N + 2; j++){
            maze[i][j] = 0;
        }
    }
    for(int i = 0; i < N + 2; i++){
        maze[0][i] = 1;
        maze[N + 1][i] = 1;
    }
    for(int i = 0; i < N + 2; i++){
        maze[i][0] = 1;
        maze[i][N + 1] = 1;
    }
}

BattleField::~BattleField(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            delete field[i][j];
        }
    }
}
