#include <stdio.h>
#include <stdlib.h>

// NODE 
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// QUEUE (for level-order construction) 
typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// QUEUE FUNCTIONS
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, Node* node) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->treeNode = node;
    temp->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

Node* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;

    QueueNode* temp = q->front;
    Node* node = temp->treeNode;

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return node;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

//  TREE NODE 
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// LEVEL-ORDER INSERTION 
Node* buildTree(int arr[], int size) {
    if (size == 0) return NULL;

    Node* root = createNode(arr[0]);

    Queue* q = createQueue();
    enqueue(q, root);

    int i = 1;

    while (i < size && !isEmpty(q)) {
        Node* current = dequeue(q);

        // left child
        if (i < size) {
            current->left = createNode(arr[i++]);
            enqueue(q, current->left);
        }

        // right child
        if (i < size) {
            current->right = createNode(arr[i++]);
            enqueue(q, current->right);
        }
    }

    return root;
}

// SEARCH 
Node* search(Node* root, int value) {
    if (root == NULL) return NULL;

    if (root->data == value)
        return root;

    Node* left = search(root->left, value);
    if (left != NULL) return left;

    return search(root->right, value);
}

// FIND PARENT 
Node* findParent(Node* root, Node* target) {
    if (root == NULL || target == NULL) return NULL;

    if (root->left == target || root->right == target)
        return root;

    Node* left = findParent(root->left, target);
    if (left != NULL) return left;

    return findParent(root->right, target);
}

// LEAF NODES 
void printLeaves(Node* root) {
    if (root == NULL) return;

    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->data);
        return;
    }

    printLeaves(root->left);
    printLeaves(root->right);
}

// SIBLINGS 
void printSiblings(Node* root, Node* target) {
    Node* parent = findParent(root, target);

    if (parent == NULL) {
        printf("No siblings (root node)\n");
        return;
    }

    if (parent->left == target && parent->right)
        printf("Sibling: %d\n", parent->right->data);
    else if (parent->right == target && parent->left)
        printf("Sibling: %d\n", parent->left->data);
    else
        printf("No siblings\n");
}

//  GRANDCHILDREN 
void printGrandchildren(Node* node) {
    if (node == NULL) return;

    if (node->left) {
        if (node->left->left) printf("%d ", node->left->left->data);
        if (node->left->right) printf("%d ", node->left->right->data);
    }

    if (node->right) {
        if (node->right->left) printf("%d ", node->right->left->data);
        if (node->right->right) printf("%d ", node->right->right->data);
    }
}

// MAIN 
int main() {

    int arr[68] = {
        45, 12, 78, 33, 90, 21, 67, 54,
        10, 29, 85, 60, 3, 99, 41, 72,
        18, 50, 36, 27, 88, 64, 1, 14,
        75, 93, 58, 31, 47, 82, 6, 95,
        22, 39, 70, 11, 56, 84, 25, 68,
        2, 16, 73, 49, 91, 34, 63, 8,
        97, 44, 53, 19, 66, 80, 28, 5,
        13, 77, 38, 52, 87, 24, 69, 94,
        7, 15, 32, 61
    };

    int size = 68;

    Node* root = buildTree(arr, size);

    // ROOT
    printf("Root: %d\n", root->data);

    // LEAVES
    printf("Leaf nodes: ");
    printLeaves(root);
    printf("\n");

    int value;
    printf("Enter node value: ");
    scanf("%d", &value);

    Node* target = search(root, value);

    if (target == NULL) {
        printf("Node not found.\n");
        return 0;
    }

    Node* parent = findParent(root, target);

    if (parent)
        printf("Parent: %d\n", parent->data);
    else
        printf("Parent: NULL (root)\n");

    printSiblings(root, target);

    printf("Grandchildren: ");
    printGrandchildren(target);
    printf("\n");

    return 0;
}