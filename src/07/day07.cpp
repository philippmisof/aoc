//
// Created by philipp on 12/11/22.
//

#include <fstream>
#include <memory>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <numeric>

using namespace std;

enum command {ls, cd};
enum node_type {file, dir};

struct Node
{
    Node* const parent{};

    typedef vector<unique_ptr<Node>> nodes_t;
    nodes_t children{};

    size_t size = -1;
    string name;
    node_type type = dir;

    Node(string const& name_node, Node* const par_node = nullptr)
        : parent{par_node}, name{name_node}
    {};

    void add_child(string const& child_name, size_t const child_size = -1, node_type const t = dir)
    {
        unique_ptr<Node> child = make_unique<Node>(child_name, this);
        child->size = child_size;
        child->type = t;
        children.push_back(move(child));
    }

    Node* change_directory(string const& node_name)
    {
        if (node_name == "..")
        {
            if (parent != nullptr) return parent;
            else throw runtime_error("No parent directory!");
        }
        else
        {
            auto child = find_if(children.begin(), children.end(),
                    [&](unique_ptr<Node>& ch)
                    { return ch->name == node_name;});
            if (child != children.end()) return (*child).get();
            else throw runtime_error("No directory with this name found.");
        }
    }
};

command read_command(istream& is)
{
    string word{};
    if (is.get() != '$') throw runtime_error("Expected a command.");
    if (is >> word)
    {
        if (word == "ls") return ls;
        else if (word == "cd") return cd;
        else throw runtime_error("Unknown command.");
    }
    else throw runtime_error("No command found.");
}

string read_cd_command(istream& is)
{
    string dir_name{};
    is >> dir_name >> ws;
    return dir_name;
}

typedef vector<pair<int, string>> file_dir_t;
file_dir_t read_ls_command(istream& is)
{
    file_dir_t list_files_dir{};
    string word;
    int size = 0;
    while (is.peek() != '$' && !is.eof())
    {
        is >> word;
        if (word == "dir") size = -1;
        else size = stoi(word);
        is >> word;
        list_files_dir.push_back({size, word});
        is >> ws;
    }
    return list_files_dir;
}

Node read_filesystem(istream& is)
{
    string line{};

    if (read_command(is) != cd)
        throw runtime_error("We can't start if we don't know where we are.");

    string dir_name(read_cd_command(is));
    Node root{dir_name};
    Node* current_node = &root;

    while (is)
    {
        command current_command = read_command(is);
        if (current_command == cd)
        {
            dir_name = read_cd_command(is);
            current_node = current_node->change_directory(dir_name);
        }
        else
        {
            file_dir_t file_dirs = read_ls_command(is);
            for (auto f: file_dirs)
            {
                if (f.first >= 0)
                    current_node->add_child(f.second, f.first, file);
                else
                    current_node->add_child(f.second);
            }
        }
    }
    return root;
}

void compute_directory_sizes(Node* node)
{
    if (!node) throw runtime_error("Invalid node pointer.");
    if (node->type == file) return;
    else
    {
        if (node->size == -1) node->size = 0;
        for (auto& ch : node->children)
        {
            compute_directory_sizes(ch.get());
            node->size += ch->size;
        }
    }
}


void get_all_directories(Node* const node, vector<Node*>& directories)
{
    if (!node) throw runtime_error("Invalid node pointer.");
    if (node->type == file) return;
    directories.push_back(node);
    for (auto& ch: node->children)
    {
        get_all_directories(ch.get(), directories);
    }
    return;
}

vector<int> get_directory_sizes(vector<Node*> const& directories)
{
    vector<int> sizes{};
    for (auto d: directories)
    {
        sizes.push_back(d->size);
    }
    sort(sizes.begin(), sizes.end());
    return sizes;
}

int sum_of_ints_smaller_than(vector<int> const& sizes, int const limit)
{
    int size{0};
    for (auto d : sizes)
    {
        if (d <= limit)
            size += d;
    }
    return size;
}

int main()
{
    ifstream input("filesystem_tree.dat");
    if (!input) throw runtime_error("Couldn't open file.");

    Node root = read_filesystem(input);
    compute_directory_sizes(&root);

    vector<Node*> directories{};
    get_all_directories(&root, directories);
    vector<int> sizes{get_directory_sizes(directories)};
    int total_size_smaller = sum_of_ints_smaller_than(sizes, 100000);
    cout << "Total size of directories with maximal size 100 000 is " << total_size_smaller << "\n";

    constexpr int total_space = 70000000;
    constexpr int needed_space = 30000000;

    int total_size = sizes.back();
    cout << total_size << ", " << total_space << ", " << needed_space << "\n";
    int min_dir_size = needed_space - (total_space - total_size);
    cout << "needed space: " << min_dir_size << "\n";

    for (auto s: sizes)
    {
        cout << s << "\n";
    }
    auto deletion_candidate_size = lower_bound(sizes.begin(), sizes.end(), min_dir_size);
    cout << "Size of the directory that fits best for deletion is " << *deletion_candidate_size << ".\n";

    return EXIT_SUCCESS;
}