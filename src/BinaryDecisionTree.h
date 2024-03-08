#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

#include "utils.h"


class Question {
private:
	int column;
	std::string value;
public:

	Question(int col, const std::string& val) {
		column = col;
		value = val;
		std::replace(value.begin(), value.end(), ' ', '_');
	}

	int getColumn() const {
		return column;
	}

	std::string getValue() const {
		return value;
	}

	bool match(std::vector<std::string> example) const {
		std::string val = example[column];

		/*if ((val == value) || (std::find(similar_characters->begin(), similar_characters->end(), example.back())) != similar_characters->end())
		{
			similar_characters->push_back(example.back());
			return true;
		}*/
		return val == value;
	}

	friend std::ostream& operator<<(std::ostream& cout, const Question& q) {
		std::string operand = (q.column == 100) ? " >= " : " = ";
		cout << "Is " << header[q.column] << operand << q.value << " ?";
		return cout;
	}
};


class Node {
public:
	virtual ~Node() { }
};


class Leaf : public Node {
private:
	std::unordered_map<std::string, int> predictions;
public:
	std::unordered_map<std::string, int> getPredictions() {
		return predictions;
	}

	// For deserialization of Binary Tree
	Leaf(const std::unordered_map<std::string, int>& predictions) {
		this->predictions = predictions;
	}

	Leaf(const Array2D& rows) {
		predictions = class_counts(rows);
	}

	friend std::ostream& operator<<(std::ostream& cout, const Leaf& leaf) {
		std::string answer;
		for (auto& row : leaf.predictions) {
			/*cout << "Is it: " << row.first << " ? ";
			std::cin >> answer;
			if (answer == "y") {
				std::cout << "I own you bitch!" << std::endl;
				break;
			}
			continue;*/
			cout << "{ " << row.first << ", " << row.second << " }\t";
		}
		return cout;
	}
};


class DecisionNode : public Node {
private:
	Question question;
	std::shared_ptr<Node> true_branch;
	std::shared_ptr<Node> false_branch;

public:
	DecisionNode(const Question& q, std::shared_ptr<Node> tb, std::shared_ptr<Node> fb) :
		question(q),
		true_branch(tb),
		false_branch(fb)
	{ }

	Question getQuestion() { return  question; }

	std::shared_ptr<Node> getTrueBranch() { return true_branch; }

	std::shared_ptr<Node> getFalseBranch() { return false_branch; }
};

