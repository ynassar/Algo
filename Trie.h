#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <map>

class Trie{ /* 
				A radix tree that supports fast string search and string retrieval by prefix.
			*/
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
	void Insert(const std::string& str); // Adds a string to the trie.
	bool Has(const std::string& str) const; // Checks whether a string is in the trie.
	std::vector<std::string> getStringsWithPrefix(const std::string& pref) const; /* Retrieves all strings with a given prefix sorted
																				     lexicographically.
																				  */
	std::vector<std::string> getStringsSorted() const; // Retrieves all strings in the trie sorted lexicographically.
};

#endif