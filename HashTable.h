#pragma once
#include <iostream>
#include <cstring>

template<typename T>
class HashTable
{
private:
    T* table;
    bool* status;
    size_t tableSize;
    size_t filled;
    size_t rounded;
    size_t (*valueToNumber)(const T&);

    size_t getHash(const T& key) const
    {
        size_t tryn = 0;
        size_t primary = primaryHash(key);
        size_t hash = secondaryHash(primary, tryn);
        auto was = new bool[tableSize];
        memset(was, 0, tableSize);
        size_t count = 0;
        while(status[hash] && (table[hash] != key) && count < filled)
        {
            tryn++;
            hash = secondaryHash(primary, tryn);
            if(!was[hash])
            {
                was[hash] = true;
                count++;
            }
        }
        if (count == filled && table[hash] != key)
        {
            throw std::runtime_error("No such key in table");
        }
        return hash;
    }
    size_t secondaryHash(double hash, const uint16_t tryn) const
    {
        double i = tryn;
        size_t preresult;
        size_t result;

        do
        {
            preresult = static_cast<size_t>(hash + (0.5 * (i + (i * i))));
            result = preresult % rounded;
            i++;
        } while (result >= tableSize);
        return result;
    }
    size_t primaryHash(const T& key) const
    {
        size_t result = valueToNumber(key);
        return result % rounded;
    }

    void rebase(size_t currentHash)
    {
        auto* was = new bool[tableSize];
        memset(was, 0, tableSize);
        was[currentHash] = true;
        size_t next;
        size_t newHash;
        size_t rehashed = 0;
        for (size_t i = 1; rehashed < filled; i++)
        {
            next = secondaryHash(currentHash, i);
            if(!was[next] && status[next])
            {
                status[next] = false;
                newHash = getHash(table[next]);
                table[newHash] = table[next];
                status[newHash] = true;
                was[newHash] = true;
                was[next] = true;
                rehashed++;
            }
        }
    }

public:
    HashTable(size_t size, size_t (*valueToNumber)(const T&)): tableSize(size), filled(0), valueToNumber(valueToNumber)
    {
        rounded = [](size_t v)
        {
            v--;
            v |= v >> 1;
            v |= v >> 2;
            v |= v >> 4;
            v |= v >> 8;
            v |= v >> 16;
            v |= v >> 32;
            v++;
            return v;
        }(size);
        table = new T[size];
        status = new bool[size];
        memset(status, 0, size);
    }
    ~HashTable()
    {
        delete[] table;
        delete[] status;
    }

    void write(const T& key)
    {
        if (filled < tableSize)
        {
            filled++;
            size_t hash = getHash(key);
            if(table[hash] != key)
            {
                table[hash] = key;
                status[hash] = true;
            }
        }
        else
        {
            throw(std::length_error("Hash table already full, nowhere to add"));
        }
    }
    size_t find(const T& key) const
    {
        size_t hash = getHash(key);

        if(!status[hash])
            throw std::runtime_error("No such key in table");

        if(table[hash] == key)
        {
            return hash;
        }
        return (0-1);
    }
    void remove(const T& key)
    {
        size_t hash = getHash(key);
        if(!status[hash])
            throw std::runtime_error("No such key in table");

        if(filled)
        {
            if(table[hash] == key)
            {
                status[hash] = false;
                filled--;
                rebase(hash);
            }
        }
        else
        {
            throw(std::runtime_error("Hash table is empty, nothing to delete"));
        }
    }
};
