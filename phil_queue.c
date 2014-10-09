#include "phil_queue.h"

bool isEmpty(void)
{
    if(count == 0)
        return true;
    return false;
}

bool push(Philosopher* value)
{
    //case 1 queue is empty
    if(q.headptr == NULL && q.tailptr == NULL)
    {
        q.headptr = value;
        q.tailptr = value;
        q.count++;
        return true;
    }

    //case 2 queue is not empty
    q.tailptr->next = value;
    q.tailptr = value;
    q.count++
    return true;
}

Philosopher* pop(void)
{
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
