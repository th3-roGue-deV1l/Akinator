#include "CART.h"

std::pair<std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>> partition(const std::vector<std::vector<std::string>>& rows, const Question& question) {
	std::vector <std::vector<std::string>> true_rows, false_rows;

	for (const auto& row : rows) {
		if (question.match(row)) {
			true_rows.push_back(row);
		}
		else {
			false_rows.push_back(row);
		}
	}
	return { true_rows, false_rows };
}

double gini(const std::vector<std::vector<std::string>>& rows) {
	std::unordered_map<std::string, int> counts = class_counts(rows);
	double impurity = 1.0;
	double prob_of_label;

	for (const auto& label : counts) {
		prob_of_label = double(label.second) / rows.size();
		impurity -= prob_of_label * prob_of_label;
	}

	return impurity;
}


double info_gain(const BigD& left, const BigD& right, double current_uncertainty) {
	double p = static_cast<double>(left.size() / (left.size() + right.size()));
	return current_uncertainty - p * gini(left) - (1 - p) * gini(right);
}

std::pair<double, Question> find_best_split(const std::vector<std::vector<std::string>>& rows) {
	double best_gain = 0.0;
	Question best_question(0, "");
	double current_uncertainty = gini(rows);
	int n_features = rows[0].size() - 1;

	for (int col = 0; col < n_features; col++) {
		std::vector<std::string> values = unique_vals(rows, col);
		for (const auto& item : values) {
			Question question(col, item);

			auto [true_rows, false_rows] = partition(rows, question);

			if (true_rows.empty() || false_rows.empty()) {
				continue;
			}

			double gain = info_gain(true_rows, false_rows, current_uncertainty);

			if (gain >= best_gain) {
				best_gain = gain;
				best_question = question;
			}
		}
	}

	return { best_gain, best_question };
}