#include<iostream>
using namespace std;
class Node{
    public:
    int val;
    Node*left;
    Node*right;
    Node(int x){
        val=x;
        left=NULL;
        right=NULL;
    }
};
class BST{
    Node*root;
    public:
        BST(){
            root=NULL;
        }
        Node*insertnode(Node*root,int val){
            if(root==NULL){
                return new Node(val);
            }
            if(val<root->val){
                root->left=insertnode(root->left,val);
            }else{
                root->right=insertnode(root->right,val);
            }
            return root;
        }
        void inorder(Node*root){
            if(root==NULL){
                return ;
            }
            inorder(root->left);
            cout<<root->val<<" ";
            inorder(root->right);
        }
       void searching(Node* root, int key) {
            if (root == NULL) {
            cout << "key not found.";
            return;
            }

            if (root->val == key) {
            cout << "key is found.";
            return; 
            }

            if (root->val < key) {
                searching(root->right, key); 
            }
            else {
                searching(root->left, key); 
            }
        }
        Node* mirror(Node* root) {
           if(root == NULL)return NULL;
           Node* p ;
           p = root->left;
           root->left = mirror(root->right);
           root->right = mirror(p);
           return root;
        }

        Node* create(Node*root){
            int y;
            cout<<"Enter how many numbers you want to insert:";
            cin>>y;
            for(int i=0;i<y;i++){
                int k;
                cout<<"Enter the number: ";
                cin>>k;
                root=insertnode(root,k);
            }
            return root;
        }
        int height(Node* root){
            int hl;
            int hr;
            if(root == NULL){
                return 0;
            }
            if(root->left == NULL && root->right ==NULL){
                return 0;
            }
            hl = 1 + height(root->left);
            hr = 1 + height(root->right);
            if(hl >= hr){
                return hl;
            }
            else if(hr > hl){
                return hr;
                }
            
        }
        int smaller(Node*root){
            Node*temp=root;
            while(temp->left!=NULL){
                temp=temp->left;
            }
            return temp->val;
        }
        int greater(Node*root){
            Node*temp=root;
            while(temp->right!=NULL){
                temp=temp->right;
            }
            return temp->val;
        }
};
int main(){
    BST tree;
    Node*root=NULL;
    root=tree.create(root);
    cout<<"inorder traversal is: ";
    // tree.insertnode(root,7);       
    tree.inorder(root);
    cout<<endl;
    cout<<"smaller number is: "<<tree.smaller(root);
    cout<<endl;
    cout<<"greater number is: "<<tree.greater(root)<<endl;
    cout<<"\nwhich number want to find: ";
    int num;
    cin>>num;
    tree.searching(root,num);
    cout<<endl;
    cout<<"tree after swaping:";
    tree.mirror(root);
    tree.inorder(root);
    cout<<endl;
    cout<<"height of tree: "<<tree.height(root);
    return 0;
}