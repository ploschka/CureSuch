#include <vector>
#include <fstream>
#include "Parser.h"

parsed_strings CSVParser::parse(const std::string& filename) const
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        throw std::runtime_error("File does not exist");
    }
    parsed_strings result;
    while(!file.eof())
    {
        parsed_string ps;
        std::string str;
        std::getline(file, str, '\n');
        if (!file.eof())
        {
            std::string semiresult;
            bool quote = false;
            auto end = str.end();

            for(auto iter = str.begin(); iter < end; iter++)
            {
                if(quote)
                {
                    if(iter == end)
                    {
                        throw std::runtime_error("No ending quote");
                    }
                    if(*iter == '\"')
                    {
                        quote = false;
                        if(*(iter + 1) != ';' && (iter + 1) < end)
                        {
                            throw std::runtime_error("No coma after ending quote");                        
                        }
                        ps.push_back(semiresult);
                        iter += 2;
                        semiresult.clear();
                    }
                    else
                    {
                        semiresult.push_back(*iter);
                    }
                }
                else
                {
                    if(*iter == ';')
                    {
                        ps.push_back(semiresult);
                        iter += 1;
                        semiresult.clear();
                    }
                    else if(*iter == '\"')
                    {
                        quote = true;
                    }
                    else
                    {
                        semiresult.push_back(*iter);
                    }
                }
            }
            if(!semiresult.empty())
                ps.push_back(semiresult);
            result.push_back(ps);
        }
    }
    return result;
}
