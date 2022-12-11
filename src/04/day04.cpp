//
// Created by philipp on 12/10/22.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct SectionRange
{
    unsigned int start;
    unsigned int end;

    void readRange(istream&& is)
    {
        string tmp{};
        getline(is, tmp, '-');
        istringstream(tmp) >> start;
        getline(is, tmp, '-');
        istringstream(tmp) >> end;
        return;
    }
};

bool is_subrange(SectionRange const& a, SectionRange const& b)
{
    return (a.start >= b.start && a.end <= b.end);
}

bool is_full_overlap(SectionRange const& a, SectionRange const& b)
{
    return (is_subrange(a, b)
            || is_subrange(b, a));
}

bool is_partly_overlap(SectionRange const& a, SectionRange const& b)
{
    return (max(a.start, b.start) <= min(a.end, b.end));
}

typedef pair<SectionRange, SectionRange> section_pair_t;
section_pair_t read_pair(istream&& is)
{
    SectionRange sr;
    string section_raw;

    getline(is, section_raw, ',');
    section_pair_t section_range{};
    section_range.first.readRange(istringstream{section_raw});
    getline(is, section_raw, ',');
    section_range.second.readRange(istringstream{section_raw});
    return section_range;
}

vector<section_pair_t> read_pairs(istream& is)
{
    string line{};
    vector<section_pair_t> ps{};
    while (getline(is, line))
    {
        ps.push_back(read_pair(istringstream{line}));
        //cout << p.back().first.end << "\n";
    }
    return ps;
}


int main()
{
    ifstream input("assignment_pairs.dat");
    if (!input) return EXIT_FAILURE;
    vector<section_pair_t> ps{read_pairs(input)};

    unsigned int num_total_overlaps =
            count_if(ps.begin(), ps.end(),
                     [](section_pair_t p)
                     { return is_full_overlap(p.first, p.second); }
    );

    cout << num_total_overlaps << " total overlaps detected.\n";

    unsigned int num_partly_overlaps =
            count_if(ps.begin(), ps.end(),
                     [](section_pair_t p)
                     { return is_partly_overlap(p.first, p.second); }
            );
    cout << num_partly_overlaps << " partly overlaps detected.\n";

    return EXIT_SUCCESS;
}