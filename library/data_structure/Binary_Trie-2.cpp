#include <vector>
#include <cassert>
using namespace std;
template<typename T = unsigned int, int MAX_LOG = 32>
struct Binary_Trie{
    private:
    struct Node{
        Node *nex[2];
        T count;
        Node() : nex{nullptr, nullptr}, count(0){}
    };
    Node *root;
    //存在しなければnullを返す
    Node* find(Node *t, T num, T xor_val = 0){
        for(int i = MAX_LOG - 1; i >= 0; i--){
            bool f = xor_val & ((T)1 << i);
            f ^= num & ((T)1 << i);
            if(!t->nex[f]) return nullptr;
            t = t->nex[f];
        }
        return t;
    }
    void insert(Node *t, T num, int d, T xor_val = 0){
        for(int i = MAX_LOG - 1; i >= 0; i--){
            t->count += d;
            bool f = xor_val & ((T)1 << i);
            f ^= (num & ((T)1 << i));
            if(!t->nex[f]) t->nex[f] = new Node();
            t = t->nex[f];
        }
        t->count += d;
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
    public:
    Binary_Trie() : root(new Node()){}
    void add(T num, T xor_val = 0){
        insert(root, num, 1, xor_val);
    }
    void erase(T num, T xor_val = 0){
        insert(root, num, -1, xor_val);
    }
    Node* find(T num, T xor_val = 0){
        find(root, num, xor_val);
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
    T min_element(T xor_val = 0){
        assert(root->count >= 1);
        return kth_element(1, xor_val);
    }
    T max_element(T xor_val = 0){
        assert(root->count >= 1);
        return kth_element(root->count, xor_val);
    }
};