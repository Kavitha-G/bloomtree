/*--------------------------------------------------------------------
SCC using Bloom Tree. 
Input format: ./scc filename num_vertices num_bits num_hash_functions 
--------------------------------------------------------------------*/

#include <bits/stdc++.h>
#include "bloomtree.h"
using namespace std;

#define l int
#define DISPLAY_SCC false
const l N = 2e5 + 5;
const l INF = 1e8;

BloomTree bloom_tree;
l num_vertices;
l WH = -1, BL = 1, num_sccs;
l dfs_num[N], dfs_low[N], dfscounter;
stack<l> dfs_scc;
set<l> in_stack;

void Init(){
	for (int i = 0; i < num_vertices; ++i) {
		dfs_num[i]=WH;
	}
}

void SCC(l u) {
	dfs_low[u] = dfs_num[u] = dfscounter++;
	dfs_scc.push(u);
	in_stack.insert(u);
	
	vector<l> adj;
	bloom_tree.Neighbours(u, adj);
	
	for (l i = 0; i < adj.size(); ++i) {	
		if (dfs_num[adj[i]] == WH) {
			SCC(adj[i]);
		}
		if (in_stack.find(adj[i]) != in_stack.end()) {
			dfs_low[u] = min(dfs_low[u], dfs_low[adj[i]]);
		}
	}
	
	if (dfs_low[u] == dfs_num[u]) {  // u is a root of a SCC.
		num_sccs++;
		while (!dfs_scc.empty() && dfs_scc.top() != u){
			if (DISPLAY_SCC) {
				cout << dfs_scc.top() << " ";
			}
			in_stack.erase(dfs_scc.top());
			dfs_scc.pop();
		}
		if (DISPLAY_SCC) {
			cout << dfs_scc.top() << "\n";
		}
		in_stack.erase(dfs_scc.top());
		dfs_scc.pop();
	}
}

int main(int argc, char** argv) {
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
	dfscounter = 0;
	num_sccs = 0;
	for (int i = 0; i < num_vertices; ++i) {
		if (dfs_num[i] == WH) {
			SCC(i);
		}
	}
	ti = clock() - ti;
	
	printf("%.5f\n", float(ti) / CLOCKS_PER_SEC);
	cout << "Number of SCCs: " << num_sccs << "\n";
	return 0;
}