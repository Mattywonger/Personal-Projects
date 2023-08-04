// Name: Grace Qiu
// JHED: yqiu26

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include "language_model.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::pair;
using std::sort;

void a_operation(map <string, int> &trigram_freq_map){
    // create a vector of pairs from the map trigram_freq_map
    vector<pair<string, int>> trigram_freq_vec(trigram_freq_map.begin(), trigram_freq_map.end());
    // sort the vector lexicographically
    sort(trigram_freq_vec.begin(), trigram_freq_vec.end());
    // print the sorted vector
    for (vector<pair<string, int>>::iterator it = trigram_freq_vec.begin(); it != trigram_freq_vec.end(); ++it) {
        cout << it->second << " - [" << it->first << "]" << endl;
    }
}

void d_operation(map <string, int> &trigram_freq_map){
    // create a vector of pairs from the map
    vector<pair<string, int>> trigram_freq_vec(trigram_freq_map.begin(), trigram_freq_map.end());
    // sort the vector lexicographically in descending order
    sort(trigram_freq_vec.begin(), trigram_freq_vec.end(),[](pair<string, int>& left, pair<string, int>& right) {
        return left.first > right.first;
    });
    // print the sorted vector
    for (vector<pair<string, int>>::iterator it = trigram_freq_vec.begin(); it != trigram_freq_vec.end(); ++it) {
        cout << it->second << " - [" << it->first << "]" << endl;
    }    
}
// a function used to allow printing in c_operation when calling c_operation independently, 
// but avoids printing when calling c_opertion in the f_operation
void c_operation_helper(map<string, int>& trigram_freq_map, bool print_output) {
    // create a vector of pairs from the map
    vector<pair<string, int>> trigram_freq_vec(trigram_freq_map.begin(), trigram_freq_map.end());
    // sort the vector in decreasing order by count, then lexicographically
    sort(trigram_freq_vec.begin(), trigram_freq_vec.end(), [](pair<string,int> &left, pair<string,int> &right){
        //when you define a lambda function, you can use the . operator to access the fields of the
        //objects that the function parameters are pointing to without dereferencing them explicitly.
        if (left.second != right.second) { // compare counts first
            return left.second > right.second;
        }
        else{
            return left.first < right.first;
        }
    });
    // print the sorted vector
    if (print_output) {
        for (vector<pair<string, int>>::iterator it = trigram_freq_vec.begin(); it != trigram_freq_vec.end(); ++it) {
            cout << it->second << " - [" << it->first << "]" << endl;
        }
    }
}

void c_operation(map <string, int> &trigram_freq_map){
    // allows printing in c_operation
    c_operation_helper(trigram_freq_map, true);
}

void f_operation(map <string, int> &trigram_freq_map, string word1, string word2){
    
    /* idea: call the c_operation function from within the f_operation function to sort the trigrams 
    in the map in descending order of frequency, and then lexicographically, and then search for 
    the trigram starting with word1 and word2. 
    */


    // to prevent the c_operation from changing the trigram_freq_map, create a copy of the map.
    map<string, int> copy_map(trigram_freq_map);
    
    // Sort the copy of the map using the c_operation
    // avoid printing in c_operation
    c_operation_helper(copy_map, false);

    // find the trigram starting with word1 and word2
    string most_freq_trigram;
    int most_freq_count = 0;
    string first_two_words = word1 + " " + word2;
    //loops through all the trigrams in copy_map that start with word1 and word2
    for (map<string,int> ::iterator it = copy_map.begin();
        it!= copy_map.end();
        ++it){
        string current_key = it->first;
        if (current_key.compare(0, first_two_words.length(), first_two_words) == 0) {
            if (it->second > most_freq_count) {
                most_freq_count = it->second;
                most_freq_trigram = current_key;
            }
        }
    }
    if(most_freq_count == 0){
        cout << "No trigrams of the form [" << word1 << " " << word2 << " ?]." << endl;
        return;
    }
    cout << most_freq_count << " - [" << most_freq_trigram << "]" << endl;
}
