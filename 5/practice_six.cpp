#include<iostream>
#include<vector>
using namespace std;

template<class Type>
class binaryTree {
private:
	vector<Type> treeVector;
public:
	binaryTree(vector<Type>);
	void preOrder(int x = 1);
	void midOrder(int x = 1);
	void postOrder(int x = 1);
};

template<class Type>
binaryTree<Type>::binaryTree(vector<Type> buildVector) {
	treeVector.push_back(buildVector.front());
	for (int i = 0; i < buildVector.size(); ++i) {
		treeVector.push_back(buildVector[i]);
	}
}

template<class Type>
void binaryTree<Type>::preOrder(int x) {
	if (x > treeVector.size() - 1) {
		return;
	}
	else {
		cout << treeVector[x] << ' ';
		preOrder(x * 2);
		preOrder(x * 2 + 1);
	}
}

template<class Type>
void binaryTree<Type>::midOrder(int x){
	if (x > treeVector.size() - 1) {
		return;
	}
	else {
		midOrder(x * 2);
		cout << treeVector[x] << ' ';
		midOrder(x * 2 + 1);
	}
}

template<class Type>
void binaryTree<Type>::postOrder(int x){
	if (x > treeVector.size() - 1) {
		return;
	}
	else {
		postOrder(x * 2);
		postOrder(x * 2 + 1);
		cout << treeVector[x] << ' ';
	}
}

int main() {
	binaryTree<int> tree(vector<int>({ 1,2,3,4,5,6,10,14,2,5 }));
	tree.preOrder();
	cout << endl;
	tree.midOrder();
	cout << endl;
	tree.postOrder();
	cout << endl;
	return 0;
}