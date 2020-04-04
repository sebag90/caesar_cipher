#define BOOST_TEST_MODULE boost_test_macro_overview
#include <boost/test/included/unit_test.hpp>
#include <string>
#include "../../functions.hpp"

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_CASE( test_no_1){

    BOOST_TEST(levenshtein("text", "test") == 1);
    BOOST_TEST(levenshtein("PLAIN", "PLAN") == 1);
    BOOST_TEST(levenshtein("TREE", "THREE") == 1);
    BOOST_TEST(levenshtein("WOMAN", "WOMEN") == 1);
    BOOST_TEST(levenshtein("KITTEN", "SITTING") == 3);
    BOOST_TEST(levenshtein("YPOEHOHRIWUBXMNHZF", "YCPOEHORIDUBXNHZF") == 4); 
}

BOOST_AUTO_TEST_CASE( test_no_2){
    
    BOOST_TEST(levenshtein("back", "book") == 2);
}