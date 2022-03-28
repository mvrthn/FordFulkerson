//
// Created by Admin on 23.03.2022.
//

#include "Edge.h"

Edge::Edge(int _flow, int _capacity, Node *_start, Node *_end) : flow(_flow), capacity(_capacity), start(_start), end(_end) {
    start->addOutgoing(this);
    end->addIncoming(this);
}

void Edge::setFlow(int _flow) {
    flow = _flow;
}

int Edge::getFlow() {
    return flow;
}

int Edge::getCapacity() {
    return capacity;
}

bool Edge::markStart(int value) {
    int minV = min(value, flow);
    if(minV > 0) {
        return start->mark(this, false, minV);
    }
    return false;
}

bool Edge::markEnd(int value) {
    int minV = min(value, capacity - flow);
    if(minV > 0) {
        return end->mark(this, true, minV);
    }
    return false;
}

Node *Edge::getStart() {
    return start;
}

Node *Edge::getEnd() {
    return end;
}

void Edge::reEvaluate(int diff, bool downstream, Node *source) {
    flow += diff * (downstream ? 1 : -1);
    (downstream ? start : end)->recalculate(diff, source);
}