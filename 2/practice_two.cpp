//1,6,7��������ڱ��ļ���ʵ��
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
	void erase(int x,int y);//��1�⺯��
	void reverse();//��2�⺯��
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

//��1�⺯��ʵ��
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

//��6�⺯��ʵ��
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

//��7�⺯��ʵ��
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


/*��ֱ�ӹ�����ִ�е�������������Ϊ���б�������д��0~9�����֣��ٴ���ɾ�����ڵ���5С�ڵ���7��Ԫ�أ�
  �ٶ��б���з�ת��Ȼ�󴴽�һ���µ��б��������������ݲ�ִ��ƴ�Ӳ�������ӡ*/
int main()
{
	sLinkList<int> aList, bList, cList;
	for (int i = 0; i < 10; ++i) {
		aList.insert(i, i);
	}
	cout << "���������Ա�����Ϊ:";
	aList.traverse();
	aList.erase(5, 7);
	cout << "���Ա�ɾ��ָ����Χ��Ϊ:";
	aList.traverse();
	aList.reverse();
	cout << "���Ա�ת��Ϊ:";
	aList.traverse();
	for (int i = 0; i < 10; ++i) {
		bList.insert(i, i + 10);
	}
	cout << "�´��������Ա�Ϊ:";
	bList.traverse();
	cList = aList + bList;
	cout << "ƴ�ӳɵ��µ����Ա�Ϊ:";
	cList.traverse();
	return 0;
}

