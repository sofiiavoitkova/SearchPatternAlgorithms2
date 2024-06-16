#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

const int SIZE = 10;

struct Wizard {
    int x, y;
    int speed;
};

struct Cell {
    int x, y;
    int distance;
};

int labyrinth[SIZE][SIZE] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

bool visited[SIZE][SIZE];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool isValid(int x, int y, int rows, int cols) {
    if (x < 0 || x >= rows) return false;
    if (y < 0 || y >= cols) return false;
    if (labyrinth[x][y] != 0) return false;
    if (visited[x][y]) return false;
    return true;
}

int bfs(int startX, int startY, int rows, int cols, int exitX, int exitY) {
    memset(visited, false, sizeof(visited));
    queue<Cell> q;
    q.push({startX, startY, 0});
    visited[startX][startY] = true;

    while (!q.empty()) {
        Cell current = q.front();
        q.pop();

        if (current.x == exitX && current.y == exitY) {
            return current.distance;
        }

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY, rows, cols)) {
                visited[newX][newY] = true;
                q.push({newX, newY, current.distance + 1});
            }
        }
    }

    return -1;
}

int main() {
    int rows = 10;
    int cols = 10;

    int exitX = 4;
    int exitY = 4;

    Wizard wizards[3] = {
            {1, 1, 2},
            {4, 4, 3},
            {3, 3, 1}
    };

    int winner = -1;
    bool foundPath = false;
    int minTime = -1;

    for (int i = 0; i < 3; ++i) {
        int distance = bfs(wizards[i].x - 1, wizards[i].y - 1, rows, cols, exitX - 1, exitY - 1);
        int time = (distance + wizards[i].speed - 1) / wizards[i].speed;
        if (distance != -1 || time != -1) {
            if (!foundPath || time < minTime) {
                winner = i;
                foundPath = true;
                minTime = time;
            }
            cout << "Wizard " << (i + 1) << ":  "<< endl;
            cout << " distance - " << distance <<  endl;
            cout <<" time - " << time << endl;
        } else {
            cout << "Wizard " << (i + 1) << " cannot reach the exit." << endl;
        }
    }

    if (winner == -1) {
        cout << "No wizard can reach the exit." << endl;
    } else {
        cout << "Wizard " << (winner + 1) << " is winner" << endl;
    }

    return 0;
}
