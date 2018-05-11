# bloomtree
Implementation of BloomTree - A Space-Efficient Approximate Representation for Graphs

## Prerequisites
MurmurHash3 has been used as the hash function in the bloom filter. 
The code for MurmurHash3 can be found in https://github.com/aappleby/smhasher/blob/master/src

## BloomTree class
```
#include "bloomtree.h"
```

Initialise the bloom tree with the number of vertices in the graph,
size of bloom filter, and number of hash functions
```
BloomTree bt;
bt.Init(num_vertices, num_bits_in_bloom_filter, num_hash_functions);
```

Methods provided by BloomTree class are
```
AddEdge(int u, int v)
Neighbours(int u, vector<int>& neighbours)
IsEdge(int u, int v)
```

## Run
```
$ make
$ ./bfs <path_to_graph> num_vertices num_bits num_hash_functions
$ ./color <path_to_graph> num_vertices num_bits num_hash_functions
$ ./scc <path_to_graph> num_vertices num_bits num_hash_functions
```

## References
* https://github.com/aappleby/smhasher/wiki/MurmurHash3
* http://blog.michaelschmatz.com/2016/04/11/how-to-write-a-bloom-filter-cpp/