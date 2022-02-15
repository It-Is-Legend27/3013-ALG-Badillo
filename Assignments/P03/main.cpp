#include <iostream>
#include <string>
#include <fstream>
#include "Trie.hpp"

using namespace std;


void load_trie(Node& tree, string file_name);

//void get_matches();

// C++ implementation of Trie data structure
int main()
{
    Trie tree;
    string x;

    tree.insert("lol");
    
    
    cout << tree.search("lol");
    return 0;
}

void load_trie(Trie tree,string file_name)
{
    ifstream fin; // file to get animal names
    string x;
    fin.open(file_name); // open file for reading

    while (fin >> x)
    {
        for (auto &c : x)
        {
            c = tolower(c);
        }
        tree.insert(x);
    }
    fin.close();
}
