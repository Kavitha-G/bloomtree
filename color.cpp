/*--------------------------------------------------------------------
Greedy Coloring using Bloom Tree. 
Input format: ./color filename num_vertices num_bits num_hash_functions 
--------------------------------------------------------------------*/

#include <bits/stdc++.h>
#include "bloomtree.h"
using namespace std;

#define l int
#define DISPLAY_COLORS true

BloomTree bloom_tree;
l num_vertices;

void Colouring(){
	l *color = new l[num_vertices];
	bool *is_neighbour_color = new bool[num_vertices];
	
	// Initially, there is no color to any neighbour.
	for (l c = 1; c <= num_vertices ; ++c) {
		is_neighbour_color[c] = false;
	}

	// Initially, no color to any vertex.
	for (l v = 0; v < num_vertices; ++v) {
		color[v] = -1;
	}

	color[0] = 1;
	l num_colors_used = 1;

	for (l v = 1; v < num_vertices; ++v)
	{
		vector<l> adj;
		bloom_tree.Neighbours(v, adj);
		
		for (l i = 0; i < adj.size(); ++i) {
			if (color[adj[i]] != -1)
				is_neighbour_color[color[adj[i]]] = true;
		}

		// Finding first unassigned colour
		l c;
		for (c = 1; c <= num_vertices; ++c) {
			if (is_neighbour_color[c] == false) break;
		}
		color[v] = c;

		for (l i = 0; i < adj.size(); ++i) {
			if (color[adj[i]] != -1)
				is_neighbour_color[color[adj[i]]] = false;
		}

		if(c > num_colors_used) num_colors_used = c;
	}
	
	if (DISPLAY_COLORS) {
		for(l v = 0; v < num_vertices; ++v) {
			cout << v << " - " << color[v] << "\n";
		}
	}

	cout << "Number of colours used: " << num_colors_used << "\n";
}

int main(int argc, char** argv){
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
	Colouring();
	ti = clock() - ti;
	
	printf("%.5f\n", float(ti) / CLOCKS_PER_SEC);
	return 0;
}
