//
// Created by ophth on 25.03.2025.
//

#include "../../Users/ophth/SISE-C-/include/heuristics.h"

using namespace std;

const vector<pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct State{
    vector<vector<int>> board;
    int zeroX, zeroY;
    vector<string> path;
    int hValue=0;

    State(vector<vector<int>> b, int x, int y, vector<string> p)
            :board(std::move(b)), zeroX(x), zeroY(y), path(std::move(p)) {}

    void calculateHamming(const vector<vector<int>>& other){
        if (other.size() != board.size())
            throw std::logic_error("incompatible boards sizes");

        if (other[0].size() != board[0].size())
            throw std::logic_error("incompatible boards sizes");

        hValue = 0;

        for(int i = 0; i < other.size(); i++){
            for(int j = 0; j < other[0].size(); j++){
                if (board[i][j] != other[i][j])
                    hValue++;
            }
        }
        hValue += path.size();
    }

    void calculateManhattan(const vector<vector<int>>& other){
        int distance = 0;
        int width = board[0].size(), height = board.size();

        if (other.size() != board.size())
            throw std::logic_error("incompatible boards sizes");

        if (other[0].size() != board[0].size())
            throw std::logic_error("incompatible boards sizes");

        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                int value = board[i][j];
                if (value != 0) {
                    int goalX = (value - 1) / width;
                    int goalY = (value - 1) % width;
                    distance += abs(i - goalX) + abs(j - goalY);
                }
            }
        }
        distance += path.size();
        hValue = distance;
    }

    bool operator<(const State& other) const{
        return hValue > other.hValue;
    }
};

vector<State> getNextStates(const State& state, int width, int height, vector<vector<int>> goalBoard, bool mode){
    vector<State> nextStates;
    for(int i = 0; i<4; i++){
        int newX = state.zeroX + moves[i].first;
        int newY = state.zeroY + moves[i].second;

        if(0 <= newX && newX < height && 0<= newY && newY < width){
            vector<vector<int>> newBoard = state.board;
            swap(newBoard[state.zeroX][state.zeroY], newBoard[newX][newY]);

            vector<string> newPath(state.path.begin(), state.path.end());
            newPath.emplace_back(i == 0 ? "U" : i == 1 ? "D" : i == 2 ? "L" : "R");

            State newState(newBoard, newX, newY, newPath);
            if (mode) {newState.calculateHamming(goalBoard);}
            else {newState.calculateManhattan(goalBoard);}
            nextStates.push_back(newState);

        }
    }
    return nextStates;
}


vector<string> solveHeuristics(vector<vector<int>>& startState, int width, int height, int maxDepth, bool mode){
    vector<vector<int>> goalBoard(height, vector<int>(width));
    int number = 1;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            goalBoard[i][j] = number++;
        }
    }
    goalBoard[height-1][width-1] = 0;

    int zeroX, zeroY;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (startState[i][j] == 0) {
                zeroX = i;
                zeroY = j;
            }
        }
    }

    priority_queue<State> q;
    State start(startState, zeroX, zeroY, vector<string>{});

    if (mode) {
        start.calculateHamming(goalBoard);
    } else {
        start.calculateManhattan(goalBoard);
    }

    q.push(start);

    while (!q.empty()){

        State currentState = q.top();
        q.pop();

        if (currentState.board == goalBoard)
            return currentState.path;

        if (currentState.path.size()>=maxDepth)
            return vector<string>{};

        vector<State> nextStates = getNextStates(currentState, width, height, goalBoard, mode);
        for(const State& nextState : nextStates){
            q.push(nextState);
        }
    }

    return vector<string>{};
}