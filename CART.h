#pragma once

#include "utils.h"
#include "BinaryDecisionTree.h"

std::pair<std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>> partition(const std::vector<std::vector<std::string>>& rows, const Question& question);

double gini(const std::vector<std::vector<std::string>>& rows);


double info_gain(const BigD& left, const BigD& right, double current_uncertainty);

std::pair<double, Question> find_best_split(const std::vector<std::vector<std::string>>& rows);