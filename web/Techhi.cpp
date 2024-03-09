#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <fstream>

#include <emscripten.h>

std::vector<std::string> header = {"Hair_Color", "Gender", "Tags", "Character"};

class Question
{
private:
  int column;
  std::string value;

public:
  Question(int col, const std::string &val)
  {
    column = col;
    value = val;
    std::replace(value.begin(), value.end(), ' ', '_');
  }

  int getColumn() const
  {
    return column;
  }

  std::string getValue() const
  {
    return value;
  }

  bool match(std::vector<std::string> example) const
  {
    std::string val = example[column];

    /*if ((val == value) || (std::find(similar_characters->begin(), similar_characters->end(), example.back())) != similar_characters->end())
    {
      similar_characters->push_back(example.back());
      return true;
    }*/
    return val == value;
  }

  friend std::ostream &operator<<(std::ostream &cout, const Question &q)
  {
    std::string operand = (q.column == 100) ? " >= " : " = ";
    cout << "Is " << header[q.column] << operand << q.value << " ?";
    return cout;
  }
};

class Node
{
public:
  virtual ~Node() {}
};

class Leaf : public Node
{
private:
  std::unordered_map<std::string, int> predictions;

public:
  std::unordered_map<std::string, int> getPredictions()
  {
    return predictions;
  }

  // For deserialization of Binary Tree
  Leaf(const std::unordered_map<std::string, int> &predictions)
  {
    this->predictions = predictions;
  }

  friend std::ostream &operator<<(std::ostream &cout, const Leaf &leaf)
  {
    std::string answer;
    for (auto &row : leaf.predictions)
    {
      cout << "{ " << row.first << ", " << row.second << " }\t";
    }
    return cout;
  }
};

class DecisionNode : public Node
{
private:
  Question question;
  std::shared_ptr<Node> true_branch;
  std::shared_ptr<Node> false_branch;

public:
  DecisionNode(const Question &q, std::shared_ptr<Node> tb, std::shared_ptr<Node> fb) : question(q),
                                                                                        true_branch(tb),
                                                                                        false_branch(fb)
  {
  }

  Question getQuestion() { return question; }

  std::shared_ptr<Node> getTrueBranch() { return true_branch; }

  std::shared_ptr<Node> getFalseBranch() { return false_branch; }
};

class Codec
{
public:
  static std::string serialize(std::shared_ptr<Node> root)
  {
    // Create an output string stream to store serialized data
    std::ostringstream temp;

    // Call the helper function to serialize the tree
    ToString(root, temp);

    // Convert the output string stream to a string and return
    return temp.str();
  }

  static std::shared_ptr<Node> deserialize(std::string data)
  {
    // Create an input string stream to read serialized data
    std::istringstream temp(data);

    // Call the helper function to deserialize the tree and return the root
    return ToStructure(temp);
  }

  static void writeToFile(std::shared_ptr<Node> root, const std::string &filename)
  {
    std::string serialized_data = serialize(root);
    std::ofstream outfile(filename);

    if (outfile.is_open())
    {
      outfile << serialized_data;
      outfile.close();
      std::cout << "Data has been written to " << filename << " successfully." << std::endl;
    }
    else
    {
      std::cerr << "Unable to open file " << filename << " for writing." << std::endl;
    }
  }

  static std::shared_ptr<Node> readFromFile(const std::string &filename)
  {
    std::ifstream infile(filename);
    if (infile.is_open())
    {
      std::string serialized_data;
      std::getline(infile, serialized_data);
      infile.close();

      std::cout << "Data has been read from " << filename << " successfully." << std::endl;

      std::istringstream iss(serialized_data);
      return ToStructure(iss);
    }
    else
    {
      std::cout << "Unable to read file " << filename << std::endl;
      exit(-1);
    }
  }

private:
  static void ToString(std::shared_ptr<Node> root, std::ostringstream &temp)
  {
    auto leaf = std::dynamic_pointer_cast<Leaf>(root);
    if (leaf)
    {
      temp << "~ " << leaf->getPredictions().size() << " ";
      for (auto &row : leaf->getPredictions())
      {
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

    if (root == nullptr)
    {
      temp << "#";
      return;
    }
  }

  static std::shared_ptr<Node> ToStructure(std::istringstream &temp)
  {
    // Read the next value from the input string stream
    std::string token = "";
    temp >> token;

    // If the value is "N", indicating a null node, return NULL
    if (token == "#")
    {
      return nullptr;
    }

    if (token == "~")
    {
      int size = 0;
      temp >> size;

      std::unordered_map<std::string, int> predictions;
      for (int i = 0; i < size; i++)
      {
        std::string class_name;
        int count;

        temp >> class_name >> count;
        predictions[class_name] = count;
      }

      return std::make_shared<Leaf>(predictions);
    }

    if (token == "%")
    {
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

std::shared_ptr<Node> currentNode;

void updateQuestion(const char *question)
{
  EM_ASM({
    // Convert the question string to a JavaScript string
    var questionStr = UTF8ToString($0);

    // Call the JavaScript updateQuestion function with the question string
    updateQuestion(questionStr);
  },
         question);
}

void play(const std::shared_ptr<Node> &node)
{
  auto leaf = std::dynamic_pointer_cast<Leaf>(node);
  if (leaf)
  {
    currentNode = leaf;
    for (const auto &pair : leaf->getPredictions())
    {
      std::string leaf_question = "Is it " + pair.first + "?";
      updateQuestion(leaf_question.c_str());
    }
  }

  auto decisionNode = std::dynamic_pointer_cast<DecisionNode>(node);
  if (decisionNode)
  {
    currentNode = decisionNode;
    std::string question = "Is " + header[decisionNode->getQuestion().getColumn()] + " = " + decisionNode->getQuestion().getValue() + " ?";
    updateQuestion(question.c_str());
  }
}

extern "C"
{
  void EMSCRIPTEN_KEEPALIVE handleUserYesInputFromJS()
  {
    auto decisionNode = std::dynamic_pointer_cast<DecisionNode>(currentNode);
    if (decisionNode)
    {
      play(decisionNode->getTrueBranch());
    }
  }

  void EMSCRIPTEN_KEEPALIVE handleUserNoInputFromJS()
  {
    auto decisionNode = std::dynamic_pointer_cast<DecisionNode>(currentNode);
    if (decisionNode)
    {
      play(decisionNode->getFalseBranch());
    }
  }
}

extern "C"
{
  void EMSCRIPTEN_KEEPALIVE startGame()
  {
    play(currentNode);
  }
}

int main()
{
  currentNode = Codec::readFromFile("serialized_data.txt");
  return 0;
}