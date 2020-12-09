#include <iostream>
using namespace std;

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

double searchkMax(double *array, int start, int end, int size, int k) //通过单边的快排找到第k大的元素
{
    int mid = midSort(array, start, end); //进行一次操作
    if (mid == size - k)                  //如果mid恰在第k大的位置上，直接返回
        return array[mid];
    else if (mid < size - k)
        return searchkMax(array, mid + 1, end, size, k); //如果mid在k的左边，只在右边找
    else
        return searchkMax(array, start, mid - 1, size, k); //如果mid在k的右边，只在左边找
}

double searchkMax(double *array, int size, int k)
{
    return searchkMax(array, 0, size - 1, size, k);
}

int main()
{
    double array[] = {2, 4, 1, 11, 0, -2, 5, 8};
    cout << "original data:";
    for (int i = 0; i < 8; ++i)
        cout << array[i] << ' ';
    cout << endl;
    for (int k = 1; k <= 8; ++k)
        cout << "when k=" << k << ",the item is " << searchkMax(array, 8, k) << endl;
    return 0;
}
