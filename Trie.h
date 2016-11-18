#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <map>

class Trie{
	struct node{
		std::map<char, int> children;
		bool isEnd;
		node(){
			isEnd = false;
		}
	};
	std::vector<node> nodes;
	void RecursivePrefixSearch(int nodeIdx, std::vector<std::string>& list, std::string& current) const;
public:
	Trie();
	Trie(const Trie& other);
	void Insert(const std::string& str);
	bool Has(const std::string& str) const;
	std::vector<std::string> getStringsWithPrefix(const std::string& pref) const;
	std::vector<std::string> getStringsSorted() const;
};

#endif