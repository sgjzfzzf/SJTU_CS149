#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>
using namespace std;

//质数发生器，用来产生大于目标值的质数
int primeNumberProducer(int num);

template <class KEY, class OTHER>
struct SET {
	KEY key;
	OTHER other;
	SET(KEY k = NULL, OTHER o = NULL) :key(k), other(o) {}
};

template<class KEY,class OTHER>
class closeHashTable {
private:
	struct node {
		SET<KEY, OTHER> data;
		int state;
		node() { state = 0; }
	};
	node* array;
	int size;
	int loadSize;//已使用的节点数
	int deleteSize;//被删除的节点数
	int goalDeleteSize;//重散列指定的被删除节点数值
	int(*key)(const KEY& x);
	static int defaultKey(const int& x) { return x; }
	void reHash(bool reSize);//重散列函数，bool变量用于判断是否需要扩展数组的长度
public:
	static int searchTimes;
	closeHashTable(int length = 101, int goalDS = 50, int (*f)(const KEY& x) = defaultKey);
	~closeHashTable() { delete[] array; }
	SET<KEY, OTHER>* find(const KEY& x)const;
	void insert(const SET<KEY, OTHER>& x, bool reHashSwitch = true);//修改后添加了一个bool变量，用于避免reHash函数与insert函数的相互调用而进入死循环
	void remove(const KEY& x);
};

template<class KEY, class OTHER>
int closeHashTable<KEY, OTHER>::searchTimes = 0;

template<class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::reHash(bool reSize) {
	int newSize;
	node* tmparray;
	tmparray = new node[size];//构建一个新的数组用来保存原有的数组
	for (int i = 0; i < size; ++i)
		tmparray[i] = array[i];
	delete[] array;
	newSize = reSize ? primeNumberProducer(size) : size;//赋值新数组的长度
	array = new node[newSize];
	for (int i = 0; i < size; ++i) {
		if (tmparray[i].state == 1) {
			insert(tmparray[i].data, false);//不直接复制而调用insert函数的目的是清除被删除节点
		}
	}
	size = newSize;
	deleteSize = 0;
	delete[] tmparray;
}

template<class KEY, class OTHER>
closeHashTable<KEY, OTHER>::closeHashTable(int length, int goalDS, int(*f)(const KEY& x)) {
	size = length;
	loadSize = deleteSize = 0;
	array = new node[size];
	key = f;
	goalDeleteSize = goalDS;
}

template<class KEY, class OTHER>
SET<KEY, OTHER>* closeHashTable<KEY, OTHER>::find(const KEY& x) const{
	int initPos, pos;
	initPos = pos = key(x) % size;
	do {
		if (array[pos].state == 0)
			return NULL;
		if (array[pos].state == 1 && array[pos].data.key == x)
			return (SET<KEY, OTHER>*) & array[pos];
		pos = (pos + 1) % size;
	} while (pos != initPos);
}

template <class KEY,class OTHER>
void closeHashTable<KEY, OTHER>::insert(const SET<KEY, OTHER>& x, bool reHashSwitch) {
	if (reHashSwitch && loadSize * 2 >= size) {
		reHash(true);//进行需要修改数组长度的重散列
		cout << "执行了一次功能1的重散列，新的size为" << size << endl;
	}
	int initPos, pos;
	initPos = pos = key(x.key) % size;
	do {
		if (array[pos].state != 1) {
			array[pos].data = x;
			array[pos].state = 1;
			++loadSize;
			return;
		}
		++searchTimes;
		pos = (pos + 1) % size;
	} while (pos != initPos);
}

template<class KEY,class OTHER>
void closeHashTable<KEY, OTHER>::remove(const KEY& x) {
	int initPos, pos;
	initPos = pos = key(x) % size;
	do {
		if (array[pos].state == 0)
			return;
		if (array[pos].state = 1 && array[pos].data.key == x) {
			array[pos].state = 2;
			--loadSize;
			++deleteSize;
			if (deleteSize >= goalDeleteSize) {
				reHash(false);//进行不需要调整数组长度的重散列
				cout << "执行了一次功能2的重散列" << endl;
			}
			return;
		}
		pos = (pos + 1) % size;
	} while (pos != initPos);
}

int primeNumberProducer(int num) {
	while (true) {
		++num;
		bool isPrime = true;
		for (int i = 2; i < sqrt(num); ++i) {
			if (num % i == 0 && num != 2) {
				isPrime = false;
				break;
			}
		}
		if (isPrime)
			return num;
	}
}

int main() {
	srand(time(NULL));
	closeHashTable<int, int> map(25013, 500);
	for (int i = 0; i < 10000; ++i) {
		int x = rand() % 25013;
		map.insert(SET<int, int>(x, x));
	}
	cout << "共计插入10000个数字，平均每个数字探查次数为:" << static_cast<double>(map.searchTimes) / 10000 << endl;
	for (int i = 10000; i < 12508; ++i) {
		int x = rand() % 25013;
		map.insert(SET<int, int>(x, x));
	}
	for (int i = 0; i < 20000; ++i)
		map.remove(i);
	return 0;
}