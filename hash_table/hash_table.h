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
        bool isPrime[1001];
        for (size_t i = 0; i < 1001; ++i) {
            isPrime[i] = true;
        }
        // zero and one are not prime
        isPrime[0] = false;
        isPrime[1] = false;
        for (size_t i = 2; i < std::sqrt(1001) + 1; ++i) {
            if (isPrime[i] == true) {
                for (int j = 2 * i; j < 1001; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        for (size_t i = 0; i < 1001; ++i) {
            if (isPrime[i] == true) prime_vector_.push_back(i);
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
        auto& list = buckets_[index];
        for (auto& node : list) {
            if (node->key == k)
                return false;
            else
                continue;
        }
        list.push_back(new Entry<Key, Value>(k, v));
        ++entry_number_;
        if (load_threshold_ < loadFactor() && prime_index_ < 168) {
            ++prime_index_;
            rehash();
        }
        return true;
    }

    Value* get(Key k) override {
        size_t index = hashFunction(k);
        auto& list = buckets_[index];
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
        auto& list = buckets_[index];
        auto it = list.begin();
        while (it != list.end()) {
            if ((*it)->key == k) {
                break;
            }
            ++it;
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

    double loadFactor() { return static_cast<double>(entry_number_) / static_cast<double>(capacity_number_); }

    void traverse() {
        for (auto& list : buckets_) {
            for (auto& node : list) {
                size_t hash = hashFunction(node->key);
                std::cout << "hash: " << hash << "  key: " << node->key << "  value: " << node->value << "  ";
            }
            if (!list.empty()) std::cout << std::endl;
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

template <typename Key, typename Value>
class HashtableOpenAddress : public Dictionary<Key, Value> {
   protected:
    size_t hashFunction(const Key& k) { return k % prime_vector_[prime_index_]; }

    void rehash() {
        entry_number_ = 0;
        capacity_number_ = prime_vector_[prime_index_];
        std::vector<Entry<Key, Value>*> buckets_copy(capacity_number_, nullptr);
        std::vector<bool> is_entry_deleted_copy(capacity_number_, false);
        buckets_copy.swap(buckets_);
        is_entry_deleted_copy.swap(is_entry_deleted_);
        for (auto& entry : buckets_copy) {
            if (entry != nullptr) {
                put(entry->key, entry->value);
                delete entry;
            }
        }
    }

    // linear probing (hash(key) + i) mod (bucket size)
    // find the first usable memory
    size_t linearProbingForFree(const Key& k) {
        size_t result = hashFunction(k);
        size_t i = 1;
        // load factor must less than 0.6, so this loop is not dead loop
        while (buckets_[result] != nullptr) {
            result = (result + i) % capacity_number_;
            ++i;
        }
        return result;
    }

    // search until meet the matched key
    size_t linearProbingForHit(const Key& k) {
        size_t result = hashFunction(k);
        size_t i = 1;
        while (buckets_[result] != nullptr || is_entry_deleted_[result] == true) {
            if (buckets_[result] != nullptr && k == buckets_[result]->key) {
                break;
            }

            result = (result + i) % capacity_number_;
            ++i;
        }
        return result;
    }

   public:
    // 11 is the 5th prime, 997 is the 168th prime
    HashtableOpenAddress() : prime_index_(4), entry_number_(0), load_threshold_(0.6) {
        // create prime table
        bool isPrime[1001];
        for (size_t i = 0; i < 1001; ++i) {
            isPrime[i] = true;
        }
        // zero and one are not prime
        isPrime[0] = false;
        isPrime[1] = false;
        for (size_t i = 2; i < std::sqrt(1001) + 1; ++i) {
            if (isPrime[i] == true) {
                for (int j = 2 * i; j < 1001; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        for (size_t i = 0; i < 1001; ++i) {
            if (isPrime[i] == true) prime_vector_.push_back(i);
        }

        capacity_number_ = prime_vector_[prime_index_];
        rehash();  // init buckets
    }

    ~HashtableOpenAddress() {
        for (size_t i = 0; i < capacity_number_; ++i) {
            if (buckets_[i] != nullptr && is_entry_deleted_[i] == false) {
                delete buckets_[i];
            }
        }
    }

    size_t size() override { return entry_number_; }

    bool put(Key k, Value v) override {
        size_t probing_result = linearProbingForHit(k);
        if (buckets_[probing_result] != nullptr) {
            return false;
        } else {
            probing_result = linearProbingForFree(k);
            buckets_[probing_result] = new Entry<Key, Value>(k, v);
            is_entry_deleted_[probing_result] = false;
            ++entry_number_;
            if (load_threshold_ < loadFactor() && prime_index_ < 168) {
                ++prime_index_;
                rehash();
            }
            return true;
        }
    }

    Value* get(Key k) override {
        size_t probing_result = linearProbingForHit(k);
        if (buckets_[probing_result] == nullptr)
            return nullptr;
        else
            return &(buckets_[probing_result]->value);
    }

    bool remove(Key k) override {
        size_t probing_result = linearProbingForHit(k);
        if (buckets_[probing_result] == nullptr) {
            return false;
        } else {
            delete buckets_[probing_result];
            buckets_[probing_result] = nullptr;
            is_entry_deleted_[probing_result] = true;
            --entry_number_;
            return true;
        }
    }

    double loadFactor() { return static_cast<double>(entry_number_) / static_cast<double>(capacity_number_); }

    void traverse() {
        for (auto& entry : buckets_) {
            if (entry != nullptr) {
                size_t hash = linearProbingForHit(entry->key);
                std::cout << "hash:" << hash << "  key:" << entry->key << "  value:" << entry->value << std::endl;
            }
        }
        std::cout << "Hash Table Traverse Finished!" << std::endl;
    }

   private:
    std::vector<Entry<Key, Value>*> buckets_;
    std::vector<bool> is_entry_deleted_;
    double load_threshold_;
    size_t capacity_number_;
    size_t entry_number_;
    size_t prime_index_;
    std::vector<size_t> prime_vector_;
};

#endif