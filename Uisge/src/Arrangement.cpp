/** @file Arrangement.cpp
 */
#include "Arrangement.h"
//
#include "Player.h"
#include "Token.h"
#include "Team.h"

// for check_connected and doDijkstra
#include "Graph.h"
#include "Node.h"
#include "Edge.h"

#include <iostream>
using namespace std;

// Dimension only needed in implementation
const unsigned int NO_OF_TOKENS_IN_ARRANGEMENT=2*NO_OF_TOKENS;

Arrangement::Arrangement(void)
{
    mConnected = true;
}

Arrangement::~Arrangement(void)
{
    /// \todo free mem allocated to mTokens
	for (int i = 0; i < mTokens.size(); i++)
	{
		delete(mTokens[i]);
	}
	//delete(&mTokens);
}

void Arrangement::Add(Player *thePlayer)
{
    /// \todo add all tokens of the the player's team
	int i=1;
	while (thePlayer->getTheTeam()->getTheToken(i)!=NULL)
	{
		mTokens.push_back(thePlayer->getTheTeam()->getTheToken(i));
		i++;
	}
}

bool Arrangement::checkConnected() const
{
    Graph theGraph;
    // insert all nodes
    for(unsigned int i=0 ; i < mTokens.size() ; i++)
    {
        Node *newNode = new Node(mTokens[i]->getName());
        theGraph.addNewNode(newNode);
    }
    /// \todo 
    // for each Token currentToken
    //  for each Token possibleNeighborToken
    //   if token 'currentToken' and token 'possibleNeighborToken' are neighbors in NORTH, EAST; SOUTH, or WEST direction
    //    add Token possibleNeighborToken to adjacency list of currentToken

	for (int i = 0; i < mTokens.size(); i++)
	{
		for (int j = 0; j < mTokens.size(); j++)
		{
			if (mTokens[i]->isNeighbor(mTokens[j],NORTH)||mTokens[i]->isNeighbor(mTokens[j],SOUTH)||mTokens[i]->isNeighbor(mTokens[j],EAST)||mTokens[i]->isNeighbor(mTokens[j],WEST))
			{
			//mTokens[i]->
				theGraph.findNodeByName(mTokens[i]->getName())->addAdjNode(theGraph.findNodeByName(mTokens[j]->getName()));
			}
		}
	}


    // check with Dijkstra algorithm, if each Token can be reached from the start token via a path of horizontal / vertical edges
    string startNodeName=mTokens[0]->getName();
    bool Result=theGraph.doDijkstra(startNodeName);
    return Result;
}
