#pragma once
#include <map>
#include <mutex>
#include <iostream>
using namespace std;
template<typename Key, typename Value>
class ThreadSafeMap {

	map<Key, Value> map_ts;
	mutex update_mutex;
public:
	ThreadSafeMap() {

	}
	void add_to_map(Key x, Value y) {
		lock_guard<mutex> lg(update_mutex);
		auto pos = map_ts.find(x);
		if (pos == map_ts.end())
			map_ts.insert(pair<Key, Value>(x, y));
		else
			map_ts[x] = y;
		cout << "Added : { " << x << " , " << y << " }" << endl;
	}

	void delete_from_map(Key x) {
		lock_guard<mutex> lg(update_mutex);
		map_ts.erase(x);
		cout << "Removed : " << x << endl;
	}
	void show_map() {
		lock_guard<mutex> lg(update_mutex);
		for (auto x : map_ts) {
			cout << "Key : " << x.first << " Value : " << x.second << endl;
		}
	}

	Value at(Key k) {
		lock_guard<mutex> lg(update_mutex);
		return map_ts.at(k);
	}

	bool find(Key k) {
		lock_guard<mutex> lg(update_mutex);
		return (map_ts.find(k) != map_ts.end());
	}

	//friend ostream& operator << (ostream&, ThreadSafeMap<Key, Value>&);
	template <typename Key, typename Value>
	friend ostream& operator <<(ostream& os,const ThreadSafeMap<Key,Value> & t)
	{
		for (auto x : t.map_ts) {
			cout << "Key : " << x.first << " Value : " << x.second << endl;
		}
		return os;
	}
};
