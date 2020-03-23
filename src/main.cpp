#include <string>
#include <iostream>
#include <cstring>

#include "terms.hpp"
#include "stemmer.h"
#include "queryHandler.hpp"

using namespace std;

/**
 * To make life easier for the TA, I have opted to hardcode in the input files 
 * so that they don't need to add them manually on the cmd line
 */ 
int main(){
    string dictionary_filename = "dictionary.txt";
    string postings_filename = "postings.txt";
    Terms t1;
    t1.populate_data(dictionary_filename, postings_filename);
    //t1.print_dictionary_entry("ahead");
    //t1.print_postings_entry(1395);
    t1.calculate_term_weight();
    //t1.print_postings_entry(1395);
    //the queries are hard coded in as well for now...
    string query1 = "europe";
    string query2 = "stock rally";
    string query3 = "debt crisis";
    string query4 = "stock future higher";
    QueryHandler q1(query4, t1);
    q1.tokenize();
    //q1.print_terms();
    q1.process_query();
}