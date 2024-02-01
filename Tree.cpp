#include <iostream>
#include <cstring>

using namespace std;

class Tree {
    private:
        struct Node {
            string question;
            Node* lChild;
            Node* rChild;

            Node() {}

            Node(string s) : question(s), lChild(nullptr), rChild(nullptr) {}
        };

        Node* root;
        // vector<Node*> leaves;

    public:
        Tree() {
            root->question = string("Does it breathe??");
            string ansl = "Non-living", ansr = "Living";

            // Node* lNode;
            // lNode->question = ansl;
            // root->lChild = lNode;

            // Node* rNode;
            // rNode->question = ansr;
            // root->rChild = rNode;
        }

        void askQuestion(Node* aNode) {
            string answer;
            cout << aNode->question << endl;
            cin >> answer;
            tolower(answer);
            if (answer == "yes") cout << "aNode->rChild->question" << endl;
            else cout << "aNode->lChild->question" << endl;
        }

        Node* nodeInit() {
            
        }

        void display() {
            askQuestion(root);
        }

        void tolower(string st) {
            const char* s = st.c_str();
            for (int i = 0; i < strlen(s); i++) {
                if (st[i] >= 65 && st[i] <= 90) st[i] -= 32;
            }
        }

};

int main() {
    Tree t;

    t.display();
}