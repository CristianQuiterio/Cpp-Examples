#if !defined (GUESS_ENUM)
#define GUESS_ENUM
   enum GuessEnum {EXACT, TOO_LOW, TOO_HIGH};
#endif

#include "Text.h"
#include "ReadFile.h"
#include "Random.h"
#include "Keyboard.h"
#include "ComputerGuessDriver.h"

#include <iostream>
using namespace std;

//insert your methods here

int getSecret(int* range)
{
  void randomInit();
  int random = getRandomInt(range[0], range[1]);

  return random;
}

int* getRange()
{
  String* fileName = readString("Enter the file name with the range information: ");
  ReadFile* file = createReadFile(getText(fileName));
  
  String* lowerLimit = readLine(file);
  int lower = a_to_i(lowerLimit);

  String* upperLimit = readLine(file);
  int upper = a_to_i(upperLimit);

  int* rangeArray = new int[2];
  rangeArray[0] = lower;
  rangeArray[1] = upper;

  destroyString(fileName);
  destroyString(lowerLimit);
  destroyString(upperLimit);
  destroyReadFile(file);

  return rangeArray;
}

int getGuess(int* range)
{
  return getValidatedInt("Please enter your guess for the secret number: ", range[0], range[1]);
}

GuessEnum processGuess(int guess, int secret)
{
  GuessEnum result;
  result = EXACT;

  if(guess != secret)
  {
    if(guess < secret)
    {
      cout << "You're too low!" << endl;
      result = TOO_LOW;
    }
    else
    {
      cout << "You're too high!" << endl;
      result = TOO_HIGH;
    }
  }
  return result;
}

int play(int* range, int secret)
{
  GuessEnum result = TOO_HIGH;
  int numGuesses = 0;
  while(result != EXACT)
  {
   result = processGuess(getGuess(range), secret);
   numGuesses++;
  }

  return numGuesses;
}

int compPlay(int* range, int secret)
{
  GuessEnum result = TOO_HIGH;
  int numGuesses = 0;
  while(result != EXACT)
  {
   result = processGuess(getCompGuess(range), secret);
   if(result == TOO_HIGH)
   {
     range[1] = getCompGuess(range);
   }
   else if (result == TOO_LOW)
   {
    range[0] = getCompGuess(range);
   }
   numGuesses++;
  }
  return numGuesses;
}

int main()
{
   String* n = createString("n");
   String* compReadyStr = createString("n");
   String* ready_str = readString("Are you ready to play? (y/n) ");
   if(compare(n, ready_str) != 0) compReadyStr = readString("Would you like the computer to play? (y/n) ");

   while (compare(n, ready_str) != 0)
   {
      int* range = getRange();

    if((compare(n, ready_str) != 0) && (compare(n, compReadyStr) == 0))
    {
      int secret = getSecret(range);

      int total_guess = play(range, secret);

      cout << "You got it in " << total_guess << " guesses!" << endl;
    } 
    else 
    {
      int secret = getPlayerSecret(range);

      int total_guess = compPlay(range, secret);

      cout << "The computer got it in " << total_guess << " guesses!" << endl;
    }

      destroyString(ready_str);
      destroyString(compReadyStr);

      delete[] range;
      range = NULL;

      cin.ignore();
      ready_str = readString("Are you ready to play? (y/n) ");
      if(compare(n, ready_str) != 0) compReadyStr = readString("Would you like the computer to play? (y/n) ");

   }

   destroyString(ready_str);
   destroyString(compReadyStr);
   destroyString(n);
   return 0;
}