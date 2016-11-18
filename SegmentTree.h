#ifndef SEG_TREE_H
#define SEG_TREE_H

#include <vector>

template<class node>
class SegmentTree{ /* A tree that supports query and update operations in O(log(n)). A Combine(node, node) function must be defined,
				   where the arguments are the answers to the queries on two contiguous ranges [s1, e1] and [e1, e2], 
				   and the return value is the answer to the query on [s1, e2].
					*/
	std::vector<node> tree; // The tree, the root node is at 1 and the children of the node at x are in x * 2 and x * 2 + 1.
	std::vector<node> arr; // The array which the segment tree is constructed upon.
	int getMidpoint(int ss, int se) const{ // Utility function that gets the midpoint of the range [ss, se]
		return ss + ((se - ss) / 2); //To avoid overflow
	}
	node RecursiveConstruct(int ss, int se, int ti = 1){ // Builds the segment tree from the array.
		if (ss == se){
			return tree[ti] = arr[ss];
		}
		else{
			int mid = getMidpoint(ss, se);
			return tree[ti] = Combine(RecursiveConstruct(ss, mid, 2 * ti), RecursiveConstruct(mid + 1, se, 2 * ti + 1));
		}
	}
	node RecursiveQuery(int ss, int se, int st, int en, int ti = 1) const{ //Queries the segment tree on [ss, se].
		if (ss == se){
			return tree[ti];
		}
		else{
			if (isAllInsideRange(ss, se, st, en))
				return tree[ti];
			int mid = getMidpoint(ss, se);
			if (!isAllOutsideOfRange(ss, mid, st, en) && !isAllOutsideOfRange(mid + 1, se, st, en)){
				return Combine(RecursiveQuery(ss, mid, st, en, 2 * ti), RecursiveQuery(mid + 1, se, st, en, 2 * ti + 1));
			}
			else if (!isAllOutsideOfRange(ss, mid, st, en)){
				return RecursiveQuery(ss, mid, st, en, 2*ti);
			}
			else if (!isAllOutsideOfRange(mid + 1, se, st, en)){
				return RecursiveQuery(mid + 1, se, st, en, 2 * ti + 1);
			}
			else{
				throw std::invalid_argument("Invalid Arguments in SegmentTree::RecursiveQuery(int, int, int, int, int)");
			}
		}
	}
	node RecursiveUpdate(int ss, int se, int idx, node newValue, int ti = 1){ /* Updates the value in the array at idx to newValue
																			     and changes the segment tree respectively */
		if (ss == se){
			return tree[ti] = arr[idx] = newValue;
		}
		else{
			int mid = getMidpoint(ss, se);
			if (mid < idx){
				return tree[ti] = Combine(tree[2 * ti], RecursiveUpdate(mid + 1, se, idx, newValue, 2 * ti + 1));
			}
			else{
				return tree[ti] = Combine(tree[2 * ti + 1], RecursiveUpdate(ss, mid, idx, newValue, 2 * ti));
			}
		}
	}
	bool isAllOutsideOfRange(int st, int en, int rangeStart, int rangeEnd) const{ /* Utility function that checks whether [st, en] is outside
																				[rangeStart, rangeEnd].
																			*/
		if (st > en)
			throw std::invalid_argument("Invalid Arguments in SegmentTree::isAllOutsideOfRange(int, int, int, int), st > en");
		return st > rangeEnd || en < rangeStart;
	}
	bool isAllInsideRange(int st, int en, int rangeStart, int rangeEnd) const{ /* Utility function that checks whether [st, en] is a subrange
																			of [rangeStart, rangeEnd].
																		 */
		if (st > en)
			throw std::invalid_argument("Invalid Arguments in SegmentTree::isAllInsideRange(int, int, int, int), st > en");
		return en <= rangeEnd && st >= rangeStart;
	}
	bool isInRange(int x) const{
		return x >= 0 && x < arr.size();
	}
public:
	SegmentTree(const std::vector<node>& a){ // Constructs the segment tree from an array.
		int height = ceil(log2(a.size()));
		int treeSize = 2* int(pow(2, height)) - 1;
		tree.resize(treeSize);
		arr = a;
		RecursiveConstruct(0, a.size() - 1);
	}
	SegmentTree(){

	}
	node Query(int st, int en) const{ // Returns the value of the query on the range [st, en].
		if (!isInRange(st) || !isInRange(en)){
			throw std::out_of_range("Subscript Out of Range in SegmentTree::Query(int, int)");
		}
		else{
			if (st > en)
				swap(st, en);
			return RecursiveQuery(0, arr.size() - 1, st, en);
		}
	}
	node Query(int idx) const{ // Returns the value of the point query at idx.
		return Query(idx, idx);
	}
	node Update(int idx, int newValue){ // Updates the value at idx to newValue.
		if (!isInRange(idx)){
			throw std::out_of_range("Subscript Out of Range in SegmentTree::Update(int)");
		}
		else{
			RecursiveUpdate(0, arr.size() - 1, idx, newValue);
		}
	}
	void SetArray(const std::vector<node>& a){ // Changes the array upon which the segment tree is constructed.
		int height = ceil(log2(a.size()));
		int treeSize = 2 * int(pow(2, height)) - 1;
		tree.resize(treeSize);
		arr = a;
		RecursiveConstruct(0, a.size() - 1);
	}
};

#endif