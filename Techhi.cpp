#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "utils.h"
#include "BinaryDecisionTree.h"
#include "CART.h"

Array2D training_data = {
	{"Green", "3", "Apple"},
	{"Yellow", "3", "Apple"},
	{"Red", "1", "Grape"},
	{"Red", "1", "Grape"},
	{"Yellow", "3", "Lemon"},
	{"Peach", "2", "Peach"}
};

Array2D CSVdata = CSV2Vector("something.csv");


Node* build_tree(const Array2D& rows) {
	auto [gain, question] = find_best_split(rows);

	if (gain == 0.0) {
		return new Leaf(rows);
	}

	auto [true_rows, false_rows] = partition(rows, question);

	auto true_branch = build_tree(true_rows);
	auto false_branch = build_tree(false_rows);

	return new DecisionNode(question, true_branch, false_branch);
}

void print_tree(Node* node, const std::string& spacing = "") {
	std::string answer;

	auto leaf = dynamic_cast<Leaf*>(node);
	if (leaf) {
		for (const auto& pair : leaf->getPredictions()) {
			std::cout << "Is it " << pair.first << "? ";
			std::cin >> answer;
			if (answer == "y") {
				std::cout << "I own you biatch!!!" << std::endl;
				return;
			}
		}
		std::cout << "Jaatha Jhuto Bolxas!!!" << std::endl;
	}

	auto decisionNode = dynamic_cast<DecisionNode*>(node);
	if (decisionNode) {
		std::cout << spacing << decisionNode->getQuestion();
		std::cin >> answer;

		if (answer == "y") {
			std::cout << spacing << "--> True:" << std::endl;
			print_tree(decisionNode->getTrueBranch(), spacing + " ");
		}
		else {
			std::cout << spacing << "--> False:";
			print_tree(decisionNode->getFalseBranch(), spacing + " ");
		}
	}
}


int main()
{
	Node* my_tree = build_tree(training_data);
	print_tree(my_tree);

	std::getchar();
	std::getchar();

	return 0;
}
