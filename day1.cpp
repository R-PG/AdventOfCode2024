#include <iostream>
#include <vector>
#include <algorithm>

int n1, n2, result(0);
std::vector<int> list1, list2;

int main()
{
    while (std::cin >> n1)
    {
        list1.emplace_back(n1);
        std::cin >> n2;
        list2.emplace_back(n2);
    }
    
    if constexpr(0)
    {
        std::sort(list1.begin(), list1.end());
        std::sort(list2.begin(), list2.end());
        for (auto i(0); i < list1.size(); ++i)
        {
            result += std::abs(list1[i] - list2[i]);
        }
    }

    if constexpr(1)
    {
        std::for_each(list1.begin(),list2.begin(), [](const int& elem){
            result += elem * std::count(list2.begin(),list2.end(),elem);
        });
    }
    std::cout << result;
}