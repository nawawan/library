#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<int> zalgo(string S){
    int n = S.size();
    vector<int> Z(n, 0);
    int left = 0;
    for(int i = 1; i < n; i++){
        int l = i - left;
        if(i + Z[l] < left + Z[left]){//すでに求めたprefixに再利用したものが完全に収まるか判定
            Z[i] = Z[l];//収まっていたらすでに求めたものを再利用できる
        }
        else{
            int j = max(0, Z[left] + left - i);//収まっていなかったら収まっている部分は必ず一致するので再利用(重ならない場合に注意)
            while(i + j < n && S[i + j] == S[j]) j++;//一致しなくなるまで探索
            Z[i] = j;
            left = i;//探索した場合はそれが必ず最もみぎに終端を持つ部分文字列になる
        }
    }
    Z[0] = n;
    return Z;
}
