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
    public:
    Node* root;
    Bst() : root(nullptr) {}
    void insertNode(int value);
    void deleteFirstNode(int value);
    void deleteLastNode(int value);
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
        return;
    }
    
    Node* temp = root;
    while(true)
    {
        if(value <= temp->val && temp->left != nullptr) // traversing tree
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

void Bst::deleteFirstNode(int value) {
    if(root == nullptr)
    {
        return;
    }

    Node* target = root;
    Node* targetParent = nullptr;

    while(target != nullptr && target->val != value) // finding node
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

    if(target == nullptr)  // if node not found
    {
        return;
    }

    if(target->left == nullptr && target->right == nullptr) // case 1: node no children
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
    else if(target->left == nullptr || target->right == nullptr) // case 2: node has one child
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
    else // case 3: node has 2 children
    {
        Node* tempParent = target;
        Node* temp = target->left;
        while(temp->right != nullptr) // finding largest node in the target node's left subtree
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

void Bst::deleteLastNode(int value)
{
    if(root == nullptr)
    {
        return;
    }

    Node *lastMatch = root, *lastMatchParent = nullptr;
    while(lastMatch != nullptr && lastMatch->val != value) // searching for 1st instance of the node in the tree
    {
        lastMatchParent = lastMatch;
        lastMatch = (value < lastMatch->val) ? lastMatch->left : lastMatch->right;
    }

    if(lastMatch == nullptr) // if no node found then return
    {
        return;
    }

    Node *currentMatch = lastMatch->left, *currentMatchParent = lastMatch;
    while(currentMatch != nullptr/* && currentMatch->val != value*/) // find next matching node till end of tree
    {
        if(currentMatch->val == value)
        {
            lastMatch = currentMatch;
            lastMatchParent = currentMatchParent;
        }

        currentMatchParent = currentMatch;
        currentMatch = (value < currentMatch->val) ? currentMatch->left : currentMatch->right;
    }

    // if(currentMatch == nullptr) // no other match found
    // {
    //     currentMatch = lastMatch;
    //     currentMatchParent = lastMatchParent;
    // }

    if(lastMatch->left == nullptr && lastMatch->right == nullptr) // lastMatch is a leaf node
    {
        if(lastMatchParent == nullptr)
        {
            root = nullptr;
        }
        else
        {
            ((lastMatchParent->left == lastMatch) ? lastMatchParent->left : lastMatchParent->right) = nullptr;
        }
        
        // if(lastMatchParent->left == lastMatch)  // above more readable or this one?
        // {
        //     lastMatchParent->left = nullptr;
        // }
        // else
        // {
        //     lastMatchParent->right = nullptr;
        // }
        
        delete lastMatch;
    }
    else if(lastMatch->left == nullptr || lastMatch->right == nullptr) // lastMatch has one child
    {
        Node* lastMatchChild = (lastMatch->left != nullptr) ? lastMatch->left : lastMatch->right;
        if(lastMatchParent == nullptr)
        {
            root = lastMatchChild;
        }
        else if(lastMatchParent->left == lastMatch)
        {
            lastMatchParent->left = lastMatchChild;
        }
        else
        {
            lastMatchParent->right = lastMatchChild;
        }
    }
    else // lastMatch has 2 children
    {
        Node *temp = lastMatch->left, *tempParent = lastMatch;
        while(temp->right != nullptr)
        {
            tempParent = temp;
            temp = temp->right;
        }

        lastMatch->val = temp->val;
        if(tempParent->right == temp)
        {
            tempParent->right = temp->left;
        }
        else
        {
            tempParent->left = temp->left;
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
    std::cout << std::endl;
}

int main(void)
{
    Bst tree;
    tree.insertNode(10);
    tree.insertNode(5);
    tree.insertNode(15);
    tree.insertNode(3);
    tree.insertNode(7);
    tree.insertNode(13);
    tree.insertNode(17);

    tree.BFS();
    tree.inOrderDFS(tree.root);
    std::cout << std::endl;
    tree.preOrderDFS(tree.root);
    std::cout << std::endl;
    tree.postOrderDFS(tree.root);
    std::cout << std::endl;

    tree.deleteFirstNode(1000);
    tree.deleteFirstNode(17);
    tree.deleteFirstNode(15);
    tree.deleteFirstNode(5);
    tree.deleteFirstNode(10);

    tree.BFS();
    tree.inOrderDFS(tree.root);
    std::cout << std::endl;
    tree.preOrderDFS(tree.root);
    std::cout << std::endl;
    tree.postOrderDFS(tree.root);
    std::cout << std::endl;

    tree.insertNode(3);
    tree.insertNode(3);
    tree.insertNode(3);
    tree.insertNode(7);
    tree.insertNode(13);

    tree.BFS();
    tree.inOrderDFS(tree.root);
    std::cout << std::endl;
    tree.preOrderDFS(tree.root);
    std::cout << std::endl;
    tree.postOrderDFS(tree.root);
    std::cout << std::endl;

    tree.deleteLastNode(3);
    tree.deleteLastNode(3);
    tree.deleteLastNode(7);
    tree.deleteLastNode(7);
    tree.deleteLastNode(13);

    tree.BFS();
    tree.inOrderDFS(tree.root);
    std::cout << std::endl;
    tree.preOrderDFS(tree.root);
    std::cout << std::endl;
    tree.postOrderDFS(tree.root);
    std::cout << std::endl;
}
