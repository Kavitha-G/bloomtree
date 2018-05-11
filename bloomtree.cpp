/*--------------------------------------------------------------------
Bloom Tree Implementation. 
--------------------------------------------------------------------*/

#include "bloomtree.h"
#include <bits/stdc++.h>
using namespace std;

#define l int
#define pb push_back
#define rep(i, a, b) for (l i = a; i < b; ++i)

void BloomTree::Init(l num_vertices, l num_bits, l num_hash_fns) {
	bf.Init(num_bits, num_hash_fns);
	this->num_vertices = num_vertices;
}

void BloomTree::AddEdge(l u, l v) {
	vector<bool> path;
	int dir_change_idx;
	GetEdgePath(u, v, path, dir_change_idx);
	Bset(u, v, path, dir_change_idx);
	reverse(path.begin(), path.end());
	dir_change_idx = path.size() - dir_change_idx;
	Bset(v, u, path, dir_change_idx);
}

void BloomTree::Neighbours(l u, vector<int>& neigh) {
	GetNeighbours(u, Parent(u + num_vertices - 1), u + num_vertices - 1, true, neigh);
}

bool BloomTree::IsEdge(l u, l v) {
	vector<bool> path;
	int dir_change_idx;
	GetEdgePath(u, v, path, dir_change_idx);
	l cur = Parent(u + num_vertices - 1), i = 1;
	bool dir = true;
	while (cur != (v + num_vertices - 1)){
		if (dir && i != dir_change_idx) {
			if (CheckBloom(((long)cur * num_vertices + u) << 1) == 0) return false;
			cur = Parent(cur);
		}
		else if (dir){
			if (CheckBloom((((long)cur * num_vertices + u) << 1) + 1) == 0) return false;
			dir = false;
			if (path[i] == 0) cur = LeftChild(cur);
			else cur = RightChild(cur);
		}
		else {
			if (path[i] == 0) {
				if (CheckBloom(((long)cur * num_vertices + u) << 1) == 0) return false;
				cur = LeftChild(cur);
			}
			else {
				if (CheckBloom((((long)cur * num_vertices + u) << 1) + 1) == 0) return false;
				cur = RightChild(cur);
			}
		}
		++i;
	}
	return true;
}

void BloomTree::GetNeighbours(l node, l next, l cur, bool dir, vector<int>& neigh) {
	if (next < 0 || next >= ((num_vertices << 1) - 1)) return;
	if (next >= num_vertices - 1) {
		neigh.pb(next - num_vertices + 1);
		return;
	}
	if (dir && CheckBloom(((long)next * num_vertices + node) << 1) == 1) {
		GetNeighbours(node, Parent(next), next, dir, neigh);
	}
	if (dir && CheckBloom((((long)next * num_vertices + node) << 1) + 1) == 1) {
		GetNeighbours(node, Sibling(cur), next, !dir, neigh);
	}
	if (!dir && CheckBloom(((long)next * num_vertices + node) << 1) == 1) {
		GetNeighbours(node, LeftChild(next), next, dir, neigh);
	}
	if (!dir && CheckBloom((((long)next * num_vertices + node) << 1) + 1) == 1) {
		GetNeighbours(node, RightChild(next), next, dir, neigh);
	}
}

void BloomTree::GetEdgePath(l u, l v, vector<bool>& path, l& dir_change_idx) {
	vector<bool> path_u, path_v;
	GetVertexPath(u, path_u);
	GetVertexPath(v, path_v);
	l len_u = path_u.size(), len_v = path_v.size(), i = 0;
	for(; i < len_u && i < len_v && path_u[i] == path_v[i]; ++i);
	rep(j, 0, len_u - i){
		path.pb(path_u[len_u - j - 1]);
	}
	dir_change_idx = path.size();
	rep(j, i, len_v){
		path.pb(path_v[j]);
	}
}

void BloomTree::GetVertexPath(l node, vector<bool>& path) {
	node = node + num_vertices - 1;
	vector<bool> ret;
	while (node != 0) {
		l par = Parent(node);
		if (node == LeftChild(par)) ret.pb(0);
		else ret.pb(1);
		node = par;
	}
	while (!ret.empty()) {
		path.pb(ret.back());
		ret.pop_back();
	}
}

void BloomTree::Bset(l src, l dest, vector<bool>& path, int dir_change_idx) {
	l cur = Parent(src + num_vertices - 1);
	l i = 1;
	bool dir = true;  // true is upward direction.
	while(cur != (dest + num_vertices - 1)){
		if (dir && i != dir_change_idx) {
			SetBloom(((long)cur * num_vertices + src) << 1);
			cur = Parent(cur);
		}
		else if (dir){
			SetBloom((((long)cur * num_vertices + src) << 1) + 1);
			dir = false;
			if (path[i] == 0) cur = LeftChild(cur);
			else cur = RightChild(cur);
		}
		else {
			if (path[i] == 0) {
				SetBloom(((long)cur * num_vertices + src) << 1);
				cur = LeftChild(cur);
			}
			else {
				SetBloom((((long)cur * num_vertices + src) << 1) + 1);
				cur = RightChild(cur);
			}
		}
		i++;
	}
}

void BloomTree::SetBloom(long x){
	string s = ToStr(x);
	uint8_t *a = (uint8_t*)malloc(s.length() + 1);
	memset(a, 0, s.length() + 1);
	memcpy(a, s.c_str(), s.length());
	uint64_t len=(uint64_t)(s.length());
	bf.Add((const uint8_t*)a, len);
}

bool BloomTree::CheckBloom(long x){
	string s = ToStr(x);
	uint8_t *a = (uint8_t*)malloc(s.length() + 1);
	memset(a, 0, s.length() + 1);
	memcpy(a, s.c_str(), s.length());
	uint64_t len=(uint64_t)(s.length());
	return bf.PossiblyContains((const uint8_t*)a, len);
}

string BloomTree::ToStr(long x){
	string s="0000000000000000";
	int j = 0;
	if (x == 0) return "0";
	while (x > 0){
		s[j++] = x % 10 + '0';
		x /= 10;
	}
	s = s.substr(0,j);
	reverse(s.begin(), s.end());
	return s;
}

l BloomTree::Parent(l node) {
	return (((node + 1) >> 1) - 1); 
}

l BloomTree::LeftChild(l node) {
	return (((node + 1) << 1) - 1);
}

l BloomTree::RightChild(l node) {
	return ((node + 1) << 1);
}

l BloomTree::Sibling(l node) {
	return (((node + 1) ^ 1) - 1);
}