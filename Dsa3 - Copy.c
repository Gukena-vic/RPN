#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100


struct Stack {
    int top;
    int capacity;
    int* array;
};


struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}


int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}


void push(struct Stack* stack, int item) {
    stack->array[++stack->top] = item;
}


int pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return -1; 
}


int precedence(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    }
    return -1;
}


void infixToPostfix(char* infix, char* postfix) {
    struct Stack* stack = createStack(MAX_SIZE);
    int i, k;
    for (i = 0, k = -1; infix[i]; ++i) {
        if (isdigit(infix[i]))
            postfix[++k] = infix[i];
        else if (infix[i] == '(')
            push(stack, infix[i]);
        else if (infix[i] == ')') {
            while (!isEmpty(stack) && stack->array[stack->top] != '(')
                postfix[++k] = pop(stack);
            if (!isEmpty(stack) && stack->array[stack->top] != '(')
                return; 
            else
                pop(stack); 
        } else {
            while (!isEmpty(stack) && precedence(infix[i]) <= precedence(stack->array[stack->top]))
                postfix[++k] = pop(stack);
            push(stack, infix[i]);
        }
    }
    while (!isEmpty(stack))
        postfix[++k] = pop(stack);
    postfix[++k] = '\0';
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];
    printf("Enter infix expression: ");
    fgets(infix, MAX_SIZE, stdin);

    
    infix[strcspn(infix, "\n")] = 0;

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
