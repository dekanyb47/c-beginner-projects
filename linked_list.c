#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct Node
{
    int val;
    struct Node *next;
} Node;


Node *init_new_node(int new_val);

void insert_left(Node **pp_head, int new_val);
void insert_at_i(Node **pp_head, int new_val, int i);
void insert_right(Node **pp_head, int new_val);

int pop_left(Node **pp_head);
int pop_at_index(Node **pp_head, int i);
int pop_right(Node **pp_head);

void reverse(Node **pp_head);

int length(const Node *head);
void traverse(const Node *head);

bool notify_node_malloc_failure(const Node *node, int new_val);
void free_memory(Node *head);


int main(){
    Node *p_head = NULL;

    insert_right(&p_head, 1);
    insert_right(&p_head, 2);
    insert_right(&p_head, 3);
    insert_right(&p_head, 4);
    insert_right(&p_head, 5);

    insert_left(&p_head, 999);
    pop_left(&p_head);

    insert_right(&p_head, 999);
    pop_right(&p_head);
  
    insert_at_i(&p_head, 99, 4);
    pop_at_index(&p_head, 4);
    
    printf("Length of linked list: %d\n", length(p_head));

    reverse(&p_head);

    traverse(p_head);

    free_memory(p_head);
    return 0;
}

Node *init_new_node(int new_val) {
    Node *p_node = malloc(sizeof(Node));

    if (p_node == NULL){
        return NULL;
    }

    p_node->val = new_val;
    p_node->next = NULL;
    return p_node; 
}

void insert_left(Node **pp_head, int new_val) {
    Node *p_new_head = init_new_node(new_val);
    if (!notify_node_malloc_failure(p_new_head, new_val)) return;

    p_new_head->next = *pp_head;
    *pp_head = p_new_head;
}

void insert_at_i(Node **pp_head, int new_val, int i){
    if (i < 0) {
        printf("Warning: Failed to insert node at index %d.\n", i);
        return;
    }

    if (i == 0){
        if (*pp_head == NULL) {
            Node *p_head = init_new_node(new_val);
            if (!notify_node_malloc_failure(p_head, new_val)) return;

            *pp_head = p_head;
            return;
        }
        else {
            insert_left(pp_head, new_val);
            return;
        }
    }

    Node *p_prev;
    Node *p_curr = *pp_head;
    int curr_i = 0;

    while (p_curr->next != NULL && curr_i < i){
        p_prev = p_curr;
        p_curr = p_curr->next;
        curr_i++;
    }

    if (curr_i + 1 == i) {      // inserting element at the end of the linked list.
        Node *p_new_node = init_new_node(new_val);
        if (!notify_node_malloc_failure(p_new_node, new_val)) return;
        p_curr->next = p_new_node;
    }
    else if (curr_i < i){
        printf("Warning: Failed to insert at index %d to a linked list with a length of %d.\n", i, curr_i + 1);
        return;
    } 
    else {
        Node *p_new_node = init_new_node(new_val);
        if (!notify_node_malloc_failure(p_new_node, new_val)) return;
        p_prev->next = p_new_node;
        p_new_node->next = p_curr;
    }
}

void insert_right(Node **pp_head, int new_val){
    if (*pp_head == NULL) {
        Node *p_head = init_new_node(new_val); 
        if (!notify_node_malloc_failure(p_head, new_val)) return;
        *pp_head = p_head;
        return;
    }

    Node *p_curr_node = *pp_head;

    while (p_curr_node->next != NULL){
        p_curr_node = p_curr_node->next;
    }

    Node *p_new_node = init_new_node(new_val);
    if (!notify_node_malloc_failure(p_new_node, new_val)) return;

    p_curr_node->next = p_new_node;
}

int pop_left(Node **pp_head) {
    if (*pp_head == NULL){
        printf("Warning: failed to pop from empty linked list. (Returned value -1.)\n");
        return -1;
    }

    int val = (*pp_head)->val;

    Node *temp = *pp_head;
    *pp_head = (*pp_head)->next;
    free(temp);

    return val;
}

int pop_at_index(Node **pp_head, int i){
    if (*pp_head == NULL){
        printf("Warning: failed to pop from empty linked list. (Returned value -1.)\n");
        return -1;
    }
    if (i < 0){
        printf("Warning: failed to pop from index %d. (Returned value -1.)\n", i);
        return -1;
    }
    if (i == 0){
        return pop_left(pp_head);
    }

    Node *p_prev;
    Node *p_curr = *pp_head;
    int curr_i = 0;

    while (p_curr->next != NULL && curr_i < i){
        p_prev = p_curr;
        p_curr = p_curr->next;
        curr_i++;
    }

    if (curr_i < i){
        printf("Warning: Failed to pop from index %d in a linked list with a length of %d. (Returned value -1.)\n", i, curr_i + 1);
        return -1;
    }
    else {
        int val = p_curr->val;
        p_prev->next = p_curr->next;
        free(p_curr);
        return val;
    }
}

int pop_right(Node **pp_head){
    if (*pp_head == NULL){
        printf("Warning: failed to pop from empty linked list. (Returned value -1.)\n");
        return -1;
    }
    if ((*pp_head)->next == NULL){
        int val = (*pp_head)->val;
        free(*pp_head);
        *pp_head = NULL;
        return val;
    }

    Node *p_prev;
    Node *p_curr = *pp_head;


    while(p_curr->next != NULL){
        p_prev = p_curr;
        p_curr = p_curr->next;
    }

    int val = p_curr->val;

    p_prev->next = NULL;
    free(p_curr);

    return val;
}

void reverse(Node **pp_head){
    if (*pp_head == NULL){
        return;
    }
    Node *p1 = *pp_head;
    Node *p2 = p1->next;
    Node *p3; 

    p1->next = NULL;

    while (p2 != NULL){
        p3 = p2->next;
        p2->next = p1;

        p1 = p2;
        p2 = p3;
    }

    *pp_head = p1;
}

void traverse(const Node *p_head){
    if (p_head == NULL){
        printf("The linked list is empty.\n");
        return;
    }

    const Node *curr = p_head;

    while (curr->next != NULL){
        printf("%d -> ", curr->val);
        curr = curr->next;
    }
    printf("%d\n", curr->val);
}

int length(const Node *head){
    if (head == NULL){
        return 0;
    }

    const Node *curr = head;
    int length = 1;

    while (curr->next != NULL){
        curr = curr->next;
        length++;
    }

    return length;
}

bool notify_node_malloc_failure(const Node *node, int new_val){
    if (node == NULL){
        printf("Memory allocation for node with value %d failed.\n", new_val);
        return false;
    }
    return true;
}

void free_memory(Node *head){
    Node *p_next; 
    Node *p_current = head;

    while (p_current != NULL){
        p_next = p_current->next;
        free(p_current);
        p_current = p_next;
    }
}
