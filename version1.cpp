#include<stdio.h>
#include<queue> 
#include<stdlib.h>
#include<string.h>
#include<limits.h> 

using namespace std;

bool bfs(int **rGraph, int s, int t, int parent[],int V)
{
    bool visited[V];
    memset(visited, false, sizeof(visited));//all vertices set to NOT visit
 
    // Create a queue, enqueue source vertex and mark to be visited
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = s;
 
    
    while (!q.empty())//BFS
    {
        int i = q.front();
        q.pop();
 
        for (int j=0; j<V; j+=1)//rest of the network find augmenting path
        {
            if (visited[i]==false && rGraph[i][j] > 0)
            {
                q.push(j);
                parent[j] = i;
                visited[j] = true;
            }
        }
    }
 
    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}
 
// Returns the maximum flow from s to t in the given graph
int fordFulkerson(int **Graph, int s, int t,int V)
{
    int u=0, v=0;
 	//int rGraph[1000][1000]; // Residual network 
 	int **rGraph;
	rGraph=(int**)malloc((V+1)*sizeof(int*));
	for(int i=0;i<(V+1)*sizeof(int);i++)
	{
		rGraph[i]=(int*)malloc((V+1)*sizeof(int));
	}
    for (u = 0; u < V+1; u+=1)//first let rediual network has the same value as Graph
    {
    	for (v = 0; v < V+1; v+=1)
    	{
    		 rGraph[u][v] = Graph[u][v];
		}
            
	}
        
 	int *parent= (int*)malloc(V+1* sizeof(int));// do BFS and store path
    int max_flow = 0;
 
    // Augment the flow while tere is path from source to sink
    while (bfs(rGraph, s, t, parent,V))
    {
        int path_flow =INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
        // update residual 
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        // Add path flow to overall flow
        max_flow += path_flow;
    }
 
    // Return the overall flow
    return max_flow;
}
int main()
{
	int vertex=0,edge=0;
	scanf("%d%d",&vertex,&edge);
	
	int **Graph;
	Graph=(int**)malloc((vertex+1)*sizeof(int*));
	for(int i=0;i<(vertex+1)*sizeof(int);i++)
	{
		Graph[i]=(int*)malloc((vertex+1)*sizeof(int));
	}
	for(int i=0;i<vertex+1;i+=1)//initialize
	{
		for(int j=0;j<vertex+1;j+=1)
		{
			Graph[i][j]=0;
		}	
	} 
	int source=0,sink=0;
	scanf("%d%d",&source,&sink);
	for(int i=0;i<edge;i++)
	{
		int capacity=0,vi=0,vj=0;
		scanf("%d%d%d",&capacity,&vi,&vj);
		Graph[vi][vj]=capacity;
		//printf("%d %d %d\n",vi,vj,Graph[vi][vj]);
	}
	/*for(int i=0;i<vertex+1;i++)
	{
		for(int j=0;j<vertex+1;j++)
		{
			printf("%d ",Graph[i][j]);
		}
		printf("\n");
	}*/
	printf("%d",fordFulkerson(Graph,source,sink,vertex));
	
}
