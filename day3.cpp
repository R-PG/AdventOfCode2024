#include <iostream>
#include <string>
#include <sstream>
#include <regex>

std::string line;
int result;

std::string doStr = "do()";
std::string dontStr = "don't()";

bool doEnabled = true;

const bool partOne = false;

int main()
{
    while(std::getline(std::cin, line))
    {
        std::regex pattern(R"(mul\(\d{1,3},\d{1,3}\))");
        
        auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
        auto end = std::sregex_iterator();
        
        size_t startIndex(0);

        for (std::sregex_iterator i = begin; i != end; ++i) 
        {    
            std::smatch match = *i;
            std::string stringMatch = match.str();
            
            std::stringstream sstring(stringMatch.substr(4, stringMatch.size()));

            int mulA, mulB;
            sstring >> mulA;
            sstring.ignore();
            sstring >> mulB;

            if constexpr(partOne)
            {
                result += mulA * mulB;
            }

            if constexpr(!partOne)
            {
                auto matchPos = line.find(stringMatch);

                size_t doIndex(std::string::npos), dontIndex(std::string::npos);
                
                size_t searchIndex = line.find(doStr, startIndex);
                while (searchIndex < matchPos && searchIndex != std::string::npos)
                {
                    doIndex = searchIndex;
                    searchIndex = line.find(doStr, searchIndex + doStr.size());
                }

                searchIndex = line.find(dontStr, startIndex);
                while (searchIndex < matchPos && searchIndex != std::string::npos)
                {
                    dontIndex = searchIndex;
                    searchIndex = line.find(dontStr, searchIndex + dontStr.size());
                }
                
                if (doIndex != std::string::npos && dontIndex != std::string::npos)
                    doEnabled = doIndex > dontIndex;
                else if (dontIndex == std::string::npos && doIndex != std::string::npos)
                    doEnabled = true;
                else if (doIndex == std::string::npos && dontIndex != std::string::npos)
                    doEnabled = false;

                if (doEnabled)
                    result += mulA * mulB;

                startIndex = matchPos;
            }
        }
    }
    std::cout << result << std::endl;
}