
#include <iostream>
#include <queue>
using namespace std;

int main() {
    char maze[5][5] = {
        {'S', '.', '#', '.', '.'},
        {'#', '.', '#', '.', '#'},
        {'.', '.', '.', '.', '.'},
        {'.', '#', '#', '#', '.'},
        {'.', '.', '.', 'E', '.'}
    };

    int visited[5][5] = {0};
    int parentX[5][5];
    int parentY[5][5];

    int moveX[4] = {-1, 1, 0, 0};
    int moveY[4] = {0, 0, -1, 1};

    queue<pair<int, int>> q;

    int startX = 0, startY = 0;
    int endX = 4, endY = 3;

    q.push({startX, startY});
    visited[startX][startY] = 1;

    // BFS to find the exit
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (x == endX && y == endY) {
            break;
        }

        for (int i = 0; i < 4; i++) {
            int newX = x + moveX[i];
            int newY = y + moveY[i];

            if (newX >= 0 && newX < 5 &&
                newY >= 0 && newY < 5 &&
                maze[newX][newY] != '#' &&
                visited[newX][newY] == 0) {

                visited[newX][newY] = 1;
                parentX[newX][newY] = x;
                parentY[newX][newY] = y;

                q.push({newX, newY});
            }
        }
    }

    // Check whether the exit was reached
    if (visited[endX][endY] == 0) {
        cout << "No path found!\n";
        return 0;
    }

    // Trace the path backward from the exit
    int x = endX;
    int y = endY;

    while (x != startX || y != startY) {
        if (maze[x][y] != 'E') {
            maze[x][y] = '*';
        }

        int oldX = parentX[x][y];
        int oldY = parentY[x][y];

        x = oldX;
        y = oldY;
    }

    // Display the maze with the solution
    cout << "Maze Solution:\n\n";

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
