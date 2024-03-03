#pragma once

#include "utils.h"
#include "BinaryDecisionTree.h"

std::pair<Array2D, Array2D> partition(const Array2D& rows, const Question& question);

double gini(const Array2D& rows);


double info_gain(const Array2D& left, const Array2D& right, double current_uncertainty);

std::pair<double, Question> find_best_split(const Array2D& rows);