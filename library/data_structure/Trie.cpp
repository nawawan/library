#include <vector>
#include <cassert>
using namespace std;
//nex : 次の文字へのパスがなければ-1この頂点番号(後述のNodesのindex)
//accept : そこが終端の文字列のindex
//count : その文字を共有する文字列の個数
template<const int char_size>
struct Trie_Node{
    vector<int> nex, accept;
    int count;
    Trie_Node() : count(0){
        nex.resize(char_size, -1);
    }
};
template<int char_size, int offset>
struct Trie{
    using Node = Trie_Node<char_size>;
    vector<Node> Nodes;
    int root;
    Trie() : root(0){
        Nodes.push_back(Node());
    }
    void add(int Node_id, int char_id){
        Nodes[Node_id].nex[char_id] = (int)Nodes.size();
        Nodes.push_back(Node());
    }
    //文字列の挿入O(|word|)
    void insert(const string &word, const int str_index){
        int now = root;
        for(int i = 0; i < (int)word.size(); i++){
            int id = word[i] - offset;
            if(Nodes[now].nex[id] == -1){
                add(now, id);
            }
            ++Nodes[now].count;
            now = Nodes[now].nex[id];
        }
        ++Nodes[now].count;
        Nodes[now].accept.push_back(str_index);
    }
    void insert(const string &word){
        insert(word, Nodes[0].count);
    }
    //単語検索O(|word|)
    int exist(const string &word, bool p = false){
        int now = 0;
        for(int i = 0; i < (int)word.size(); i++){
            int temp = word[i] - offset;
            if(Nodes[now].nex[temp] == -1) return 0;
            now = Nodes[now].nex[temp];
        }
        if(p) return Nodes[now].count;
        return (int)Nodes[now].accept.size();
    }
    int prefix(const string &word){
        return exist(word, true);
    }
    //辞書順に数えてk番目の文字列を出力 O(|word|)(定数倍26)?
    string kth_string(int k){
        assert(k <= count());
        string res;
        int now = 0;
        int sum = 0;
        int cnt = 0;
        while(sum < k){
            cnt++;
            int nxt = -1;
            for(int i = 0; i < char_size; i++){
                int nxt = Nodes[now].nex[i];
                if(nxt == -1) continue;
                int temp = sum + Nodes[nxt].count;
                if(temp >= k){
                    res += (char)(offset + i);
                    now = nxt;
                    break;
                }
                sum += Nodes[nxt].count;
            }
            sum += (int)Nodes[now].accept.size();
        }
        return res;
    }
    int count(){
        return Nodes[0].count;
    }
    int size(){
        return (int)Nodes.size();
    }
};