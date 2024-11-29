#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class Node 
{
public:
    string englishWord;
    string ukrainianTranslation;
    int accessCount;
    Node* left;
    Node* right;

    Node(string english, string ukrainian, int accessCount = 0) {
        this->englishWord = english;
        this->ukrainianTranslation = ukrainian;
        this->accessCount = accessCount;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class BinaryTree 
{
public:
    Node* root;

    BinaryTree()
    {
        root = nullptr;
    }

    void addNode(string english, string ukrainian, int accessCount = 0)
    {
        Node* newNode = new Node(english, ukrainian, accessCount);
        if (root == nullptr)
        {
            root = newNode;
        }
        else
        {
            Node* focusNode = root;
            Node* parent;

            while (true)
            {
                parent = focusNode;
                if (english < focusNode->englishWord)
                {
                    focusNode = focusNode->left;
                    if (focusNode == nullptr)
                    {
                        parent->left = newNode;
                        return;
                    }
                }
                else if (english > focusNode->englishWord)
                {
                    focusNode = focusNode->right;
                    if (focusNode == nullptr)
                    {
                        parent->right = newNode;
                        return;
                    }
                }
                else
                {
                    focusNode->ukrainianTranslation = ukrainian;
                    return;
                }
            }
        }
    }

    Node* findWord(string english)
    {
        Node* focusNode = root;

        while (focusNode != nullptr)
        {
            if (english == focusNode->englishWord)
            {
                focusNode->accessCount++;
                return focusNode;
            }
            else if (english < focusNode->englishWord)
            {
                focusNode = focusNode->left;
            }
            else {
                focusNode = focusNode->right;
            }
        }

        return nullptr;
    }

    Node* deleteNode(Node* root, string english)
    {
        if (root == nullptr) return root;

        if (english < root->englishWord)
        {
            root->left = deleteNode(root->left, english);
        }
        else if (english > root->englishWord)
        {
            root->right = deleteNode(root->right, english);
        }
        else
        {
            if (root->left == nullptr)
            {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = findMin(root->right);
            root->englishWord = temp->englishWord;
            root->ukrainianTranslation = temp->ukrainianTranslation;
            root->accessCount = temp->accessCount;
            root->right = deleteNode(root->right, temp->englishWord);
        }
        return root;
    }

    Node* findMin(Node* node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    void displayWord(string english)
    {
        Node* result = findWord(english);
        if (result != nullptr)
        {
            cout << "Word: " << result->englishWord << " - Translation: " << result->ukrainianTranslation << " - Access Count: " << result->accessCount << endl;
        }
        else
        {
            cout << "Word not found." << endl;
        }
    }

    void inOrderTraversal(Node* focusNode, Node* nodes[], int& index)
    {
        if (focusNode != nullptr)
        {
            inOrderTraversal(focusNode->left, nodes, index);
            nodes[index++] = focusNode;
            inOrderTraversal(focusNode->right, nodes, index);
        }
    }

    void sortNodes(Node* nodes[], int size, bool ascending = true)
    {
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                if ((ascending && nodes[i]->accessCount > nodes[j]->accessCount) ||
                    (!ascending && nodes[i]->accessCount < nodes[j]->accessCount))
                {
                    Node* temp = nodes[i];
                    nodes[i] = nodes[j];
                    nodes[j] = temp;
                }
            }
        }
    }

    void displayTopPopular()
    {
        Node* nodes[100]; 
        int count = 0;

        inOrderTraversal(root, nodes, count);
        sortNodes(nodes, count, false); 

        cout << "Top 3 most popular words:" << endl;
        for (int i = 0; i < min(3, count); i++)
        {
            cout << nodes[i]->englishWord << " - " << nodes[i]->ukrainianTranslation << " (Access count: " << nodes[i]->accessCount << ")" << endl;
        }
    }

    void displayTopUnpopular()
    {
        Node* nodes[100];  
        int count = 0;

        inOrderTraversal(root, nodes, count);
        sortNodes(nodes, count, true);

        cout << "Top 3 least popular words:" << endl;
        for (int i = 0; i < min(3, count); i++)
        {
            cout << nodes[i]->englishWord << " - " << nodes[i]->ukrainianTranslation << " (Access count: " << nodes[i]->accessCount << ")" << endl;
        }
    }
};

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    BinaryTree dictionary;

    dictionary.addNode("hello", "привіт");
    dictionary.addNode("world", "земля");
    dictionary.addNode("apple", "яблоко");
    dictionary.addNode("sun", "сонце");
    dictionary.addNode("moon", "луна");

    dictionary.displayWord("world");

    dictionary.addNode("computer", "комп'ютер");

    dictionary.addNode("world", "світло");

    dictionary.root = dictionary.deleteNode(dictionary.root, "sun");

    dictionary.displayTopPopular();
    dictionary.displayTopUnpopular();

    return 0;
}

