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
    cout << "请输入你要检验的数:";
    cin >> num;
    cout << isPrime(num) << endl;
    return 0;
}
