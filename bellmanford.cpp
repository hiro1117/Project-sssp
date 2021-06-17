#include "bellmanford.h"
#include <stdio.h>


// Define parent array and distance-cost array
void bellmanford(Graph* g, int source, int costFromParent[MAX_NODE], int parentNode[MAX_NODE])
{
    int i;
    int j;
    int from;      //start node
    int to;        //end node
    int cost;      //cost


    int totalNode = g->numOfNodes;  // total number of nodes in graph
    int totalEdge = g->numOfEdge;   // total number of edges in graph

    // Fill the parent array and distance-cost array
    // all distance is infinity and parent is 0
    for(i=1; i<=totalNode; i++)
    {
        costFromParent[i] = MAX_INT;
        parentNode[i]     = 0;
    };

    //cost from start node to start node is 0
    costFromParent[source] = 0;
    //parentNode[source]     = source;

    // relax edges  'total num of nodes - 1' TIMES
    for(i=1; i<=totalNode-1; i++)
    {


       bellmanford_label0: for(j=0; j<totalEdge; j++)
        {
            //Insert edge data from Edge in Graph structure
            //Edge* edges = g->edge;
            from = g->edge[j].from;
            to   = g->edge[j].to;
            cost = g->edge[j].cost;

            // When cost of parent node is not infinity
            // if the cost of parent node plus cost is lower than next node's cost
            // Update next node's cost as the cost of parent node plus cost and parent node
            if(costFromParent[from] != MAX_INT && costFromParent[to] > costFromParent[from] + cost)
            {
                costFromParent[to] = costFromParent[from] + cost;
                parentNode[to]     = from;
                //printf("from is %d, to is %d\n", from, to);
            }
        }


    }

    // Detect negative cycle
    // If there is negative cycle, then it can not find the path
    // Set for loop after calculate path, and if it's still changing value, it means there is negative cycle.

    //printf("---- Checking Negative weight cycle ----\n");
    for(i=0; i < totalEdge; i++)
    {
        from = g->edge[i].from;
        to = g->edge[i].to;
        cost = g->edge[i].cost;

        if(costFromParent[from] != MAX_INT && costFromParent[to] > costFromParent[to] + cost)
        {
            printf("Negative weight cycle detected\n");
            return;
        }
    }

    //printf("No negative weight cycle detected\n");
    //printResult(costFromParent, totalNode);
    //printResult(parentNode, totalNode);

}

void bellmanford_top(int input_data[64*1024], int cost_from_parent[MAX_NODE], int parent_node[MAX_NODE])
{
//#pragma HLS INTERFACE s_axilite port=return
//#pragma HLS INTERFACE s_axilite port=parentNode
//#pragma HLS INTERFACE s_axilite port=costFromParent
//#pragma HLS INTERFACE s_axilite port=inputData
  Graph g;

    int n = input_data[64*1024-4];          // num of total nodes
    int m = input_data[64*1024-3];          // num of total edges
    int start = input_data[64*1024-2];      // start node
    int goal  = input_data[64*1024-1];      // goal node
    printf("n=%d, m=%d, start=%d, goal=%d\n", n, m, start, goal);

    // Insert number of nodes and edges via pointer using '->'
    g.numOfNodes = n;
    g.numOfEdge  = m;
    // insert array of edges on Graph

    //g->edge = e;


    // Read file for edge.from, edge.to, edge.cost (.gr file)
    for(int i=0; i<m; i++)
    {
        g.edge[i].from = input_data[0+3*i];
        g.edge[i].to   = input_data[1+3*i];
        g.edge[i].cost = input_data[2+3*i];
        //printf("[%d]: from is %d, to is %d, cost is %d\n",
        //		i, g.edge[i].from, g.edge[i].to, g.edge[i].cost);

    };

    bellmanford(&g, start, cost_from_parent, parent_node);

}

