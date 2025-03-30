//
// Created by ophth on 20.03.2025.
//

#include "../../Users/ophth/SISE-C-/include/algorithms.h"

using namespace std;

const vector<pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct State{
    vector<vector<int>> board;
    int zeroX, zeroY;
    vector<string> path;
    int hValue=0;

    State(vector<vector<int>> b, int x, int y, vector<string> p)
    :board(std::move(b)), zeroX(x), zeroY(y), path(std::move(p)) {}

    bool operator<(const State& other) const{
        return board < other.board;
    }
};

vector<State> getNextStates(const State& state, int width, int height){
    vector<State> nextStates;
    for(int i = 0; i<4; i++){
        int newX = state.zeroX + moves[i].first;
        int newY = state.zeroY + moves[i].second;

        if(0 <= newX && newX < height && 0<= newY && newY < width){
            vector<vector<int>> newBoard = state.board;
            swap(newBoard[state.zeroX][state.zeroY], newBoard[newX][newY]);

            vector<string> newPath(state.path.begin(), state.path.end());
            newPath.emplace_back(i == 0 ? "U" : i == 1 ? "D" : i == 2 ? "L" : "R");

            nextStates.emplace_back(newBoard, newX, newY, newPath);
        }
    }
    return nextStates;
}

vector<string> solveDFS(vector<vector<int>>& startState, int width, int height, int maxDepth){
    vector<vector<int>> goalBoard(height, vector<int>(width));
    int number = 1;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            goalBoard[i][j] = number++;
        }
    }
    goalBoard[height-1][width-1] = 0;

    int zeroX, zeroY;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (startState[i][j] == 0) {
                zeroX = i;
                zeroY = j;
            }

    stack<State> stack;
    stack.emplace(startState, zeroX, zeroY, vector<string>{});

    /*set<vector<vector<int>>> visited;
    visited.insert(startState);*/

    while (!stack.empty()) {
        State currentState = stack.top();
        stack.pop(); //musi być tak bo pop nie zwraca wartości.

        if(currentState.board == goalBoard)
            return currentState.path;

        if(currentState.path.size() >= maxDepth)
            continue;

        vector<State> nextStates = getNextStates(currentState, width, height);
        for(const State& nextState : nextStates){
            /*if(visited.find(nextState.board) == visited.end()){
                visited.insert(nextState.board);*/
                stack.push(nextState);
            //}
        }
    }

    return vector<string>{};
}



vector<string> solveBFS(vector<vector<int>>& startState, int width, int height, int maxDepth){
    vector<vector<int>> goalBoard(height, vector<int>(width));
    int number = 1;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            goalBoard[i][j] = number++;
        }
    }
    goalBoard[height-1][width-1] = 0;

    int zeroX, zeroY;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (startState[i][j] == 0) {
                zeroX = i;
                zeroY = j;
            }

    queue<State> q;
    q.emplace(startState, zeroX, zeroY, vector<string>{});

    set<vector<vector<int>>> visited;
    visited.insert(startState);

    while(!q.empty()){
        State currentState = q.front();
        q.pop();

        if(currentState.board == goalBoard)
            return currentState.path;

        if(currentState.path.size() >= maxDepth)
            return vector<string>{};

        vector<State> nextStates = getNextStates(currentState, width, height);
        for(const State& nextState : nextStates){
            if(visited.find(nextState.board) == visited.end()){
                visited.insert(nextState.board);
                q.push(nextState);
            }
        }
    }
    return vector<string>{};
}