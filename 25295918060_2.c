#include <stdio.h>
#include <string.h>

#define SIZE 5
#define MAX 100

// ──────────────── Selection Sort ────────────────
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        int temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

// ──────────────── Stack ────────────────
int stack[MAX], top = -1;

void push(int val) { stack[++top] = val; }
int pop()          { return stack[top--]; }
int isStackEmpty() { return top == -1; }

// ──────────────── Queue ────────────────
int queue[MAX], front = 0, rear = 0;

void enqueue(int val) { queue[rear++] = val; }
int dequeue()         { return queue[front++]; }
int isQueueEmpty()    { return front == rear; }

int main() {
    // Step 1: Last 5 digits of 25295918060 → 18060
    int original[SIZE] = {1, 8, 0, 6, 0};
    int arr[SIZE];
    memcpy(arr, original, sizeof(original));

    // Step 2: 18060 % 3 = 0 → Selection Sort
    selectionSort(arr, SIZE);

    // Step 3: Print sorted number
    printf("Sorted (Selection Sort): ");
    for (int i = 0; i < SIZE; i++) printf("%d", arr[i]);
    printf("\n");

    // Step 4: Push original array onto stack in original order
    for (int i = 0; i < SIZE; i++)
        push(original[i]);

    // Step 5: Pop from stack and print (reversed)
    printf("Stack pop (reversed): ");
    int popped[SIZE];
    int idx = 0;
    while (!isStackEmpty()) {
        int val = pop();
        popped[idx++] = val;
        printf("%d", val);
    }
    printf("\n");

    // Step 6: Enqueue popped elements
    for (int i = 0; i < SIZE; i++)
        enqueue(popped[i]);

    // Step 7: Dequeue and print
    printf("Queue dequeue output: ");
    while (!isQueueEmpty())
        printf("%d", dequeue());
    printf("\n");

    return 0;
}
