/** @file Node.cpp
 */
#include "Node.h"
#include "Edge.h"

Node::Node(string sName)
{
    mName = sName;
    mStatus = NOT_VISITED;
    mDistance = INFINITY;
}

//do not del the adj nodes here...they will be deleted by graph destructor
Node::~Node()
{
    adjNodeList.clear();
}

enum Status Node::getStatus() const
{
    return mStatus;
}

void Node::setStatus(enum Status status)
{
    mStatus = status;
}

string Node::getName() const
{
    return mName;
}

void Node::addAdjNode(Node *adj, unsigned cost)
{
    //create an edge with 'this' as the originating node and adj as the destination node
    Edge newEdge(this, adj, cost);
    adjNodeList.push_back(newEdge);
}

vector<Edge>& Node::getAdjNodes()
{
    return adjNodeList;
}

//displays all adjacent verticies of this vertex
void Node::displayList()
{
    string edgeOp = " -> " ;
    for(unsigned int i=0 ; i < adjNodeList.size() ; i++)
    {
        Edge edge = adjNodeList[i];
        cout << mName << " -> " << edge.getDestinationNode()->getName() << " at cost: " << edge.getCost() << endl ;
    }

}
void Node::setDistance(unsigned int distance)
{
    mDistance=distance;
}

unsigned int Node::getDistance() const
{
    return mDistance;
}

void Node::displayNode()
{
    cout << "Name:" << mName ;
    if (mStatus == VISITED)
        cout << " mStatus: VISITED" ;
    else
        cout << " mStatus: NOT_VISITED" ;
    cout << " Distance:" << mDistance << endl ;
}
