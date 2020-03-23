#include "terms.hpp"
#include "fileparser.hpp"

#include <bits/stdc++.h> 
#include <cmath>

using namespace std;

void Terms::populate_data(string dictionary_filename, string postings_filename){
    update_dictionary(dictionary_filename);
    update_postings(postings_filename);
}

void Terms::update_dictionary(std::string filename){
    FileParser fp(filename);
    fp.open();
    string line = "none";
    while(line != ""){
        line = fp.poll();
        istringstream par(line);
        DictionaryEntry temp;
        par >> temp.term;
        par >> temp.document_freq;
        par >> temp.offset;
        dictionary.insert({temp.term, temp});
    }
}
void Terms::update_postings(std::string filename){
    FileParser fp(filename);
    fp.open();
    string line = "none";
    while(line != ""){
        line = fp.poll();
        istringstream par(line);
        Posting temp;
        par >> temp.document_id;
        par >> temp.term_freq;
        temp.weight = 0.0;
        postings.push_back(temp);
    }
}

void Terms::print_dictionary_entry(std::string term){
    auto ret = dictionary.find(term);
    cout << ret->first << " " << ret->second.document_freq << " " << ret->second.offset <<endl;
}

void Terms::print_postings_entry(int offset){
    Posting temp;
    temp = postings.at(offset);
    cout << temp.document_id << " " << temp.term_freq << " " << temp.weight <<endl;
}

DictionaryEntry Terms::get_dictionary_entry(std::string term){
    auto itr = dictionary.find(term);
    return itr->second;
}

Posting Terms::get_postings_entry(int offset){
    return postings.at(offset);
}
/**
 * Modifies the term_freq in the postings list to represent
 * the weight of the term. The weight is calculated using
 * weight = log10(term_frequency)
 */ 
void Terms::calculate_term_weight(){
    for(auto post = postings.begin(); post != postings.end(); ++post){
        post->weight = 1 + log10(post->term_freq);
    }
}