#include <stack>
using namespace std;
template<typename Monoid, Monoid (*XX)(Monoid, Monoid), Monoid (*e)()>
struct swag{
    vector<Monoid> v;
    Monoid B;
    stack<Monoid> front, back, front_val;
    int l, r;
    swag(vector<int> a) : v(a), l(0), r(0),F(e()), B(e()) {
        front_val.push(e());
    }
    Monoid query(int x, int y){
        while(r < y){
            push(r);
            ++r;
        }
        while(l < x){
            pop();
            l++;
        }
        return XX(front_val.top(), B);
    }
    void push(int x){
        back.push(v[x]);
        B = XX(B, v[x]);
    }
    void pop(){
        if(front.empty()){
            while(!back.empty()){
                front_val.push(XX(front_val.top(), back.top()));
                front.push(back.top());
                back.pop();
            }
            B = e();
        }
        front.pop();
        front_val.pop();
    }
    bool empty(){
        return (front.empty() && back.empty())
    }
    int size(){
        return front.size() + back.size();
    }
};