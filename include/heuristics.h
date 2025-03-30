//
// Created by ophth on 25.03.2025.
//

#ifndef UNTITLED_HEURISTICS_H
#define UNTITLED_HEURISTICS_H

#include <iostream>
#include <vector>
#include <queue>

struct State;

std::vector<State> getNextStates(const State& state, int width, int height, std::vector<std::vector<int>> goalBoard, bool mode);

std::vector<std::string> solveHeuristics(std::vector<std::vector<int>>& startState, int width, int height, int maxDepth, bool mode);

#endif //UNTITLED_HEURISTICS_H
