#include "queryHandler.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include<cstring>
#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>
#include "stemmer.h"

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
     *  Implement document at a time algorithm here. The Postings lists are saved
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

   bool is_empty = false; 
  
   Posting temp;
   vector<double> posting_weight;
   vector<double> query_weight;
   while(!is_empty){
        int min = 2000;
       //get the next smallest document
       for(int i =0; i < number_of_terms; ++i){
           temp = term_posting_list[i].front();
           if(temp.document_id < min){
               min = temp.document_id;
           }
       }
       for(int i = 0; i < number_of_terms; ++i){
           temp = term_posting_list[i].front();
           if(temp.document_id == min){
               term_posting_list[i].pop();
               double idf_weight = 1 + log10(200 / terms.get_dictionary_entry(query.terms.at(i)).document_freq);
               temp.weight_tf = temp.weight_tf / terms.documents[temp.document_id].number_of_terms;
               //cout << "posting weight is: " << temp.weight_tf * idf_weight << " idf is: " << idf_weight << " tf is: " << temp.weight_tf <<endl;
                posting_weight.push_back(temp.weight_tf * idf_weight);
                double q_weight = 1 + log10(1); //tf for query
                q_weight = q_weight *  (200 / terms.get_dictionary_entry(query.terms.at(i)).document_freq);         //idf
                //cout << "qeight is " << q_weight << endl;
                query_weight.push_back(q_weight);
                //get the cosine similarity now
                terms.documents[temp.document_id].cosine_similarity = calculate_cosine_similarity(posting_weight, query_weight);
           }
       }
       //now check if all queues are empty
       for(int i = 0; i < number_of_terms; ++i){
           is_empty = true;
           if(!term_posting_list[i].empty()){
               is_empty = false;
           }
       }
       //is_empty = true;
   }


double QueryHandler::calculate_cosine_similarity(vector<double> p_weights, vector<double> q_weights){
    double numerator = 0;
    double denominator = 0;
    for(int i = 0; i < p_weights.size(); ++i){
        numerator = numerator +  (p_weights.at(i) * q_weights.at(i));
        denominator = denominator + (pow(p_weights.at(i), 2.0));
    }
    denominator = sqrt(denominator);
    //cout << "The cosine similarity is: " << numerator/denominator << endl;
    return numerator / denominator;
}

void QueryHandler::print_results(){

    for(int i = 0; i < 200; ++i){
        if(terms.documents[i].cosine_similarity > 0){
            cout << "document: " << i+1 << "with a similarity of: " << terms.documents[i].cosine_similarity << endl;
        }
    }
}

/**
 * TODO: add a method which will find the top 10 results and write them to a file
 * The cosine similarities are all saved in the array: terms.documents[].cosine_similarity
 * The document id is the index of the array + 1. So, Document1 is stored in index 0. to
 * access the cosine similarity of document 1, use terms.documents[0].cosine_similarity
 * If a cosine similarity = 0, then that means there are no terms in common and that 
 * document can be ignored.
 * 
 */ 


