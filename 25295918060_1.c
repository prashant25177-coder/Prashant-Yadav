#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 5

// ──────────────── Merge Sort ────────────────
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ──────────────── Doubly Linked List ────────────────
typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node;

Node* newNode(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = val;
    n->prev = n->next = NULL;
    return n;
}

Node* insertEnd(Node* head, int val) {
    Node* n = newNode(val);
    if (!head) return n;
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = n;
    n->prev = temp;
    return head;
}

void forwardTraversal(Node* head) {
    while (head) {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}

void backwardTraversal(Node* head) {
    // Go to last node
    while (head->next) head = head->next;
    // Traverse backward
    while (head) {
        printf("%d", head->data);
        head = head->prev;
    }
    printf("\n");
}

int main() {
    // Step 1: Last 5 digits of 25295918060 → 18060
    int original[SIZE] = {1, 8, 0, 6, 0};
    int arr[SIZE];
    memcpy(arr, original, sizeof(original));

    // Step 2: 18060 % 3 = 0 → Merge Sort
    mergeSort(arr, 0, SIZE - 1);

    // Step 3: Print sorted number
    printf("Sorted (Merge Sort): ");
    for (int i = 0; i < SIZE; i++) printf("%d", arr[i]);
    printf("\n");

    // Step 4: Reverse the original array in-place
    int left = 0, right = SIZE - 1;
    while (left < right) {
        int temp = original[left];
        original[left] = original[right];
        original[right] = temp;
        left++; right--;
    }

    // Step 5: Print reversed array
    printf("Reversed array: ");
    for (int i = 0; i < SIZE; i++) printf("%d", original[i]);
    printf("\n");

    // Step 6: Build Doubly Linked List from reversed array
    Node* head = NULL;
    for (int i = 0; i < SIZE; i++)
        head = insertEnd(head, original[i]);

    // Step 7: Forward traversal → reversed order
    printf("DLL forward traversal: ");
    forwardTraversal(head);

    // Step 8: Backward traversal → original order
    printf("DLL backward traversal: ");
    backwardTraversal(head);

    return 0;
}
