//
// Created by ophth on 20.03.2025.
//
#ifndef UNTITLED_ALGORITHMS_H
#define UNTITLED_ALGORITHMS_H

#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <stack>
#include <queue>

struct State;

std::vector<std::string> solveDFS(std::vector<std::vector<int>>& startState, int width, int height, int maxDepth);

std::vector<std::string> solveBFS(std::vector<std::vector<int>>& startState, int width, int height, int maxDepth);

std::vector<State> getNextStates(const State& state, int width, int height);

#endif //UNTITLED_ALGORITHMS_H
