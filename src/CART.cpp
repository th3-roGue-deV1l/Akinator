#include "CART.h"

static tbb::mutex mutex;

std::pair<Array2D, Array2D> partition(const Array2D& rows, const Question& question) {
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

double gini(const Array2D& rows) {
	std::unordered_map<std::string, int> counts = class_counts(rows);

	double impurity = 1.0;
	double prob_of_label;

	for (const auto& label : counts) {
		prob_of_label = double(label.second) / rows.size();
		impurity -= prob_of_label * prob_of_label;
	}

	return impurity;
}


double info_gain(const Array2D& left, const Array2D& right, double current_uncertainty) {
	double p = static_cast<double>(left.size() / (left.size() + right.size()));
	return current_uncertainty - p * gini(left) - (1 - p) * gini(right);
}



// Define a functor for the loop body
struct LoopBody {
	// Variables shared by all threads
	Array2D& rows;
	double& best_gain;
	Question& best_question;
	double current_uncertainty;

	// Constructor to initialize shared variables
	LoopBody(Array2D& rows, double& best_gain, Question& best_question, double current_uncertainty)
		: rows(rows), best_gain(best_gain), best_question(best_question), current_uncertainty(current_uncertainty) {}

	// Overloaded operator() to define the loop body
	void operator()(const tbb::blocked_range<int>& range) const {
		for (int col = range.begin(); col != range.end(); ++col) {
			std::vector<std::string> values = unique_vals(rows, col);

			for (const auto& item : values) {
				Question question(col, item);

				auto [true_rows, false_rows] = partition(rows, question);

				if (true_rows.empty() || false_rows.empty()) {
					continue;
				}

				double gain = info_gain(true_rows, false_rows, current_uncertainty);

				
				{
					tbb::mutex::scoped_lock(mutex);
					if (gain >= best_gain) {
						best_gain = gain;
						best_question = question;
					}
				}
			}
		}
	}
};

// Parallelize the nested loop using tbb::parallel_for
void parallel_nested_loop(Array2D& rows, int n_features, double& best_gain, Question& best_question, double current_uncertainty) {
	// Define the range for the outer loop
	tbb::blocked_range<int> range(0, n_features);

	// Perform the parallel loop
	tbb::parallel_for(range, LoopBody(rows, best_gain, best_question, current_uncertainty));
}



std::pair<double, Question> find_best_split(Array2D& rows) {
	double best_gain = 0.0;
	Question best_question(0, "");
	double current_uncertainty = gini(rows);
	int n_features = rows[0].size() - 1;

	parallel_nested_loop(rows, n_features, best_gain, best_question, current_uncertainty);

	return { best_gain, best_question };
}