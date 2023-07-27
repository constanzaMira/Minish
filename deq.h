// deq.h

struct deq_elem {           // element of double ended queue
    char *str;              // stored string
    struct deq_elem *next;  // next element - NULL if last
    struct deq_elem *prev;  // previous element - NULL if first
};

struct deq {                // double ended queue
    int count;              // how many elements in queue
    struct deq_elem *leftmost;  // leftmost element in queue - NULL if count==0
    struct deq_elem *rightmost; // rightmost element in queue - NULL if count==0
};

extern struct deq *deq_create(void);
// create new, empty deq

extern struct deq_elem *deq_append(struct deq *deque, char *s);
// append element on the right end, return new elem

extern struct deq_elem *deq_append_left(struct deq *deque, char *s);
// append element on the left end, return new elem

extern struct deq_elem *deq_pop(struct deq *deque);
// pop element of the right end, return element (NULL if empty deque), caller must free if necessary

extern struct deq_elem *deq_pop_left(struct deq *deque);
// pop element of the left end, return element (NULL if empty deque), caller must free if necessary

extern void deq_print(struct deq *deque);
// printf all str from elements from deque, left to right

extern void deq_print_left(struct deq *deque, int times);
// printf all str from elements from deque, right to left

extern void deq_free_memory(struct deq *deq_list);
//free memory of deq