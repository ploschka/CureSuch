#pragma once
#include <iostream>
#include <cstring>
#include <utility>

using std::is_pointer_v;

template<typename T1, typename T2>
class HashTable
{
typedef std::pair<T1, T2> elem;
private:
    elem* table;
    bool* status;
    size_t tableSize;
    size_t filled;
    size_t rounded;
    size_t (*keyToNumber)(const T1&);

    size_t getHash(const T1& key) const
    {
        size_t tryn = 0;
        size_t primary = primaryHash(key);
        size_t hash = secondaryHash(primary, tryn);
        auto was = new bool[tableSize];
        memset(was, 0, tableSize);
        size_t count = 0;
        while(status[hash] && !(table[hash].first == key) && count < filled)
        {
            tryn++;
            hash = secondaryHash(primary, tryn);
            if(!was[hash])
            {
                was[hash] = true;
                count++;
            }
        }
        if (count == filled && !(table[hash].first == key))
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
    size_t primaryHash(const T1& key) const
    {
        size_t result = keyToNumber(key);
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
                newHash = getHash(table[next].first);
                table[newHash] = table[next];
                status[newHash] = true;
                was[newHash] = true;
                was[next] = true;
                rehashed++;
            }
        }
    }

public:
    HashTable(size_t size, size_t (*keyToNumber)(const T1&)): tableSize(size), filled(0), keyToNumber(keyToNumber)
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
        table = new elem[size];
        status = new bool[size];
        memset(status, 0, size);
    }
    ~HashTable()
    {
        delete[] table;
        delete[] status;
    }

    void write(const T1& key, const T2& value)
    {
        if (filled < tableSize)
        {
            filled++;
            size_t hash = getHash(key);
            if(!(table[hash].first == key) || !status[hash])
            {
                table[hash] = std::make_pair(key, value);
                status[hash] = true;
            }
            else
            {
                throw std::runtime_error("Value with this key is already in table");
            }
        }
        else
        {
            throw(std::length_error("Hash table already full, nowhere to add"));
        }
    }
    elem& find(const T1& key) const
    {
        size_t hash = getHash(key);

        if(!status[hash])
            throw std::runtime_error("No such key in table");

        if(table[hash].first == key)
        {
            return table[hash];
        }
        throw std::runtime_error("No such key in table");
    }
    void remove(const T1& key)
    {
        size_t hash = getHash(key);
        if(!status[hash])
            throw std::runtime_error("No such key in table");

        if(filled)
        {
            if(table[hash].first == key)
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
    template<typename T, typename TT>
    friend std::ostream& operator<<(std::ostream& os, const HashTable<T, TT>&);
};

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const HashTable<T1, T2>& tb)
{
    for(size_t i = 0; i < tb.tableSize; i++)
    {
        os << i << ' ';
        if(tb.status[i])
        {
#ifdef TYPE1POINTER
            os << *(tb.table[i].first);
#else
            os << tb.table[i].first;
#endif
            os << ": ";
#ifdef TYPE2POINTER
            os << *(tb.table[i].second);
#else
            os << tb.table[i].second;
#endif
        }
        os << '\n';
    }
    return os;
}
