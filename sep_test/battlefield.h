#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include "box.h"

#define N 100
class BattleField
{
public:
    BattleField();
    ~BattleField();
    Box *field[N][N];
    int maze[N + 2][N + 2];
    // find path in this function
    bool findPath();
    void DFS(int y, int x);
};

#endif // BATTLEFIELD_H
