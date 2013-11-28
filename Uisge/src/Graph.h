/** @file Graph.h
 */
#ifndef Graph_H
#define Graph_H

#include <vector>
#include <string>

using namespace std;

class Node;

/** @brief An object of this class represents a graph of nodes.
 *
 */
class Graph
{
private:
    vector<Node*> mNodes; ///< The nodes, or vertices
    void clearVisited() const;  ///< Sets all nodes to NOT_VISITED
public:
    Graph(void); ///< Constructor
    ~Graph(void); ///< Destructor


    void addNewNode(Node *nNode); ///< Add a node to the graph

    Node* findNodeByName(string sName) const; ///< Find a node identified by sName

    void displayGraph() const; ///< \deprecated For information, not for final use on the UI

    bool doDijkstra(string sNodename) const; ///< Dijkstra algorithm checks whether all nodes of the graph can be reached via a path from the starting node identified by sNodename
};

#endif
