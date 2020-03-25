#ifndef QUERY_H
#define QUERY_H

#include "terms.hpp"
#include <string>
#include <vector>
 

struct Query{
    std::string original_query;
    std::vector<std::string> terms;
};

class QueryHandler{
    public:
        QueryHandler(std::string query_in, Terms terms_in);
        void tokenize();
        void print_terms();
        std::vector<std::string> get_terms();
        void process_query();
    private:
        Query query;
        Terms terms;
        std::vector<std::string> removeSpaces(std::string line);
        const int NUMBER_OF_DOCUMENTS = 200;
};





#endif