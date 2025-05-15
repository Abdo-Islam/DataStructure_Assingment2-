#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
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
        height = 1;
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

void displaySpaces(int count) {
    for (int i = 0; i < count; ++i)
        cout << " ";
}

class AddressBook {
private:
    Contact* root;
    int n;
    Contact* addContact(Contact* ancestor, id_info data);
    Contact* restructure(Contact* node);
    Contact* minInSubtree(Contact* root);
    void displayStructureLogic(Contact** contactsAtLevel, int level, int maxLevel);
    int maxDepth(Contact* node) {
        if (node == nullptr)
        return 0;
        return max(maxDepth(node->left), maxDepth(node->right)) + 1;
    }
    void deleteTree(Contact* root);
    
    public:
    AddressBook() : n(0) { root=nullptr;}
    Contact* getContact(int id);
    void addContactPrompt();
    void addContactTest(id_info data);
    Contact* deleteContact(Contact* root, int id);
    bool search(int id);
    void searchContactPrompt();
    void deleteContactPrompt();
    void listContacts();
    void inorder(Contact* p);
    Contact* getRoot(){return root;}
    void displayStructure(Contact* root);
    ~AddressBook() {deleteTree(root);}
};
Contact* AddressBook::minInSubtree(Contact* root) {
    Contact* current = root;

    // loop down to find the leftmost leaf
    while (current->left != nullptr)
        current = current->left;
    return current;
}


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
Contact* AddressBook::getContact(int id) {
    Contact* p = root;
    while (p != nullptr) {
        if(id == p->data.id) {
            return p;
        }
        else if(id > p->data.id)
            p = p->right;
        else if(id < p->data.id)
            p = p->left;
    }
    return nullptr;
}

void AddressBook::searchContactPrompt() {
    int id;
    cout << "enter the ID of the contact you want to search : ";
    cin >> id;
    bool isFound = false;
    if(search(id))
        isFound = true;
    if(isFound) {
        cout << "Contact Found." << endl;
        Contact* p = getContact(id);
        p->displayInfo();
    }
    else {
        cout << "Contact Not Found." << endl;
    }
}

void AddressBook::listContacts() {
    Contact* p = root;
    if(p == nullptr) {
        cout << "No contacts in the address book." << endl;
        return;
    }
    inorder(p);
}

void AddressBook::inorder(Contact* p) {
    if(p != nullptr) {
        inorder(p->left);
        p->listInfo();
        inorder(p->right);
    }
}


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
void AddressBook::addContactTest(id_info data){
    root = addContact(root, data);
    root->parent=nullptr;
    n++;
}

void AddressBook::deleteContactPrompt() {
    int id;
    cout << "please enter the ID of the contact you want to delete : ";
    cin >> id;
    while(!search(id)) {
        cout << "this id doesn't exist, please enter a valid ID : ";
        cin >> id;
    }
    root = deleteContact(root, id);
    if (root != nullptr)
        root->parent = nullptr;
}

