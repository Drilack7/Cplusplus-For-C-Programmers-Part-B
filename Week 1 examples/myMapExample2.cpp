
// This program asks the user for a file to
//open for reading.
//It then reads the file into a vector of strings
//Each string is a word that in the file was separated by white space
//It then uses an unordered map to count the number of occurences of each word


#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <iostream>
using namespace std;

int main()
{
    vector <std::string> words;
    string temp_str, file_name;
    cout << "What File do you want?\n";
    cin >> file_name;

    ifstream fin(file_name);
    while (fin >> temp_str) // Will read up to eof()
        words.push_back(temp_str);

    fin.close();

    unordered_map<std::string, size_t>  word_map;
    for (const auto &w : words)
        ++word_map[w];

    for (const auto &pair : word_map)
        cout << pair.second
	     << " occurrences of word '"
	     << pair.first << "'\n";
}
