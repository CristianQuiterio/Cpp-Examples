#include "ComputerGuessDriver.h"
#include "keyboard.h"

int getCompGuess(int* range)
{
  return (range[0] + range[1])/2;
}

int getPlayerSecret(int* range)
{
  return getValidatedInt("Please enter the secret number: ", range[0], range[1]);
}
