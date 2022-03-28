#ifndef FORDFULKERSON_NODE_H
#define FORDFULKERSON_NODE_H

#include "Edge.h"
#include <vector>

class Node {
private:
    int index;
    std::vector<Edge *> outgoing;
    std::vector<Edge *> incoming;
    bool marked;
    Edge *path;
    bool downstream;
    int value;
public:
    Node();
    Node(int _index);
    void setIndex(int _index);
    int getIndex();
    void addOutgoing(Edge *edge);
    void addIncoming(Edge *edge);
    std::vector<Edge *> *getOutgoing();
    std::vector<Edge *> *getIncoming();
    void setValue(int _value);
    int getValue();
    bool mark(Edge *edge, bool _downstream, int _value);
    void unmark();
    void recalculate(int diff, Node* source);
    bool isMarked();
};

#endif //FORDFULKERSON_NODE_H
