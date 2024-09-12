#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

typedef struct Stack {
    TreeNode* node;
    struct Stack* next;
} Stack;

Stack* top = NULL;


//==================================================================

int isEmpty() {
    return top == NULL;
}

void push(TreeNode* node) {
    Stack* newNode = (Stack*)malloc(sizeof(Stack));
    newNode->node = node;
    newNode->next = top;
    top = newNode;
    printf("push(%d) ", node->data);
}

TreeNode* pop() {
    if (isEmpty()) return NULL;
    Stack* temp = top;
    TreeNode* poppedNode = top->node;
    top = top->next;
    free(temp);
    printf("pop(%d) ", poppedNode->data);
    return poppedNode;
}

TreeNode* initNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

//========================================================================


// ��带 �����, �Է¹��� node�� direction(0:left, 1:right)���� ����
//�ùٸ� ��ġ�� �ش� ��带 ��ġ�ϴ� �Լ�
void PlaceNode(TreeNode* node, int direction, int data) {
    if (direction == 0)
        node->left = initNode(data);
    else
        node->right = initNode(data);
}

void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);
    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);
    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);
    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);
    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);
    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);
    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}


void LinkPreOrder(TreeNode* root) {
    if (root == NULL) return;
    push(root);
    while (!isEmpty()) {
        TreeNode* node = pop();
        if (node != NULL) {
            printf("visit(%d) ", node->data);
            if (node->right != NULL) push(node->right);
            if (node->left != NULL) push(node->left);
        }
    }
}


void LinkInOrder(TreeNode* root) {
    TreeNode* curr = root;
    while (curr != NULL || !isEmpty()) {
        while (curr != NULL) {
            push(curr);
            curr = curr->left;
        }
        curr = pop();
        if (curr != NULL) {
            printf("visit(%d) ", curr->data);
            curr = curr->right;
        }
    }
}


void LinkPostOrder(TreeNode* root) {
    TreeNode* lastVisited = NULL;
    TreeNode* curr = root;
    while (curr != NULL || !isEmpty()) {
        while (curr != NULL) {
            push(curr);
            curr = curr->left;
        }
        TreeNode* peekNode = top->node;
        if (peekNode->right != NULL && lastVisited != peekNode->right) {
            curr = peekNode->right;
        }
        else {
            pop();
            printf("visit(%d) ", peekNode->data);
            lastVisited = peekNode;
        }
    }
}

void LinkOrders(TreeNode* root) {
    printf("LinkedPreOrder: ");
    LinkPreOrder(root);
    printf("\n");

    printf("\nLinkedInOrder: ");
    LinkInOrder(root);
    printf("\n");

    printf("\nLinkedPostOrder: ");
    LinkPostOrder(root);
    printf("\n");
}

int main() {
    TreeNode* root = NULL;
    root = initNode(1); // root->data =1�� initNode �ȿ� �ֽ��ϴ�

    //������ ���(array��, link��)�� ���� Ʈ�� ����
    //���� ����� ���� �Լ����̴�.
    GenerateLinkTree(root);

    //������ Ʈ���� ���� �ݺ�������� ��ȸ
    //��ȸ�� ����, ����, ���� ��� ����
    //�̶� ��� push�� pop�� ���
    LinkOrders(root);

    return 0;
}

