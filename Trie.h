#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <map>
using namespace std;

class Trie{
	struct node{
		map<char, int> children;
		bool isEnd;
		node(){
			isEnd = false;
		}
	};
	vector<node> nodes;
	void RecursivePrefixSearch(int nodeIdx, vector<string>& list, string& current) const{
		if (nodes[nodeIdx].isEnd)
			list.push_back(current);
		for (auto it : nodes[nodeIdx].children){
			current += it.first;
			RecursivePrefixSearch(it.second, list, current);
			current.pop_back();
		}
	}
public:
	Trie(){
		nodes.push_back(node());
	}
	Trie(const Trie& other){
		nodes.clear();
		nodes.push_back(node());
		vector<string> strList = other.getStringsSorted();
		for (int i = 0; i < strList.size(); i++)
			Insert(strList[i]);
	}
	void Insert(const string& str){
		int nodeIdx = 0;
		for (int i = 0; i < str.size(); i++){
			if (nodes[nodeIdx].children.count(str[i])){
				nodeIdx = nodes[nodeIdx].children[str[i]];
			}
			else{
				nodes[nodeIdx].children[str[i]] = nodes.size();
				nodeIdx = nodes.size();
				nodes.push_back(node());
			}
		}
		nodes[nodeIdx].isEnd = true;
	}
	bool Has(const string& str) const{
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
	vector<string> getStringsWithPrefix(const string& pref) const{
		int nodeIdx = 0;
		for (int i = 0; i < pref.size(); i++){
			if (nodes[nodeIdx].children.count(pref[i]))
				nodeIdx = nodes[nodeIdx].children.at(pref[i]);
			else
				return vector<string>(0);
		}
		vector<string> ret;
		string str = pref;
		RecursivePrefixSearch(nodeIdx, ret, str);
		return ret;
	}
	vector<string> getStringsSorted() const{
		return getStringsWithPrefix("");
	}
};

#endif