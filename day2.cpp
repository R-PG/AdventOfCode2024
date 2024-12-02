#include <iostream>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>

std::string line;
int result;

int main()
{
    while (std::getline(std::cin, line))
    {
        std::vector<int> levels;
        int level;
        std::istringstream iss(line);

        while (iss >> level) levels.emplace_back(level);

        int factor;
        auto validDiff = [&factor](int elem){return elem * factor > 0 && elem * factor < 4;};
        
        if constexpr(0)
        {  
            std::adjacent_difference(levels.begin(), levels.end(), levels.begin());
            
            factor = (levels[1] > 0) ? 1 : -1;
  
            result += std::all_of(levels.cbegin() + 1, levels.cend(), validDiff);
        }
        
        if constexpr(1)
        {    

            auto it = std::find_if_not(levels.begin() + 1, levels.end(), validDiff);

            if (it != levels.end())
            {
                for (int i = 0; i < levels.size(); ++i)
                {
                    std::vector<int> newLevels;
                    std::copy(levels.begin(), levels.begin() + i, std::back_inserter(newLevels));
                    std::copy(levels.begin() + i + 1, levels.end(), std::back_inserter(newLevels));

                    std::adjacent_difference(newLevels.begin(), newLevels.end(), newLevels.begin());
            
                    factor = (newLevels[1] > 0) ? 1 : -1;

                    if (std::all_of(newLevels.cbegin() + 1, newLevels.cend(), validDiff)) 
                    {
                        result++;
                        break;
                    }
                }
            }
            else
            {
                result++;
            }
        }
    }
    std::cout << result << std::endl;
}
