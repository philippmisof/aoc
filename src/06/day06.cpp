//
// Created by philipp on 12/11/22.
//

#include <fstream>
#include <deque>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;


string get_marker(istream& is, size_t const n)
{
    deque<char> sequence{};
    char c;
    while (is.get(c))
    {
        auto pos = ranges::find(sequence, c);
        if (pos != sequence.end())
        {
            sequence.erase(sequence.begin(), next(pos));
        }
        sequence.push_back(c);
        if (sequence.size() == n) break;
    }
    string marker{sequence.begin(), sequence.end()};
    return marker;
}

int main()
{
    ifstream input("signal_tuning_marker.dat");
    if (!input) throw runtime_error("Could not open file");

    string marker = get_marker(input, 4);
    cout << "Found marker " << marker << " after " << input.tellg() << " characters.\n";

    input = ifstream("signal_tuning_marker.dat");
    string message = get_marker(input, 14);
    cout << "Found message " << message << " after " << input.tellg() << " characters.\n";
    return EXIT_SUCCESS;
}
