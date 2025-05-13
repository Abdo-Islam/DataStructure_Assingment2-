#include <iostream>
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

void displaySpaces(int count) {
    for (int i = 0; i < count; ++i)
        cout << " ";
}

class AddressBook {
private:
    Contact* root;
    int n;
    Contact* addContact(Contact* ancestor, id_info data);
    Contact* restructureAdd(Contact* parent);
    bool search(int id);
    Contact* deleteContact(Contact* ancestor, int id);
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
    void addContactPrompt();
    void addContactTest(id_info data);
    bool searchContact();
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

bool AddressBook::searchContact() {
    int id;
    cout << "enter the ID of the contact you want to search : ";
    cin >> id;
    bool isFound = search(id);
    if(isFound) {
        cout << "Contact Found." << endl;
        return true;

    }
    else {
        cout << "Contact Not Found." << endl;
        return false;
    }
}


void AddressBook::listContacts() {
    Contact* p = root;
    inorder(p);
}

void AddressBook::inorder(Contact* p) {
    if(p != nullptr) {
        inorder(p->left);
        cout<<"Node:\n";
        p->listInfo();
        if(p->parent == nullptr){
            cout<<"Parent:\nNULL\n";
        }
        else {
            cout << "Parent:\n";
            p->parent->listInfo();
        }
        if(p->right != nullptr){
            cout<<"Right:\n";
            p->right->listInfo();
        }
        if(p->left != nullptr){
            cout<<"Left:\n";
            p->left->listInfo();
        }
        cout<<endl;
        inorder(p->right);
    }
}


void AddressBook::addContactPrompt() {
    int id;
    contact_info contactInfo;
    id_info data;
    cout << "please enter the ID of the contact you want to addContact : ";
    cin >> id;
    data.id = id;

    while(search(id)) {
        cout << "this ID is used in another contact, please enter another ID : ";
        cin >> id;
    }
    cout << "enter the name of the contact : ";
    cin >> contactInfo.name;
    cout << "enter the email of the contact : ";
    cin >> contactInfo.email;
    cout << "enter the phone of the contact : ";
    cin >> contactInfo.phone;
    data.contactInfo = contactInfo;

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
    root->parent = nullptr;
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
    // Update height of each root
    ancestor->updateHeight();

    // Rebalance the node if needed
    return restructureAdd(ancestor);
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
Contact* AddressBook::deleteContact(Contact* ancestor, int id) {
    // single node tree
    if (ancestor == nullptr)
        return ancestor;

    if (id < ancestor->data.id)
        ancestor->left = deleteContact(ancestor->left, id);

    else if (id > ancestor->data.id)
        ancestor->right = deleteContact(ancestor->right, id);

    else {
        if ((ancestor->left == nullptr) || (ancestor->right == nullptr)) {
            // num children <= 1
            Contact* temp = ancestor->left ? ancestor->left : ancestor->right;

            if (temp != nullptr) {
                // single child case (skip over it)
                temp->parent = ancestor->parent;  // Update parent pointer
                if(ancestor == ancestor->parent->right)
                    ancestor->parent->right = temp;
                else
                    ancestor->parent->left = temp;
            }
            // update parent for both cases
            if (ancestor->parent) {
                if (ancestor->parent->left == ancestor) {
                    ancestor->parent->left = temp;
                } else {
                    ancestor->parent->right = temp;
                }
            }
            // remove contact node
            delete ancestor;
            return temp;
        }
        else {
            // Regular case (replace by successor)
            Contact* successor = minInSubtree(ancestor->right); // min value in the root's right subtree
            id_info successorData = successor->data;
            ancestor->data = successorData;

            // Update the successor's parent's child pointer
            if (successor->parent->left == successor) {
                successor->parent->left = successor->right;
            } else {
                successor->parent->right = successor->right;
            }

            // If the successor has a right child, update its parent pointer
            if (successor->right) {
                successor->right->parent = successor->parent;
            }

            delete successor;

        }
    }
    // This is accessed when base case is reached + backtracking
    ancestor->updateHeight();
    // Rebalance the node if needed
    return restructureAdd(ancestor);
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
    id_info T1, T2, T3, T4, T5, T6, T7;
    T1.id = 1;
    T1.contactInfo = {"A","AA","AAA"};

    T2.id = 2;
    T2.contactInfo = {"B", "BB", "BBB"};

    T3.id = 3;
    T3.contactInfo = {"C", "CC", "CCC"};

    T4.id = 4;
    T4.contactInfo = {"D", "DD", "DDD"};

    T5.id = 5;
    T5.contactInfo = {"E", "EE", "EEE"};

    T6.id = 6;
    T6.contactInfo = {"F", "FF", "FFF"};

    T7.id = 7;
    T7.contactInfo = {"G", "GG", "GGG"};

    id_info T[] = {T1, T2, T3, T4, T5, T6, T7};

    for(int i=0;i<7;i++){
        tree.addContactTest(T[i]);
    }
    cout << "\nContacts:" << endl;
    tree.listContacts();
    cout<<endl;
    tree.displayStructure(tree.getRoot());



    return 0;
}


