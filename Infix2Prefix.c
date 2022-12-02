#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char *data;
    int top;
    int size;
} Stack;

Stack* initStack(int size)
{
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->data = (char*)malloc(sizeof(char) * size);
    s->top = -1;
    s->size = size;
    return s;
}

bool isEmpty(Stack *s)
{
    return s->top == -1;
}

bool isFull(Stack *s)
{
    return s->top == s->size - 1;
}

void push(Stack *s, char c)
{
    if (isFull(s)) {
        printf("Stack is full!\n");
        return;
    }

    s->data[++s->top] = c;
}

char pop(Stack *s)
{
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return '\0';
    }

    return s->data[s->top--];
}

char peek(Stack *s)
{
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return '\0';
    }

    return s->data[s->top];
}

int isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        return 1;
    }

    return 0;
}

int precedence(char c)
{
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    } else if (c == '^') {
        return 3;
    }

    return -1;
}

char* StringReverse(char *str)
{
    int len = strlen(str);
    char *rev = (char*) malloc(sizeof(char) * len);
    int i = 0;
    int j = len - 1;

    while (j >= 0) {
        rev[i++] = str[j--];
    }

    return rev;
}

char* infixToPrefix(char *infix)
{
    int i, j;
    infix = StringReverse(infix);
    int len = strlen(infix);
    char *prefix = (char*)malloc(sizeof(char) * (len + 1));
    Stack *s = initStack(len);

    for (i = 0, j = 0; i < len; i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        } else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }

    for (i = 0; i < len; i++) {
        if (infix[i] == '(') {
            push(s, infix[i]);
        } else if (isalpha(infix[i]) || isdigit(infix[i])) {
            prefix[j++] = infix[i];
        } else if (isOperator(infix[i])) {
            while (!isEmpty(s) && precedence(infix[i]) <= precedence(peek(s))) {
                prefix[j++] = pop(s);
            }
            push(s, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(s) && peek(s) != '(') {
                prefix[j++] = pop(s);
            }
            pop(s);
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

    printf("=======================\n");

    char* new_infix = malloc(sizeof(char) * 100);
    printf("Enter an infix expression: ");
    scanf("%s", new_infix);

    char* new_prefix = infixToPrefix(new_infix);
    printf("The prefix expression is: %s\n", new_prefix);

    return 0;
}
