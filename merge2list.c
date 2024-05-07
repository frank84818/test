#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef struct Node {
    struct Node *next;
    int value;
} Node_t;

void append(Node_t **, int);
void traverse(Node_t **);
void remove_node(Node_t **, Node_t *);
void deleteMiddle(Node_t **);

Node_t *merged2SortedList(Node_t *, Node_t *);
Node_t *partitionList(Node_t *, int);

Node_t *partitionList(Node_t *list, int value) {

    Node_t *L2 = NULL; // new head

    Node_t **ptr1 = &list, **ptr2 = &L2;

    // for (Node_t *node = list; node; node=node->next) {
    //     // printf("1");
    //     if (node -> value < value) {
    //         *ptr1 = node;
    //         ptr1 = &((*ptr1)->next);

    //     }
    //     else {
    //         *ptr2 = node; // *ptr2 == L2; => L2 = node
    //         ptr2 = &((*ptr2)->next);
    //     }
    // }

    for (Node_t *node = list; node; node=node->next) {
        
        Node_t ***indir = node->value < value ? &ptr1: &ptr2;
        **indir = node;
        *indir = &((**indir)->next);
        
    }
    
    // Concatenate 2 lists and mamdatorily assign NULL to the end of the concatenated list.
    *ptr1 = L2;
    *ptr2 = NULL;

    return list;


}

Node_t *merged2SortedList(Node_t *L1, Node_t *L2) {

    Node_t *head = NULL, **ptr=&head, **node;

    for (node = NULL; L1 && L2; *node = (*node)->next) {
        node = L1->value > L2->value ? &L2 : &L1;
        *ptr = *node;
        ptr = &(*ptr)->next;
    }

    // TIPS: ptr | NULL = ptr 
    *ptr = (Node_t *) ((uintptr_t) L1 |(uintptr_t) L2); // Append the remaining nodes of L1 or L2 to the merged list.

    return head;

}


void deleteMiddle(Node_t **head) {
    Node_t **indir = head;
    Node_t *prev = NULL;
    // use fast which step 2 at each iteration to detect the middle node
    // Speed of fast: 2
    // Speed of indir: 1

    for (Node_t **fast = head; *fast && (*fast) -> next; fast = &(*fast)->next->next) {
        
        prev = *indir;
        indir = &(*indir) -> next;

    }

    // *indir = (*indir) -> next;

    Node_t *next = *indir;
    prev -> next = (*indir) -> next; // This step will modify *indir!
    // Use another ptr to memorize *indir
    
    free(next);

}


void append(Node_t **head, int value) {



    Node_t **indirect = head;
    Node_t *new = malloc(1*sizeof(Node_t));
    new -> value = value; new->next = NULL;

    while ((*indirect)) {
        indirect = &((*indirect)->next);
    }

    (*indirect) = new;

    // traverse(head);

}

void traverse(Node_t **head) {

    printf("List start\n");
    printf("Head");

    // Node_t **indirect = head;
    // int index = 0;
    // while ((*indirect)) {
    //     printf("Node #%d's value is %d.\n", index++, (*indirect)->value);
    //     indirect = &(*indirect) -> next;

    // }
    int index = 0;
    for (Node_t *node = *head; node; node = node->next){
        // printf("Node #%d's value is %d.\n", index++, node->value);
        printf("->%d", node -> value);
    }
    printf("\n");
}

void remove_node(Node_t **head, Node_t *target) {

    Node_t **indirect = head;

    while ((*indirect) != target) {
        indirect = &(*indirect)->next;
    }
    (*indirect) = target -> next;

    free(target);

}

Node_t *find(Node_t **head, int value) {

    for (Node_t **indirect = head; (*indirect)!= NULL; indirect = &(*indirect)->next) {
        if ((*indirect)->value == value){
            
            return (*indirect);
        }
    }

    return NULL;
}


int main() {

    // Node_t *head = NULL; //dummy_node -> next

    // for (int i = 0; i<10; i++) {
    //     append(&head, i);
    // }
    // printf("=====\n");
    // traverse(&head);

    // printf("=====\n");
    
    // for (int j = -1; j<15; j++) {
    //     Node_t *target = find(&head, j);
    //     if (target != NULL) {
    //         printf("Remove %d from list\n", j);
    //         remove_node(&head, target);
    //     }
    //     else {
    //         printf("Value %d doesn't exist.\n", j);
    //     }

    // }

    // traverse(&head);

    Node_t *L1 = NULL, *L2 = NULL;

    for (int i = 0; i < 10; i+=2) {
        append(&L1, i);
        append(&L2, i+1);
    }
    traverse(&L1);
    traverse(&L2);
    
    Node_t *merged = merged2SortedList(L1, L2);
    traverse(&merged);

    deleteMiddle(&merged);
    deleteMiddle(&merged);
    deleteMiddle(&merged);
    deleteMiddle(&merged);

    traverse(&merged);

    Node_t *random;
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        append(&random, rand() % 10);
    }
    traverse(&random);
    Node_t *partitioned = partitionList(random, 4);

    traverse(&partitioned);

    return 0;

}