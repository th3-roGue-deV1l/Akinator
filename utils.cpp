#include "utils.h"

std::vector<std::string> unique_vals(const BigD& rows, int col) {
	std::vector<std::string> unique;
	for (const auto& row : rows) {
		unique.push_back(row[col]);
	}
	return unique;
}

std::unordered_map<std::string, int> class_counts(const std::vector<std::vector<std::string>>& rows) {
	std::unordered_map<std::string, int> counts;
	for (const auto& row : rows) {
		std::string label = row.back();
		if (counts.find(label) == counts.end())
		{
			counts[label] = 0;
		}
		counts[label]++;
	}
	return counts;
}