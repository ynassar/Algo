#ifndef BINTREE_H_
#define BINTREE_H_

#include <vector>

// TODO: Make template class (at least int, ll, float, double)
class BinaryIndexedTree{ /*
							A tree that supports adding a value to an element, scaling all elements up or down by a factor c
							and querying the sum between two indices in O(log(n))
						 */
	std::vector<int> ft;
public:
	BinaryIndexedTree(int size = 0){
		ft.resize(size + 1, 0);
	}
	BinaryIndexedTree(const BinaryIndexedTree& other){
		ft = other.ft;
	}
	void AddTo(int idx, int val){ // Adds val to a[idx] (1-indexed)
		if (idx < 1 || idx >= ft.size())
			throw std::out_of_range("Subscript Out of Range in BinaryIndexedTree::AddTo(int, int)");
		for (idx; idx <= ft.size(); idx += idx & (-idx))
			ft[idx] += val;
	}
	int getSumUntil(int idx){ // Returns the sum of the elements in range [1..idx]
		if (idx < 1 || idx >= ft.size())
			throw std::out_of_range("Subscript Out of Range in BinaryIndexedTree::AddTo(int,int)");
		int sum = 0;
		for (idx; idx <= ft.size(); idx += idx & (-idx))
			sum += ft[idx];
		return sum;
	}
	int getSumOfRange(int a, int b){ // Returns the sum of the elements in range [a..b]
		if (a > b)
			std::swap(a, b);
		if (a < 1 || b >= ft.size())
			throw std::out_of_range("Subscript Out of Range in BinaryIndexedTree::getSumOfRange(int,int)");
		return getSumUntil(b) - ((a == 1) ? 0 : getSumUntil(a - 1));
	}
	void ScaleUpBy(int c){ // Multiplies all elements by c
		for (int i = 1; i <= ft.size(); i++){
			ft[i] *= c;
		}
	}
	void ScaleDownBy(int c){ // Divides all elements by c
		for (int i = 1; i <= ft.size(); i++){
			ft[i] /= c;
		}
	}
};

class BinaryIndexedTreeRU{
	
};
#endif