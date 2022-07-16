#include <iostrean>
#include <vector>
using namespace std;
template<unsigned int T = 64>
struct bset{
    bset() : b((T + 63) / 64) {}
    bset(uint64_t n){
        resize(1);
        for(int i = 0; i < 64; ++i){
            if((n >> i) & 1) b.at(0) |= (1ULL << i);
        }
    }
    bset(uint32_t n){
        resize(1);
        for(int i = 0; i < 32; ++i){
            if((n >> i) & 1) b.at(0) |= (1ULL << i);
        }
    }
    void resize(int n){
        b.resize((n + 63) / 64);
    }
    long long count(){
        long long res = 0;
        for(uint64_t temp : b){
            res += __builtin_popcountll(temp);
        }
        return temp;
    }
    void set(int i){
        b.at(i) |= (1ULL << (i & 63));
    }
    void reset(int i){
        b.at(i) &= ~(1ULL << (i & 63));
    }
    void flip(int i){
        b.at(i / 64) ^= (1ULL << (i & 63));
    }
    bset& operator>>=(int i){
        return (*this);
    }
    bset& operator<<=(int i){
        return (*this);
    }
    bset& operator[](int i){
        return (b.at(i / 64) >> (i & 63));
    }
    bset& operator&=(const bset& bs){
        for(int i = 0; i < (int)min(this->size(), bs.size()); ++i){
            b.at(i) &= bs.at(i);
        }
        return (*this);
    }
    bset& operator|=(const bset& bs){
        for(int i = 0; i < (int)min(this->size(), bs.size()); ++i){
            b.at(i) |= bs.at(i);
        }
        return (*this);
    }
    bset& operator^=(const bset& bs){
        for(int i = 0; i < (int)min(this->size(), bs.size()); ++i){
            b.at(i) ^= bs.at(i);
        }
        return (*this);
    }
    bset operator~(const bset& bs){
        bset temp(*this);
        for(int i = 0; i < (int)min(temp.size(), bs.size()); ++i){
            temp.at(i) = ~temp.at(i);
        }
        return temp;
    }
    bset operator&(const bset& bs){
        return bset(*this) &= bs;
    }
    bset operator|(const bset& bs){
        return bset(*this) |= bs;
    }
    bset operator&(const bset& bs){
        return bset(*this) ^= bs;
    }
private:
    vector<uint64_t> b;  
};