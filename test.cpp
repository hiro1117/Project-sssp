#include "bellmanford.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
double gettime() {
   double t;
   struct timeval tv;
   gettimeofday(&tv, NULL);  // マイクロ秒単位で現在時刻を取得
   t = (double)tv.tv_sec + (double)tv.tv_usec*1.0e-6;
   return t;
}

void printResult(int* arr, int size)
{
    int i;
    for(i=1; i<=size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

    int costFromParent[MAX_NODE];
    int parentNode[MAX_NODE];

#include <sys/time.h>

int main(int argc, char** arvg)
{
    int i;

    // Initialization and file open
    //neighborEdgeOfStart neighbor[MAX_EDGE];

    FILE *fp;
    const char* filename = "n6.dat";
    fp = fopen(filename, "rb");
    if(!fp) {
    	printf("file '%s' could not be opened\n", filename);
    	exit(-1);
    }
    int* inputData = (int*) malloc(256*1024);

    // File read for num of node, edge, and start, goal (.p2p file)
    fread(inputData, 4, 64*1024, fp);
    fclose(fp);

    double start = gettime();
    bellmanford_top(inputData, costFromParent, parentNode);
    double end   = gettime();

    int n = inputData[64*1024-4];
    printf("\ncostFromParent\n\n");
    printResult(costFromParent, 16);
    printf("\nparentNode\n\n");
    printResult(parentNode, 16);

    printf("time(s)=%f\n", end-start);
    
    return 0;

}





/* .... 
----- List up the neighbor node of start node, and print the cost ----- 

 Find neighbor node of start

printf("\n ------ List of start-node's neighbor node and cost ------\n\n");*/

/**
for(i=0; i<m; i++)
{
    if(g->edge[i].from == start)
    {
        neighbor[i].from = g->edge[i].from;
        neighbor[i].to   = g->edge[i].to;
        neighbor[i].cost = g->edge[i].cost;
        printf("[%d]: start-node %d's neighbor node is %d, and cost of between is %d\n", i, start, neighbor[i].to, neighbor[i].cost);
    }
    else if(g->edge[i].to == start)
    {
        neighbor[i].from = g->edge[i].from;
        neighbor[i].to   = g->edge[i].to;
        neighbor[i].cost = g->edge[i].cost;
        printf("[%d]: start-node %d's neighbor node is %d, and cost of between is %d\n", i, start, neighbor[i].from, neighbor[i].cost);
    }
};
**/
