#ifndef ENTRY_HENTRY_H
#define ENTRY_HENTRY_H

#include <assert.h>

template <typename Key, typename Value>
struct Entry {
    Key key;
    Value value;
    Entry(Key k = Key(), Value v = Value()) : key(k), value(v){};
    Entry(Entry<Key, Value> const& e) : key(e.key), value(e.value){};
    bool operator<(Entry<Key, Value> const& e) { return key < e.key; }
    bool operator>(Entry<Key, Value> const& e) { return key > e.key; }
    bool operator==(Entry<Key, Value> const& e) { return key == e.key; }
    bool operator!=(Entry<Key, Value> const& e) { return key != e.key; }
};

#endif  // !ENTRY_HENTRY_H