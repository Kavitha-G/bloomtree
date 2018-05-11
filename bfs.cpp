/*--------------------------------------------------------------------
BFS using Bloom Tree. 
Input format: ./bfs filename num_vertices num_bits num_hash_functions 
--------------------------------------------------------------------*/

#include <bits/stdc++.h>
#include "bloomtree.h"
using namespace std;

#define l int
#define DISPLAY_BFS_DIST true
const l N = 2e5 + 5;
const l INF = 1e8;

BloomTree bloom_tree;
l num_vertices;
l bfs_dist[N];

// Initialises bfs_dist to INF
void Init() {
	for (int i = 0; i < num_vertices; ++i) {
		bfs_dist[i] = INF;
	}
}

void BreadthFirstSearch(l s) {
	queue<l> q;
	q.push(s);
	bfs_dist[s] = 0;
	
	while(!q.empty()){
		l u = q.front();
		q.pop();

		vector<l> adj;
		bloom_tree.Neighbours(u, adj);
		
		for (l i = 0; i < adj.size(); ++i) {
			if (bfs_dist[adj[i]] == INF){
				bfs_dist[adj[i]] = bfs_dist[u] + 1;
				q.push(adj[i]);
			}
		}
	}
	if (DISPLAY_BFS_DIST) {
		for (int i = 0; i < num_vertices; ++i) {
			if (bfs_dist[i] != INF) {
				cout << i << " - " << bfs_dist[i] << "\n";
			}
		}
	}

}

int main(int argc,char** argv){
	if (argc != 5) {
		cout << "Input format: ./program_name filename num_vertices num_bits num_hash_functions\n";
		return 0;
	}
	
	clock_t ti;
	
	num_vertices = atoi(argv[2]);
	int num_bits = atoi(argv[3]);
	int num_hash_funs = atoi(argv[4]);
	
	bloom_tree.Init(num_vertices, num_bits, num_hash_funs);

	ifstream fin(argv[1], ios::in);
	while(!fin.eof()){
		l u,v;
		fin >> u >> v;
		if (u == v) continue;
		bloom_tree.AddEdge(u,v);
	}
	fin.close();

	ti = clock();
	Init();
	BreadthFirstSearch(0);
	ti = clock() - ti;
	
	printf("%.5f\n", float(ti) / CLOCKS_PER_SEC);
	return 0;
}