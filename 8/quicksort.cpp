#include <iostream>
#include <stack>
using namespace std;

struct qsortData
{
    int start;
    int end;
    qsortData(int s, int e) : start(s), end(e) {}
};

int midSort(double *array, int start, int end)
{
    double k = array[start];
    while (start < end)
    {
        while (array[end] >= k && start < end)
            --end;
        if (start < end)
            array[start] = array[end];
        while (array[start] < k && start < end)
            ++start;
        if (start < end)
            array[end] = array[start];
    }
    array[start] = k;
    return start;
}

//用栈取代递归函数
void quickSort(double *array, int size)
{
    stack<qsortData> qstack;
    qstack.push(qsortData(0, size - 1)); //初始数据入栈
    while (!qstack.empty())
    {
        qsortData qsd = qstack.top();
        qstack.pop();
        if (qsd.start >= qsd.end)
            continue;
        else if (qsd.end - qsd.start == 1)
        {
            if (array[qsd.end] < array[qsd.start])
            {
                double tmp = array[qsd.end];
                array[qsd.end] = array[qsd.start];
                array[qsd.start] = tmp;
            }
        } //两个直接退栈的条件
        int mid = midSort(array, qsd.start, qsd.end);
        qstack.push(qsortData(qsd.start, mid - 1));
        qstack.push(qsortData(mid + 1, qsd.end)); //新的参数依次入栈
    }
}

int main()
{
    double array[] = {3.2, 32.6, 7.7, 14.6, 2.4, 5.3, 10.7};
    cout << "Original data:";
    for (int i = 0; i < 7; ++i)
        cout << array[i] << ' ';
    cout << endl;
    quickSort(array, 7);
    cout << "Sorted data:";
    for (int i = 0; i < 7; ++i)
        cout << array[i] << ' ';
    cout << endl;
    return 0;
}
