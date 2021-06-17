#define MAX_NODE 2048
#define MAX_EDGE 8192
#define MAX_INT  10000000


// Definition of List of Graph Edges
typedef struct{
    int from;           //u  start node
    int to;             //v  end node
    int cost;           //w  cost between 
} Edge;
// Definition of List of Graph Preferences
typedef struct{
    int numOfNodes;     //V total number of nodes in graph
    int numOfEdge;      //E total number of edges in graph
    Edge edge[MAX_EDGE];  //  array of edges
}Graph;

// Definition of Bellmanford Algorithm function
void bellmanford(Graph* g, int source, int costFromParent[MAX_NODE], int parentNode[MAX_NODE]);
// Definition of Bellmanford Algorithm Sub function
void bellmanford_top(int input_data[64*1024], int cost_from_parent[MAX_NODE], int parent_node[MAX_NODE]);






