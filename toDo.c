#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Task {
    char name[100];
    bool completed;
    struct Task* next;
} Task;

Task* createTask(char name[]) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    strcpy(newTask->name, name);
    newTask->completed = false;
    newTask->next = NULL;
    return newTask;
}
void addToDoTask(Task** head, char name[]) {
    Task* newTask = createTask(name);

    if (*head == NULL) {
        *head = newTask;
    } else {
        Task* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTask;
    }

    printf("Task '%s' added to the To-Do list.\n", name);
}
void markTaskCompleted(Task** head, char name[], Task** completedStack) {
    Task* temp = *head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            temp->completed = true;
            printf("Task '%s' marked as completed.\n", name);

            // Push the completed task onto the stack
            Task* completedTask = createTask(name);
            completedTask->completed = true;
            completedTask->next = *completedStack;
            *completedStack = completedTask;
            return;
        }
        temp = temp->next;
    }

    printf("Task '%s' not found in the To-Do list.\n", name);
}
void removeTask(Task** head, char name[], Task** removalQueue) {
    Task* prev = NULL;
    Task* curr = *head;

    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            if (prev == NULL) {
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }

            // Enqueue the removed task into the queue for cleanup
            curr->next = *removalQueue;
            *removalQueue = curr;

            printf("Task '%s' removed from the To-Do list.\n", name);
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("Task '%s' not found in the To-Do list.\n", name);
}
Task* findTask(Task* head, char name[]) {
    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

void viewToDoList(Task* head) {
    if (head == NULL) {
        printf("To-Do list is empty.\n");
    } else {
        printf("To-Do List:\n");
        while (head != NULL) {
            printf("%s - %s\n", head->completed ? "[X]" : "[ ]", head->name);
            head = head->next;
        }
    }
}
int main() {
    Task* toDoList = NULL;
    Task* completedStack = NULL;
    Task* removalQueue = NULL;
    char taskName[100];
    int choice;

    do {
        printf("\nTo-Do List Application\n");
        printf("1. Add Task\n");
        printf("2. Mark Task as Completed\n");
        printf("3. Remove Task\n");
        printf("4. Find a Task\n");
        printf("5. View To-Do List\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter task name: ");
                scanf(" %[^\n]", taskName);
                addToDoTask(&toDoList, taskName);
                break;

            case 2:
                printf("Enter task name to mark as completed: ");
                scanf(" %[^\n]", taskName);
                markTaskCompleted(&toDoList, taskName, &completedStack);
                break;

            case 3:
                printf("Enter task name to remove: ");
                scanf(" %[^\n]", taskName);
                removeTask(&toDoList, taskName, &removalQueue);
                break;
            case 4:
                printf("Enter task name to find: ");
                scanf(" %[^\n]", taskName);
                Task* foundTask = findTask(toDoList, taskName);
                if (foundTask != NULL) {
                    printf("Task '%s' found in the To-Do list.\n", taskName);
                } else {
                    printf("Task '%s' not found in the To-Do list.\n", taskName);
                }
                break;

            case 5:
                viewToDoList(toDoList);
                break;

            case 6:
                printf("Exiting the application.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    // Clean up memory before exiting
 while (toDoList != NULL) {
 Task* temp = toDoList;
 toDoList = toDoList->next;
 free(temp);
 }

 // Clear the completed tasks stack
 while (completedStack != NULL) {
 Task* temp = completedStack;
 completedStack = completedStack->next;
 free(temp);
 }

// Clear the removal queue
    while (removalQueue != NULL) {
        Task* temp = removalQueue;
        removalQueue = removalQueue->next;
        free(temp);
    }

    return 0;
}
