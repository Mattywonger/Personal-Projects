// Name: Grace Qiu
// JHED: yqiu26

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "language_model.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::string;
using std::map;
using std::vector;

int main(int argc, char** argv) {
    // declare the map to store values
    map<string, int> trigram_freq_map;

    // error in input stream
    if (argc < 3) {
        cerr << "Not enough arguments" << endl;
        return 1;
    }

    // get input file list filename
    string input_file_list = argv[1];

    // open input file list
    ifstream input_file_list_stream(input_file_list);
    
    // error in opening file list
    if (!input_file_list_stream) {
        cerr << "Invalid file list: " << input_file_list << endl;
        return 1;
    }
    
    // open input files
    string input_filename;
    while (input_file_list_stream >> input_filename) {
        
        // open input file
        ifstream input_file(input_filename);

        // error in opening file
        if (!input_file) {
            cerr << "Invalid file: " << input_filename << endl;
            continue;
        }

        string word1 = "<START_1>";
        string word2 = "<START_2>";

        string word;
        while (input_file >> word) {
            // Process word and update trigram frequency map
            string trigram = word1 + " " + word2 + " " + word;
            trigram_freq_map[trigram]++;

            // Shift words in trigram to the right
            word1 = word2;
            word2 = word;
        }

        // Add end trigrams
        trigram_freq_map[word1 + " " + word2 + " <END_1>"]++;
        trigram_freq_map[word2 + " <END_1> <END_2>"]++;
    }

    string operation = argv[2];
    if (operation == "a") a_operation(trigram_freq_map);
    else if (operation == "d") d_operation(trigram_freq_map);
    else if (operation == "c") c_operation(trigram_freq_map);
    else if (operation == "f"){
        string word1 = argv[3];
        string word2 = argv[4];
        if (word1.empty() || word2.empty()){
            cerr << "Invalid argument list: f requires two additional command-line arguments" << endl;
            return 1;
        }
        f_operation(trigram_freq_map, word1, word2);
    }
    else{
        cerr << "Invalid command: valid options are a, d, c, and f" << endl;
        return 1;
    }
    return 0;
}
