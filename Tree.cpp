#include "Tree.h"

Tree:: addNode(simple_string s, bool tf, Node* curr) {
    Node *newNode = new Node(std::move(s));
    if (root == nullptr) {
        root = newNode;
        return;
    }

    if (tf) curr->right = newNode;
    else curr->left = newNode;

}

//        void updateLeaves() {
//            Node* curr = root;
//            if (curr->left == nullptr && curr->right == nullptr) leaves.push_back(curr);
//            curr = curr->left;
//        }

Tree:: Node* displayResult (Node* aNode) {
    if (aNode->left == nullptr || aNode->right == nullptr) {
        std::string answer;
        std::cout << "Is your answer " << aNode->data << std::endl;
        std::cin >> answer;
        if (answer == "yes") {
            std::cout << "Thanks for playing !!!";
            return aNode;
        }
        std::cout << "Please enter a question with a distinguishing trait for your answer.";
        std::cin >> answer;
        addNode(answer, false, aNode);
        return aNode->right;
    }
    return nullptr;
}

//        void tolower(std::string st) {
//            const char* s = st.c_str();
//            for (int i = 0; i < strlen(s); i++) {
//                if (st[i] >= 65 && st[i] <= 90) st[i] -= 32;
//            }
//        }


Tree:: askQuestion(Tree::Node *qNode) {

    simple_string answer;
    std::cout << qNode->data;
    std::cin >> answer;

    if (qNode->left == nullptr || qNode->right == nullptr) return displayResult(qNode);

    if (strcmp(answer, "yes")) askQuestion (qNode->right);
    else askQuestion (qNode->left);
}
