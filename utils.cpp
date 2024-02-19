#include "utils.h"

std::vector<std::string> unique_vals(const Array2D& rows, int col) {
	std::vector<std::string> unique;
	for (const auto& row : rows) {
		unique.push_back(row[col]);
	}
	return unique;
}

std::unordered_map<std::string, int> class_counts(const Array2D& rows) {
	std::unordered_map<std::string, int> counts;
	for (const auto& row : rows) {
		const std::string& label = row.back();
		if (counts.find(label) == counts.end())
		{
			counts[label] = 0;
		}
		counts[label]++;
	}
	return counts;
}

std::vector<std::vector<std::string> > CSV2Vector (std::string file_name) {
    std::ifstream file(file_name);
	
	Array2D data;
	std::string line;
    
    while (std::getline(file, line)) {
		std::vector<std::string> row;
		std::stringstream ss(line);
		std::string item;

		while (std::getline(ss, item, ','))
		{
			row.push_back(item);
		}
		data.push_back(row);
    }

    return data;
}