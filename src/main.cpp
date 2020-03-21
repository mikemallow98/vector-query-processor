#include <string>
#include "terms.hpp"


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
    t1.print_dictionary_entry("ahead");
    t1.print_postings_entry(1395);
    t1.calculate_term_weight();
}