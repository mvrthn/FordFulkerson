#include "Node.h"

using namespace std;

Node::Node(): marked(false) {}

Node::Node(int _index): index(_index), marked(false) {}

void Node::setIndex(int _index) {
    index = _index;
}

int Node::getIndex() {
    return index;
}

void Node::addOutgoing(Edge *edge) {
    outgoing.push_back(edge);
}

void Node::addIncoming(Edge *edge) {
    incoming.push_back(edge);
}

vector<Edge *> *Node::getOutgoing() {
    return &outgoing;
}

vector<Edge *> *Node::getIncoming() {
    return &incoming;
}

void Node::setValue(int _value) {
    value = _value;
}

int Node::getValue() {
    return value;
}

bool Node::mark(Edge *edge, bool _downstream, int _value) {
    if(marked) {
        return false;
    }
    marked = true;
    path = edge;
    downstream = _downstream;
    value = _value;
    return true;
}

void Node::unmark() {
    marked = false;
}

void Node::recalculate(int diff, Node *source) {
    if(this != source) {
        path->reEvaluate((diff == 0 ? value : diff), downstream, source);
    }
}

bool Node::isMarked() {
    return marked;
}

