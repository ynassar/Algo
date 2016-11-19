#ifndef ROPE_H
#define ROPE_H

#include <string>

class Rope{
	struct node{
		node* left;
		node* right;
		int weight;
		char* data;
	};
	
	node* root;
	int splitLength;

	char RecursiveIndex(int idx, node* current) const{
		if (current->weight < idx){
			return RecursiveIndex(idx - current->weight, current->right);
		}
		else{
			if (current->left != NULL){
				return RecursiveIndex(idx, current->left);
			}
			else{
				return current->data[idx];
			}
		}
	}
	Rope(node* rt): root(rt){
	}
	void Adjust(node* current){
		if (current->left || current->right)
			throw std::invalid_argument("Non-leaf node passed to Rope::Adjust(node*)");
		if (current->weight >= splitLength){
			int half = current->weight / 2;
			current->left = new node;
			current->right = new node;
			current->left->data = current->data;
			current->left->weight = half;
			current->right->data = current->data + half;
			current->right->weight = current->weight - half;
			current->data = NULL;
			Adjust(current->left);
			Adjust(current->right);
		}
	}
	int RecursiveTotalLength(node* current) const{
		if (current->right == NULL)
			return current->weight;
		return current->weight + RecursiveTotalLength(current->right);
	}
	node* RecursiveSubrope(node* current, int start, int length) const{
		if (!current->left) {
			node *s = new node;
			s->left = 0;
			s->data = current->data + start;
			s->weight = length;
			return s;
		}
		else if (start + length <= current->left->weight) {
			return RecursiveSubrope(current->left, start, length);
		}
		else if (current->left->weight <= start) {
			return RecursiveSubrope(current->right, start - current->left->weight, length - current->left->weight);
		}
		else {
			node *s = new node;
			s->left = RecursiveSubrope(current->left, start, current->left->weight - start);
			s->right = RecursiveSubrope(current->right, 0, length - (current->left->weight - start));
			s->weight = length;
			return s;
		}
	}
	void RecursiveCopyRope(node* my, node* other){
		if (other->left){
			my->left = new node;
			my->left->weight = other->left->weight;
			if (other->left->data){
				my->left->data = new char[other->left->weight + 1];
				strcpy_s(my->left->data, other->left->weight + 1, other->left->data);
			}
			else{
				my->left->data = NULL;
			}
			RecursiveCopyRope(my->left, other->left);
		}
		if (other->right){
			my->right = new node;
			my->right->weight = other->right->weight;
			if (other->right->data){
				my->right->data = new char[other->right->weight + 1];
				strcpy_s(my->right->data, other->right->weight + 1, other->right->data);
			}
			else{
				my->right->data = NULL;
			}
			RecursiveCopyRope(my->right, other->right);
		}
	}
public:
	Rope(const std::string& s, int sl = 1024){
		if (sl < 2)
			throw std::invalid_argument("Invalid Split Length in Rope::Rope(const std::string&, int)");
		splitLength = sl;
		root = new node;
		root->data = new char[s.length() + 1];
		strcpy_s(root->data, s.length() + 1, s.c_str());
		root->right = NULL;
		root->left = NULL;
		root->weight = s.length();
		Adjust(root);
	}
	Rope(const Rope& other){
		splitLength = other.splitLength;
		root = new node;
		root->weight = other.root->weight;
		if (other.root->data){
			root->data = new char[other.root->weight + 1];
			strcpy_s(root->data, other.root->weight + 1, other.root->data);
		}
		else{
			root->data = NULL;
		}
		RecursiveCopyRope(root, other.root);
	}
	char At(int idx) const{
		if (idx < 0 || idx >= root->weight)
			throw std::out_of_range("Subscript Out of Range in Rope::At(int)");
		return RecursiveIndex(idx, root);
	}
	Rope operator+(const Rope& other){
		node* newRoot = new node;
		newRoot->left = this->root;
		newRoot->right = other.root;
		newRoot->weight = RecursiveTotalLength(this->root);
		newRoot->data = NULL;
		return Rope(newRoot);
	}
};

#endif