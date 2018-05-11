#include "bloomfilter.h"
#include<bits/stdc++.h>
using namespace std;

void BloomFilter::Init(uint64_t size, uint8_t num_hashes){
	m_bits.assign(size, 0);
	m_num_hashes = num_hashes;
}

std::array<uint64_t, 2> Mhash(const uint8_t *data, std::size_t len) {
	std::array<uint64_t, 2> hash_value;
	MurmurHash3_x64_128(data, len, 0, hash_value.data());
	return hash_value;
}

inline uint64_t NthHash(uint8_t n, uint64_t hashA, uint64_t hashB, uint64_t filter_size) {
	return (hashA + n * hashB) % filter_size;
}
void BloomFilter::Add(const uint8_t *data, std::size_t len) {
	auto hash_values = Mhash(data, len);
	for (int n = 0; n < m_num_hashes; n++) {
		m_bits[NthHash(n, hash_values[0], hash_values[1], m_bits.size())] = true;
	}
}

bool BloomFilter::PossiblyContains(const uint8_t *data, std::size_t len) const {
	auto hash_values = Mhash(data, len);
	for (int n = 0; n < m_num_hashes; n++) {
		if (!m_bits[NthHash(n, hash_values[0], hash_values[1], m_bits.size())]) {
			return false;
		}
	}
	return true;
}