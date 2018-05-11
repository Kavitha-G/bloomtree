CXX=g++
DEPS=MurmurHash3.cpp bloomfilter.cpp bloomtree.cpp
FLAGS=-std=c++11
all: bfs color scc
bfs:bfs.cpp
	$(CXX) $^ $(DEPS) $(FLAGS) -o $@ 
color:color.cpp
	$(CXX) $^ $(DEPS) $(FLAGS) -o $@ 
scc:scc.cpp
	$(CXX) $^ $(DEPS) $(FLAGS) -o $@ 