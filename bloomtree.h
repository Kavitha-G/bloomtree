/*--------------------------------------------------------------------
Bloom Tree Implementation. 
--------------------------------------------------------------------*/

#include "bloomfilter.h"
#include <bits/stdc++.h>
using namespace std;

#define l int
#define vi vector<l>

class BloomTree {
	public:
	// Initialises the bloom tree.
	void Init(l num_vertices, l num_bits, l num_hash_fns);

	// Adds edge between u and v vertices of the original graph.
	void AddEdge(l u, l v);

	// Returns a list of neighbours of vertex u of original graph.
	void Neighbours(l u, vector<int>& neigh);

	// Returns true if there is an edge between u and v of original graph.
	bool IsEdge(l u, l v);

	private:
	// Get neighbours. Utility function.
	void GetNeighbours(l node, l next, l cur, bool dir, vector<int>& neigh);

	// Returns the path from root to node.
	void GetVertexPath(l node, vector<bool>& path);

	// Returns the path from u to v.
	void GetEdgePath(l u, l v, vector<bool>& path, l& dir_change_idx);

	// Sets all required bits for the edge u to v in the bloom tree.
	void Bset(l src, l dest, vector<bool>& path, int dir_change_idx);

	// Sets the bit x of bloom tree.
	void SetBloom(long x);

	// Checks the bit x of bloom tree.
	bool CheckBloom(long x);

	// Converts int to string. Utility function.
	string ToStr(long x);
	
	// Returns the parent of node.
	l Parent(l node);

	// Returns the left child of node.
	l LeftChild(l node);

	// Returns the right child of node.
	l RightChild(l node);

	// Returns the sibling of node.
	l Sibling(l node);
	
	// Number of vertices.
	int num_vertices;
	// The bloom filter for storing the bloom tree.
	BloomFilter bf;
};