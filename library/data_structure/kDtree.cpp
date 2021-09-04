#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Node{
    int num;
    Node *left;
    Node *right;
    Node(int x, Node* l, Node* r) : num(x), left(l), right(r){}
};
struct kdtree{
    vector<int> x, y;
    //点群のx座標とy座標をコンストラクタに渡す
    kdtree(vector<int>&X, vector<int>&Y) : x(X), y(Y) {}
    //平衡二分探索木を作成してその根のポインタを返す
    //O(Nlog(N)^2)
    Node* build(vector<int>&ind, int l, int r, int depth){
        if(l >= r) return nullptr;
        int mid = (l + r) / 2;
        if(depth % 2 == 0){
            sort(ind.begin() + l, ind.begin() + r, [&](int i, int j){
                return x[i] < x[j];
            });
        }
        else{
            sort(ind.begin() + l, ind.begin() + r, [&](int i, int j){
                return y[i] < y[j];
            });
        }
        return new Node(ind[mid], build(ind, l, mid, depth + 1), build(ind, mid + 1, r, depth + 1));
    }
    //二次元平面のlx <= x < rx && ly <= y < ryにある点のindexがretに格納される
    void search(int &lx, int &rx, int &ly, int &ry, int d, Node *node, vector<int>&ret){
        int id = node->num;
        if(lx <= x[id] && x[id] <= rx && ly <= y[id] && y[id] <= ry) ret.push_back(id);
        if(d % 2 == 0){
            if(node->left != nullptr && lx <= x[id]){
                search(lx, rx, ly, ry, d + 1, node->left, ret);
            }
            if(node->right != nullptr && x[id] <= rx){
                search(lx, rx, ly, ry, d + 1, node->right, ret);
            }
        }
        else{
            if(node->left != nullptr && ly <= y[id]){
                search(lx, rx, ly, ry, d + 1, node->left, ret);
            }
            if(node->right != nullptr && y[id] <= ry){
                search(lx, rx, ly, ry, d + 1, node->right, ret);
            }
        }
    }
};