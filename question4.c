#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Structure for duplicate records (same last name)
typedef struct Record {
    char firstname[MAX];
    char lastname[MAX];
    float grade;
    struct Record* next;
} Record;

// BST Node
typedef struct BSTNode {
    char lastname[MAX];     // key
    Record* records;        // linked list of records with same lastname
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Create a new record
Record* createRecord(char* fname, char* lname, float grade) {
    Record* newRec = (Record*)malloc(sizeof(Record));
    strcpy(newRec->firstname, fname);
    strcpy(newRec->lastname, lname);
    newRec->grade = grade;
    newRec->next = NULL;
    return newRec;
}

// Create a new BST node
BSTNode* createNode(char* fname, char* lname, float grade) {
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    strcpy(newNode->lastname, lname);
    newNode->left = newNode->right = NULL;

    // First record
    newNode->records = createRecord(fname, lname, grade);

    return newNode;
}

// Insert into BST
BSTNode* insert(BSTNode* root, char* fname, char* lname, float grade) {
    if (root == NULL) {
        return createNode(fname, lname, grade);
    }

    int cmp = strcmp(lname, root->lastname);

    if (cmp < 0) {
        root->left = insert(root->left, fname, lname, grade);
    }
    else if (cmp > 0) {
        root->right = insert(root->right, fname, lname, grade);
    }
    else {
        // Duplicate last name → add to linked list
        Record* newRec = createRecord(fname, lname, grade);
        newRec->next = root->records;
        root->records = newRec;
    }

    return root;
}

// Search BST by last name
BSTNode* search(BSTNode* root, char* lname) {
    if (root == NULL) return NULL;

    int cmp = strcmp(lname, root->lastname);

    if (cmp == 0) return root;
    else if (cmp < 0) return search(root->left, lname);
    else return search(root->right, lname);
}

// Display records in a node
void displayRecords(Record* head) {
    while (head != NULL) {
        printf("First Name: %s | Last Name: %s | Grade: %.2f\n",
               head->firstname, head->lastname, head->grade);
        head = head->next;
    }
}

// Read file and build BST
BSTNode* buildBSTFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return NULL;
    }

    char line[256];
    BSTNode* root = NULL;

    while (fgets(line, sizeof(line), file)) {
        char fname[MAX], lname[MAX];
        float grade;

        // Parse line: Firstname|Lastname|Grade
        if (sscanf(line, "%[^|]|%[^|]|%f", fname, lname, &grade) == 3) {
            root = insert(root, fname, lname, grade);
        } else {
            printf("Skipping invalid record: %s", line);
        }
    }

    fclose(file);
    return root;
}

// Free linked list
void freeRecords(Record* head) {
    Record* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Free BST
void freeBST(BSTNode* root) {
    if (root == NULL) return;

    freeBST(root->left);
    freeBST(root->right);
    freeRecords(root->records);
    free(root);
}

// Main
int main() {
    BSTNode* root = buildBSTFromFile("bst_students.txt");

    if (root == NULL) {
        printf("No data loaded.\n");
        return 1;
    }

    char searchName[MAX];

    printf("Enter last name to search: ");
    scanf("%s", searchName);

    BSTNode* result = search(root, searchName);

    if (result == NULL) {
        printf("No student found with last name '%s'\n", searchName);
    } else {
        printf("\nStudents with last name '%s':\n", searchName);
        displayRecords(result->records);
    }

    freeBST(root);
    return 0;
}