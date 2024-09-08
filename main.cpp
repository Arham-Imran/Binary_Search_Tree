#include <iostream>
#include <queue>

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
    void inOrderDFS(Node* temp);  // Left, Root, Right
    void preOrderDFS(Node* temp); // Root, Left, Right
    void postOrderDFS(Node* temp); // Left, Right, Root
    void BFS();
};

void Bst::insertNode(int value)
{
    if(root == nullptr)
    {
        root = new Node(value);
    }
    
    Node* temp = nullptr;
    while(true)
    {
        if(value <= temp->val && temp->left != nullptr)
        {
            temp = temp->left;
        }
        else if(value > temp->val && temp->right != nullptr)
        {
            temp = temp->right;
        }
        else
        {
            if(value <= temp->val)
            {
                temp->left = new Node(value);
            }
            else
            {
                temp->right = new Node(value);
            }
            
            break;
        }
    }
}

void Bst::deleteNode(int value) {
    if(root == nullptr)
    {
        return;
    }

    Node* target = root;
    Node* targetParent = nullptr;

    while(target != nullptr && target->val != value)
    {
        targetParent = target;
        if(value < target->val)
        {
            target = target->left;
        }
        else
        {
            target = target->right;
        }
    }

    if(target == nullptr)
    {
        return;
    }

    if(target->left == nullptr && target->right == nullptr)
    {
        if(targetParent == nullptr)
        {
            root = nullptr;
        }
        else if(targetParent->left == target)
        {
            targetParent->left = nullptr;
        }
        else
        {
            targetParent->right = nullptr;
        }
        delete target;
    }
    else if(target->left == nullptr || target->right == nullptr)
    {
        Node* child = (target->left != nullptr) ? target->left : target->right;

        if(targetParent == nullptr)
        {
            root = child;
        }
        else if(targetParent->left == target)
        {
            targetParent->left = child;
        }
        else
        {
            targetParent->right = child;
        }
        delete target;
    }
    else
    {
        Node* tempParent = target;
        Node* temp = target->left;
        while(temp->right != nullptr)
        {
            tempParent = temp;
            temp = temp->right;
        }

        target->val = temp->val;

        if(tempParent->left == temp)
        {
            tempParent->left = temp->left;
        }
        else
        {
            tempParent->right = temp->left;
        }
        delete temp;
    }
}

void Bst::inOrderDFS(Node* temp) // Left, Root, Right
{
    if(temp == nullptr)
    {
        return;
    }
    else
    {
        inOrderDFS(temp->left);
        std::cout << temp->val << " ";
        inOrderDFS(temp->right); 
    }
}

void Bst::preOrderDFS(Node* temp) // Root, Left, Right
{
    if(temp == nullptr)
    {
        return;
    }
    else
    {
        std::cout << temp->val << " ";
        preOrderDFS(temp->left);
        preOrderDFS(temp->right); 
    }
}

void Bst::postOrderDFS(Node* temp) // Left, Right, Root
{
    if(temp == nullptr)
    {
        return;
    }
    else
    {
        postOrderDFS(temp->left);
        postOrderDFS(temp->right); 
        std::cout << temp->val << " ";
    }
}

void Bst::BFS() 
{
    if(root == nullptr)
    {
        return;
    }

    std::queue<Node*> nodeQueue; 
    nodeQueue.push(root);

    while(!nodeQueue.empty())
    {
        Node* current = nodeQueue.front();
        nodeQueue.pop();

        std::cout << current->val << " ";

        if(current->left != nullptr)
        {
            nodeQueue.push(current->left);
        }

        if(current->right != nullptr)
        {
            nodeQueue.push(current->right);
        }
    }
}

int main(void)
{

}
