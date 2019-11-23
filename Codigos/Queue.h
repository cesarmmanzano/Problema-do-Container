#ifndef QueueCF_h
#define QueueCF_h

#include  <stdlib.h>
using namespace std;

#define MAXELEMENTS 100

struct Queue
{
    int first,last;
    queue_element local[MAXELEMENTS];
};

void initQueue(Queue&);
void insertQ(Queue&,queue_element);
int isEmptyQ(Queue);
queue_element eliminate(Queue&);
queue_element consult(Queue);



void initQueue(Queue& Q)
{
    Q.first = 0;
    Q.last = -1;
}

int isEmptyQ(Queue Q)
{
    if(Q.first > Q.last)
        return 1;
    else
        return 0;
}


void insertQ(Queue& Q, queue_element V)
{
    if(Q.last == MAXELEMENTS)
        exit(1);
    Q.last++;
    Q.local[Q.last] = V;
}


queue_element eliminate(Queue& Q)
{
    if(isEmptyQ(Q))
        exit(1);
    return (Q.local [Q.first++ ]);
}


queue_element consult(Queue Q)
{
    if(isEmptyQ(Q))
        exit(1);
    return (Q.local[Q.first]);
}

#endif
