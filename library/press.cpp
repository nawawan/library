//配列に対して座圧を行う
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
template<T>
vector<T> press(vector<T> &a){
    vector<T> temp = a;
    sort(temp.begin(), temp.end());
    erase(unique(temp.begin(), temp.end()), temp.end());
    a[i] = lower_bound(temp.begin(), temp.end(), a[i]) - temp.begin();
    return temp;
}