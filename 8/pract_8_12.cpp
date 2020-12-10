#include <iostream>
#include<stack>
using namespace std;

//以下为快排算法
struct qsortData
{
    int start;
    int end;
    qsortData(int s,int e):start(s),end(e){}
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

void quickSort(double *array, int size)
{
    stack<qsortData> qstack;
    qstack.push(qsortData(0,size-1));
    while(!qstack.empty())
    {
        qsortData qsd=qstack.top();
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
        } 
        int mid=midSort(array, qsd.start, qsd.end);
        qstack.push(qsortData(qsd.start,mid-1));
        qstack.push(qsortData(mid+1,qsd.end));
    }
}

void search(double *array,int size,int k)
{
    quickSort(array, size);//进行快排，时间复杂度为O(NlogN)
    int left=0,right=size-1;
    int sum;
    while (left<=right){//两个坐标从左右一起向中间找，相遇则结束，时间复杂度为O(N)
        sum=array[left]+array[right];
        if (sum==k&&left<=right)//如果两数和为目标值，输出
        {
            cout<<'('<<array[left]<<','<<array[right]<<')'<<' ';
            ++left;
            --right;
        }
        else if (sum<k&&left<=right)//如果小于目标值，增大左坐标以增大和
            ++left;
        else//如果大于目标值，减小右坐标以减小和
            --right;
    }
    cout<<endl;//总的时空复杂度为O(N+NlogN)=O(NlogN)，符合题意
}

int main()
{
    double array[] = {10,9,8,7,6,5,4,3,2,1};
    cout<<"original data:";
    for (int i=0;i<10;++i)
        cout<<array[i]<<' ';
    cout<<endl;
    cout<<"when x1+x2=11:";
    search(array,10,11);
    return 0;
}
