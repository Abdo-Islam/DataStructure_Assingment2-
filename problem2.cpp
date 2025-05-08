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

    //Should we allow the creation of Contact nodes without their ID being specified?
    //I modified the constructor to not allow that
    //The contact info may not be decided at the moment of creation though, therefore I implmented both cases
    Contact(int id){
        parent = nullptr; 
        right = nullptr; 
        left = nullptr; 
        height = 0;
        this->id = id;
        this->data.name = "placeholder name";
        this->data.email = "placeholder@email.com";
        this->data.phone = "XXX-XXX-XXXX";
    }
    Contact(int id, contact_info data){
        parent = nullptr;
        right = nullptr;
        left = nullptr;
        height = 0;
        this->id = id;
        this->data.name = data.name;
        this->data.email = data.email;
        this->data.phone = data.phone;
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
    void addContact(Contact node);
    bool search(int id); 
    void deleteContact(int id);
    void inorder(Contact* p);
public: 
    AddressBook() : n(0) {}
    void addContactPrompt();
    bool searchContact();
    void deleteContactPrompt();
    void listContacts(); 
    void displayStructure();
}; 


void AddressBook::addContactPrompt() {
    int id;
    contact_info data;
    cout << "please enter the ID of the contact you want to addContact : ";
    cin >> id;

    while(search(id)) {
        cout << "this ID is used in another contact, please enter another ID : ";
        cin >> id;
    }
    cout << "enter the name of the contact : "; 
    cin >> data.name; 
    cout << "enter the email of the contact : "; 
    cin >> data.email; 
    cout << "enter the phone of the contact : "; 
    cin >> data.phone; 
    
    Contact contact(id, data);
    addContact(contact);
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

void AddressBook::deleteContactPrompt() {
    int id; 
    cout << "please enter the ID of the contact you want to delete : "; 
    cin >> id;
    while(!search(id)) {
        cout << "this id doesn't exist, please enter a valid ID : "; 
        cin >> id; 
    }
    deleteContact(id);
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