#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *next;
    int value;
} Node_t;

void append(Node_t **, int);
void traverse(Node_t **);
void remove_node(Node_t **, Node_t *);



void append(Node_t **head, int value) {



    Node_t **indirect = head;
    Node_t *new = malloc(1*sizeof(Node_t));
    new -> value = value; new->next = NULL;

    while ((*indirect) -> next) {
        indirect = &((*indirect)->next);
    }

    Node_t target = {.value = value, .next=NULL};
    
    (*indirect)->next = new;

    // traverse(head);

}

void traverse(Node_t **head) {

    Node_t **indirect = head;
    int index = 0;
    while ((*indirect)->next) {
        indirect = &(*indirect) -> next;
        printf("Node #%d's value is %d.\n", index++, (*indirect)->value);

    }
}

void remove_node(Node_t **head, Node_t *target) {

    Node_t **indirect = head;

    while ((*indirect)->next != target) {
        indirect = &(*indirect)->next;
    }
    (*indirect)->next = target -> next;

    free(target);

}

Node_t *find(Node_t **head, int value) {

    for (Node_t **indirect = head; (*indirect)->next != NULL; indirect = &(*indirect)->next) {
        printf("value: %d\n", ((*indirect)->next)->value);
        if (((*indirect)->next)->value == value){
            
            return (*indirect)->next;
        }
    }

    return NULL;
}


int main() {

    Node_t *head = malloc(sizeof(Node_t));
    head->value = 0; head->next=NULL;

    for (int i = 0; i<10; i++) {
        append(&head, i);
    }
    printf("=====\n");
    traverse(&head);

    printf("=====\n");
    
    for (int j = -1; j<15; j++) {
        Node_t *target = find(&head, j);
        if (target != NULL) {
            printf("Remove %d from list", j);
            remove_node(&head, target);
        }
        else {
            printf("Value %d doesn't exist.\n", j);
        }

        traverse(&head);
        printf("=====\n");

    }

    traverse(&head);

    return 0;

}