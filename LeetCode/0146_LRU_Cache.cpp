class LRUCache {
// unordered_map : k - list iter
// put, get, move
// list<pair<k, v>>
private:
    list<pair<int, int>> store;
    unordered_map<int, list<pair<int, int>>::iterator> m;
    int _capacity = 0;
public:
    LRUCache(int capacity) {
        _capacity = capacity;
    }
    
    int get(int key) {
        if (m.count(key)) {
            store.splice(store.begin(), store, m[key]);
            return store.begin()->second;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (m.count(key)) {
            store.splice(store.begin(), store, m[key]);
            store.begin()->second = value;
        } else {
            if (store.size() == _capacity) {
                int to_evict = store.back().first;
                m.erase(to_evict);
                store.pop_back();
            }
            store.push_front(make_pair(key, value));
            m[key] = store.begin();
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

class LRUCache {
private:
    int _capacity = 0;
    unordered_map<int, list<pair<int, int>>::iterator> _m;
    list<pair<int, int>> _list;
public:
    LRUCache(int capacity) {
        _capacity = capacity;
    }
    
    int get(int key) {
        if (_m.count(key)) {
            auto it = _m[key];
            _list.splice(_list.end(), _list, it);
            return _list.back().second;
        } else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        if (_m.count(key)) {
            auto it = _m[key];
            _list.splice(_list.end(), _list, it);
            _list.back().second = value;
        } else {
            if (_list.size() == _capacity) {
                pair<int, int> least_recently_used = _list.front();
                _m.erase(least_recently_used.first);
                _list.pop_front();
            }
            _list.emplace_back(key, value);
            _m[key] = _list.end();
            _m[key] --;
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

class LRUCache {
private:
    list<pair<int, int>> _storage;
    unordered_map<int, list<pair<int, int>>::iterator> _m;
    int _capacity;
public:
    LRUCache(int capacity) {
        _capacity = capacity;
    }
    
    int get(int key) {
        if (_m.count(key)) {
            auto it = _m[key];
            _storage.splice(_storage.begin(), _storage, it);
            return it->second;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (_m.count(key)) {
            auto it = _m[key];
            _storage.splice(_storage.begin(), _storage, it);
            it->second = value;
        } else {
            if (_storage.size() == _capacity) {
                auto p = _storage.back();
                _m.erase(p.first);
                _storage.pop_back();
            }
            _storage.push_front(make_pair(key, value));
            _m[key] = _storage.begin();
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

class LRUCache {
private:
    int _capacity;
    unordered_map<int, list<pair<int, int>>::iterator> _map; // k to list item
    list<pair<int, int>> _storage; // list of pairs of kv
public:
    LRUCache(int capacity) {
        //put O(1) find & remove O(1) add at the head, list 
        //get O(1) map
        _capacity = capacity;
        
    }
    
    int get(int key) {
        // map (key - list item - val)
        // if exists, remove the item add to head
        int val = -1;
        if (_map.count(key)) {
            val = _map[key]->second;
            _storage.splice(_storage.begin(), _storage, _map[key]);
        }
        return val;
    }
    
    void put(int key, int value) {
        //map(key - list item)
        // if exists, update item, remove the item add to head
        // if not, new item at the head
        //        if capacity full
        //           remove the last item, remove map key
        if (_map.count(key)) {
            _map[key]->second = value;
            _storage.splice(_storage.begin(), _storage, _map[key]);
        } else {
            _storage.push_front(make_pair(key, value));
            _map[key] = _storage.begin();
            _capacity --;
            if (_capacity < 0) {
                _map.erase(_storage.back().first);
                _storage.pop_back();
                _capacity ++;
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

//43% 35%
class LRUCache {
private:
    list<pair<int, int>> _cache_val;
    unordered_map<int, list<pair<int, int>>::iterator> _cache_map;
    int _capacity;
    int _current = 0;
public:
    LRUCache(int capacity) {
        _capacity = capacity;
    }
    
    int get(int key) {
        if (_cache_map.find(key) != _cache_map.end()) {
            //_cache_val.splice(_cache_val.begin(), _cache_val, _cache_map[key]);// smart way
            // normal way:
            pair<int, int> cache_item {_cache_map[key]->first, _cache_map[key]->second};
            _cache_val.erase(_cache_map[key]);
            _cache_val.push_front(cache_item);
            //Dont forget to reassign map! Otherwise get heap-use-after-free
            _cache_map[key] = _cache_val.begin();
            return cache_item.second;
        } else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        if (_cache_map.find(key) != _cache_map.end()) {
            _cache_map[key]->second = value;
            //_cache_val.splice(_cache_val.begin(), _cache_val, _cache_map[key]);// smart way
            // normal way:
            pair<int, int> cache_item {_cache_map[key]->first, _cache_map[key]->second};
            _cache_val.erase(_cache_map[key]);
            _cache_val.push_front(cache_item);
            //Dont forget to reassign map! Otherwise get heap-use-after-free
            _cache_map[key] = _cache_val.begin();
        } else {
            if (_current >= _capacity) {
                _cache_map.erase(_cache_val.back().first);
                _cache_val.pop_back();
            } else {
                _current ++;
            }
            _cache_val.push_front(pair<int, int> {key, value});
            _cache_map[key] = _cache_val.begin();
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

//95% 90
class LRUCache {
private:
    list<pair<int, int>> _cache_val;
    unordered_map<int, list<pair<int, int>>::iterator> _cache_map;
    int _capacity;
    int _current = 0;
public:
    LRUCache(int capacity) {
        _capacity = capacity;
    }
    
    int get(int key) {
        if (_cache_map.find(key) != _cache_map.end()) {
            _cache_val.splice(_cache_val.begin(), _cache_val, _cache_map[key]);// smart way
            return _cache_map[key]->second;
        } else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        if (_cache_map.find(key) != _cache_map.end()) {
            _cache_map[key]->second = value;
            _cache_val.splice(_cache_val.begin(), _cache_val, _cache_map[key]);// smart way
        } else {
            if (_current >= _capacity) {
                _cache_map.erase(_cache_val.back().first);
                _cache_val.pop_back();
            } else {
                _current ++;
            }
            _cache_val.push_front(pair<int, int> {key, value});
            _cache_map[key] = _cache_val.begin();
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// Remember the usage of std::pair/std::list/std::unordered_map
// std::list
//     with std::pair
//     empty: is empty
//     insert: move or copy a new element 
//     emplace: construct a new element in place 
//     splice: move elements between lists (insert + delete)
// std::unordered_map
//     find() (return iterator) and iter->second return the value (works like [], but could be utilized to check existence) (if you want to check existence and use the value at the same time, use iterator would save you an extra search)
// time O(1), space O(n)
//
// Q: Is replace values faster or delete then construct new one?
class LRUCache {
private:
    int _capacity;
    // double linked list, easily move itself to the front, all required manipulations are O(1)
    // use a pair to record key, in order to delete it in _map
    list<pair<int, int>> _list;
    // use a pair iterator to quickly designate the element that need to be moved 
    unordered_map<int, list<pair<int, int>>::iterator> _map;
public:
    LRUCache(int capacity) {
        _capacity = capacity;
    }
    
    int get(int key) {
        auto iter = _map.find(key);
        if (iter == _map.end()) {
            return -1;
        }
        _list.splice( _list.begin(), _list, iter->second);
        return iter->second->second;
    }
    
    void put(int key, int value) {
        auto iter = _map.find(key);
        if (iter != _map.end()) {
            iter->second->second = value;
            _list.splice( _list.begin(), _list, iter->second);
            return;
        }
        if (_map.size() < _capacity) {
            _list.emplace_front(key, value);
        } else {
            auto list_iter = _list.end();
            list_iter --;
            _map.erase(list_iter->first);
            //replace pair values with new ones
            list_iter->first = key;
            list_iter->second = value;
            _list.splice( _list.begin(), _list, list_iter);
        }
        _map[key] = _list.begin();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// Wrong answer, get a node should move the node to the front
// Should use double linked list, which can easily move itself to the front
// also, did not check whether a key was already present when putting.
struct Node {
    int value;
    int key;
    Node* next;
    Node (int key, int value) : key(key), value(value), next(NULL) {} 
};

class LRUCache {
private:
    Node* _head = NULL;
    Node* _tail = NULL;
    unordered_map<int, Node*> _map;
    int _capacity;
    int _current_space = 0;
public:
    LRUCache(int capacity) {
        _capacity = capacity;
        //_map.reserve(_capacity);
    }
    
    int get(int key) {
        if (_map.find(key) == _map.end()) {
            return -1;
        } else {
            return (_map[key])->value;
        }
    }
    
    void put(int key, int value) {
        if (_head == NULL) {
            // empty
            // capacity is positive, at least 1
            _head = new Node(key, value); // need to deleted when deconstructed
            _tail = _head;
            _tail->next = _head; // always form a loop, point to iteself now
            _map[key] = _head;
            _current_space ++;
        } else if (_current_space == _capacity) {
            //move to the oldest node
            _tail = _tail->next;
            
            _map.erase(_tail->key);
            
            _tail->key = key;
            _tail->value = value;
            _map[key] = _tail;
            _tail = _tail->next;
        } else { // _current_space < _capacity
            _tail->next = new Node(key, value);
            _tail = _tail->next;
            _tail->next = _head; // always form a loop
            _map[key] = _tail;
            _current_space ++;
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
