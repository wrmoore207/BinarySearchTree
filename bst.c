#include <stdio.h>
#include <stdlib.h>

// Node structure for Binary Search Tree (BST)
typedef struct bstnode {
    int data;
    struct bstnode* leftChild;
    struct bstnode* rightChild;
} bstnode_t;

// Structure for Binary Search Tree (BST)
typedef struct bst {
    unsigned int size;
    bstnode_t* root;
} bst_t;

// Function to create a new node in the BST
bstnode_t* makeNode(int data) {
    // Allocate memory for the new node
    bstnode_t* newNode = (bstnode_t*)malloc(sizeof(*newNode));
    // Initialize node data and children pointers
    newNode->data = data;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

// Function to create a new BST
bst_t* bst_create() {
    // Allocate memory for the new BST
    bst_t* newBST = (bst_t*)malloc(sizeof(*newBST));
    // Initialize size and root
    newBST->size = 0;
    newBST->root = NULL;
    return newBST;
}

// Function to check if the BST is empty
int bst_empty(bst_t* t) {
    if (t == NULL) {
        return -1; // If the tree is NULL, return -1
    }
    if (t->size == 0) {
        return 0; // If the tree is empty, return 0
    }
    return 1; // If there is at least one item in the tree, return 1
}

// Function to add an item to the BST
int bst_add(bst_t* t, int item) {
    if (t == NULL) {
        return -1; // Return -1 if the tree is NULL
    }
    bstnode_t* newNode = makeNode(item); // Create a new node with the given item

    // If the tree is empty, set the new node as the root
    if (t->root == NULL) {
        t->root = newNode;
        t->size++;
        return 1;
    }

    // If the tree is not empty, use a helper function to recursively add the node
    return addHelper(t->root, newNode);
}

// Helper function to recursively add a node to the BST
int addHelper(bstnode_t* existingNode, bstnode_t* newNode) {
    // Compare the data of the new node with the data of the existing node
    if (newNode->data < existingNode->data) {
        // If the left child is NULL, set the new node as the left child
        if (existingNode->leftChild == NULL) {
            existingNode->leftChild = newNode;
            return 0;
        } else {
            // If the left child is not NULL, recursively call the function on the left child
            return addHelper(existingNode->leftChild, newNode);
        }
    } else if (newNode->data > existingNode->data) {
        // If the right child is NULL, set the new node as the right child
        if (existingNode->rightChild == NULL) {
            existingNode->rightChild = newNode;
            return 0;
        } else {
            // If the right child is not NULL, recursively call the function on the right child
            return addHelper(existingNode->rightChild, newNode);
        }
    }
    // If the data is equal, do not insert (assuming duplicates are not allowed)
    return -1;
}

// Function to print the BST based on the specified order (pre-order, in-order, post-order)
void bst_print(bst_t* t, int order) {
    if (t == NULL) {
        return; // If the tree is NULL, return
    }

    // Check the specified order and call the corresponding print function
    if (order == -1) {
        prePrint(t->root);
    } else if (order == 0) {
        iOPrint(t->root);
    } else if (order == 1) {
        postPrint(t->root);
    }
}

// Pre-order print function
void prePrint(bstnode_t* node) {
    if (node == NULL) {
        return; // If the node is NULL, return
    } else {
        // Print the node's data, then recursively call the function on the left and right children
        printf("%d\n", node->data);
        prePrint(node->leftChild);
        prePrint(node->rightChild);
    }
}

// In-order print function
void iOPrint(bstnode_t* node) {
    if (node == NULL) {
        return; // If the node is NULL, return
    } else {
        // Recursively call the function on the left child, print the node's data, then call on the right child
        iOPrint(node->leftChild);
        printf("%d\n", node->data);
        iOPrint(node->rightChild);
    }
}

// Post-order print function
void postPrint(bstnode_t* node) {
    if (node == NULL) {
        return; // If the node is NULL, return
    } else {
        // Recursively call the function on the left and right children, then print the node's data
        postPrint(node->leftChild);
        postPrint(node->rightChild);
        printf("%d\n", node->data);
    }
}

// Function to calculate the sum of all elements in the BST
int bst_sum(bst_t* t) {
    if (t == NULL) {
        return 0; // If the tree is NULL, return 0
    }

    int sum = 0; // Initialize sum

    // Call a helper function to calculate the sum
    sum = sumHelper(t->root);

    return sum;
}

// Helper function to recursively calculate the sum of all elements in the BST
int sumHelper(bstnode_t* node) {
    if (node == NULL) {
        return 0; // If the node is NULL, return 0
    } else {
        // Sum the node's data, left child, and right child recursively
        return node->data + sumHelper(node->leftChild) + sumHelper(node->rightChild);
    }
}

// Function to find a value in the BST
int bst_find(bst_t* t, int value) {
    if (t == NULL) {
        return 0; // If the tree is NULL, the value is not found
    }

    // Call a helper function to search for the value
    return findHelper(t->root, value);
}

// Helper function to recursively search for a value in the BST
int findHelper(bstnode_t* node, int value) {
    if (node == NULL) {
        return 0; // If the node is NULL, the value is not found
    }

    // Compare the value with the node's data
    if (value == node->data) {
        return 1; // If the value is found, return 1
    } else if (value < node->data) {
        // If the value is less than the node's data, search in the left child
        return findHelper(node->leftChild, value);
    } else {
        // If the value is greater than the node's data, search in the right child
        return findHelper(node->rightChild, value);
    }
}

// Function to get the size of the BST
unsigned int bst_size(bst_t* t) {
    if (t == NULL) {
        return 0; // If the tree is NULL, return 0
    }
    return t->size; // Return the size of the tree
}

// Function to free the memory allocated for the BST
void bst_free(bst_t* t) {
    // Call a helper function to free the memory recursively
    freeHelper(t->root);
    // Free the memory allocated for the BST structure
    free(t);
}

// Helper function to recursively free the memory of each node in the BST
void freeHelper(bstnode_t* node) {
    if (node == NULL) {
        return; // If the node is NULL, return
    }

    // Recursively free the memory of the left and right children
    freeHelper(node->leftChild);
    freeHelper(node->rightChild);

    // Free the memory of the current node
    free(node);
}

int main() {
    // Create a new BST
    bst_t* myBST = bst_create();

    // Insert elements into the BST
    bst_add(myBST, 50);
    bst_add(myBST, 30);
    bst_add(myBST, 70);
    bst_add(myBST, 20);
    bst_add(myBST, 40);
    bst_add(myBST, 60);
    bst_add(myBST, 80);

    // Print the elements in different orders
    printf("In-order traversal:\n");
    bst_print(myBST, 0);

    printf("\nPre-order traversal:\n");
    bst_print(myBST, -1);

    printf("\nPost-order traversal:\n");
    bst_print(myBST, 1);

    // Check if the BST is empty
    if (bst_empty(myBST) == 0) {
        printf("\nThe BST is empty.\n");
    } else {
        printf("\nThe BST is not empty.\n");
    }

    // Get the size of the BST
    printf("Size of the BST: %u\n", bst_size(myBST));

    // Calculate the sum of all elements in the BST
    printf("Sum of elements in the BST: %d\n", bst_sum(myBST));

    // Search for a value in the BST
    int searchValue = 40;
    if (bst_find(myBST, searchValue) == 1) {
        printf("%d is found in the BST.\n", searchValue);
    } else {
        printf("%d is not found in the BST.\n", searchValue);
    }

    // Free memory allocated for the BST
    bst_free(myBST);

    return 0;
}

