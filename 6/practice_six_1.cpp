#include<iostream>
#include<vector>
using namespace std;

template <class KEY,class OTHER>
struct SET {
	KEY key;
	OTHER other;
	SET(KEY key,OTHER other):key(key),other(other){}
	SET(const SET<KEY,OTHER>& set) :key(set.key), other(set.other) {}
};

template <class KEY, class OTHER>
int seqSearch(SET<KEY, OTHER> data[], int size, const KEY& x) {
	data[0].key = x;
	int i = size;
	for (; x != data[i].key; --i);
	if (i != size) {
		swap<SET<KEY, OTHER>>(data[i], data[i + 1]);
	}
	return i;
}

int main() {
	SET<int, char> data[] = { SET<int,char>(1,'a'),SET<int,char>(1,'a'),SET<int,char>(2,'b'),SET<int,char>(3,'c') };
	cout << "索引为0的数据已经被隐藏" << endl;
	cout << "初始数组:";
	for (int i = 1; i < 4; ++i)
		cout << data[i].key << ',' << data[i].other << ' ';
	cout << endl;
	cout << "对key=2的目标搜索两次次并依次返回结果:";
	for (int i = 0; i < 2; ++i)
		cout << seqSearch(data, 3, 1) << ' ';
	cout << endl;
	cout << "输出数组最终的形态:";
	for (int i = 1; i < 4; ++i)
		cout << data[i].key << ',' << data[i].other << ' ';
	cout << endl;
	return 0;
}