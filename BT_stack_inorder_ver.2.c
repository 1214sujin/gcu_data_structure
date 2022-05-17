#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int data;
    struct treeNode* left;
    struct treeNode* right;
} tn;

typedef struct stackNode {
    tn* data;
    struct stackNode* link;
} sn;
sn* top;

void push(tn* item) {
    sn* temp = (sn*)malloc(sizeof(sn));
    temp->data = item;
    temp->link = top;
    top = temp;
}

tn* pop() {
    tn* item;
    sn* temp = top;
    if (top == NULL) return NULL;
    else {
        item = temp->data;
        top = temp->link;
        free(temp);
        return item;
    }
}

tn* makeRootNode(int item, tn* leftNode, tn* rightNode) {
    tn* root = (tn*)malloc(sizeof(tn));
    root->data = item;
    root->left = leftNode;
    root->right = rightNode;
    return root;
}

void inorder(tn* root) {
     while (1) {
        while (root != NULL) {
            push(root);
            root = root->left;
        }
        if (top == NULL) return;
        root = pop();
        printf("[%d] ", root->data);
        root = root->right;
        while (root == NULL) {
            if (top == NULL) return;
            root = pop();
            printf("[%d] ", root->data);
            root = root->right;
        }
        push(root);
        root = root->left;
    }
}

void main() {
    tn* n6 = makeRootNode(25, NULL, NULL);
    tn* n5 = makeRootNode(16, NULL, NULL);
    tn* n4 = makeRootNode(1, NULL, NULL);
    tn* n3 = makeRootNode(20, n5, n6);
    tn* n2 = makeRootNode(4, n4, NULL);
    tn* n1 = makeRootNode(15, n2, n3);

    printf("중위 순회=");
    inorder(n1);

}