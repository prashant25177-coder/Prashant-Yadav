#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5
#define QMAX 100

// ──────────────── BST Node ────────────────
typedef struct Node {
    int data;
    int insertOrder;   // 1-based order of insertion (for step 6 labels)
    struct Node *left, *right;
} Node;

Node* newNode(int val, int order) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = val;
    n->insertOrder = order;
    n->left = n->right = NULL;
    return n;
}

// ≤ goes left, > goes right
Node* insert(Node* root, int val, int order) {
    if (!root) return newNode(val, order);
    if (val <= root->data)
        root->left = insert(root->left, val, order);
    else
        root->right = insert(root->right, val, order);
    return root;
}

// ──────────────── Traversals ────────────────
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d", root->data);
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    printf("%d", root->data);
    preorder(root->left);
    preorder(root->right);
}

// ──────────────── Level Order (array queue) ────────────────
typedef struct {
    Node* node;
    int   level;
} QItem;

QItem q[QMAX];
int qfront, qrear;

void enq(Node* n, int lvl) { q[qrear].node = n; q[qrear++].level = lvl; }
QItem deq()                { return q[qfront++]; }
int   qempty()             { return qfront == qrear; }

void levelOrder(Node* root) {
    qfront = qrear = 0;
    if (!root) return;
    enq(root, 1);

    // collect nodes in level order, paired with their insertOrder
    // We'll store (insertOrder, level) pairs
    // Print: Level of Node <insertOrder> = L<level>
    // We need to track all 5 nodes
    int nodeLevel[SIZE + 1]; // nodeLevel[insertOrder] = level
    memset(nodeLevel, 0, sizeof(nodeLevel));

    while (!qempty()) {
        QItem item = deq();
        Node* cur = item.node;
        int   lvl = item.level;
        nodeLevel[cur->insertOrder] = lvl;
        if (cur->left)  enq(cur->left,  lvl + 1);
        if (cur->right) enq(cur->right, lvl + 1);
    }

    for (int i = 1; i <= SIZE; i++)
        printf("Level of Node %d = L%d\n", i, nodeLevel[i]);
}

// ──────────────── Height helper ────────────────
int heightOf(Node* root) {
    if (!root) return -1;
    int lh = heightOf(root->left);
    int rh = heightOf(root->right);
    return 1 + (lh > rh ? lh : rh);
}

// ──────────────── Post Order + Height & Depth ────────────────
int nodeHeight[SIZE + 1];
int nodeDepth[SIZE + 1];

void postOrder(Node* root, int depth) {
    if (!root) return;
    postOrder(root->left,  depth + 1);
    postOrder(root->right, depth + 1);
    // visit
    int h = heightOf(root);
    nodeHeight[root->insertOrder] = h;
    nodeDepth[root->insertOrder]  = depth;
}

int main() {
    // Step 1 & 2: digits of 18060
    int original[SIZE] = {1, 8, 0, 6, 0};

    // Step 3: Build BST in insertion order
    Node* root = NULL;
    for (int i = 0; i < SIZE; i++)
        root = insert(root, original[i], i + 1);

    // Step 4a: Inorder
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    // Step 4b: Preorder
    printf("Pre-Order Traversal: ");
    preorder(root);
    printf("\n");

    // Step 5: Level Order with levels
    levelOrder(root);

    // Step 6: Post Order → height & depth
    postOrder(root, 0);
    for (int i = 1; i <= SIZE; i++)
        printf("Height of Node %d = H%d, Depth of Node %d = Y%d\n",
               i, nodeHeight[i], i, nodeDepth[i]);

    return 0;
}
