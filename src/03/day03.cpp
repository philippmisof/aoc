//
// Created by philipp on 12/10/22.
//

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <memory>

using namespace std;

enum Task { PART1, PART2 };

char find_wrong_packed_item(string const& line)
{
    size_t length = line.length();
    if ( (length % 2) == 1 ) cout << "Warning, odd number of items!\n";
    auto item = find_first_of(line.begin()+length/2, line.end(),
                  line.begin(), line.begin()+length/2);

    return *item;
}

unsigned int get_priority(char const c)
{
    int p = int(c) - int('a') + 1;
    if (p >= 1 && p <= 26) return p;
    else
    {
        p = int(c) - int('A') + 27;
        if (p >= 27 && p <= 52) return p;
        else cout << "Warning, character " << c << "doesn\'t match letter\n";
    }
}

char find_badge(array<string, 3>& lines)
{
    constexpr size_t max_size = max(int('Z'), int('z')) + 1;
    array<int,max_size> table;
    uninitialized_fill(table.begin(), table.end(), 0);
    char badge = '0';
    for (int i = 0; i < 3; ++i)
    {
        for (auto c : lines[i])
        {
            if (int(c) >= max_size) continue;
            int current_val = table.at(int(c));
            if (current_val == i)
            {
                ++table.at(int(c));
                if (i == 2)
                {
                    badge = c;
                    //cout << "Badge: " << c << "\n";
                    break;
                }
            }
        }
    }
    return badge;
}

unsigned int check_backpacks(ifstream& is, Task part)
{
    string line{};
    unsigned int sum_priorities = 0;
    if (part == PART1)
    {
        while(getline(is, line))
        {
            char item = find_wrong_packed_item(line);
            sum_priorities += get_priority(item);
        }
    }
    else
    {
        array<string, 3> lines{};
        int counter{0};
        char badge{};
        while(getline(is, line))
        {
            lines[counter % 3] = line;
            counter++;
            if ( (counter % 3) == 0 )
            {
                badge = find_badge(lines);
                sum_priorities += get_priority(badge);
            }
        }
    }
    return sum_priorities;
}

int main()
{
    ifstream input("backpack_items.dat");

    unsigned int sum_priorities = check_backpacks(input, PART1);
    cout << "The sum of all priorities is " << sum_priorities << ".\n\n";

    input = ifstream("backpack_items.dat");
    sum_priorities = check_backpacks(input, PART2);
    cout << "The sum of all badge priorities is " << sum_priorities << ".\n";


    return EXIT_SUCCESS;
}
