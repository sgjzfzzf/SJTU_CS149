//1,6,7三道题均在本文件中实现
#include<iostream>
using namespace std;

template<class elemType>
class sLinkList 
{
private:
	struct node {
		elemType data;
		node* next;
		node(const elemType& x, node* n = NULL)
		{
			data = x;
			next = n;
		}
		node(const node& tmp)
		{
			data = tmp.x;
			next = tmp.n;
		}
		node() :next(NULL) {}
		~node(){}
	};
	node* head;
	int currentLength;
	node* move(int i) const
	{
		node* p = head;
		while (i-- >= 0) {
			p = p->next;
		}
		return p;
	}
public:
	sLinkList()
	{
		head = new node;
		currentLength = 0;
	}
	~sLinkList() {
		clear();
		delete head;
	}
	void clear();
	int length() const 
	{
		return currentLength;
	}
	void insert(int i, const elemType& x);
	void remove(int i);
	int search(const elemType& x) const;
	elemType visit(int i) const;
	void traverse() const;
	void erase(int x,int y);//第1题函数
	void reverse();//第2题函数
	sLinkList& operator+ (const sLinkList& bList);
	void operator= (const sLinkList& bList);
};

template<class elemType>
void sLinkList<elemType>::clear()
{
	node* p = head->next, * q;
	head->next = NULL;
	while (p != NULL) {
		q = p->next;
		delete p;
		p = q;
	}
	currentLength = 0;
}

template<class elemType>
void sLinkList<elemType>::insert(int i, const elemType& x) 
{
	node* pos;
	pos = move(i - 1);
	pos->next = new node(x, pos->next);
	++currentLength;
}

template<class elemType>
void sLinkList<elemType>::remove(int i)
{
	node* pos, * delp;
	pos = move(i - 1);
	delp = pos->next;
	pos->next = delp->next;
	delete delp;
	--currentLength;
}

template<class elemType>
int sLinkList<elemType>::search(const elemType& x) const
{
	node* p = head->next;
	int i = 0;
	while (p != NULL && p->data != x) {
		p = p->next;
		++i;
	}
	if (p == NULL) {
		return -1;
	}
	else {
		return i;
	}
}

template<class elemType>
elemType sLinkList<elemType>::visit(int i) const
{
	return move(i)->data;
}

template<class elemType>
void sLinkList<elemType>::traverse() const
{
	node* p = head->next;
	cout << endl;
	while (p != NULL) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

//第1题函数实现
template<class elemType>
void sLinkList<elemType>::erase(int x, int y)
{
	node* p = head;
	while (p->next != NULL) {
		if (p->next->data >= x && p->next->data <= y) {
			node* tmp = p->next;
			p->next = tmp->next;
			delete tmp;
			--currentLength;
		}
		else {
			p = p->next;
		}
	}
	
}

//第6题函数实现
template<class elemType>
void sLinkList<elemType>::reverse()
{
	node* p = head, * lastP = nullptr, * nextP;
	if (p->next != NULL) {
		nextP = p->next;
		p->next = nullptr;
		p = nextP;
		delete head;
	}
	while (p->next != NULL) {
		nextP = p->next;
		p->next = lastP;
		lastP = p;
		p = nextP;
	}
	p->next = lastP;
	head = new node;
	head->next = p;
}

//第7题函数实现
template<class elemType>
sLinkList<elemType>& sLinkList<elemType>::operator+ (const sLinkList<elemType>& bList)
{
	static sLinkList<elemType>* tmp;
	tmp = new sLinkList<elemType>;
	node* p = head->next, * tmpp = tmp->head;
	for (int i = 0; i < 2; ++i) {
		while (p != NULL) {
			tmpp->next = new node;
			tmpp->next->data = p->data;
			tmpp = tmpp->next;
			p = p->next;
		}
		p = bList.head->next;
	}
	p = nullptr;
	tmpp = nullptr;
	tmp->currentLength = currentLength + bList.currentLength;
	return *tmp;
}

template<class elemType>
void sLinkList<elemType>::operator= (const sLinkList<elemType>& aList)
{
	head = aList.head;
	currentLength = aList.currentLength;
}


/*可直接供编译执行的主函数，功能为向列表中依次写入0~9的数字，再从中删除大于等于5小于等于7的元素，
  再对列表进行反转，然后创建一个新的列表，向其中输入数据并执行拼接操作并打印*/
int main()
{
	sLinkList<int> aList, bList, cList;
	for (int i = 0; i < 10; ++i) {
		aList.insert(i, i);
	}
	cout << "创建的线性表内容为:";
	aList.traverse();
	aList.erase(5, 7);
	cout << "线性表删除指定范围后为:";
	aList.traverse();
	aList.reverse();
	cout << "线性表反转后为:";
	aList.traverse();
	for (int i = 0; i < 10; ++i) {
		bList.insert(i, i + 10);
	}
	cout << "新创建的线性表为:";
	bList.traverse();
	cList = aList + bList;
	cout << "拼接成的新的线性表为:";
	cList.traverse();
	return 0;
}

