#ifndef DICTIONARY_H
#define DICTIONARY_H

template <typename Key, typename Value>
class Dictionary {
    virtual size_t size() = 0;
    virtual bool put(Key k, Value v) = 0;
    virtual Value* get(Key k) = 0;
    virtual bool remove(Key k) = 0;
};

#endif