#include<stdio.h>
#include<queue> 
#include<stdlib.h>
#include<string.h>
 
using namespace std;

typedef int Graph[1010][1010];  // adjacency matrix
Graph C, F, R;  // capacity¡Bflow¡Bresidual network
bool visit[1010]; // the vertice which have been visited after BFS
int path[1010];   // BFS tree
int flow[1010];   // source to each vertex min flow
 
int BFS(int s, int t)   
{
    memset(visit, false, sizeof(visit));//set visit[]=0
    queue<int> Q;   // BFS queue
    visit[s] = true;
    path[s] = s;
    flow[s] = 1e9;
    Q.push(s);
 
    while (!Q.empty())
    {
        int i = Q.front(); 
		Q.pop();
        for (int j=0; j<1010; ++j)
            if (!visit[j] && R[i][j] > 0)//residual network find augmenting path
            {
                visit[j] = true;
                path[j] = i;
                flow[j] = min(flow[i], R[i][j]);//find the shortest path ,calculate for the min flow in the path
                Q.push(j);
 
                if (j == t) return flow[t];
            }
    }
    return 0;   //if can't find the augmenting path ,then flow =0 
}
 
int fordFulkerson(int s, int t)
{
    memset(F, 0, sizeof(F));//set flow to 0
    memcpy(R, C, sizeof(C));//copy capacity to residual network
 
    int f=0, df=0;  // f=maximum flow,df=augmenting maximum flow    
	for (f=0; df=BFS(s,t); f+=df)
        for (int i=path[t], j=t; i!=j; i=path[j=i])//renew augmenting path
        {
            F[i][j] = F[i][j] + df;
            F[j][i] = -F[i][j];
            R[i][j] = C[i][j] - F[i][j];
            R[j][i] = C[j][i] - F[j][i];
        }
    return f;
}

int main()
{
	int vertex=0,edge=0;
	scanf("%d%d",&vertex,&edge);
	
	for(int i=0;i<vertex+1;i+=1)//initialize
	{
		for(int j=0;j<vertex+1;j+=1)
		{
			C[i][j]=0;
		}	
	} 
	
	int source=0,sink=0;
	scanf("%d%d",&source,&sink);
	for(int i=0;i<edge;i++)
	{
		int capacity=0,vi=0,vj=0;
		scanf("%d%d%d",&capacity,&vi,&vj);
		C[vi][vj]=capacity;
		
	}

	printf("%d",fordFulkerson(source,sink));
	
}
