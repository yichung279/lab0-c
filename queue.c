/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
        return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;

    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    if (q == NULL)
        return;
    /* Free queue structure */
    list_ele_t *current = q->head;
    list_ele_t *tmp;
    while (current) {
        tmp = current;
        current = current->next;
        free(tmp);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    if (q == NULL)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    char *str = strdup(s);
    if (str == NULL)
        return false;
    /* What if either call to malloc returns NULL? */
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;

    newh->next = q->head;
    newh->value = str;

    q->head = newh;
    q->tail = q->tail ? q->tail : newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
        return false;

    char *str = strdup(s);
    if (str == NULL)
        return false;

    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (newt == NULL)
        return false;

    newt->next = NULL;
    newt->value = str;

    if (q->tail)
        q->tail->next = newt;

    q->head = q->head ? q->head : newt;
    q->tail = newt;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q_size(q) == 0)
        return false;

    if (sp) {
        int str_len = bufsize / sizeof(char) - 1;
        memcpy(sp, q->head->value, str_len);
        sp[str_len] = '\0';
    }

    list_ele_t *tmp = q->head->next;
    free(q->head);
    q->head = tmp;
    q->tail = (q->size == 1) ? NULL : q->tail;
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q ? q->size : 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q_size(q) <= 1)
        return;

    list_ele_t *last = NULL;
    list_ele_t *next = q->head;
    list_ele_t *tmp;
    while (next) {
        tmp = next->next;
        next->next = last;
        last = next;
        next = tmp;
    }

    tmp = q->head;
    q->head = q->tail;
    q->tail = tmp;
}
