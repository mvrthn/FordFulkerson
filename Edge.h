#ifndef FORDFULKERSON_EDGE_H
#define FORDFULKERSON_EDGE_H

#include "Node.h"

class Node;

class Edge {
private:
    int flow;
    const int capacity;
    Node *start, *end;
public:
    Edge(int _flow, int _capacity, Node *_start, Node *_end);
    void setFlow(int _flow);
    int getFlow();
    int getCapacity();
    bool markStart(int value);
    bool markEnd(int value);
    Node *getStart();
    Node *getEnd();
    void reEvaluate(int diff, bool downstream, Node* source);
};


#endif //FORDFULKERSON_EDGE_H
