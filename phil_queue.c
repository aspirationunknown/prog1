#include "phil_queue.h"

bool isEmpty(void)
{
    if(q.headptr == NULL && q.tailptr == NULL)
        return true;
    return false;
}

bool push(Philosopher value)
{
    Philosopher* temp = malloc(sizeof(Philosopher));
    //case 1 queue is empty
    if(q.headptr == NULL && q.tailptr == NULL)
    {
        q.headptr = value;
        q.tailptr = value;
        return true;
    }

    //case 2 queue is not empty
    q.tailptr->next = value;
    q.tailptr = value;
    return true;
}

Philosopher* pop(void)
{
    if(isEmpty())
        return NULL;

    Philosopher* temp;

    temp = q.headptr;
    q.headptr = temp->next;
    //if removing last element
    if(q.tailptr == temp)
    {
        q.tailptr = NULL;
        q.headptr = NULL;
    }
    return temp;
}
