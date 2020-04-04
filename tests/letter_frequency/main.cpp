#define BOOST_TEST_MODULE boost_test_macro_overview
#include <boost/test/included/unit_test.hpp>
#include <string>
#include "../../functions.hpp"


namespace tt = boost::test_tools;

BOOST_AUTO_TEST_CASE( test_no_1){

    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    BOOST_TEST(calculate_letter_frequecy("tttteest", alphabet) == "tes"); 
}
