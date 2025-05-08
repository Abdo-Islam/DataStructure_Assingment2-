#include <iostream> 
using namespace std; 

struct contact_info {
    string name;
    string email;
    string phone;
};

struct Node {
    Node* parent; 
    Node* right;
    Node* left;
    int height; 
    int id;
    contact_info data;
    Node(){
        parent = nullptr; 
        right = nullptr; 
        left = nullptr; 
        height = 0; 
    }
    void listInfo() {
        cout << "ID: " << id << ", Name: " << data.name << ", Phone: " << data.phone; 
        cout << ", Email: " << data.email; 
    }
    void displayInfo() {
        cout << "ID: " << id << endl;  
        cout << "Name: " << data.name << endl; 
        cout << "Phone: " << data.phone << endl; 
        cout << "Email: " << data.email << endl; 
    }
}; 

class AVLTree {
private: 
    Node* root; 
    int n;
    void add(Node node);
    bool search(int id); 
    void deletion(int id);  
    void inorder(Node* p); 
public: 
    AVLTree() : n(0) {}
    void addContact();
    bool searchContact();
    void deleteContact();
    void listContacts(); 
    void displayTree(); 
}; 


void AVLTree::addContact() {
    Node contact;  
    cout << "please enter the ID of the contact you want to add : "; 
    cin >> contact.id; 
    while(search(contact.id)) {
        cout << "this ID is used in another contact, please enter another ID : "; 
        cin >> contact.id; 
    }
    cout << "enter the name of the contact : "; 
    cin >> contact.data.name; 
    cout << "enter the email of the contact : "; 
    cin >> contact.data.email; 
    cout << "enter the phone of the contact : "; 
    cin >> contact.data.phone; 
    add(contact); 
}

bool AVLTree::searchContact() {
    int id; 
    cout << "enter the ID of the contact you want to search : "; 
    cin >> id; 
    bool isFound = search(id); 
    if(isFound) {
        cout << "Contact Found." << endl; 

    } 
    else {
        cout << "Contact Not Found." << endl; 
    }
}

void AVLTree::deleteContact() {
    int id; 
    cout << "please enter the ID of the contact you want to delete : "; 
    while(!search(id)) {
        cout << "this id doesn't exist, please enter a valid ID : "; 
        cin >> id; 
    }
    deletion(id); 
}

bool AVLTree::search(int id) {
    Node* p = root;
    while (p != nullptr) {
        if(id == p->id) 
            return true; 
        else if(id > p->id)  
            p = p->right;
        else if(id < p->id)
            p = p->left; 
    }
    return false; 
}


void AVLTree::listContacts() {
    Node* p = root; 
    inorder(p); 
}

void AVLTree::inorder(Node* p) {
    if(p != nullptr) {
        inorder(p->left); 
        p->listInfo(); 
        inorder(p->right); 
    }
}  