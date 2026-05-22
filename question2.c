#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define delay(seconds) Sleep((seconds) * 1000)
#else
#include <unistd.h>
#define delay(seconds) sleep(seconds)
#endif

// Structure for a bus stop
typedef struct Node {
    char name[50];
    int stopNumber;
    struct Node* next;
    struct Node* prev;
} Node;

// Create a new node
Node* createNode(char name[], int number) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newNode->name, name);
    newNode->stopNumber = number;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Insert at end
void insertEnd(Node** head, char name[], int number) {
    Node* newNode = createNode(name, number);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

// Traverse forward (home → campus)
void traverseForward(Node* head) {
    Node* temp = head;

    if (temp == NULL) {
        printf("Route is empty.\n");
        return;
    }

    printf("\nMoving forward:\n");
    while (temp != NULL) {
        printf("Stop %d: %s\n", temp->stopNumber, temp->name);
        delay(3);
        temp = temp->next;
    }

    printf("Reached final stop.\n");
}

// Traverse backward (campus → home)
void traverseBackward(Node* head) {
    Node* temp = head;

    if (temp == NULL) {
        printf("Route is empty.\n");
        return;
    }

    // Go to last node first
    while (temp->next != NULL) {
        temp = temp->next;
    }

    printf("\nMoving backward:\n");
    while (temp != NULL) {
        printf("Stop %d: %s\n", temp->stopNumber, temp->name);
        delay(3);
        temp = temp->prev;
    }

    printf("Reached first stop.\n");
}

// Free memory
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Main program
int main() {
    Node* head = NULL;
    int n, choice, number;
    char name[50];

    printf("Enter number of initial bus stops: ");
    scanf("%d", &n);
    getchar(); // consume newline

    for (int i = 0; i < n; i++) {
        printf("\nEnter name of stop %d: ", i + 1);
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0'; // remove newline

        printf("Enter stop number: ");
        scanf("%d", &number);
        getchar();

        insertEnd(&head, name, number);
    }

    do {
        printf("\n--- MENU ---\n");
        printf("1. Move Forward (Home → Campus)\n");
        printf("2. Move Backward (Campus → Home)\n");
        printf("3. Add Bus Stop\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                traverseForward(head);
                break;

            case 2:
                traverseBackward(head);
                break;

            case 3:
                printf("Enter new stop name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                printf("Enter stop number: ");
                scanf("%d", &number);
                getchar();

                insertEnd(&head, name, number);
                printf("Bus stop added successfully.\n");
                break;

            case 4:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 4);

    freeList(head);
    return 0;
}