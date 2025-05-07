#include <iostream>
using namespace std;
class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node(int x)
    {
        val = x;
        left = NULL;
        right = NULL;
    }
};
class BST
{
    Node *root;

public:
    BST()
    {
        root = NULL;
    }
    Node *insertnode(Node *root, int val)
    {
        if (root == NULL)
        {
            return new Node(val);
        }
        if (val < root->val)
        {
            root->left = insertnode(root->left, val);
        }
        else
        {
            root->right = insertnode(root->right, val);
        }
        return root;
    }
    void inorder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
    Node *create(Node *root)
    {
        int y;
        cout << "enter how many numbers you want to insert:";
        cin >> y;
        for (int i = 0; i < y; i++)
        {
            int k;
            cout << "enter the number: ";
            cin >> k;
            root = insertnode(root, k);
        }
        return root;
    }
    int smallerNO(Node *root)
    {
        Node *temp = root;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp->val;
    }
    int greaterNO(Node *root)
    {
        Node *temp = root;
        while (temp->right != NULL)
        {
            temp = temp->right;
        }
        return temp->val;
    }
};
int main()
{
    BST tree;
    Node *root = NULL;
    root = tree.create(root);
    cout << "inorder traversal is: ";
    tree.inorder(root);
    cout << endl;
    cout << "smaller number is: " << tree.smallerNO(root);
    cout << endl;
    cout << "greater number is: " << tree.greaterNO(root);
    return 0;
}