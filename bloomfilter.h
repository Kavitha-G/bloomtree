#include "MurmurHash3.h"
#include<bits/stdc++.h>
using namespace std;

class BloomFilter {
	public:
	// Initialises the bloom filter with the
	// size of bloom filter and number of hashes.
	void Init(uint64_t size, uint8_t num_hashes);
	
	// Adds element to the bloom filter.
	void Add(const uint8_t *data, std::size_t len);
	
	// Returns true if the bloom filter contains the element.
	// False positives may occur.
	bool PossiblyContains(const uint8_t *data, std::size_t len) const;

	private:
	// Number of hash functions. 
	uint8_t m_num_hashes;
	// Number of bits in bloom filter.
	std::vector<bool> m_bits;
};

