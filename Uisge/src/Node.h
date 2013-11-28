/** @file Node.h
 */
#ifndef Node_H
#define Node_H

#include "GlobalDefs.h"

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Edge;

//enum for the status of a node, needed by Dijkstra algorithm
enum Status {NOT_VISITED,  VISITED };

/** @brief An object of this class represents a node of a graph.
 *
 */

class Node
{
private:
    string mName;             ///< Name of the node, set within construction, never changed
    vector<Edge> adjNodeList; ///< Collection (vector) of outgoing edges for this node

    enum Status mStatus;      ///< Used in doDijkstra to mark the node visited
    unsigned int mDistance;   ///< Contains the distance of the node from the starting node of the Dijstra algorithm
public:
    Node(string id); ///< Constructor
    ~Node(); ///< Destructor

    string getName() const; ///< Gets the name of the Node, no change of mName considered, therefore no setter is defined.

    enum Status getStatus() const; ///< Gets the Status.
    void setStatus(enum Status newStatus); ///< Set the status with newStatus.

    unsigned int getDistance() const; ///< Get distance of the node from the starting node of the Dijstra algorithm
    void setDistance(unsigned int distance); ///< Set distance of the node from the starting node of the Dijstra algorithm

    void addAdjNode(Node *adj, unsigned cost=1); ///< Add a new node to the graph, default cost is 1

    vector<Edge>& getAdjNodes(); ///< Get all adjacent verticies of this node

    void displayList(); ///< \deprecated For debugging purposes: displays all adjacent nodes of this node, not for final use on the UI.
    void displayNode(); ///< \deprecated For debugging purposes: displays info on a single node, not for final use on the UI.
};

#endif
