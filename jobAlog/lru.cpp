#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
  public:
    int maxn;
    list<int> ls;
    unordered_map<int, list<int>::iterator> mp;
    unordered_map<int, int> val;
    LRUCache(int n) { maxn = n; }
    int get(int key) {
        if (mp.find(key) != mp.end()) {
            int value = val[key];
            auto it = mp[key];
            ls.erase(it);
            ls.push_back(key);
            mp[key] = --ls.end();
            return value;
        } else {
            return -1;
        }
    }
    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            int value = val[key];
            auto it = mp[key];
            ls.erase(it);
            ls.push_back(key);
            mp[key] = --ls.end();
            val[key] = value;
        } else {
            if (ls.size() == maxn) {
                mp.erase(*ls.begin());
                ls.pop_front();
            }
            ls.push_back(key);
            mp[key] = --ls.end();
            val[key] = value;
        }
    }
};

int main() {
    LRUCache cache = LRUCache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    std::cout << cache.get(1) << "\n"; // 返回 1
    cache.put(3, 3);                   // 该操作会使得关键字 2 作废
    std::cout << cache.get(2) << "\n"; // 返回 -1 (未找到)
    cache.put(4, 4);                   // 该操作会使得关键字 1 作废
    std::cout << cache.get(1) << "\n"; // 返回 -1 (未找到)
    std::cout << cache.get(3) << "\n"; // 返回 3
    std::cout << cache.get(4) << "\n"; // 返回 4
}
