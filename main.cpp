#include <iostream>
#include "../Users/ophth/SISE-C-/include/algorithms.h"
#include "../Users/ophth/SISE-C-/include/heuristics.h"

using namespace std;

int main() {
    vector<vector<int>> puzzle = {
            {5, 1, 3, 4},
            {9, 2, 6, 8},
            {13, 14, 7, 11},
            {0, 15, 10, 12}
    };

    int width = 4;
    int height = 4;
    int maxDepth = 20;

    vector<string> pathDFS = solveDFS(puzzle, width, height, maxDepth);

    if (pathDFS.empty())
        cout << "Solution not found (DFS)" << endl;
    else {
    cout << "DFS: Found solution in " << pathDFS.size() << " moves:\n";
    for (const string& move : pathDFS)
        cout << move << " ";
    cout << endl;}

    vector<string> pathBFS = solveBFS(puzzle, width, height, maxDepth);

    if (pathBFS.empty())
        cout << "Solution not found (BFS)" << endl;
    else {
    cout << "BFS: Found solution in " << pathBFS.size() << " moves:\n";
    for (const string& move : pathBFS)
        cout << move << " ";
    cout << endl;}

    vector<string> pathHamming = solveHeuristics(puzzle, width, height, maxDepth, true);

    if (pathHamming.empty())
        cout << "Solution not found (Hamming)" << endl;
    else {
        cout << "Hamming: Found solution in " << pathHamming.size() << " moves:\n";
        for (const string& move : pathHamming)
            cout << move << " ";
        cout << endl;}

    vector<string> pathManhattan = solveHeuristics(puzzle, width, height, maxDepth, false);

    if (pathManhattan.empty())
        cout << "Solution not found (Hamming)" << endl;
    else {
        cout << "Hamming: Found solution in " << pathManhattan.size() << " moves:\n";
        for (const string& move : pathManhattan)
            cout << move << " ";
        cout << endl;}

    return 0;
}
