#ifndef TERMS
#define TERMS

#include <string>
#include <unordered_map>
#include <vector>


struct DictionaryEntry{
    std::string term;
    int document_freq;
    int offset;
};

struct Posting{
    int document_id;
    int term_freq;
    double weight;
};

class Terms{
    public: 
        void populate_data(std::string dictionary_filename, std::string postings_filename);
        void print_dictionary_entry(std::string term);
        void print_postings_entry(int offset);
        DictionaryEntry get_dictionary_entry(std::string term);
        Posting get_postings_entry(int offset);
        void calculate_term_weight();

    private:
        std::unordered_map<std::string, DictionaryEntry> dictionary;
        std::vector<Posting> postings;
        void update_dictionary(std::string filename);
        void update_postings(std::string filename);

};

#endif