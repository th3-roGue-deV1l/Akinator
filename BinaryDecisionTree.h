#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "utils.h"


class Question {
private:
	std::vector<std::string> header = { "Color", "Diameter", "Label" };
	int column;
	std::string value;
public:
	Question(int col, const std::string& val) : column(col), value(val) {}

	bool match(std::vector<std::string> example) const {
		std::string val = example[column];

		if (column == 1) {
			return std::stoi(val) >= std::stoi(value);
		}
		return val == value;
	}

	friend std::ostream& operator<<(std::ostream& cout, const Question& q) {
		std::string operand = (q.column == 1) ? " >= " : " = ";
		cout << "Is " << q.header[q.column] << operand << q.value << " ?";
		return cout;
	}
};


class Node {
public:
	virtual ~Node() {}
};


class Leaf : public Node {
private:
	std::unordered_map<std::string, int> predictions;
public:
	std::unordered_map<std::string, int> getPredictions() {
		return predictions;
	}

	Leaf(const std::vector<std::vector<std::string>>& rows) {
		predictions = class_counts(rows);
	}

	friend std::ostream& operator<<(std::ostream& cout, const Leaf& leaf) {
		std::string answer;
		for (auto& row : leaf.predictions) {
			cout << "Is it: " << row.first << " ? ";
			std::cin >> answer;
			if (answer == "y") {
				std::cout << "I own you bitch!" << std::endl;
				break;
			}
			continue;
			//cout << "{ " << row.first << ", " << row.second << " }\n";
		}
		return cout;
	}
};


class DecisionNode : public Node {
private:
	Question question;
	Node* true_branch;
	Node* false_branch;

public:
	DecisionNode(const Question& q, Node* tb, Node* fb) :
		question(q),
		true_branch(tb),
		false_branch(fb)
	{ }

	Question getQuestion() { return  question; }

	Node* getTrueBranch() { return true_branch; }

	Node* getFalseBranch() { return false_branch; }
};

