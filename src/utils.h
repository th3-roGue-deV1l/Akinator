#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "fstream"
#include "sstream"
#include "string"

typedef std::vector<std::vector<std::string>> Array2D;

std::unordered_map<std::string, int> class_counts(const Array2D& rows);

std::vector<std::string> unique_vals(const Array2D& rows, int col);

std::vector<std::vector<std::string> > CSV2Vector (const char* file_name);
