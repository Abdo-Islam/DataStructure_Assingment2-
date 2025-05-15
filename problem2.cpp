#include <iostream>
using namespace std;

struct contact_info {
    string name;
    string email;
    string phone;
};
struct id_info{
    contact_info contactInfo;
    int id;
};

struct Contact {
    Contact* parent;
    Contact* right;
    Contact* left;
    int height;
    id_info data;

    //Should we allow the creation of Contact nodes without their ID being specified?
    //I modified the constructor to not allow that
    //The contact info may not be decided at the moment of creation though, therefore I implmented both cases
    Contact(int id){
        parent = nullptr;
        right = nullptr;
        left = nullptr;
        height = 1;
        this->data.id = id;
        this->data.contactInfo.name = "placeholder name";
        this->data.contactInfo.email = "placeholder@email.com";
        this->data.contactInfo.phone = "XXX-XXX-XXXX";
    }
    Contact(id_info data){
        parent = nullptr;
        right = nullptr;
        left = nullptr;
        height = 0;
        this->data.id = data.id;
        this->data.contactInfo.name = data.contactInfo.name;
        this->data.contactInfo.email = data.contactInfo.email;
        this->data.contactInfo.phone = data.contactInfo.phone;
    }
    Contact(int id, contact_info data){
        parent = nullptr;
        right = nullptr;
        left = nullptr;
        height = 0;
        this->data.id = id;
        this->data.contactInfo.name = data.name;
        this->data.contactInfo.email = data.email;
        this->data.contactInfo.phone = data.phone;
    }

    void listInfo() {
        cout << "ID: " << data.id << ", Name: " << data.contactInfo.name << ", Phone: " << data.contactInfo.phone;
        cout << ", Email: " << data.contactInfo.email<<endl;
    }
    void displayInfo() {
        cout << "ID: " << data.id << endl;
        cout << "Name: " << data.contactInfo.name << endl;
        cout << "Phone: " << data.contactInfo.phone << endl;
        cout << "Email: " << data.contactInfo.email << endl;
    }
    void updateHeight();
    int getHeight(){
        return height;
    }
    int getBF();
    Contact* rightRotate(){
        Contact *leftChild = this->left;
        Contact *leftRightGrandchild = leftChild->right;

        leftChild->right = this;
        this->left = leftRightGrandchild;

        // Update parents
        leftChild->parent = this->parent;
        this->parent = leftChild;
        if (leftRightGrandchild) {
            leftRightGrandchild->parent = this;
        }

        // Update heights
        this->updateHeight();
        leftChild->updateHeight();

        return leftChild;
    }
    Contact* leftRotate(){
        Contact *rightChild = this->right;
        Contact *rightLeftGrandchild = rightChild->left;

        rightChild->left = this;
        this->right = rightLeftGrandchild;

        // Update parents
        rightChild->parent = this->parent;
        this->parent = rightChild;
        if (rightLeftGrandchild){
            rightLeftGrandchild->parent = this;
        }
        // Update heights
        this->updateHeight();
        rightChild->updateHeight();

        return rightChild;
    }

};
void Contact::updateHeight(){
    if(this->left == nullptr && this->right == nullptr)
        this->height = 1;
    else if(this->left == nullptr){
        this->height = 1 + this->right->getHeight();
    }
    else if(this->right == nullptr){
        this->height = 1 + this->left->getHeight();
    }
    else{
        this->height = 1 + max(this->left->getHeight(), this->right->getHeight());
    }
}
int Contact::getBF() {
    int leftH = (left ? left->getHeight() : 0);
    int rightH = (right ? right->getHeight() : 0);
    return leftH - rightH;
}

class AddressBook {
private:
    Contact* root;
    int n;
    bool search(int id);// done
    void deleteContact(int id);
    void inorder(Contact* p);   // done 
    Contact* restructureAdd(Contact* node); 
    Contact* addContact(Contact* ancestor, id_info data); 
public:
    AddressBook() : n(0) { root=nullptr;}
    void addContactPrompt();
    bool searchContact();
    //void deleteContactPrompt();
    void listContacts();
    void displayStructure();
    Contact* getRoot(){
        return root;
    }
};


