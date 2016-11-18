#include "Trie.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

void Trie::RecursivePrefixSearch(int nodeIdx, vector<string>& list, string& current) const{
	if (nodes[nodeIdx].isEnd)
		list.push_back(current);
	for (auto it : nodes[nodeIdx].children){
		current += it.first;
		RecursivePrefixSearch(it.second, list, current);
		current.pop_back();
	}
}

Trie::Trie(){
	nodes.push_back(node());
}
Trie::Trie(const Trie& other){
	nodes.clear();
	nodes.push_back(node());
	std::vector<std::string> strList = other.getStringsSorted();
	for (int i = 0; i < strList.size(); i++)
		Insert(strList[i]);
}
void Trie::Insert(const std::string& str){
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
bool Trie::Has(const std::string& str) const{
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
std::vector<std::string> Trie::getStringsWithPrefix(const std::string& pref) const{
	int nodeIdx = 0;
	for (int i = 0; i < pref.size(); i++){
		if (nodes[nodeIdx].children.count(pref[i]))
			nodeIdx = nodes[nodeIdx].children.at(pref[i]);
		else
			return std::vector<std::string>(0);
	}
	std::vector<std::string> ret;
	std::string str = pref;
	RecursivePrefixSearch(nodeIdx, ret, str);
	return ret;
}
std::vector<std::string> Trie::getStringsSorted() const{
	return getStringsWithPrefix("");
}