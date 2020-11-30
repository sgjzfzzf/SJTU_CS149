#include<iostream>
#include<cmath>
using namespace std;

bool isPrime(int num){
    for (int i = 2; i < sqrt(num); ++i){
        if (num % i == 0)
            return false;
    }
    return true;
}

int main(){
    int num;
    cout << "Please input the number you want to check:";
    cin >> num;
    cout << isPrime(num) << endl;
    return 0;
}

/*
分析：该函数在最坏的情况下的循环次数为int(sqrt(n))-2，所以时间复杂度为O(k^1/2)
*/
