#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> adj[49];
vector<int> orders;
set<pair<int, int>> edges;
int visited[49];
vector<int> actualorder;

int finaldis = 0;

void check(vector<int> path)
{
	for(int i=1; i<path.size()-1; i++)
	{
		if(visited[path[i]]==1)
		{
			actualorder.push_back(path[i]);
			visited[path[i]] = 2;
			cout<<"Delivered to house no.  "<<path[i]<<" which lies in the shortest route between "<<path[0]<<" to "<<path[path.size()-1]<<"\n";
		}
	}
}

vector<int> dijkstra(int cur, int next)
{
	int d[49];
	int parent[49];
	for(int i=0; i<49; i++) d[i] = INT_MAX;
	memset(parent, -1, sizeof(parent));
	d[cur] = 0;
	set<pair<int, int>> q;
	q.insert({0, cur});
	while(!q.empty())
	{
		int v = q.begin()->second;
		q.erase(q.begin());
		for(auto edge:adj[v])
		{
			int u = edge.first;
			int x = edge.second;
			if(d[v] + x < d[u])
			{
				q.erase({d[u], u});
				d[u] = d[v] + x;
				q.insert({d[u], u});
				parent[u] = v;
			}
		}
	}
	vector<int> path;
	for (int t = next; t!=cur; t=parent[t]) path.push_back(t);
	path.push_back(cur);
	reverse(path.begin(), path.end());
	check(path);
	actualorder.push_back(next);
	visited[next] = 2;
	path.push_back(d[next]);
	return path;
}


void print(vector<int> path, int cur, int next)
{
	cout<<"Path from address of house no.  "<<cur<<" "<<"to address of house no.  "<<next<<":\n";
	int x = path.size();
	FILE *fp;
	fp = fopen("route.txt", "a+");
	for(int i=0; i<x-2; i++)
	{
		cout<<path[i]<<" "<<"->"<<" ";
		fprintf(fp, "%d ", path[i]);
	}
	fprintf(fp, "%d", path[x-2]);
	fprintf(fp, ".");
	fclose(fp);
	cout<<path[x-2];
	cout<<"\nFood delivered to house no.  "<<next<<"\n";
	cout<<"Total distance = "<<path[x-1]<<" kms"<<"\n\n";
	finaldis += path[x-1];
}


void deliver()
{
	int cur = 0, next;
	
	for(int i=0;i<orders.size();i++)
	{
		next = orders[i];
		if(visited[next]==2)
		{
			continue;
		}
		cout<<"\nStarting delivery to house no.  "<<next<<"\n";
		vector<int> path = dijkstra(cur, next);
		print(path, cur, next);
		cur = next;

	}
}


int main()
{
	// creating a graph with random distances between edges
	FILE *fp;
	fp = fopen("edges.txt", "w");
	for(int i = 0; i<48;i++)
	{
		int d = rand()%10 + 1;
		adj[i].push_back({i+1, d});
		adj[i+1].push_back({i, d});
		edges.insert({i, i+1});
		edges.insert({i+1, 1});
		fprintf(fp, "%d %d %d ", i, i+1, d);
	}

	int m = rand()%10 + 30;
	while(m>0)
	{
		int x = rand()%50, y = rand()%50;
		int d = rand()%10 + 1;
		if(edges.find({x,y})==edges.end())
		{
			fprintf(fp, "%d %d %d ", x, y, d);
			edges.insert({x,y});
			edges.insert({y,x});
			adj[x].push_back({y, d});
			adj[y].push_back({x, d});
			m--;
		}
	}
	fclose(fp);
	
	for(int i=0; i<49; i++)
	{
	    cout<<"house no.  "<<i<<" is connected to the following:\n";
	    for(auto edge:adj[i])
	    {
	        cout<<"house no.  "<<edge.first<<" with a distance of "<<edge.second<<"\n";
	    }
	    cout<<"\n";
	}

	//plot the graph
	cout<<"Enter the number of orders:\n";
	int n;
	cin>>n;
	orders.resize(n);
	cout<<"Enter the order addresses (house no. s)\n";
	memset(visited, 0, sizeof(visited));
	
	FILE *fpp;
	fpp = fopen("orders.txt", "w");
	for(int i = 0; i<n; i++)
	{
		cin>>orders[i];
		fprintf(fpp, "%d ", orders[i]);
		visited[orders[i]] = 1;
	}
	fclose(fpp);
	
	deliver();
	cout<<"Actual order of delivery:\n";
	for(int i : actualorder)
		cout<<i<<" ";
	cout<<"\n";
	cout<<"\nTotal distance travelled : "<<finaldis<<" kms"<<"\n";
	return 0;
}
