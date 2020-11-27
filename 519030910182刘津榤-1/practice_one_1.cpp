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
�������ú������������µ�ѭ������Ϊint(sqrt(n))-2������ʱ�临�Ӷ�ΪO(k^1/2)
*/
