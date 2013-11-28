/** @file Edge.h
 */
#ifndef Edge_H
#define Edge_H

class Node;

/** @brief An object of this class represents an edge in a directed graph.
 *  Each edge is a connection between the two nodes mSourceNode and mDestinationNode. Each edge has a cost mCost, which defaults to 1.
 */
class Edge
{
private:
    Node *mSourceNode;      ///< The source node
    Node *mDestinationNode; ///< The destination node
    unsigned int mCost;     ///< The cost of the edge, default is 1

public:

    Edge(Node *theSourceNode, Node *theDestinationNode, unsigned inCost=1); ///< Constructor
    ~Edge(void); ///< Destructor

    // getters
    Node* getDestinationNode() const; ///< Get the destination node of the edge
    Node* getSourceNode() const; ///< Get the source node of the edge
    unsigned int getCost() const; ///< Get the cost of the edge
};

#endif


