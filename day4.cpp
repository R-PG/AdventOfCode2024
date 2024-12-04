#include <iostream>
#include <string>
#include <vector>

#define ID(i,j,n) (i * n + j)

enum direction{N, S, E, W, NE, SE, NW, SW};

std::vector<char> letters;
int result(0);
int m(0), n(0);

const bool partOne = false;

// Part I
std::pair<int,int> nextCoords( std::pair<int,int> coords, int dir)
{
    switch (dir)
    {
        case N:
            return {coords.first + 1, coords.second};
        case S:
            return {coords.first - 1, coords.second};
        case E:
            return {coords.first, coords.second + 1};
        case W:
            return {coords.first, coords.second - 1};
        case NE:
            return {coords.first + 1, coords.second + 1};
        case SE:
            return {coords.first - 1, coords.second + 1};
        case NW:
            return {coords.first + 1, coords.second - 1};
        case SW:
            return {coords.first - 1, coords.second - 1};
    }
}

// Part II
int nextDir(int dir)
{
    switch (dir)
    {
        case NE:
            return SW;
        case SE:
            return NW;
        case NW:
            return SE;
        case SW:
            return NE;
    }
}

inline bool coordsSafe(std::pair<int,int> coords)
{
    return coords.first >= 0 && coords.first < m && coords.second >= 0 && coords.second < n;
}

bool search(char nextLetterExpected, std::pair<int,int> coords, int dir)
{
    if constexpr (partOne)
    {
        coords = nextCoords(coords, dir);
        if (coordsSafe(coords) && letters[ID(coords.first,coords.second,n)] == nextLetterExpected)
        {
                switch(nextLetterExpected)
                {
                    case 'M':
                        return true && search('A', coords, dir);
                    case 'A':
                        return true && search('S', coords, dir);
                    case 'S':
                        return true;
                }
        }
        return false;
    }

    if constexpr (!partOne)
    {
        coords = nextCoords(coords, dir);
        if (coordsSafe(coords) && letters[ID(coords.first,coords.second,n)] == nextLetterExpected)
        {
            dir = nextDir(dir);
            coords = nextCoords(coords, dir);
            coords = nextCoords(coords, dir);

            switch(nextLetterExpected)
            {
                case 'M':
                    return coordsSafe(coords) && letters[ID(coords.first,coords.second,n)] == 'S';
                case 'S':
                    return coordsSafe(coords) && letters[ID(coords.first,coords.second,n)] == 'M';
            }
        }
        return false;
    }
}

int main()
{
    int c = std::getchar();
    if (c != EOF) m++;

    while (c != EOF)
    {
        if (c == '\n') m++;
        else letters.emplace_back(c);
        c = std::getchar();
    }

    n = letters.size()/m;

    if constexpr (partOne)
    {
        for (int i(0); i < m; ++i)
            for (int j(0); j < n; ++j)
                if (letters[ID(i,j,n)] == 'X')
                    for (int dir = N; dir <= SW; ++dir)
                        result += search('M', {i,j}, dir);
    }

    if constexpr (!partOne)
    {
        for (int i(0); i < m; ++i)
            for (int j(0); j < n; ++j)
                if (letters[ID(i,j,n)] == 'A')
    result += ((search('M', {i,j}, NW) || search('S', {i,j}, NW))) && (search('M', {i,j}, NE) || search('S', {i,j}, NE));
    }

    std::cout << result << std::endl;
}