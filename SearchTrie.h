#ifndef SEARCH_TRIE_H
#define SEARCH_TRIE_H

#include <vector>
#include <map>

template<class value>
class SearchTrie{ /*
					A trie that supports storing additional data on the nodes.
				  */
	struct node{
		std::map<char, int> children;
		bool isEnd;
		value* val;
		node(){
			isEnd = false;
			val = NULL;
		}
	};
	std::vector<node> nodes;
	void RecursivePrefixSearch(int nodeIdx, std::vector<std::pair<std::string, value*> >& list, std::string& current) const{
		if (nodes[nodeIdx].isEnd){
			list.push_back(std::make_pair(current, nodes[nodeIdx].val));
		}
		for (auto it : nodes[nodeIdx].children){
			current += it.first;
			RecursivePrefixSearch(it.second, list, current);
			current.pop_back();
		}
	}
public:
	SearchTrie(){
		nodes.push_back(node());
	}
	SearchTrie(const SearchTrie& other){
		nodes.clear();
		nodes.push_back(node());
		std::vector<std::pair<std::string, value*> > strList = other.getSortedByKey();
		for (int i = 0; i < strList.size(); i++)
			Insert(strList[i].first, *strList[i].second);
	}
	void Insert(const std::string& key, const value& val){ // Inserts a key-value pair into the trie.
		int nodeIdx = 0;
		for (int i = 0; i < key.size(); i++){
			if (nodes[nodeIdx].children.count(key[i])){
				nodeIdx = nodes[nodeIdx].children[key[i]];
			}
			else{
				nodes[nodeIdx].children[key[i]] = nodes.size();
				nodeIdx = nodes.size();
				nodes.push_back(node());
			}
		}
		nodes[nodeIdx].isEnd = true;
		nodes[nodeIdx].val = new value(val);
	}
	bool Has(const std::string& str){ // Checks whether a given key is in the trie.
		int nodeIdx = 0;
		for (int i = 0; i < str.size(); i++){
			if (nodes[nodeIdx].children.count(str[i])){
				nodeIdx = nodes[nodeIdx].children.at(str[i]);
			}
			else{
				return false;
			}
		}
		return nodes[nodeIdx].isEnd;
	}
	value* Retrieve(const std::string& key){ // Retrieves the value associated with a given key.
		int nodeIdx = 0;
		for (int i = 0; i < key.size(); i++){
			if (nodes[nodeIdx].children.count(key[i])){
				nodeIdx = nodes[nodeIdx].children.at(key[i]);
			}
			else{
				return false;
			}
		}
		return nodes[nodeIdx].val;
	}
	std::vector<std::pair<std::string, value*> > getPairsWithPrefix(const std::string& pref) const{ /* Gets all pairs with a key
																										prefixed by pref, sorted
																										lexicographically by key. */

		int nodeIdx = 0;
		for (int i = 0; i < pref.size(); i++){
			if (nodes[nodeIdx].children.count(pref[i]))
				nodeIdx = nodes[nodeIdx].children.at(pref[i]);
			else
				return std::vector<std::pair<std::string, value*> >(0);
		}
		std::vector<std::pair<std::string, value*>> ret;
		std::string str = pref;
		RecursivePrefixSearch(nodeIdx, ret, str);
		return ret;
	}
	std::vector<std::pair<std::string, value*> > getSortedByKey() const{ /* Gets all key-value pairs sorted lexicographically
																			by key. */
																		 
		return getPairsWithPrefix("");
	}
};


#endif