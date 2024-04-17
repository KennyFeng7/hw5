#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <vector>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordlehelper(const std::string& in, 
                     std::string floating, 
                     const std::set<std::string>& dict, 
                     std::set<std::string>& results, 
                     int index,
                     std::string current);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> results;
    int index =0;
    string current ="";
    wordlehelper(in, floating, dict, results, index, current);
    return results;
}

// Define any helper functions here
void wordlehelper(const std::string& in, 
                     std::string floating, 
                     const std::set<std::string>& dict, 
                     std::set<std::string>& results, 
                     int index,
                     std::string current)
{
    if (index == in.length()){
      if (floating.length() == 0 && dict.find(current) != dict.end()){
        results.insert(current);
      }
      return;
    }

    if (in[index] != '-'){ 
        wordlehelper(in, floating, dict, results, index + 1, current + in[index]);
    } 
    else{
        int count = 0;
        for ( int i = index; i < in.length(); i++) {
          if (in[i] == '-') {
            count++;
          }
        }
        if(count < floating.length()){
          return;
        }
        for (char c = 'a'; c <= 'z'; c++) {
            std::string next = floating;
            if (next.find(c) != std::string::npos){
                next.erase(next.find(c),1); 
            }
            wordlehelper(in, next, dict, results, index + 1, current + c);
        }
    }
}

