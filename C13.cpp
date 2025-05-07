#include <iostream>
using namespace std;
class Node{
public:
    string data;
    Node *left;
    Node *right;
    Node(string val){
        data = val;
        left = right = NULL;
    }
};
class Stack{
private:
    struct StackNode{
        Node *treeNode;
        StackNode *next;
        StackNode(Node *node, StackNode *nextNode) : treeNode(node), next(nextNode) {}
    };
    StackNode *top;

public:
    Stack(){
        top = NULL;
    }
    void push(Node *node){
        StackNode *newNode = new StackNode(node, top);
        top = newNode;
    }
    Node *pop(){
        if (isEmpty())
            return NULL;
        StackNode *temp = top;
        top = top->next;
        Node *poppedNode = temp->treeNode;
        delete temp;
        return poppedNode;
    }
    bool isEmpty(){
        return top == NULL;
    }
};
class Queue{
private:
    struct QueueNode{
        Node *treeNode;
        QueueNode *next;

        QueueNode(Node *node, QueueNode *nextNode) : treeNode(node), next(nextNode) {}
    };
    QueueNode *front, *rear;

public:
    Queue(){
        front = rear = NULL;
    }
    void enqueue(Node *node){
        QueueNode *newNode = new QueueNode(node, NULL);
        if (rear == NULL){
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }
    Node *dequeue(){
        if (isEmpty())
            return NULL;
        QueueNode *temp = front;
        front = front->next;
        if (front == NULL)
            rear = NULL;
        Node *dequeuedNode = temp->treeNode;
        delete temp;
        return dequeuedNode;
    }
    bool isEmpty(){
        return front == NULL;
    }
};
class Tree{
private:
    Node *root;
    Node *insertNode(){
        string value;
        cout << "Enter value (-1 for no node): ";
        cin >> value;
        if (value == "-1")
            return NULL;
        Node *newNode = new Node(value);
        cout << "Enter left child of " << value << ":\n";
        newNode->left = insertNode();
        cout << "Enter right child of " << value << ":\n";
        newNode->right = insertNode();
        return newNode;
    }
    // Recursive Traversals
    void inorder(Node *root){
        if (root == NULL)
            return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
    void preorder(Node *root){
        if (root == NULL)
            return;
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
    void postorder(Node *root){
        if (root == NULL)
            return;
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }

public:
    Tree(){
        root = NULL;
    }
    void insert(){
        root = insertNode();
    }
    void inorderNonRecursive(){
        if (root == NULL)
            return;
        Stack s;
        Node *current = root;
        while (current != NULL || !s.isEmpty()){
            while (current != NULL){
                s.push(current);
                current = current->left;
            }
            current = s.pop();
            cout << current->data << " ";
            current = current->right;
        }
    }
    void preorderNonRecursive(){
        if (root == NULL)
            return;
        Stack s;
        s.push(root);
        while (!s.isEmpty())
        {
            Node *current = s.pop();
            cout << current->data << " ";
            if (current->right)
                s.push(current->right);
            if (current->left)
                s.push(current->left);
        }
    }
    void postorderNonRecursive(){
        if (root == NULL)
            return;
        Stack s1, s2;
        s1.push(root);
        while (!s1.isEmpty()){
            Node *current = s1.pop();
            s2.push(current);
            if (current->left)
                s1.push(current->left);
            if (current->right)
                s1.push(current->right);
        }
        while (!s2.isEmpty()){
            cout << s2.pop()->data << " ";
        }
    }
    void levelOrder(){
        if (root == NULL)
            return;
        Queue q;
        q.enqueue(root);
        while (!q.isEmpty()){
            Node *current = q.dequeue();
            cout << current->data << " ";
            if (current->left)
                q.enqueue(current->left);
            if (current->right)
                q.enqueue(current->right);
        }
    }
    void printTree(){
        if (root == NULL){
            cout << "Tree is empty!\n";
            return;
        }
        int choice;
        cout << "Select traversal type:\n";
        cout << "1. Recursive Traversal\n";
        cout << "2. Non-Recursive Traversal\n";
        cin >> choice;
        if (choice == 1){
            cout << "1. Inorder\n2. Preorder\n3. Postorder\n";
            cin >> choice;
            switch (choice){
            case 1:
            	cout<<"Inorder Traversal: ";
                inorder(root);
                break;
            case 2:
            	cout<<"Preorder Traversal: ";
                preorder(root);
                break;
            case 3:
            	cout<<"Postorder Traversal: ";
                postorder(root);
                break;
            default:
                cout << "Invalid choice!\n";
                return;
            }
        }
        else if (choice == 2){
            cout << "1. Inorder\n2. Preorder\n3. Postorder\n4. Level Order\n";
            cin >> choice;
            switch (choice){
            case 1:
            	cout<<" NonRec Inorder Traversal: ";
                inorderNonRecursive();
                break;
            case 2:
            	cout<<" NonRec Preorder Traversal: ";
                preorderNonRecursive();
                break;
            case 3:
            	cout<<" NonRec Postorder Traversal: ";
                postorderNonRecursive();
                break;
            case 4:
            	cout<<" NonRec Levelorder Traversal: ";
                levelOrder();
                break;
            default:
                cout << "Invalid choice!\n";
                return;
            }
        }
        else{
            cout << "Invalid choice!\n";
        }
        cout << endl;
    }
};
int main(){
    Tree tree;
    int choice;
    do{
        cout << "Menu:\n1. Insert\n2. Print\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice){
        case 1:
            tree.insert();
            break;
        case 2:
            tree.printTree();
            break;
        case 3:
            cout << "Exiting Program...\n";
            break;
        default:
            cout << "Invalid choice! Enter a valid choice.\n";
        }
    } while (choice != 3);
    return 0;
}
