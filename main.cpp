#include <cstdio>
#include "Node.h"
#include "Node.cpp"
#include "Edge.h"
#include "Edge.cpp"

void load(Node *source, Node *target, Node *nodes) {
    int a, b, f, c;
    while(scanf_s("%d %d %d %d\n", &f, &c, &a, &b) != EOF) {
        Node *s, *e;
        switch(a) {
            case -1:
                s = source;
                break;
            case -2:
                s = target;
                break;
            default:
                s = &nodes[a];
        }
        switch(b) {
            case -1:
                e = source;
                break;
            case -2:
                e = target;
                break;
            default:
                e = &nodes[b];
        }
        new Edge(f, c, s, e);
    }
}

void print(Node *source, Node *target, Node *nodes, int n) {
    for(int i = -1; i < n + 1; i++) {
        Node *node;
        if(i == -1) {
            node = source;
        }
        else if(i == n) {
            node = target;
        }
        else {
            node = &nodes[i];
        }
        vector<Edge *> out = *node->getOutgoing();
        vector<Edge *> in = *node->getIncoming();
        printf("index: %d, outgoing: %d, incoming: %d\n", node->getIndex(), out.size(), in.size());
    }
}

bool findPath(Node *source, Node *target, vector<Node *> *toUnmark) {
    source->setValue(INT_MAX);
    vector<Node *> toCheck;
    toCheck.push_back(source);
    toUnmark->push_back(source);
    while(!toCheck.empty()) {
        Node *node = toCheck.front();
        int value = node->getValue();
        vector<Edge *> *out = node->getOutgoing();
        vector<Edge *> *in = node->getIncoming();
        for(auto edge : *out) {
            if(edge->markEnd(value)) {
                toCheck.push_back(edge->getEnd());
                toUnmark->push_back(edge->getEnd());
                if(toCheck.back() == target) {
                    return true;
                }
            }
        }
        for(auto edge : *in) {
            if(edge->markStart(value)) {
                toCheck.push_back(edge->getStart());
                toUnmark->push_back(edge->getStart());
                if(toCheck.back() == target) {
                    return true;
                }
            }
        }
        toCheck.erase(toCheck.begin());
    }
    return false;
}

int findMaxFlow(Node *target) {
    int maxFlow = 0;
    vector<Edge *> *edges = target->getIncoming();
    for(auto edge : *edges) {
        maxFlow += edge->getFlow();
    }
    return maxFlow;
}

void findMinCrossSection(vector<pair<int, int>> *crossSection, vector<Node *> *toUnmark, int *testFlow) {
    for(auto node : *toUnmark) {
        int index = node->getIndex();
        vector<Edge *> *out = node->getOutgoing();
        vector<Edge *> *in = node->getIncoming();
        for(auto edge : *out) {
            if(!edge->getEnd()->isMarked()) {
                crossSection->push_back(pair(index, edge->getEnd()->getIndex()));
                *testFlow += edge->getFlow();
            }
        }
        for(auto edge : *in) {
            if(!edge->getStart()->isMarked()) {
                crossSection->push_back(pair(index, edge->getStart()->getIndex()));
                *testFlow += edge->getFlow();
            }
        }
    }
}

int main() {
    int n;
    scanf_s("%d\n", &n);
    Node* source = new Node(-1);
    Node* target = new Node(-2);
    Node* nodes = new Node[n];
    for(int i = 0; i < n; i++) {
        nodes[i].setIndex(i);
    }
    load(source, target, nodes);

    int maxFlow;
    vector<pair<int, int>> minCrossSection;
    int testFlow = 0;
    while(true) {
        vector<Node *> toUnmark;
        if(!findPath(source, target, &toUnmark)) {
            maxFlow = findMaxFlow(target);
            findMinCrossSection(&minCrossSection, &toUnmark, &testFlow);
            break;
        }
        target->recalculate(0, source);
        for(auto node : toUnmark) {
            node->unmark();
        }
    }

    printf("Max flow: %d\nMin cross-section:\n", maxFlow);
    for(auto pair : minCrossSection) {
        printf("%d -> %d\n", pair.first, pair.second);
    }
    printf("flow: %d\n", testFlow);
    return 0;
}

