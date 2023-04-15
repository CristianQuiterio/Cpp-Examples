#if !defined PASSWORD_H
#define PASSWORD_H

//INSTRUCTIONS
/*Your task is to write a Password class that stores the current list of
 possible passwords in a ListArray. You will need to store the list of original
 words, the list of possible passwords, and the length of the first word added 
 to the original list to check for input errors.*/
 
 /*Note that the program also tells you the best word in the original 
 list to guess! The result when guessing this word (if it is not the password) 
 will eliminate the most passwords from the possible passwords list. 
 This has been done for you.*/
 
//complete the includes
#include "ListArray.h"
#include "ReadFile.h"
#include "Text.h"
#include "Keyboard.h"

using CSC2110::ListArray;
using CSC2110::String;

class Password
{
   private:
      ListArray<String>* viable_words;  //the list of words that can still be the password
      ListArray<String>* all_words;  //the original list of words
      int len;  //the length of the first word entered is stored to check that all subsequent words have the same length

      //a private helper method to report the number of character matches between two Strings
      int getNumMatches(String* curr_word, String* word_guess);

	 	 //int try_password, num_matches;
		 
   public:
	   //constructor
	   Password();
	   //destructor, delete the individual words
	   ~Password();
	   void addWord(String* fh);
	   int bestGuess();
	   int getNumberOfPasswordsLeft();
	   void displayViableWords();
	   String* getOriginalWord(int index);
	   void guess(int try_password, int num_matches);
	   
};

#endif