#include <iostream>
#include <string.h>
using namespace std;

struct node{
    string label;
    int count;
    struct node *child[10];
}*root;

class GT{
public:
    void create();
    void display(node *r1);
    GT(){root=NULL;}
};

void GT::create(){
    int books, chapters;
    root = new node;
    cout << "Enter book name: ";
    cin >> root->label;
    cout << "Enter number of chapters in book \"" << root->label << "\": ";
    cin >> chapters;
    root->count = chapters;
    for (int i = 0; i < chapters; i++){
        root->child[i] = new node;
        cout << "Enter chapter " << i + 1 << " name: ";
        cin >> root->child[i]->label;
        cout << "Enter number of sections in chapter \""<< root->child[i]->label << "\": ";
        cin >> root->child[i]->count;
        for (int j = 0; j < root->child[i]->count; j++){
            root->child[i]->child[j] = new node;
            cout << "Enter section " << j + 1 << " name: ";
            cin >> root->child[i]->child[j]->label;
            cout << "Enter number of subsections in section \""<< root->child[i]->child[j]->label << "\": ";
        	cin >> root->child[i]->child[j]->count;
            for (int k = 0; k < root->child[i]->child[j]->count; k++){
		        root->child[i]->child[j]->child[k] = new node;
		        cout << "Enter subsection " << k + 1 << " name: ";
		        cin >> root->child[i]->child[j]->child[k]->label;
			}
        }
    }
}

void GT::display(node *r1){
    int chapters;
    if (r1 != NULL){
        cout << "\n-----Book Hierarchy---";
        cout << "\nBook title: " << r1->label;
        for (int i = 0; i < r1->count; i++){
            cout << "\nChapter " << i + 1 << ": " << r1->child[i]->label;
			for (int j = 0; j < r1->child[i]->count; j++){
	            cout << "\nSection "<< j + 1 << ": " << r1->child[i]->child[j]->label;
	            for (int k = 0; k < r1->child[i]->child[j]->count; k++){
		            cout << "\nSubsection " << k + 1 << ": " << r1->child[i]->child[j]->child[k]->label;
		    	}    
            }
        }
    }
}
int main(){
    int choice;
    GT gt;
    char c='y';
    do{
        cout << "\nBook Tree Creation\n-----------------\n1.Create\n2.Display\nEnter your choice: ";
        cin >> choice;
        switch (choice){
        case 1:
            gt.create();
            break;
        case 2:
            gt.display(root);
            break;
        default:
            cout << "Invalid choice!!!";
        }
        cout << "Do you want to continue? (y/n): ";
        cin >> c;
    }while (c=='y');
    return 0;
}

