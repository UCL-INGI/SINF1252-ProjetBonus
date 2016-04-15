typedef struct BSTreeNode {
    int key;
    int data;

    struct BSTreeNode *left;
    struct BSTreeNode *right;
} Node;

int has_key(Node root, int key);

int compare(Node root_a, Node root_b);