Contact* AddressBook::addContact(Contact* parent, id_info data) {
    if (parent == nullptr) {
        return new Contact(data.id, data.contactInfo);
    }

    if (data.id < parent->data.id) {
        Contact *newChild = addContact(parent->left, data);
        parent->left = newChild;
        newChild->parent = parent;
    }
    else {
        Contact* newChild = addContact(parent->right, data);
        parent->right = newChild;
        newChild->parent = parent;
    }
    // Update height of each root
    parent->updateHeight();

    // Rebalance the node if needed
    return restructure(parent);
}
Contact* AddressBook::restructure(Contact* node) {
    // LX
    if (node->getBF() > 1) {
        if (node->left->getBF() < 0){
            //rotate grandchild
            node->left = node->left->rightRotate(); // LR
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
            node->right = node->right->leftRotate(); // RL
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

Contact* AddressBook::deleteContact(Contact* root, int id) {
    // single node tree
    if (root == nullptr)
        return root;

    if (id < root->data.id) {
        root->left = deleteContact(root->left, id);
        if (root->left) root->left->parent = root;  // Fix child pointer
    }

    else if (id > root->data.id) {
        root->right = deleteContact(root->right, id);
        if (root->right) root->right->parent = root;  // Fix child pointer
    }

    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            // num children <= 1
            Contact* temp = root->left ? root->left : root->right;

            // single child case (must update its parent)
            if (temp != nullptr) {
                temp->parent = root->parent;
            }

            // If root has a parent, link it with its new child (may be null)
            if (root->parent != nullptr) {
                if (root->parent->left == root) {
                    root->parent->left = temp;
                } else {
                    root->parent->right = temp;
                }
            } else {
                // root node of the entire tree being deleted
                this->root = temp;
            }

            delete root;
            return temp;
        }

        else {
            // Regular case (replace by successor)
            Contact* successor = minInSubtree(root->right); // min value in the root's right subtree
            id_info successorData = successor->data;
            root->data = successorData;

            // Delete successor (which will have at most one child)
            root->right = deleteContact(root->right, successorData.id);
            if (root->right) root->right->parent = root;  // Fix child pointer

            // No need to return early, continue to update and rebalance below
        }
    }

    // Update height
    root->updateHeight();

    // Rebalance the node if needed
    Contact* newRoot = restructure(root);

    // Fix parent-child linkage if root was rotated
    if (newRoot->parent == nullptr) {
        this->root = newRoot;
    }

    return newRoot;
}


void AddressBook::displayStructureLogic(Contact** contactsAtLevel, int level, int maxLevel) {
    int levelWidth = (int)pow(2, level - 1);
    bool allNull = true;
    for (int i = 0; i < levelWidth; ++i) {
        if (contactsAtLevel[i] != nullptr) {
            allNull = false;
            break;
        }
    }
    if (allNull)
        return;

    int floor = maxLevel - level;
    int betwNodeAndChildLinkSpaces = (int)pow(2, max(floor - 1, 0));
    int preSpaces = (int)pow(2, floor) - 1;
    int betwNodesSpaces = (int)pow(2, floor + 1) - 1;

    displaySpaces(preSpaces);

    for (int i = 0; i < levelWidth; ++i) {
        if (contactsAtLevel[i] != nullptr)
            cout << contactsAtLevel[i]->data.id;
        else
            cout << " ";
        displaySpaces(betwNodesSpaces);
    }
    cout << endl;

    for (int i = 0; i < levelWidth; ++i) {
        displaySpaces(preSpaces - betwNodeAndChildLinkSpaces);

        if (contactsAtLevel[i] == nullptr) {
            displaySpaces(betwNodeAndChildLinkSpaces * 2 + betwNodeAndChildLinkSpaces + 1);
            continue;
        }

        if (contactsAtLevel[i]->left != nullptr)
            cout << "/";
        else
            displaySpaces(1);

        displaySpaces(betwNodeAndChildLinkSpaces * 2 - 1);

        if (contactsAtLevel[i]->right != nullptr)
            cout << "\\";
        else
            displaySpaces(1);

        displaySpaces(betwNodeAndChildLinkSpaces * 2 - betwNodeAndChildLinkSpaces);
    }
    cout << endl;

    Contact** nextLevel = new Contact*[levelWidth * 2];
    for (int i = 0; i < levelWidth * 2; ++i)
        nextLevel[i] = nullptr;

    for (int i = 0; i < levelWidth; ++i) {
        nextLevel[2 * i] = contactsAtLevel[i] ? contactsAtLevel[i]->left : nullptr;
        nextLevel[2 * i + 1] = contactsAtLevel[i] ? contactsAtLevel[i]->right : nullptr;
    }

    displayStructureLogic(nextLevel, level + 1, maxLevel);
    delete[] nextLevel;

}
void AddressBook::displayStructure(Contact* root) {
    int maxLevel = maxDepth(root);
    if(n == 0) {
        cout << "No contacts in the address book." << endl;
        return;
    }
    int maxNumContacts = (int)pow(2, maxLevel);

    Contact** currentLevel = new Contact*[maxNumContacts];
    for (int i = 0; i < maxNumContacts; ++i)
        currentLevel[i] = nullptr;

    currentLevel[0] = root;
    displayStructureLogic(currentLevel, 1, maxLevel);
    delete[] currentLevel;
}
void AddressBook::deleteTree(Contact* root) {
    if (root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
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
    int inputChoice;
    cin >> inputChoice;
    while (inputChoice != 1 && inputChoice != 2 && inputChoice != 3) {
        cout << "please enter a valid choice : ";
        cin >> inputChoice;
    }  
    if (inputChoice == 1) {
        int choice;
        do {
            cout << "1-add contact" << endl;
            cout << "2-search for a contact" << endl;
            cout << "3-delete a contact" << endl;
            cout << "4-list all contacts" << endl;
            cout << "5-display the structure of the address book" << endl;
            cout << "6-exit" << endl;
            cin >> choice;

            switch (choice) {
                case 1:
                    tree.addContactPrompt();
                    break;
                case 2:
                    tree.searchContactPrompt();
                    break;
                case 3:
                    tree.deleteContactPrompt();
                    break;
                case 4:
                    tree.listContacts();
                    break;
                case 5:
                    tree.displayStructure(tree.getRoot());
                    break;
                case 6:
                    cout << "Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 6);
    }
    else if (inputChoice == 2) {
        ifstream inputFile("contacts.txt");
        string line; 
        if (!inputFile) {
            cout << "Error opening file." << endl;
            return 1;
        }
        while(getline(inputFile, line)) {
            stringstream ss(line);
            id_info data;
            ss >> data.id;
            ss.ignore(1); 
            getline(ss, data.contactInfo.name, ',');
            getline(ss, data.contactInfo.phone, ',');   
            getline(ss, data.contactInfo.email, ',');
            tree.addContactTest(data);
        }
        tree.listContacts();
        tree.displayStructure(tree.getRoot());
        tree.deleteContact(tree.getRoot(), 7); 
        cout << "contact with id 7 deleted" << endl;
        tree.deleteContact(tree.getRoot(), 3); 
        cout << "contact with id 3 deleted" << endl;
        tree.deleteContact(tree.getRoot(), 4);
        cout << "contact with id 4 deleted" << endl;
        if (tree.search(3)) 
        cout << "contact with id 3 exists" << endl;
        else
        cout << "contact with id 3 doesn't exist" << endl; 
        if (tree.search(5))
        cout << "contact with id 5 exists" << endl;
        else
        cout << "contact with id 5 doesn't exist" << endl;
        tree.listContacts();
        tree.displayStructure(tree.getRoot());
    }
    return 0;
}


