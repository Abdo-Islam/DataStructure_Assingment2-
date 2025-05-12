#include <iostream>
#include <fstream>
#include <string> 
using namespace std;

class node{
public:
    string URL;
    node* next;
    node(){
        this->URL = "";
        this->next = NULL;
    }
    node(string url){
        this->URL = url;
        this->next = NULL;
    }
};

class LinkedStack{
    node* top;
    int size;
public:
    LinkedStack(){
        top = NULL;
        size = 0;
    }
    LinkedStack(string url){
        node* data = new node;
        data->URL = url;
        data->next = top;
        top = data;
        size++;
    }
    bool isEmpty(){
        return (top == NULL);
    }
    void push(string url){
            node* data = new node;
            data->URL = url;
            data->next = top;
            top = data;
            size++;
    }
    void clear(){
        node* temp = new node;
        while(top != NULL){
            temp = top;
            top = top->next;
            delete temp;
        }
        size = 0;
    }
    string getTop(){
        if(isEmpty()){
            string empty = "[]";
            return empty;
        }
        else
            return top->URL;
    }
    void pop(){
        if(!isEmpty()){
            node* temp = top;
            top = top->next;
            delete temp;
        }
        size--;
    }
    int getSize(){
        return size;
    }
    void display(){
        if(!isEmpty()){
            node* temp = top;
            cout << "[  ";
            while(temp != NULL){
                cout << temp->URL << "  ";
                temp = temp->next;
            }
            cout << "]\n";
        }
        else
            cout << "[]\n";
    }
    ~LinkedStack(){
        clear();
    }
};

int convert(string line){
    if(line[2] == 's')
        return 1;
    else if(line[2] == 'B' || line[2] == 'b')
        return 2;
    else
        return 3;
}

string getUrl(string line){
    string url = "";
    for(int i = 7; i < line.length()-2; i++){
        url += line[i];
    }
    return url;
}
int main(){
    LinkedStack Back;
    LinkedStack Forward;
    int option;
    string fileName = "";
    cout << "Insert file name with extension .txt : \n--> ";
    cin >> fileName;
    ifstream inFile(fileName);
    string line;
    if (inFile.is_open()) {
        while (getline(inFile, line)) { 
            option = convert(line);
            if(option == 1){
                string url = getUrl(line);
                Forward.clear();
                Back.push(url);
                cout << "Visiting...\n";
                cout << "Back Stack: ";
                Back.display();
                cout << "Forward Stack: ";
                Forward.display();
                cout << "Current: " << Back.getTop() << "\n\n";
            }
            else if(option == 2){
                cout << "Go Back...\n";
                if(Back.getSize() > 1){
                    Forward.push(Back.getTop());
                    Back.pop();
                    cout << "Back Stack: ";
                    Back.display();
                    cout << "Forward Stack: ";
                    Forward.display();
                    cout << "Current: " << Back.getTop() << "\n\n";
                }
                else{
                    cout << "Can't go back :(\nEnter more URLs pls :)\n\n";
                    cout << "backStack: ";
                    Back.display();
                    cout << "Forward Stack: ";
                    Forward.display();
                    cout << "Current: " << Back.getTop() << "\n\n";
                }
            }
            else{
                cout << "Go Forward...\n";
                if(Forward.getSize() > 0){
                    Back.push(Forward.getTop());
                    Forward.pop();
                    cout << "backStack: ";
                    Back.display();
                    cout << "Forward Stack: ";
                    Forward.display();
                    cout << "Current: " << Back.getTop() << "\n\n";
                }
                else{
                    cout << "Can't go forward :(\nNo history yet :(\n";
                    cout << "backStack: ";
                    Back.display();
                    cout << "Forward Stack: ";
                    Forward.display();
                    cout << "Current: " << Back.getTop() << "\n\n";
                }
            }
        }
        cout << "\nDone reading file :)\n";
        inFile.close();
    }
    else {
        cout << "Wrong file name : " << fileName << "\nTry again at another time :)\n";
        return 0;
    } 
}