/** @file Graph.cpp
 */
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <limits.h>


//An object of class graph holds a directed graph
Graph::Graph(void)
{
}

Graph::~Graph(void)
{
    //free mem allocated to all nodes/vertices
    for(unsigned int i=0 ; i < mNodes.size() ; i++)
        delete mNodes[i];
    mNodes.clear();
}

void Graph::clearVisited() const
{
    for(unsigned int i = 0; i < mNodes.size() ; i++)
    {
        mNodes[i]->setStatus(NOT_VISITED);
    }
}

void Graph::addNewNode(Node *nNode)
{
    mNodes.push_back(nNode);
}

Node* Graph::findNodeByName(string name) const
{
    for(unsigned int i = 0 ; i < mNodes.size() ; i++)
    {
        if(mNodes[i]->getName() == name)
            return mNodes[i];
    }
    return NULL;
}

void Graph::displayGraph() const
{
    for(unsigned int i=0 ; i < mNodes.size() ; i++)
    {
        mNodes[i]->displayNode();
        mNodes[i]->displayList();
    }
}

bool Graph::doDijkstra(string sNodename) const
{
    // 1. Assign to every node a tentative distance value:
    //    set it to zero for our initial node and to infinity for all other nodes.
    Node *startNode=findNodeByName(sNodename);
    Node *currentNode=startNode;

    startNode->setDistance(0);
    for(unsigned int i=0 ; i < mNodes.size() ; i++)
    {
		if (mNodes[i]->getName() != sNodename)
            mNodes[i]->setDistance(INFINITY);
    }

    // 2. Mark all nodes unvisited.
    clearVisited();
    // Set the initial node as current.
    currentNode=startNode;

    //  Create a set of the unvisited nodes called the UnvisitedNodes consisting of all the nodes except the initial node.
    vector <Node*> UnvisitedNodes;
    for(unsigned int i=0 ; i < mNodes.size() ; i++)
    {
		UnvisitedNodes.push_back(mNodes[i]);
    }

    while (!UnvisitedNodes.empty())
    {
	unsigned int smallestDistance=INFINITY;
	// get node with smallest distance
	for(unsigned int i=0 ; i < UnvisitedNodes.size(); i++)
	{   
            Node *theNode=UnvisitedNodes[i];
            unsigned int theDistance=theNode->getDistance();
            if (theDistance < smallestDistance)
            {
                smallestDistance=theDistance;
                currentNode=theNode;
            }
	}

	//  and remove it from the unvisited set. 
	//  A visited node will never be checked again; its distance recorded now is final and minimal.	
	for(unsigned int i=0 ; i < UnvisitedNodes.size(); i++)
	{
            if (UnvisitedNodes[i] == currentNode)
            {
                UnvisitedNodes.erase(UnvisitedNodes.begin() + i);
            }
	}

	if (smallestDistance == INFINITY)
        {
            // no node can be reached anymore
            return false;
        }

	// 3.For the current node, consider all of its unvisited neighbors and calculate their tentative distances. 
	vector<Edge>& CurrentEdges=currentNode->getAdjNodes();
	for(unsigned int i=0 ; i < CurrentEdges.size(); i++)
	{
            unsigned int currentDistance=currentNode->getDistance();
            unsigned int toBeAddedDistance=CurrentEdges[i].getCost();

            //  If this distance is less than the previously recorded tentative distance of neighbor, then overwrite that distance.
            unsigned int alternateDistance=currentDistance+toBeAddedDistance;
            Node *DestinationNode=CurrentEdges[i].getDestinationNode();
            unsigned int previousDistance=DestinationNode->getDistance();

            if (alternateDistance < previousDistance)
                DestinationNode->setDistance(alternateDistance);
            //  Even though a neighbor has been examined, it is not marked as "visited" at this time, and it remains in the unvisited set.
	}

	// 4. When we are done considering all of the neighbors of the current node, mark the current node as visited
	currentNode->setStatus(VISITED); 
    } //... go back while there are unvisited nodes.
    // all nodes have been reached with a distance smaller than infinity
    // displayGraph(); cout << "\n before return true";
    return true;
}
