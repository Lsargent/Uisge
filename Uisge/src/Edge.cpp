/** @file Node.cpp
 */
#include "Node.h"
#include "Edge.h"

Edge::Edge(Node *theSourceNode, Node *theDestinationNode, unsigned inCost)
{
    mSourceNode = theSourceNode;
    mDestinationNode = theDestinationNode;
    mCost = inCost;
}

Edge::~Edge(void)
{
}

Node* Edge::getDestinationNode() const
{
    return mDestinationNode;
}

Node* Edge::getSourceNode() const
{
    return mSourceNode;
}

unsigned int Edge::getCost() const
{
    return mCost;
}