void AddressBook::addContactPrompt() {
    int id;
    id_info data;
    cout << "please enter the ID of the contact you want to addContact : ";
    cin >> id;
    while(search(id)) {
        cout << "this ID is used in another contact, please enter another ID : ";
        cin >> id;
    }
    data.id = id;
    cout << "enter the name of the contact : ";
    cin >> data.contactInfo.name;
    cout << "enter the email of the contact : ";
    cin >> data.contactInfo.email;
    cout << "enter the phone of the contact : ";
    cin >> data.contactInfo.phone;
    Contact* newContact = new Contact(data);

    root = addContact(root, data);
    root->parent=nullptr;
    n++;
}

bool AddressBook::searchContact() {
    int id; 
    cout << "enter the ID of the contact you want to search : "; 
    cin >> id; 
    Contact* p = root;
    while (p != nullptr) {
        if(id == p->data.id) 
        {
            cout << "Contact Found." << endl; 
            p->displayInfo();
            break; 
        }
        else if(id > p->data.id)  
            p = p->right;
        else if(id < p->data.id)
            p = p->left; 
    }
    cout << "Contact Not Found." << endl; 
    return false;
}

/*void AddressBook::deleteContactPrompt() {
    int id;
    cout << "please enter the ID of the contact you want to delete : ";
    cin >> id;
    if(!search(id)) 
        cout << "Contact Not Found." << endl; 
    else {
        deleteContact(id);
        cout << "Contact with ID " << id << " deleted." << endl;
    }
}
    while(!search(id)) {
        cout << "this id doesn't exist, please enter a valid ID : ";
        cin >> id;
    }
    deleteContact(id);
}*/

bool AddressBook::search(int id) {
    Contact* p = root;
    while (p != nullptr) {
        if(id == p->data.id)
            return true;
        else if(id > p->data.id)
            p = p->right;
        else if(id < p->data.id)
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


Contact* AddressBook::restructureAdd(Contact* node) {
    // LX
    if (node->getBF() > 1) {
        if (node->left->getBF() < 0){
            //rotate grandchild
            node->left = node->left->leftRotate(); // LR
        }
        else{
            //LL
        }
        Contact* newRoot = node->rightRotate();

        return newRoot;
    }

        // RX
    else if (node->getBF() < -1) {
        if (node->right->getBF() > 0) {
            node->right = node->right->rightRotate(); // RL
        }
        else{
            //RR
        }

        Contact* newRoot = node->leftRotate();

        return newRoot;
    }
    else {
        return node; // already balanced
    }
}
Contact* AddressBook::addContact(Contact* ancestor, id_info data) {
    if (ancestor == nullptr) {
        return new Contact(data.id, data.contactInfo);
    }

    if (data.id < ancestor->data.id) {
        Contact *newChild = addContact(ancestor->left, data);
        ancestor->left = newChild;
        newChild->parent = ancestor;
    }
    else {
        Contact* newChild = addContact(ancestor->right, data);
        ancestor->right = newChild;
        newChild->parent = ancestor;
    }
    // Update height of each ancestor
    ancestor->updateHeight();

    // Rebalance the node if needed
    return restructureAdd(ancestor);
}

int main() {
    AddressBook tree;

    cout << "Welcome back ya User!" << endl;
    cout << "this is an address book program" << endl;
    cout << "you can add contacts, search for them, delete them, list them or " << endl;
    cout << "display the structure of the address book" << endl;
    cout << "what do you want to do?" << endl;
    cout << "1-enter the input needed manually" << endl;
    cout << "2-enter the input needed from a file" << endl;
    cout << "3-exit" << endl;
    int inputChoice;
    cin >> inputChoice;
    while (inputChoice != 1 && inputChoice != 2 && inputChoice != 3) {
        cout << "please enter a valid choice : ";
        cin >> inputChoice;
    }

    
    
    return 0;
}


