#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILES 100
#define MAX_DIRS 10
#define MAX_NAME_LEN 50

// Structure for a hierarchical node
struct Node {
    char name[MAX_NAME_LEN];
    struct Node *child[MAX_DIRS];
    int childCount;
};

// Function prototypes
void singleLevelDirectory();
void twoLevelDirectory();
void hierarchicalDirectory();
struct Node *createNode(char *name);
void displayHierarchy(struct Node *node, int depth);

int main() {
    int choice;

    while (1) {
        printf("\nFile Organization Techniques Simulation:\n");
        printf("1. Single-Level Directory\n");
        printf("2. Two-Level Directory\n");
        printf("3. Hierarchical Directory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                singleLevelDirectory();
                break;
            case 2:
                twoLevelDirectory();
                break;
            case 3:
                hierarchicalDirectory();
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Single-Level Directory
void singleLevelDirectory() {
    char files[MAX_FILES][MAX_NAME_LEN];
    int fileCount = 0;
    int choice;
    char fileName[MAX_NAME_LEN];

    while (1) {
        printf("\nSingle-Level Directory:\n");
        printf("1. Create File\n");
        printf("2. Search File\n");
        printf("3. List Files\n");
        printf("4. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (fileCount >= MAX_FILES) {
                    printf("Directory is full!\n");
                } else {
                    printf("Enter file name: ");
                    scanf("%s", fileName);
                    strcpy(files[fileCount], fileName);
                    fileCount++;
                    printf("File '%s' created.\n", fileName);
                }
                break;
            case 2:
                printf("Enter file name to search: ");
                scanf("%s", fileName);
                int found = 0;
                for (int i = 0; i < fileCount; i++) {
                    if (strcmp(files[i], fileName) == 0) {
                        printf("File '%s' found.\n", fileName);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("File '%s' not found.\n", fileName);
                }
                break;
            case 3:
                printf("Files in Directory:\n");
                for (int i = 0; i < fileCount; i++) {
                    printf("%s\n", files[i]);
                }
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Two-Level Directory
void twoLevelDirectory() {
    struct Directory {
        char name[MAX_NAME_LEN];
        char files[MAX_FILES][MAX_NAME_LEN];
        int fileCount;
    } dirs[MAX_DIRS];

    int dirCount = 0;
    int choice;
    char dirName[MAX_NAME_LEN], fileName[MAX_NAME_LEN];

    while (1) {
        printf("\nTwo-Level Directory:\n");
        printf("1. Create Directory\n");
        printf("2. Create File in Directory\n");
        printf("3. Search File\n");
        printf("4. List Files in Directory\n");
        printf("5. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (dirCount >= MAX_DIRS) {
                    printf("Maximum directories reached!\n");
                } else {
                    printf("Enter directory name: ");
                    scanf("%s", dirName);
                    strcpy(dirs[dirCount].name, dirName);
                    dirs[dirCount].fileCount = 0;
                    dirCount++;
                    printf("Directory '%s' created.\n", dirName);
                }
                break;
            case 2:
                printf("Enter directory name: ");
                scanf("%s", dirName);
                int dirIndex = -1;
                for (int i = 0; i < dirCount; i++) {
                    if (strcmp(dirs[i].name, dirName) == 0) {
                        dirIndex = i;
                        break;
                    }
                }
                if (dirIndex == -1) {
                    printf("Directory '%s' not found.\n", dirName);
                } else {
                    if (dirs[dirIndex].fileCount >= MAX_FILES) {
                        printf("Directory is full!\n");
                    } else {
                        printf("Enter file name: ");
                        scanf("%s", fileName);
                        strcpy(dirs[dirIndex].files[dirs[dirIndex].fileCount], fileName);
                        dirs[dirIndex].fileCount++;
                        printf("File '%s' created in directory '%s'.\n", fileName, dirName);
                    }
                }
                break;
            case 3:
                printf("Enter file name to search: ");
                scanf("%s", fileName);
                int found = 0;
                for (int i = 0; i < dirCount; i++) {
                    for (int j = 0; j < dirs[i].fileCount; j++) {
                        if (strcmp(dirs[i].files[j], fileName) == 0) {
                            printf("File '%s' found in directory '%s'.\n", fileName, dirs[i].name);
                            found = 1;
                            break;
                        }
                    }
                    if (found) break;
                }
                if (!found) {
                    printf("File '%s' not found.\n", fileName);
                }
                break;
            case 4:
                printf("Enter directory name: ");
                scanf("%s", dirName);
                dirIndex = -1;
                for (int i = 0; i < dirCount; i++) {
                    if (strcmp(dirs[i].name, dirName) == 0) {
                        dirIndex = i;
                        break;
                    }
                }
                if (dirIndex == -1) {
                    printf("Directory '%s' not found.\n", dirName);
                } else {
                    printf("Files in directory '%s':\n", dirName);
                    for (int i = 0; i < dirs[dirIndex].fileCount; i++) {
                        printf("%s\n", dirs[dirIndex].files[i]);
                    }
                }
                break;
            case 5:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Hierarchical Directory
void hierarchicalDirectory() {
    struct Node *root = createNode("Root");
    int choice;
    char dirName[MAX_NAME_LEN], parentName[MAX_NAME_LEN];

    while (1) {
        printf("\nHierarchical Directory:\n");
        printf("1. Create Subdirectory\n");
        printf("2. Display Hierarchy\n");
        printf("3. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter parent directory name: ");
                scanf("%s", parentName);
                struct Node *parent = NULL, *queue[MAX_DIRS];
                int front = 0, rear = 0;
                queue[rear++] = root;

                while (front < rear) {
                    struct Node *current = queue[front++];
                    if (strcmp(current->name, parentName) == 0) {
                        parent = current;
                        break;
                    }
                    for (int i = 0; i < current->childCount; i++) {
                        queue[rear++] = current->child[i];
                    }
                }

                if (!parent) {
                    printf("Parent directory '%s' not found.\n", parentName);
                } else if (parent->childCount >= MAX_DIRS) {
                    printf("Maximum subdirectories reached for '%s'.\n", parentName);
                } else {
                    printf("Enter subdirectory name: ");
                    scanf("%s", dirName);
                    parent->child[parent->childCount++] = createNode(dirName);
                    printf("Subdirectory '%s' created under '%s'.\n", dirName, parentName);
                }
                break;
            case 2:
                printf("Directory Hierarchy:\n");
                displayHierarchy(root, 0);
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

struct Node *createNode(char *name) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    newNode->childCount = 0;
    return newNode;
}

void displayHierarchy(struct Node *node, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%s\n", node->name);
    for (int i = 0; i < node->childCount; i++) {
        displayHierarchy(node->child[i], depth + 1);
    }
}
