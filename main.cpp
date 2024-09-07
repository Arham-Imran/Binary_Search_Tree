#include <iostream>

class Node
{
    public:
    int val;
    Node *left, *right;
    Node(int a) : val(a), left(nullptr), right(nullptr) {}
};

class Bst
{
    private:
    Node* root;

    public:
    Bst() : root(nullptr) {}
    void insertNode(int value);
    void deleteNode(int value);
    void inOrderDFS();  // Left, Root, Right
    void preOrderDFS(); // Root, Left, Right
    void postOrderDFS(); // Left, Right, Root
    void BFS();
};

int main(void)
{

}
