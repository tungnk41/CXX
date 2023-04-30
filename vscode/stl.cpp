#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <deque>

using namespace std;

void _array() {
    /*Array*/
    array<int,3> arr;
    array<array<int,3>,3> arr2 { {{1,2,3},{1,2,3},{1,2,3}} };
    //arr[0] 
}
void _vector() {
    /*Vector*/
    vector<int> v;
    vector<int> v2(10); // 10 elements : all 0
    vector<int> v3(10,1); // 10 elements : all 1
    vector<vector<int>> v4;
    // v.emplace_back(2), v.push_back(1); v.clear(), v.size(), v[0],
    // v.sort(v.begin(), v.end())
}
void _pair() {
    /*Pair*/
    pair<int,int> p;
    pair<int,int> p2 {1,2};
    // p.first, p.second
}
void _iterator() {
    /*Iterator*/
    vector<int>::iterator it = v.begin();
    auto it2 = v.begin();
    // *it
}
void _set() {
    /*Set : TreeSet*/
    set<int> s1;
    //set.insert(x), set.erase(x), set.count(x)  => logN, s.clear(), s.size()
    //s.find() : Iterator, s.lower_bound(x): iterator first element which >= x, s.upper_bound(x): iterator first element which > x

    /*MultiSet : Set that contains duplicate/multiple same value, always sorted*/
    multiset<int> mset;
}
void _map() {
    /*Map*/
    map<int,int> m;
    //m[key] = value: m[0] = 10, m.clear(), auto it = m.find(value), m.count(key), m.find(key), m.erase(key)
    /*MultiMap : Map that contains duplicate/multiple same value, always sorted by key*/
    multimap<int,int> mmap;
}
void _queue() {
    /*queue*/
    queue<int> q;
    // q.push(x), q.size(), q.empty(), q.front(), q.back(), q.pop()
}
void _stack() {
    /*stack*/
    stack<int> s;
    // s.push(x), q.size(), q.empty(), q.top(), q.pop()
}
void _dequeue() {
    /*deque*/
    deque<int> dq;
    // dq.push_back(x), dq.push_front(x), pop_back(), pop_front(), front(), back(),size()
}
void _priorityQueue() {
    /*priority queue: default max heap*/
    /*max heap*/
    priority_queue<int> pq;
    //push(x), top(x), pop(x)

    /*Min heap*/
    //auto comp = []( A a, A b ) { return a.second > b.second; };
    //priority_queue<A,vector<A>, decltype(comp)> pq(comp);
    priority_queue <int, vector<int>, greater<int> > pq2;
}


int main() {
    _array();
    _vector();
    _pair();
    _iterator();
    _set();
    _map();
    _queue();
    _stack();
    _dequeue();
    _priorityQueue();

    return 0;
}