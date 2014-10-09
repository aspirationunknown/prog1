struct Philosopher
{
    int rank;
    bool isHungry;
};

struct node
{
    Philosopher* value;
    node* next;
};

struct Queue
{
    int count; //the number of items in the queue
    node* headptr;
    node* tailptr;
};

//global queue
Queue q;

//Queue functions
bool isEmpty(void);
bool push(Philosopher value);
Philosopher* pop(void);

