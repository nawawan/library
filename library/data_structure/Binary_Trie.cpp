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
    Node* find(Node *t, T num, int now_bit, T xor_val = 0){
        if(now_bit == -1) return t;
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
        find(root, num, MAX_LOG - 1, xor_val);
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