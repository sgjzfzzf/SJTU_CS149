#include <iostream>
using namespace std;

void sort(int *array, int size)
{
    int tmp, left = 0, right = size - 1; //tmp为额外使用的单元
    while (left < right)
    { //left==right时函数终止，即遍历完一次数组，故时间复杂度为O(N)
        while (array[left] < 0)
            ++left; //从左向右找到正数
        while (array[right] > 0)
            --right; //从右向左找到负数
        if (left < right)
        { //左正右负则进行交换
            tmp = array[left];
            array[left] = array[right];
            array[right] = tmp;
        }
    }
}

int main()
{
    int array[] = {4, -3, -11, 2, 5, -3, 0, 1, -5};
    cout << "original data:";
    for (int i = 0; i < 9; ++i)
        cout << array[i] << ' ';
    cout << endl;
    sort(array, 9);
    cout << "sorted data:";
    for (int i = 0; i < 9; ++i)
        cout << array[i] << ' ';
    cout << endl;
    return 0;
}
