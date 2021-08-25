#include <vector>

template <typename K, typename V>
class HashMap {
    private:
        std::vector<K> keys;
        std::vector<V> vals;

        int indexOf(K k) {
            int ind = 0;
            for(K _k : vals) {
                if(k == _k) return ind;
                ind++;
            }
            return -1;
        };

    public:
        HashMap() {};
        ~HashMap() {
            keys.clear();
            vals.clear();

            keys.shrink_to_fit();
            vals.shrink_to_fit();
        };
        void set(K k, V v) {
            if(indexOf(k) == -1) {
                keys.push_back(k);
                vals.push_back(v);
            } else {
                vals[indexOf(k)] = v;
            }
        };
        V* get(K k) {
            if(indexOf(k) == -1) { return nullptr; }
            return &vals[indexOf(k)];
        }
        V* operator[] (K k) {
            return get(k);
        }
};