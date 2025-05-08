#include <iostream> 
using namespace std; 

struct contact_info {
    string name;
    string email;
    string phone;
};

struct Contact {
    Contact* parent;
    Contact* right;
    Contact* left;
    int height; 
    int id;
    contact_info data;
    Contact(){
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

class AddressBook {
private: 
    Contact* root;
    int n;
    void add(Contact node);
    bool search(int id); 
    void deletion(int id);  
    void inorder(Contact* p);
public: 
    AddressBook() : n(0) {}
    void addContact();
    bool searchContact();
    void deleteContact();
    void listContacts(); 
    void displayStructure();
}; 


void AddressBook::addContact() {
    Contact contact;
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

bool AddressBook::searchContact() {
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

void AddressBook::deleteContact() {
    int id; 
    cout << "please enter the ID of the contact you want to delete : "; 
    while(!search(id)) {
        cout << "this id doesn't exist, please enter a valid ID : "; 
        cin >> id; 
    }
    deletion(id); 
}

bool AddressBook::search(int id) {
    Contact* p = root;
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


void AddressBook::listContacts() {
    Contact* p = root;
    inorder(p); 
}

void AddressBook::inorder(Contact* p) {
    if(p != nullptr) {
        inorder(p->left); 
        p->listInfo(); 
        inorder(p->right); 
    }
}  