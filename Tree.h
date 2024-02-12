//
// Created by Roguebook on 12/02/2024.
//

#ifndef AKINATOR_TREE_H
#define AKINATOR_TREE_H

#include <iostream>
#include <stack>
#include "string"
#include <utility>
#include "SimpleString.h"
//#include <ErrorList>
//#include "colors.h"

typedef std::string T;

class Tree {

    private:

        struct Node {

            T data;
            Node* left;
            Node* right;

            bool question = false;

            explicit
            Node(simple_string s) : data(std::move(s)), left(nullptr), right(nullptr) {}
        };

        Node* root;
    //        std::vector<Node*> leaves;

    public:
        Tree() {
            root = nullptr;
        }

        void addNode(simple_string s, bool tf, Node* curr);

        Node* displayResult (Node* aNode);

        Node* askQuestion (Node* qNode);

};


#endif //AKINATOR_TREE_H
