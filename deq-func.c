#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "deq.h"
#include "wrappers.h"

struct deq *deq_create(void)
{
    // create new, empty deq
    struct deq *new_deq = (struct deq*) malloc_or_exit(sizeof(struct deq));

    new_deq->leftmost = NULL;
    new_deq->rightmost = NULL;
    new_deq->count = 0;

    return new_deq;
}

struct deq_elem *deq_append(struct deq *deque, char *s)
{
    // append element on the right end, return new elem
    if(deque == NULL || s == NULL){
        return NULL;
    }

    struct deq_elem *new_elem = (struct deq_elem*) malloc_or_exit(sizeof(struct deq_elem));
    new_elem->str = strdup_or_exit(s);
    new_elem->next = NULL;
    new_elem->prev = NULL;

    if(deque->count == 0){ //in case there are no elements in deq
        deque->leftmost = new_elem;
        deque->rightmost = new_elem;
    }else{
        new_elem->prev = deque->rightmost;
        deque->rightmost->next = new_elem;
        deque->rightmost = new_elem;
    }
    
    deque->count++;
    return new_elem;
}

struct deq_elem *deq_append_left(struct deq *deque, char *s)
{
    // append element on the left end, return new elem
    if(deque == NULL || s == NULL){
        return NULL;
    }

    struct deq_elem *new_elem = (struct deq_elem*) malloc_or_exit(sizeof(struct deq_elem));
    new_elem->str = strdup_or_exit(s);
    new_elem->next = NULL;
    new_elem->prev = NULL;

    if(deque->count == 0){ //in case there are no elements in deq
        deque->leftmost = new_elem;
        deque->rightmost = new_elem;
    }else{
        deque->leftmost->prev = new_elem;
        new_elem->next = deque->leftmost;
        deque->leftmost = new_elem;
    }

    deque->count++;
    return new_elem;
}

struct deq_elem *deq_pop(struct deq *deque)
{
    // pop element of the right end, return element (NULL if empty deque), caller must free if necessary
    if(deque == NULL || deque->count == 0){
        return NULL;
    }

    struct deq_elem *popped = deque->rightmost; //to save popped element before changing pointers and then return it

    if(deque->count == 1){ //in case there is only one element in deq
        deque->leftmost = NULL;
        deque->rightmost = NULL;
    }else{
        deque->rightmost = deque->rightmost->prev; //el rightmost pasa a ser el anterior de la deq
        deque->rightmost->next = NULL; //el next del rightmost pasa a ser NULL
    }

    deque->count--;
    return popped;
}

struct deq_elem *deq_pop_left(struct deq *deque)
{
    // pop element of the left end, return element (NULL if empty deque), caller must free if necessary
    if(deque == NULL || deque->count == 0){
        return NULL;
    }

    struct deq_elem *popped = deque->leftmost; //to save popped element before changing pointers and then return it

    if(deque->count == 1){ //in case there is only one element in deq
        deque->leftmost = NULL;
        deque->rightmost = NULL;
    }else{
        deque->leftmost = deque->leftmost->next; //el leftmost pasa a ser el siguiente de la deq
        deque->leftmost->prev = NULL; //el prev del leftmost pasa a ser NULL
    }

    deque->count--;
    return popped;
}

void deq_print(struct deq *deque)
{
    // printf all str from elements from deque, left to right
    if(deque == NULL || deque->count == 0){
        printf("Deque is empty. \n");
        return;
    }

    struct deq_elem *current = deque->leftmost; // Puntero auxiliar 

    while (current != NULL){ //recorro todos los elementos y voy imprimiendo, de leftmost a rightmost
        printf("%s", deque->leftmost->str);
        current = current->next;
    }
}

void deq_print_left(struct deq *deque, int times)
{
    // printf all str from elements from deque, left to right
    if(deque == NULL || deque->count == 0){
        printf("Deque is empty. \n");
        return;
    }

    struct deq_elem *current = deque->rightmost; // Puntero auxiliar 
    int count = 0;

    while (current != NULL && count < times){ //recorro todos los elementos y voy imprimiendo, de leftmost a rightmost
        printf("%i: %s",count, current->str);
        current = current->prev;
        count ++;
    }   
}


void deq_free_memory(struct deq *deq_list)
{
    struct deq_elem *current = deq_list->leftmost; // Puntero auxiliar 
    struct deq_elem *next;

    while(current != NULL){
        next = current->next;
        free(current->str);
        free(current);
        current = next;
    }

    free(deq_list);
}