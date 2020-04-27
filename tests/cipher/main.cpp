#define BOOST_TEST_MODULE boost_test_macro_overview
#include <boost/test/included/unit_test.hpp>
#include <string>
#include "../../functions.h"


namespace tt = boost::test_tools;

BOOST_AUTO_TEST_CASE( test_no_1){

    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int key = 4;
    std::string cipher_alphabet = create_alphabet(alphabet, key);
    std::string message = "ciao";

    BOOST_TEST(cipher(message, alphabet, cipher_alphabet) == "gmes"); 
}

BOOST_AUTO_TEST_CASE( test_no_2){

    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int key = 7;
    std::string cipher_alphabet = create_alphabet(alphabet, key);
    std::string message = "If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.";

    std::string result = "Pm ol ohk hufaopun jvumpkluaphs av zhf, ol dyval pa pu jpwoly, aoha pz, if zv johunpun aol vykly vm aol slaalyz vm aol hswohila, aoha uva h dvyk jvbsk il thkl vba.";

    BOOST_TEST(cipher(message, alphabet, cipher_alphabet) == result); 
}