#pragma once

#include<iostream>
#include <vector>
#include<unordered_map>

typedef std::vector<std::vector<std::string>> BigD;

std::unordered_map<std::string, int> class_counts(const std::vector<std::vector<std::string>>& rows);

std::vector<std::string> unique_vals(const BigD& rows, int col);
