#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

enum { FINAL_TERM, TERM, ATOM, LIST };

/* forward declaration */
struct node;

/* a node_val can either be a char (eventually I'll support ints duh and strings of arbitrary length)) or a pointer to a new list */
union node_val {
    char c;
    struct node* list;
};

/* lol why not? car is a node_val (either a char or a new list) and cdr is a pointer to another node. */
/* if cdr is NULL? */
typedef struct node {
    int type;
    union node_val car;
    struct node* cdr;
} node;

int count_list(char* s) {
    int depth = 1;
    int count = 0;
    for (int i = 1; depth != 0; i++) {
        if (s[i] == '(') {
            depth++;
        } else if (s[i] == ')') {
            depth--;
        }
        count++;
    }
    return count + 1;
}

char* return_string(char* s){
    char* out;
    for (int i = 0; (s[i] != ')' && s[i] != '(' && !isspace(s[i])); i++) {
        out[i] = s[i];
    }
    return out;
}

node * makelist(char* s) {
    if (s[0] == ' ' || s[0] == '\n') {
        return makelist(s+1);
    } else if (s[0] == '\0') {
        node* output = malloc(sizeof(node));
        output->type = FINAL_TERM;
        output->car.list = NULL;
        output->cdr = NULL;
        return output;
    } else if (s[0] == '(') {
        node* output = malloc(sizeof(node));
        output->type = LIST;
        output->car.list = makelist(s+1);
        output->cdr = makelist(s + count_list(s));
        return output;
    } else if (s[0] == ')') {
        node* output = malloc(sizeof(node));
        output->type = TERM;
        output->car.list = NULL;
        output->cdr = NULL;
        return output;
    } else {
        node* output = malloc(sizeof(node));
        output->type = ATOM;
        output->car.c = s[0];
        output->cdr = makelist(s + 1);
        return output;
    }
}
