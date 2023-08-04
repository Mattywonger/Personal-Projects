// Name: Grace Qiu
// JHED: yqiu26

#ifndef TRIGRAM_OPERATIONS_H
#define TRIGRAM_OPERATIONS_H

#include <map>
#include <string>


void a_operation(std::map <std::string, int> &trigram_freq_map);
void d_operation(std::map <std::string, int> &trigram_freq_map);
void c_operation_helper(std::map<std::string, int>& trigram_freq_map, bool print_output);
void c_operation(std::map <std::string, int> &trigram_freq_map);
void f_operation(std::map <std::string, int> &trigram_freq_map, std::string word1, std::string word2);

#endif // TRIGRAM_OPERATIONS_H