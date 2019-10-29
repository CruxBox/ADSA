#include<bits/stdc++.h>

using namespace std;

#define forall(n) for(int i=0;i<n;i++)
#define INF 10000

class Graph{

	int V;
	vector<pair<int,int> > *adj;
	vector<int> minheap;
	int minsize;
public:
	Graph(int v){
		V = v;
		adj = new vector<pair<int,int> >[V];
		minsize = V;
	}

	void addEdge(int u, int v,int w){
		adj[u].push_back(make_pair(v,w));
		adj[v].push_back(make_pair(u,w));
	}

	void solve(){
	
		int dist[V];
		bool vis[V];
		forall(V){
			vis[i] = false;
			dist[i] = INF;
			minheap.push_back(dist[i]);
		}
		dist[source] = 0;
		minheap[source] = 0;

		queue<int> q;

		q.push(source);

		while(){
			int u = q.front();
			q.pop();
			vis[u] = 1;
			for(int i = 0; i< adj[u].size();i++){
				if(vis[adj[u][i].first] == 1) continue;
				dist[adj[u][i].first] = min(dist[adj[u][i].first], dist[u] + adj[u][i].second);
				q.push(adj[u][i].first);
			}
		}

		int x;
		cout<<"Queries: dest"<<endl;
		while(x!=-1){
			cin>>x;
			cout<<dist[x]<<endl;
		}
	}
};

int main(){

	int n,m;
	cin>>n>>m;

	Graph g(n+1);

	int x,y,z;
	for(int i=0;i<m;i++){
		cin>>x>>y>>z;
		g.addEdge(x,y,z);
	}

	g.solve();

}
