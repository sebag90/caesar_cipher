#!/usr/bin/python3

import functions as fn
import operator
import copy
 
            
def main():
    # TODO
    # add support for ENG/ITA
    
    # retrieve all articles from folder bestand and stopwords
    articles_org = fn.retrieve_articles()
    stopwords = fn.collect_stopwords()

    # clean the articles
    for element in articles_org:
        new_str = fn.clean_string(articles_org[element])
        articles_org[element] = new_str

    # stem the articles
    for key in articles_org:
        articles_org[key] = fn.str_2_vec(articles_org[key], stopwords)

    # uncomment to check for stemming of documents
    # for key in articles_org:
    #     print(key, "\t", articles_org[key])
    
    while True:
        user_input =  input("Enter data query or enter '...' to exit:\n> ")
        if user_input == "...":
            break
        # create a local copy of the cleaned and stemmed dict
        articles = copy.deepcopy(articles_org)

        # clean and stem user input
        cleaned_input = fn.clean_string(user_input)
        stemmed_input = fn.str_2_vec(cleaned_input, stopwords)
       
        if len(stemmed_input) != 0:
            # create document matrix terms
            matrix_terms = fn.create_matrix_terms(articles)

            # warning if stemmed query not in stemmed matrix terms
            input_present = False
            for term in stemmed_input:
                if term in matrix_terms:
                    input_present = True
            if input_present == False:
                print("no match found\n")
            else:
                articles["query"] = stemmed_input
                # TODO: modify create_matrix_terms to perform it based on list 
                # as input + list if already exists to avoid double matrix term creation of dict

                # create document matrix terms
                matrix_terms = fn.create_matrix_terms(articles)

                # calculate frequency list for every term 
                freq_list = fn.calc_freq(articles, matrix_terms)
                for key in articles:
                    vec = fn.calculate_vec(matrix_terms, articles[key])
                    articles[key] = vec

                # uncomment to check for stemming of documents
                # for key in articles:
                #     print(key, "\t", articles[key])
                
                # uncomment to check for stemmed matrix terms
                # print(matrix_terms)

                # calculate TF * IFD (1 - log(n/nj))
                articles = fn.calc_tf_idf(articles, freq_list)   

                # calculate vector cos similarity and print out the best result
                results = fn.find_best_match(articles)
                print("Best result: ", max(results.items(), key=operator.itemgetter(1))[0], "\n")
        else:
            print("Sorry, try with another query")
    

if __name__ == "__main__":
    main()