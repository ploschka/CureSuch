#ifndef GOD_H
#define GOD_H
#include <utility>
#include <string>

template<typename T>
size_t num_to_num(const std::pair<std::string, T*>& p)
{
    size_t result = 0;
    std::string combined = p.first;
    size_t j = 1;
    for(auto i: combined)
    {
        result += i * j;
        j++;
    }
    return result;
}

template<typename T1, typename T2>
bool operator<(const std::pair<T1, const T2>& first, const std::pair<T1, const T2>& second)
{
    return first.first < second.first;
}

template<typename T1, typename T2>
bool operator==(std::pair<T1, const T2>& first, std::pair<T1, const T2>& second)
{
    return (first.first == second.first);
}

#endif // GOD_H
