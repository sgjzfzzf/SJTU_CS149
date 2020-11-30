#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
using namespace std;

template<class Type>
class priorityQueue {
public:
	priorityQueue();
	priorityQueue(Type* data, int size);
	bool isEmpty() const;
	void enQueue(const Type& x);
	Type deQueue();
private:
	vector<Type> array;
	void percolateDown(int hole);
};

template<class Type>
bool priorityQueue<Type>::isEmpty() const {
	return array.size() - 1 == 0;
}

template<class Type>
priorityQueue<Type>::priorityQueue() {
	array.push_back(NULL);
}

template<class Type>
priorityQueue<Type>::priorityQueue(Type* data, int size) {
	array.push_back(NULL);
	for (int i = 0; i < size; ++i)
		array.push_back(data[i]);
}

template<class Type>
void priorityQueue<Type>::enQueue(const Type& x) {
	array.push_back(x);
	int hole = array.size() - 1;
	for (; hole > 1 && array[hole] > array[hole / 2]; hole /= 2) {
		swap<Type>(array[hole], array[hole / 2]);
	}
}

template<class Type>
Type priorityQueue<Type>::deQueue() {
	Type returnResult = array[1];
	array[1] = array[array.size() - 1];
	array.pop_back();
	percolateDown(1);
	return returnResult;
}

template<class Type>
void priorityQueue<Type>::percolateDown(int hole) {
	int child;
	for (; hole * 2 < array.size(); hole = child) {
		child = hole * 2;
		if (child != array.size() - 1 && array[child + 1] > array[child])
			++child;
		if (array[child] > array[hole])
			swap<Type>(array[child], array[hole]);
		else
			break;
	}
}

int main() {
	srand(time(NULL));
	priorityQueue<int> arr;
	cout << "随机生成0~99的数字并将其插入最大化堆:";
	for (int i = 0; i < 20; ++i) {
		int x = rand() % 100;
		arr.enQueue(x);
		cout << x << ' ';
	}
	cout << endl;
	cout << "输出依次从最大化堆出队的数据:";
	while (!arr.isEmpty())
		cout << arr.deQueue() << ' ';
	cout << endl;
	return 0;
}