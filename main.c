#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_SIZE 20
#define MAX_TEST_CASES 100

typedef struct Node {
    int key;
    int height;
    int balance;

    char data[DATA_SIZE];

    struct Node* left;
    struct Node* right;
} Node;

Node* root = NULL;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(Node* root) {
    if (root == NULL) {
        return 0;
    }

    return root->height;
}

int calculateHeight(Node* root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + max(getHeight(root->left), getHeight(root->right));
}

int getBalance(Node* root) {
    if (root == NULL) {
        return 0;
    }

    return getHeight(root->left) - getHeight(root->right);
}

Node* rotateLeft(Node* root) {
    Node* newRoot = root->right;
    Node* temp = newRoot->left;

    newRoot->left = root;
    root->right = temp;

    root->height = calculateHeight(root);
    newRoot->height = calculateHeight(newRoot);

    root->balance = getBalance(root);
    newRoot->balance = getBalance(newRoot);

    return newRoot;
}

Node* rotateRight(Node* root) {
    Node* newRoot = root->left;
    Node* temp = newRoot->right;

    newRoot->right = root;
    root->left = temp;

    root->height = calculateHeight(root);
    newRoot->height = calculateHeight(newRoot);

    root->balance = getBalance(root);
    newRoot->balance = getBalance(newRoot);

    return newRoot;
}

Node* balanceTree(Node* root) {
    if (root == NULL) {
        return root;
    }

    root->height = calculateHeight(root);
    root->balance = getBalance(root);

    if (root->balance > 1) {
        if (root->left->balance < 0) {
            root->left = rotateLeft(root->left);
        }
        root = rotateRight(root);
    } else if (root->balance < -1) {
        if (root->right->balance > 0) {
            root->right = rotateRight(root->right);
        }
        root = rotateLeft(root);
    }

    return root;
}

Node* createNode(int key, char data[DATA_SIZE]) {
    Node* newNode = (Node*) malloc(sizeof(Node));

    newNode->key = key;
    strcpy(newNode->data, data);

    newNode->height = 1;
    newNode->balance = 0;

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node* insertNode(Node* root, int key, char data[DATA_SIZE]) {
    if (root == NULL) {
        return createNode(key, data);
    }

    if (key < root->key) {
        root->left = insertNode(root->left, key, data);
    } else if (key > root->key) {
        root->right = insertNode(root->right, key, data);
    }

//    return root;
    return balanceTree(root);
}

Node* getSuccesor(Node* root) {
    Node* temp = root->right;
    while (temp != NULL && temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}

Node* getPredecessor(Node* root) {
    Node* temp = root->left;
    while (temp != NULL && temp->right != NULL) {
        temp = temp->right;
    }
    return temp;
}

Node* removeNode(Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = removeNode(root->left, key);
    } else if (key > root->key) {
        root->right = removeNode(root->right, key);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = getPredecessor(root);
        root->key = temp->key;
        strcpy(root->data, temp->data);
        root->left = removeNode(root->left, temp->key);
    }

    return balanceTree(root);
}

Node* searchNode(Node* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    if (key < root->key) {
        return searchNode(root->left, key);
    } else if (key > root->key) {
        return searchNode(root->right, key);
    } else {
        return root;
    }
}

void updateNode(Node* root, int key, char data[DATA_SIZE]) {
    Node* temp = searchNode(root, key);
    if (temp != NULL) {
        strcpy(temp->data, data);
    }
}

void preOrder(Node* root) {
    if (root == NULL) {
        return;
    }

    printf("%d %s\n", root->key, root->data);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root) {
    if (root == NULL) {
        return;
    }

    inOrder(root->left);
    printf("%d %s\n", root->key, root->data);
    inOrder(root->right);
}

void postOrder(Node* root) {
    if (root == NULL) {
        return;
    }

    postOrder(root->left);
    postOrder(root->right);
    printf("%d %s\n", root->key, root->data);
}

typedef enum {
    INSERT,
    DELETE,
    SEARCH,
    UPDATE
} Operation;

typedef struct TestCase {
    Operation operation;
    int key;
    char data[DATA_SIZE];
} TestCase;

TestCase testCases[MAX_TEST_CASES] = {
//        Ascending sequence of numbers test case
//        {INSERT, 1, "One"},
//        {INSERT, 2, "Two"},
//        {INSERT, 3, "Three"},
//        {INSERT, 4, "Four"},
//        {INSERT, 5, "Five"},
//        {INSERT, 6, "Six"},
//        {INSERT, 7, "Seven"},
//        {INSERT, 8, "Eight"},
//        {INSERT, 9, "Nine"},
//        {INSERT, 10, "Ten"},

//        Descending sequence of numbers test case
//        {INSERT, 10, "Ten"},
//        {INSERT, 9, "Nine"},
//        {INSERT, 8, "Eight"},
//        {INSERT, 7, "Seven"},
//        {INSERT, 6, "Six"},
//        {INSERT, 5, "Five"},
//        {INSERT, 4, "Four"},
//        {INSERT, 3, "Three"},
//        {INSERT, 2, "Two"},
//        {INSERT, 1, "One"},

//        Random sequence of numbers test case
        {INSERT, 41, "FortyOne"},
        {INSERT, 18, "Eighteen"},
        {INSERT, 9, "Nine"},
        {INSERT, 5, "Five"},
        {INSERT, 75, "SeventyFive"},
        {INSERT, 59, "FiftyNine"},
        {INSERT, 12, "Twelve"},
        {INSERT, 100, "OneHundred"},
        {INSERT, 87, "EightySeven"},
        {INSERT, 2, "Two"},

//        Delete test case
        {DELETE, 18, ""},

//        Update test case
        {UPDATE, 41, "NewFortyOne"}
};

int main() {
    int testCaseSize = 12;

    for (int i = 0; testCases[i].operation >= 0 && testCases[i].operation <= 3 && i < testCaseSize; i++) {
        switch (testCases[i].operation) {
            case INSERT:
                printf("Inserting: %d %s\n", testCases[i].key, testCases[i].data);
                root = insertNode(root, testCases[i].key, testCases[i].data);
                break;
            case DELETE:
                printf("Deleting: %d\n", testCases[i].key);
                root = removeNode(root, testCases[i].key);
                break;
            case SEARCH: {
                    printf("Searching: %d\n", testCases[i].key);
                    Node* found = searchNode(root, testCases[i].key);
                    if (found) {
                        printf("Found: %d %s\n", found->key, found->data);
                    } else {
                        printf("Not found: %d\n", testCases[i].key);
                    }
                }
                break;
            case UPDATE:
                printf("Updating: %d %s\n", testCases[i].key, testCases[i].data);
                updateNode(root, testCases[i].key, testCases[i].data);
                break;
        }
    }

    printf("\n");
    printf("PreOrder Traversal:\n");
    preOrder(root);
    printf("\nInOrder Traversal:\n");
    inOrder(root);
    printf("\nPostOrder Traversal:\n");
    postOrder(root);

    return 0;
}
