#include "queryHandler.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include<cstring>
#include <iostream>
#include <queue>
#include "stemmer.h"
#include "terms.hpp"

using namespace std;



QueryHandler::QueryHandler(std::string query_in, Terms terms_in){
    query.original_query = query_in;
    terms = terms_in;
}
/**
 * uses the same tokenization method as last project.
 */ 
void QueryHandler::tokenize(){
    query.terms = removeSpaces(query.original_query);
    vector<string> tokenized;
    for(auto i = query.terms.begin(); i != query.terms.end(); ++i){
        char tmp[i->length() + 4];
        strcpy(tmp, i->c_str());
        int sub = stem(tmp, 0, i->length() -1);
        string t_string(tmp);
        tokenized.push_back(t_string.substr(0, sub+1));

    }
    query.terms = tokenized;
}

std::vector<std::string> QueryHandler::removeSpaces(std::string line){
    std::vector<std::string> retval;
    boost::algorithm::split(retval, line, boost::algorithm::is_any_of(" "));  
    return retval;
}

/**
 * prints each term in the query
 */ 
void QueryHandler::print_terms(){
    for(auto i = query.terms.begin(); i != query.terms.end(); ++i){
        cout << *i << endl;
    }
}

/**
 * Getter for the terms in the query
 */ 
std::vector<std::string> QueryHandler::get_terms(){
    return query.terms;
}

/**
 * This method will first retreieve the dictionary entry for each query term
 * Using that entry, it will then get the location of the posting lists
 * Then, it will retrieve the postings list
 * To compare similarity, Document at a time algorithm will be used
 */ 
void QueryHandler::process_query(){
    int number_of_terms = query.terms.size();
    queue<Posting> term_posting_list[number_of_terms];
    DictionaryEntry dic_ent;
    for(int i = 0; i < number_of_terms; ++i){
        dic_ent = terms.get_dictionary_entry(query.terms.at(i));
        for(int k = 0; k < dic_ent.document_freq; ++k){
            term_posting_list[i].push(terms.get_postings_entry(dic_ent.offset + k));
        }
    }
    /**
     * 
     * TODO: Implement document at a time algorithm here. The Postings lists are saved
     * in the term_posting_list array as a series of queues (should be the easiest way
     * since DaaT uses a k way merge). 
     */

    /**
     * note that comparing the similarity has to be done with the k way merge of the 
     * documents. So peek each queue, the lowest document id(s) will be considered. Pop the
     * values and calculate that documents overall similarity using the cosine similarity
     *  formula (will need a separate data structure to contain the scores of each
     *  document probably).
     */ 

    /*so, until all of the queues are empty, peek() each queue. Whichever queue has the 
    * smallest documente_id, pop it and calculate the cosine similarity. If there is a tie
    * pop all of them and calculate the cosine similarity. 
    * After that, compare the weights to find the ordering
    */

    for(int i = 0; i < number_of_terms; ++i){
        for(int k = 0; k < dic_ent.document_freq; ++k){
            
        }
    }


}