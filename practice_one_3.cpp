#include<iostream>
using namespace std;

int sumOfFactorial(int k){
    int sum = 0, kFactorial = 1;
    for (int i = 1; i < k + 1; ++i){
        kFactorial *= i;
        sum += kFactorial;
    }
    return sum;
}

int main(){
    int k;
    cout << "请输入k的值:";
    cin >> k;
    cout << "结果为:" << sumOfFactorial(k) <<endl;
    return 0;
}
