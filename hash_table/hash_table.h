#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>

#include "public/dictionary.h"
#include "public/entry.h"

template <typename Key, typename Value>
class Hashtable : public Dictionary<Key, Value> {
   protected:
    // find matched entry
    size_t probeForHit(const Key& k);
    // find first unused memory
    size_t probeForFree(const Key& k);

    void rehash();

   public:
    Hashtable(size_t capacity = 5);
    ~Hashtable();

    size_t size() override { return entry_number_; }
    bool put(Key k, Vaule v) override;
    V* get(Key k) override;
    bool remove(Key k) override;

   private:
    Entry<Key, Value>** ht;
    Bitmap* removed;
    size_t capacity_number;
    size_t entry_number_;
};

//implementation

#endif