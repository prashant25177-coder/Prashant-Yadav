#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5

// ──────────────── BST Node ────────────────
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* newNode(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = val;
    n->left = n->right = NULL;
    return n;
}

// < goes left, >= goes right
Node* insert(Node* root, int val) {
    if (!root) return newNode(val);
    if (val < root->data)
        root->left  = insert(root->left,  val);
    else
        root->right = insert(root->right, val);
    return root;
}

// ──────────────── BST Traversals ────────────────
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d", root->data);
    inorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d", root->data);
}

// ──────────────── Min Heap ────────────────
int heap[SIZE];
int heapSize = 0;

void heapifyUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent] > heap[i]) {
            int tmp = heap[parent]; heap[parent] = heap[i]; heap[i] = tmp;
            i = parent;
        } else break;
    }
}

void insertHeap(int val) {
    heap[heapSize++] = val;
    heapifyUp(heapSize - 1);
}

void heapifyDown(int i, int n) {
    while (1) {
        int smallest = i;
        int l = 2*i+1, r = 2*i+2;
        if (l < n && heap[l] < heap[smallest]) smallest = l;
        if (r < n && heap[r] < heap[smallest]) smallest = r;
        if (smallest != i) {
            int tmp = heap[i]; heap[i] = heap[smallest]; heap[smallest] = tmp;
            i = smallest;
        } else break;
    }
}

int deleteRoot() {
    int root = heap[0];
    heap[0] = heap[--heapSize];
    heapifyDown(0, heapSize);
    return root;
}

void printHeap(int n) {
    for (int i = 0; i < n; i++) printf("%d", heap[i]);
    printf("\n");
}

int main() {
    // Step 1 & 2: last 5 digits of 25295918060
    int original[SIZE] = {1, 8, 0, 6, 0};

    // Step 3: Build BST (< left, >= right)
    Node* root = NULL;
    for (int i = 0; i < SIZE; i++)
        root = insert(root, original[i]);

    // Step 4a: Inorder
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    // Step 4b: Post-Order
    printf("Post-Order Traversal: ");
    postorder(root);
    printf("\n");

    // Step 5: 18060 % 2 = 0 → Min Heap
    for (int i = 0; i < SIZE; i++)
        insertHeap(original[i]);

    // Step 6: Print heap after construction
    printf("Min Heap after construction: ");
    printHeap(heapSize);

    // Step 7 & 8: Delete root, print deleted element
    int deleted = deleteRoot();
    printf("Deleted element: %d\n", deleted);

    // Step 9: Print new heap
    printf("Heap after deletion: ");
    printHeap(heapSize);

    return 0;
}
