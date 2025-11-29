#include <vector>
#include <cassert>
using namespace std;
//非再帰
template<typename T = unsigned int, int MAX_LOG = 32>
struct Binary_Trie{
    private:
    struct Node{
        Node *nex[2];
        int count;
        long long sum;
        Node() : nex{nullptr, nullptr}, count(0), sum(0){}
    };
    Node *root;
    //存在しなければnullを返す
    Node* find(Node *t, T num, T xor_val = 0){
        for(int i = MAX_LOG - 1; i >= 0; i--){
            bool f = xor_val & ((T)1 << i);
            f ^= (bool)(num & ((T)1 << i));
            if(!t->nex[f]) return nullptr;
            t = t->nex[f];
        }
        return (t->count > 0 ? t : nullptr);
    }
    void insert(Node *t, T num, int d, T xor_val = 0){
        for(int i = MAX_LOG - 1; i >= 0; i--){
            t->count += d;
            t->sum += (long long)num * d;
            bool f = xor_val & ((T)1 << i);
            f ^= (bool)(num & ((T)1 << i));
            if(!t->nex[f]) t->nex[f] = new Node();
            t = t->nex[f];
        }
        t->count += d;
        t->sum += (long long)num * d;
    }
    T kth_element(Node *t, int k, T xor_val = 0){
        T res = 0;
        for(int i = MAX_LOG - 1; i >= 0; i--){
            bool f = xor_val & ((T)1 << i);
            if((t->nex[f] ? t->nex[f]->count : 0) < k){
                k -= (t->nex[f] ? t->nex[f]->count : 0);
                res |= ((T)1 << i);
                t = t->nex[f ^ 1];
            }
            else{
                t = t->nex[f];
            }
        }
        return res;
    }
    long long kth_element_sum(Node *t, int k, T xor_val = 0){
        T num = 0;
        long long res = 0;
        for(int i = MAX_LOG - 1; i >= 0; i--){
            bool f = xor_val & ((T)1 << i);
            if((t->nex[f] ? t->nex[f]->count : 0) < k){
                k -= (t->nex[f] ? t->nex[f]->count : 0);
                res += (t->nex[f] ? t->nex[f]->sum : 0);
                num |= ((T)1 << i);
                t = t->nex[f ^ 1];
            }
            else{
                t = t->nex[f];
            }
        }
        return res + (long long)num * k;
    }
    int count_less(Node* t, T num, T xor_val = 0){
        int res = 0;
        for(int i = MAX_LOG - 1; i >= 0; i--){
            bool f = xor_val & ((T)1 << i);
            if((num & ((T)1 << i)) && t->nex[f]) res += t->nex[f]->count;
            f ^= (bool)(num & ((T)1 << i));
            if(t->nex[f]) t = t->nex[f];
            else return res;
        }
        return res;
    }
    public:
    Binary_Trie() : root(new Node()){}
    void add(T num, int d = 1, T xor_val = 0){
        insert(root, num, d, xor_val);
    }
    void erase(T num, int d = -1, T xor_val = 0){
        insert(root, num, d, xor_val);
    }
    Node* find(T num, T xor_val = 0){
        return find(root, num, xor_val);
    }
    T count(T num, T xor_val = 0){
        Node* res = find(num, xor_val);
        if(!res) return 0;
        return res->count;
    }
    //1-indexed
    T kth_element(int k, T xor_val = 0){
        assert(root->count >= k);
        return kth_element(root, k, xor_val);
    }
    long long kth_element_sum(int k, T xor_val = 0){
        if(k == 0) return 0;
        assert(root->count >= k);
        return kth_element_sum(root, k, xor_val);
    }
    T min_element(T xor_val = 0){
        assert(root->count >= 1);
        return kth_element(1, xor_val);
    }
    T max_element(T xor_val = 0){
        assert(root->count >= 1);
        return kth_element(root->count, xor_val);
    }
    int count_less(T num, T xor_val = 0){
        return count_less(root, num, xor_val);
    }
    //実装サボってます
    int lower_bound(T num, T xor_val = 0){
        if(count(num, xor_val)) return num;
        int cnt = count_less(num, xor_val);
        assert(root->count >= cnt + 1);
        return kth_element(cnt + 1, xor_val);
    }
    int upper_bound(T num, T xor_val = 0){
        int cnt = count_less(num, xor_val) + count(num, xor_val);
        assert(root->count >= cnt + 1);
        return kth_element(cnt + 1, xor_val);
    }
    int size(){
        return root->count;
    }
};







// 再帰
template<typename T = unsigned int, int MAX_LOG = 32>
struct Binary_Trie{
    private:
    struct Node{
        Node *nex[2];
        int count;
        Node() : nex{nullptr, nullptr}, count(0){}
    };
    Node *root;
    //存在しなければnullを返す
    Node* find(Node *t, T num, int now_bit, T xor_val = 0){
        if(now_bit == -1) return (t->count > 0 ? t : nullptr);
        bool f = xor_val & ((T)1 << now_bit);
        f ^= num & ((T)1 << now_bit);
        if(!t->nex[f]) return nullptr;
        return find(t->nex[f], num, now_bit - 1, xor_val);
    }
    Node* insert(Node *t, T num, int d, int now_bit, T xor_val = 0){
        if(now_bit == -1){
            t->count += d;
        }
        else{
            t->count += d;
            bool f = xor_val & ((T)1 << now_bit);
            f ^= num & ((T)1 << now_bit);
            if(!t->nex[f]) t->nex[f] = new Node();
            t->nex[f] = insert(t->nex[f], num, d, now_bit - 1, xor_val);
        }
        return t;
    }
    T kth_element(Node *t, int k, int now_bit, T xor_val = 0){
        if(now_bit == -1) return 0;
        bool f = xor_val & ((T)1 << now_bit);
        if((t->nex[f] ? t->nex[f]->count : 0) < k){
            T res = kth_element(t->nex[f ^ 1], k - (t->nex[f] ? t->nex[f]->count : 0), now_bit - 1, xor_val);
            return (res | ((T)1 << now_bit));
        }
        return kth_element(t->nex[f], k, now_bit - 1, xor_val);
    }
    public:
    Binary_Trie() : root(new Node()){}
    void add(T num, T xor_val = 0){
        insert(root, num, 1, MAX_LOG - 1, xor_val);
    }
    void erase(T num, T xor_val = 0){
        insert(root, num, -1, MAX_LOG - 1, xor_val);
    }
    Node* find(T num, T xor_val = 0){
        return find(root, num, MAX_LOG - 1, xor_val);
    }
    T count(T num, T xor_val = 0){
        Node* res = find(num, xor_val);
        if(!res) return 0;
        return res->count;
    }
    //1-indexed
    T kth_element(int k, T xor_val = 0){
        assert(root->count >= k);
        return kth_element(root, k, MAX_LOG - 1, xor_val);
    }
    T min_element(T xor_val = 0){
        assert(root->count >= 1);
        return kth_element(1, xor_val);
    }
    T max_element(T xor_val = 0){
        assert(root->count >= 1);
        return kth_element(root->count, xor_val);
    }
};