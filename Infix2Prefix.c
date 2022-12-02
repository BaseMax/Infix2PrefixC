#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    int top;
    int size;
} Stack;

Stack* initStack(int size) {
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->data = (char*)malloc(sizeof(char) * size);
    s->top = -1;
    s->size = size;
    return s;
}

void push(Stack *s, char c) {
    if (s->top == s->size - 1) {
        printf("Stack is full!\n");
        return;
    }

    s->data[++s->top] = c;
}

char pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack is empty!\n");
        return -1;
    }

    return s->data[s->top--];
}

char peek(Stack *s) {
    if (s->top == -1) {
        printf("Stack is empty!\n");
        return -1;
    }

    return s->data[s->top];
}

int isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        return 1;
    }

    return 0;
}

int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    } else if (c == '^') {
        return 3;
    }

    return -1;
}

char* StringReverse(char *str) {
    int len = strlen(str);
    char *rev = (char*)malloc(sizeof(char) * len);

    for (int i = 0; i < len; i++) {
        rev[i] = str[len - i - 1];
    }
    rev[len] = '\0';

    return rev;
}

char* infixToPrefix(char *infix) {
    int i, j;
    int len = strlen(infix);
    char *prefix = (char*)malloc(sizeof(char) * (len + 1));
    Stack *s = initStack(len);

    for (i = len - 1, j = 0; i >= 0; i--) {
        if (infix[i] == ')') {
            push(s, infix[i]);
        } else if (infix[i] == '(') {
            while (peek(s) != ')') {
                prefix[j++] = pop(s);
            }

            pop(s);
        } else if (isOperator(infix[i])) {
            while (s->top != -1 && precedence(peek(s)) >= precedence(infix[i])) {
                prefix[j++] = pop(s);
            }

            push(s, infix[i]);
        } else {
            prefix[j++] = infix[i];
        }
    }

    while (s->top != -1) {
        prefix[j++] = pop(s);
    }

    prefix[j] = '\0';

    prefix = StringReverse(prefix);

    return prefix;
}

int main(int argc, char** argv)
{
    char* infix = "5+6*7";
    char* prefix = infixToPrefix(infix);

    printf("Infix:  %s\n", infix);
    printf("Prefix: %s\n", prefix);

    if (strcmp(prefix, "+5*67") == 0) printf("TEST PASS\n");
    else printf("TEST FAIL\n");

    return 0;
}
