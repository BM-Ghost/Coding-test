#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    enum TypeTag { ADD, MUL, SUB, CONST } type;
    int value;
    struct Node* left;
    struct Node* right;
} Node;

int add(int a, int b) {
    return a + b;
}

int mul(int a, int b) {
    return a * b;
}

int sub(int a, int b) {
    return a - b;
}

int eval(Node* node) {
    if (node->type == ADD)
        return add(eval(node->left), eval(node->right));
    else if (node->type == MUL)
        return mul(eval(node->left), eval(node->right));
    else if (node->type == SUB)
        return sub(eval(node->left), eval(node->right));
    else if (node->type == CONST)
        return node->value;
    else
        return 0; // Handle other cases if needed
}

int fibonacci(int n) {
    if (n <= 1)
        return n;
    int fib[n + 1];
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    return fib[n];
}

int main() {
    Node addNode = { ADD, 0, malloc(sizeof(Node)), malloc(sizeof(Node)) };
    addNode.left->type = CONST;
    addNode.left->value = 10;
    addNode.right->type = CONST;
    addNode.right->value = 6;

    Node mulNode = { MUL, 0, malloc(sizeof(Node)), malloc(sizeof(Node)) };
    mulNode.left->type = CONST;
    mulNode.left->value = 5;
    mulNode.right->type = CONST;
    mulNode.right->value = 4;

    Node subNode = { SUB, 0, &mulNode, &addNode };

    Node fiboNode = { SUB, 0, &subNode, NULL };

    printf("add : %d\n", eval(&addNode));
    printf("mul : %d\n", eval(&mulNode));
    printf("sub : %d\n", eval(&subNode));
    printf("fibo : %d\n", fibonacci(eval(&fiboNode)));

    // Free allocated memory
    free(addNode.left);
    free(addNode.right);
    free(mulNode.left);
    free(mulNode.right);

    return 0;
}
