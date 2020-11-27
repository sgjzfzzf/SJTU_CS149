#include<iostream>
#include<vector>
using namespace std;

template <class KEY, class OTHER>
struct SET {
	KEY key;
	OTHER other;
	SET(int k, int o) :key(k), other(o) {}
};

template<class KEY, class OTHER>
class BinarySearchTree {
private:
	struct BinaryNode {
		SET<KEY, OTHER> data;
		BinaryNode* left;
		BinaryNode* right;
		BinaryNode(const SET<KEY, OTHER>& thedata, BinaryNode* lt = NULL, BinaryNode* rt = NULL) :data(thedata), left(lt), right(rt) {}
	};
	BinaryNode* root;
public:
	BinarySearchTree();
	~BinarySearchTree();
	SET<KEY, OTHER>* find(const KEY& x)const;
	void insert(const SET<KEY, OTHER>& x);
	void remove(const KEY& x);
	void deleteLarger(const KEY& x);
	void deleteSmaller(const KEY& x);
	void deleteRange(const KEY& x1, const KEY& x2);
	SET<KEY, OTHER> searchiMax(int i);
private:
	void insert(const SET<KEY, OTHER>& x, BinaryNode*& t);
	void remove(const KEY& x, BinaryNode*& t);
	void deleteLarger(const KEY& x, BinaryNode* t);
	void deleteSmaller(const KEY& x, BinaryNode* t);
	void deleteRange(const KEY& x1, const KEY& x2, BinaryNode* t);
	void preOrder(vector<SET<KEY,OTHER>>& sets, BinaryNode* t);
	SET<KEY, OTHER>* find(const KEY& x, BinaryNode* t)const;
	void makeEmpty(BinaryNode* t);
};

template<class KEY, class OTHER>
SET<KEY, OTHER>* BinarySearchTree<KEY, OTHER>::find(const KEY& x)const {
	return find(x, root);
}

template<class KEY, class OTHER>
SET<KEY, OTHER>* BinarySearchTree<KEY, OTHER>::find(const KEY& x, BinaryNode* t)const {
	if (t == NULL || t->data.key == x)
		return (SET<KEY, OTHER>*)t;
	if (x < t->data.key)
		return find(x, t->left);
	else
		return find(x, t->right);
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::insert(const SET<KEY, OTHER>& x) {
	insert(x, root);
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::insert(const SET<KEY, OTHER>& x, BinaryNode*& t) {
	if (t == NULL)
		t = new BinaryNode(x, NULL, NULL);
	else if (x.key < t->data.key)
		insert(x, t->left);
	else if (t->data.key < x.key)
		insert(x, t->right);
}

template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::remove(const KEY& x) {
	remove(x, root);
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::remove(const KEY& x, BinaryNode*& t) {
	if (t == NULL)
		return;
	if (x < t->data.key)
		remove(x, t->left);
	else if (t->data.key < x)
		remove(x, t->right);
	else if (t->left != NULL && t->right != NULL) {
		BinaryNode* tmp = t->right;
		while (tmp->left != NULL)
			tmp = tmp->left;
		t->data = tmp->data;
		remove(t->data.key, t->right);
	}
	else {
		BinaryNode* oldNode = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete oldNode;
	}
}

template<class KEY, class OTHER>
BinarySearchTree<KEY, OTHER>::BinarySearchTree() {
	root = NULL;
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::makeEmpty(BinaryNode* t) {
	if (t == NULL)
		return;
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
}

template<class KEY, class OTHER>
BinarySearchTree<KEY, OTHER>::~BinarySearchTree() {
	makeEmpty(root);
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::deleteLarger(const KEY& x){
	deleteLarger(x, root);
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::deleteSmaller(const KEY& x){
	deleteSmaller(x, root);
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::deleteRange(const KEY& x1, const KEY& x2){
	deleteRange(x1, x2, root);
}

template<class KEY, class OTHER>
SET<KEY, OTHER> BinarySearchTree<KEY, OTHER>::searchiMax(int i){
	vector<SET<KEY, OTHER>> sets;
	preOrder(sets, root);
	return (sets[sets.size() - i]);
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::deleteLarger(const KEY& x, BinaryNode* t){
	if (t == NULL)
		return;
	else {
		bool flag = t->right == NULL || t->right->data.key > x ? true : false;
		deleteLarger(x, t->right);
		if (flag)
			t->right = NULL;
		if (t->data.key > x) {
			t->right = NULL;
			if (t == root)
				root = t->left;
			deleteLarger(x, t->left);
			delete t;
		}
	}
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::deleteSmaller(const KEY& x, BinaryNode* t){
	if (t == NULL)
		return;
	else {
		bool flag = t->left == NULL || t->left->data.key < x ? true : false;
		deleteSmaller(x, t->left);
		if (flag)
			t->left = NULL;
		if (t->data.key < x) {
			if (t == root) 
				root = t->right;
			deleteSmaller(x, t->right);
			delete t;
		}
	}
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::deleteRange(const KEY& x1, const KEY& x2, BinaryNode* t){
	if (t == NULL)
		return;
	else {
		if (t->data.key <= x1)
			deleteRange(x1, x2, t->right);
		else if (t->data.key >= x2)
			deleteRange(x1, x2, t->left);
		else {
			remove(t->data.key);
			deleteRange(x1, x2, root);
		}
	}
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::preOrder(vector<SET<KEY, OTHER>>& sets, BinaryNode* t){
	if(t == NULL)
		return;
	preOrder(sets, t->left);
	sets.push_back(t->data);
	preOrder(sets, t->right);
}

int main() {
	BinarySearchTree<int, char> tree;
	for (int i = 0; i < 10; ++i)
		tree.insert(SET<int, char>(i, i + 'a'));
	cout << "原始状态:";
	for (int i = 0; i < 10; ++i)
		cout << tree.find(i)->other << ' ';
	cout << endl;
	cout << "搜索key第3大对应的元素:" << tree.searchiMax(3).other << endl;
	cout << "删除key大于7的元素:" << endl;
	tree.deleteLarger(7);
	for (int i = 0; i < 10; ++i) {
		SET<int, char>* p = tree.find(i);
		if (p)
			cout << p->other << ' ';
		else
			cout << "key=" << i << "已经被删除 ";
	}
	cout << endl;
	cout << "删除key小于3的元素:" << endl;
	tree.deleteSmaller(3);
	for (int i = 0; i < 10; ++i) {
		SET<int, char>* p = tree.find(i);
		if (p)
			cout << p->other << ' ';
		else
			cout << "key=" << i << "已经被删除 ";
	}
	cout << endl;
	cout << "key的值在4到7之间的元素:" << endl;
	tree.deleteRange(4, 7);
	for (int i = 0; i < 10; ++i) {
		SET<int, char>* p = tree.find(i);
		if (p)
			cout << p->other << ' ';
		else
			cout << "key=" << i << "已经被删除 ";
	}
	cout << endl;
	return 0;
}