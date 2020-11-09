#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "stack.h"

using namespace std;
string readFile();


class Maze {
private:
    string maze[7],   // store the current game state
        visited[7];// store the points we visit while playing
    Stack path;
    int r = 0, c = 0;      // point to the current position
    // function to determine if a move is valid or not
    bool validMove(int mr, int mc) {
        return ValidIndex(mr) &&
            ValidIndex(mc) &&
            playable(mr, mc) &&
            isVisited(mr, mc);
    }
    // returns false if it's a wall
    bool playable(int i, int j) { return (maze[i])[j] != '*'; }
    // returns false if it's out of index
    bool ValidIndex(int i) { return i >= 0 && i < 7; }
    // returns false if a cell is visited before
    bool isVisited(int i, int j) { return (visited[i])[j] == '.'; }
    // returns the first valid move.
    char nextMove() {
        if (validMove(r, c + 1)) { return 'r'; }
        if (validMove(r, c - 1)) { return 'l'; }
        if (validMove(r - 1, c)) { return 'u'; }
        if (validMove(r + 1, c)) { return 'd'; }
        return 'X';
    }
public:
    Maze() {
        // read the maze from a file
        string mazeString = readFile();
        int j = 0;
        // initialize maze array and visited array
        for (int i = 0; i < mazeString.length(); i++) {
            if (mazeString[i] == '\n') {
                j++;
            }
            else if (mazeString[i] == '.') {
                maze[j] += '.';
                visited[j] += '*';
            }
            else {
                maze[j] += mazeString[i];
                visited[j] += '.';
            }
        }
        // initialize the stack
        path = Stack();
    }
    // make the next valid move
    void makeMove() {
        char m = nextMove();
        path.push(m);
        r = m == 'u' ? r - 1 :
            m == 'd' ? r + 1 :
            r;
        c = m == 'l' ? c - 1 :
            m == 'r' ? c + 1 :
            c;
        (visited[r])[c] = '*';// sign the cell as visited
        // sign the cell as a path cell
        (maze[r])[c] = (maze[r])[c] == ' ' ? '.' : (maze[r])[c];
    }
    void undo() {
        if (path.isEmpty()) {
            // no moves to undo
            return;
        }
        char m = path.pop();
        (maze[r])[c] = ' ';
        r = m == 'u' ? r + 1 :
            m == 'd' ? r - 1 :
            r;
        c = m == 'l' ? c + 1 :
            m == 'r' ? c - 1 :
            c;
    }
    bool isAtStart() {
        return path.isEmpty();
    }
    bool isBlocked() {
        return nextMove() == 'X';
    }
    bool isWin() {
        return (maze[r])[c] == '$';
    }
    void printMaze() {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                cout << " " << (maze[i])[j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    cout << "\n\nQ7\n";
    // create a new object of the class Maze.
    Maze m = Maze();

    m.printMaze();
    // keep playing until win.
    while (!m.isWin()) {
        // if you can't play any moves :
        if (m.isBlocked()) {
            // and if you are not at the start position
            if (!m.isAtStart()) {
                m.undo();
            }
            else {
                // No way to solve this Maze
                cout << "No Solution!\n";
                return;
            }
        }
        else {
            // make the next valid move.
            m.makeMove();
        }
    }
    cout << "solution found!\n";
    m.printMaze();
}


string readFile() {
    ifstream inFile;
    inFile.open("maze.txt"); // open the file input.txt
    stringstream strStream;
    strStream << inFile.rdbuf(); // read the file
    return strStream.str(); // return it as string
}