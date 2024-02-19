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

std::vector<std::vector<std::string> > CSV2Vector (const char* file_name) {
    std::ifstream filename;
    filename.open(file_name);
    if(!fopen(file_name, "r")) throw "FILE DOESN'T EXIST !!!";

    std::string name;
    std::vector<std::string> line;
    std::vector<std::vector<std::string> > data;
    std::string item;

    int i = 0;
    while (!filename.eof()) {
        filename >> name;
        std::stringstream ss(name);

        while (getline(ss, item, ',')) {
            line.push_back(item);
        }
        data.push_back(line);
        i++;
    }
    return data;
}