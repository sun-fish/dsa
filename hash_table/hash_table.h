#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cmath>
#include <list>
#include <vector>

#include "public/dictionary.h"
#include "public/entry.h"

template <typename Key, typename Value>
class HashtableChain : public Dictionary<Key, Value> {
   protected:
    size_t hashFunction(const Key& k) { return k % prime_vector_[prime_index_]; }
    void rehash() { 
        std::vector<std::list<Entry<Key, Value>*>> buckets_copy;
        buckets_copy.swap(buckets_);
        capacity_number_ = prime_vector_[prime_index_];
        buckets_.resize(capacity_number_);
        entry_number_ = 0;
        for (auto& list : buckets_copy) {
            for (auto& node : list) {
                put(node->key, node->value);
                delete node;
            }
        }
        return;
    }

   public:
    // 11 is the 5th prime, 997 is the 168th prime
    HashtableChain() : prime_index_(4), entry_number_(0), load_threshold_(0.6) {
        // create prime table
        bool prime[1001];
        for (size_t i = 0; i < 1001; ++i) {
            prime[i] = true;
        }
        // zero and one are not prime
        prime[0] = false;
        prime[1] = false;
        for (size_t i = 2; i < std::sqrt(1001) + 1; ++i) {
            for (int j = 2 * i; j < 1001; j += i) {
                prime[j] = false;
            }
        }
        for (size_t i = 0; i < 1001; ++i) {
            if (prime[i] == true) prime_vector_.push_back(i);
        }

        capacity_number_ = prime_vector_[prime_index_];

        // create buckets
        buckets_.reserve(capacity_number_);
        for (size_t i = 0; i < capacity_number_; ++i) {
            buckets_.push_back(std::list<Entry<Key, Value>*>());
        }
    }

    ~HashtableChain() {
        for (auto& list : buckets_) {
            for (auto& node : list) {
                delete node;
            }
        }
    }

    size_t size() override { return entry_number_; }

    bool put(Key k, Value v) override {
        size_t index = hashFunction(k);
        auto &list = buckets_[index];
        for (auto& node : list) {
            if (node->key == k)
                return false;
            else
                continue;
        }
        list.push_back(new Entry<Key, Value>(k, v));
        ++entry_number_;
        if (static_cast<double>(entry_number_) / static_cast<double>(capacity_number_) > load_threshold_ &&
            prime_index_ < 168) {
            ++prime_index_;
            rehash();
        }
        return true;
    }

    Value* get(Key k) override {
        size_t index = hashFunction(k);
        auto list = buckets_[index];
        for (auto& node : list) {
            if (node->key == k)
                return &(node->value);
            else
                continue;
        }
        return nullptr;
    }

    bool remove(Key k) override {
        size_t index = hashFunction(k);
        auto list = buckets_[index];
        auto it = list.begin();
        while (it != list.end()) {
            if ((*it)->key == k) {
                break;
            }
        }
        if (it == list.end()) {
            return false;
        } else {
            delete *it;
            list.erase(it);
            --entry_number_;
            return true;
        }
    }

    void traverse() {
        for (auto& list : buckets_) {
            for (auto& node : list) {
                size_t hash = hashFunction(node->key);
                std::cout << "hash: " << hash << "  key: " << node->key << "  value: " << node->value;
            }
            std::cout << std::endl;
        }
        std::cout << "Hash Table Traverse Finished!" << std::endl;
    }

   private:
    std::vector<std::list<Entry<Key, Value>*>> buckets_;
    double load_threshold_;
    size_t capacity_number_;
    size_t entry_number_;
    size_t prime_index_;
    std::vector<size_t> prime_vector_;
};

// implementation

template <typename Key, typename Value>
class HashtableOpenAddress : public Dictionary<Key, Value> {};

#endif