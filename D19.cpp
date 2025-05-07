#include <iostream>
#include <cmath>
using namespace std;

struct AVLNode {
    string key, meaning;
    AVLNode *left, *right;
    int height;
    AVLNode(string k, string m) : key(k), meaning(m), left(NULL), right(NULL), height(1) {}
};

int height(AVLNode *node) {
    return node ? node->height : 0;
}

int getBalance(AVLNode *node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

AVLNode* leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

AVLNode* insert(AVLNode *node, string key, string meaning) {
    if (!node) return new AVLNode(key, meaning);

    if (key < node->key)
        node->left = insert(node->left, key, meaning);
    else if (key > node->key)
        node->right = insert(node->right, key, meaning);
    else {
        node->meaning = meaning;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) return rightRotate(node);
    if (balance < -1 && key > node->right->key) return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left)
        current = current->left;
    return current;
}

AVLNode* deleteNode(AVLNode* root, string key) {
    if (!root) return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            delete temp;
        } else {
            AVLNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(AVLNode* node) {
    if (node) {
        inorder(node->left);
        cout << node->key << ": " << node->meaning << endl;
        inorder(node->right);
    }
}

void reverseInorder(AVLNode* node) {
    if (node) {
        reverseInorder(node->right);
        cout << node->key << ": " << node->meaning << endl;
        reverseInorder(node->left);
    }
}

AVLNode* search(AVLNode* node, string key, int& comparisons) {
    while (node) {
        comparisons++;
        if (key == node->key) return node;
        else if (key < node->key) node = node->left;
        else node = node->right;
    }
    return NULL;
}

int countNodes(AVLNode* node) {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

class AVLTree {
    AVLNode* root;
public:
    AVLTree() { root = NULL; }

    void insert(string key, string meaning) {
        root = ::insert(root, key, meaning);  // Use global insert
    }

    void remove(string key) {
        root = deleteNode(root, key);
    }

    void update(string key, string newMeaning) {
        root = ::insert(root, key, newMeaning);  // Use global insert to update
    }

    void display(bool ascending = true) {
        if (ascending) {
            cout << "\nDictionary in Ascending Order:\n";
            inorder(root);
        } else {
            cout << "\nDictionary in Descending Order:\n";
            reverseInorder(root);
        }
    }

    void find(string key) {
        int comparisons = 0;
        AVLNode* result = search(root, key, comparisons);
        if (result)
            cout << "\nFound '" << key << "' with meaning: " << result->meaning
                 << " in " << comparisons << " comparisons.\n";
        else
            cout << "\nKeyword '" << key << "' not found after " << comparisons << " comparisons.\n";
    }

    void maxComparisons() {
        int n = countNodes(root);
        int maxComp = (n == 0) ? 0 : (int)(log2(n)) + 1;
        cout << "\nMaximum comparisons needed in worst case: " << maxComp << endl;
    }
};

int main() {
    AVLTree dict;
    int choice;
    string key, meaning;

    do {
        cout << "\nDictionary Menu:\n";
        cout << "1. Add Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Update Meaning\n";
        cout << "4. Display Ascending\n";
        cout << "5. Display Descending\n";
        cout << "6. Find Keyword\n";
        cout << "7. Max Comparisons\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: "; cin >> key;
                cout << "Enter meaning: "; cin.ignore(); getline(cin, meaning);
                dict.insert(key, meaning);
                break;
            case 2:
                cout << "Enter key to delete: "; cin >> key;
                dict.remove(key);
                break;
            case 3:
                cout << "Enter key: "; cin >> key;
                cout << "Enter new meaning: "; cin.ignore(); getline(cin, meaning);
                dict.update(key, meaning);
                break;
            case 4:
                dict.display(true);
                break;
            case 5:
                dict.display(false);
                break;
            case 6:
                cout << "Enter key to find: "; cin >> key;
                dict.find(key);
                break;
            case 7:
                dict.maxComparisons();
                break;
        }
    } while (choice != 0);

    return 0;
}

