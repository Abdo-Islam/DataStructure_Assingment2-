// void AddressBook::addContact(Contact node) {
//     // if(root == nullptr) {
//     //     root = new Contact(node.id, node.data); 
//     //     n++; 
//     // } else {
//     //     Contact* p = root; 
//     //     Contact* parent = nullptr; 
//     //     while(p != nullptr) {
//     //         parent = p; 
//     //         if(node.id < p->id) 
//     //             p = p->left; 
//     //         else if(node.id > p->id) 
//     //             p = p->right; 
//     //         else {
//     //             cout << "Contact with ID " << node.id << " already exists." << endl; 
//     //             return; 
//     //         }
//     //     }
//     //     if(node.id < parent->id) {
//     //         parent->left = new Contact(node.id, node.data); 
//     //         parent->left->parent = parent; 
//     //     } else {
//     //         parent->right = new Contact(node.id, node.data); 
//     //         parent->right->parent = parent; 
//     //     }
    //p = new Contact(node.id, node.data); 
//         p->parent = parent;
//         if(p->id < parent->id){
//             parent->left = p;
//         }
//         else {
//             parent->right = p; 
//         } 
//     //     n++; 
//     // }

//     if(root == nullptr) {
//         root = new Contact(node.id, node.data); 
//     }
//     else {
//         Contact* p = root; 
//         Contact* parent = p; 
//         while (p != nullptr) {
//             parent = p;
//             if(node.id > p->id) 
//                 p = p->right; 
//             else if (node.id < p->id)
//                 p = p->left; 
//         }
//         p = new Contact(node.id, node.data); 
//         p->parent = parent;
//         if(p->id < parent->id){
//             parent->left = p;
//         }
//         else {
//             parent->right = p; 
//         } 
//         p->height = 1;
//     }
//     n++; 
// }