#include "BinaryDecisionTree.h"
#include <algorithm>
#include <sstream>

class Codec {
public:
    static std::string serialize(std::shared_ptr<Node> root) {
        // Create an output string stream to store serialized data
        std::ostringstream temp;

        // Call the helper function to serialize the tree
        ToString(root, temp);

        // Convert the output string stream to a string and return
        return temp.str();
    }

    static std::shared_ptr<Node> deserialize(std::string data) {
        // Create an input string stream to read serialized data
        std::istringstream temp(data);

        // Call the helper function to deserialize the tree and return the root
        return ToStructure(temp);
    }

    static void writeToFile(std::shared_ptr<Node> root, const std::string& filename) {
        std::string serialized_data = serialize(root);
        std::ofstream outfile(filename);

        if (outfile.is_open()) {
            outfile << serialized_data;
            outfile.close();
            std::cout << "Data has been written to " << filename << " successfully." << std::endl;
        }
        else {
            std::cerr << "Unable to open file " << filename << " for writing." << std::endl;
        }
    }

    static std::shared_ptr<Node> readFromFile(const std::string& filename) {
        std::ifstream infile(filename);
        if (infile.is_open()) {
            std::string serialized_data;
            std::getline(infile, serialized_data);
            infile.close();

            std::cout << "Data has been read from " << filename << " successfully." << std::endl;

            std::istringstream iss(serialized_data);
            return ToStructure(iss);
        }
        else {
            std::cout << "Unable to read file " << filename << std::endl;
            exit(-1);
        }
    }

private:

    static void ToString(std::shared_ptr<Node> root, std::ostringstream& temp) {
        auto leaf = std::dynamic_pointer_cast<Leaf>(root);
        if (leaf) {
            temp << "~ " << leaf->getPredictions().size() << " ";
            for (auto& row : leaf->getPredictions()) {
                std::string name = row.first;
                std::replace(name.begin(), name.end(), ' ', '_');
                temp << name << " " << row.second << " ";
            }
            return;
        }

        auto decision_node = std::dynamic_pointer_cast<DecisionNode>(root);
        if (decision_node)
        {
            temp << "% " << decision_node->getQuestion().getColumn() << " " << decision_node->getQuestion().getValue() << " ";

            // Recursively serialize left and right subtrees
            ToString(decision_node->getTrueBranch(), temp);
            ToString(decision_node->getFalseBranch(), temp);
        }

        if (root == nullptr) {
            temp << "#";
            return;
        }
    }

    static std::shared_ptr<Node> ToStructure(std::istringstream& temp) {
        // Read the next value from the input string stream
        std::string token = "";
        temp >> token;

        // If the value is "N", indicating a null node, return NULL
        if (token == "#" ) {
            return nullptr;
        }

        if (token == "~") {
            int size = 0;
            temp >> size;

            std::unordered_map<std::string, int> predictions;
            for (int i = 0; i < size; i++) {
                std::string class_name;
                int count;
                
                temp >> class_name >> count;
                predictions[class_name] = count;
            }

            return std::make_shared<Leaf>(predictions);
        }

        if (token == "%") {
            int column;
            std::string value;

            temp >> column >> value;
            
            auto question = Question(column, value);
            auto true_branch = ToStructure(temp);
            auto false_branch = ToStructure(temp);

            return std::make_shared<DecisionNode>(question, true_branch, false_branch);
        }

        return nullptr;
    }

};