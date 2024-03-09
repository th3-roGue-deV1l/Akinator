#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "utils.h"
#include "BinaryDecisionTree.h"
#include "CART.h"
#include "Codec.h"

std::vector<std::string> header;
long long totalDuration;
Array2D CSVdata = CSV2Vector("D:/Projects/C++/DSA/Techhi/data/anime_data_refined.csv");

std::shared_ptr<Node> build_tree(Array2D& rows) {
	auto [gain, question] = find_best_split(rows);

	if (gain == 0.0) {
		return std::make_shared<Leaf>(rows);
	}

	auto [true_rows, false_rows] = partition(rows, question);

	auto true_branch = build_tree(true_rows);
	auto false_branch = build_tree(false_rows);

	return std::make_shared<DecisionNode>(question, true_branch, false_branch);
}

void print_tree(const std::shared_ptr<Node>& node, const std::string& spacing = "") {
	std::string answer;

	auto leaf = std::dynamic_pointer_cast<Leaf>(node);
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

	auto decisionNode = std::dynamic_pointer_cast<DecisionNode>(node);
	if (decisionNode) {
		std::cout << spacing << decisionNode->getQuestion();
		std::cin >> answer;

		if (answer == "y") {
			std::cout << spacing << "--> True:" << std::endl;
			print_tree(decisionNode->getTrueBranch(), spacing + " ");
		}
		else {
			std::cout << spacing << "--> False:" << std::endl;
			print_tree(decisionNode->getFalseBranch(), spacing + " ");
		}
	}
}

void display_tree(std::shared_ptr<Node> node, const std::string& prefix = "", bool isLeft = false) {
	auto leaf = std::dynamic_pointer_cast<Leaf>(node);
	if (leaf) {
		std::cout << prefix;
		std::cout << (isLeft ? "|--" : "+--");
		for (auto& row : leaf->getPredictions()) {
			std::cout << "{ " << row.first << ", " << row.second << " }\t";
		}
		std::cout << std::endl;
	}

	auto decisionNode = std::dynamic_pointer_cast<DecisionNode>(node);
	if (decisionNode) {
		std::cout << prefix;
		std::cout << (isLeft ? "|--" : "+--");

		std::cout << decisionNode->getQuestion() << std::endl;

		display_tree(decisionNode->getTrueBranch(), prefix + (isLeft ? "|   " : "    "), true);
	
		display_tree(decisionNode->getFalseBranch(), prefix + (isLeft ? "|   " : "    "), false);
	}
}


int main()
{
    try {
		    std::shared_ptr<Node> my_tree;
		    {
		    	Timer timer;
		    	my_tree = build_tree(CSVdata);
		    }
		    Codec::writeToFile(my_tree, "D:/Projects/C++/DSA/Techhi/web/serialized_data.txt");

			display_tree(my_tree);
    }
    catch (const char& err) {
        std::cerr << err;
    }

	std::getchar();
	return 0;
}
