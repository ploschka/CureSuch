#pragma once

#include <vector>
#include <string>

typedef std::vector<std::string> parsed_string;
typedef std::vector<parsed_string> parsed_strings;

class IParser
{
public:
    virtual parsed_strings parse(const std::string& filename) const = 0;
    virtual ~IParser() = default;
};

class CSVParser: public IParser
{
public:
    parsed_strings parse(const std::string& filename) const;
};
