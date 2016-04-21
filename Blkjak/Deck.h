/************************************************************************
* Class: Deck
*
* Constructors:
*	Deck()
*		Allocates a new deck of Cards
*
* Mutators:
*	None
*
* Methods
*	~Deck();
*		This is the destructor for the class, deallocates memory used
*	void Shuffle();
*		Shuffles the Cards in the deck
*	Card Deal();
*		Returns the current Card
*	void IncrementCurrent();
*		Increments currentCount
*	void ResetCurrent();
*		Resets currentCount
*
*	Members:
*************************************************************************/

#ifndef DECK_H
#define DECK_H

#include <iostream>
using std::cout;

#include "Card.h"
#include "Random.h"

class Deck
{
public:
	//no arg ctor
	Deck();

	//dtor
	~Deck();

	//shuffles Cards
	void Shuffle();

	//deals current Card
	Card Deal();

	//sets currentCard to 0
	void ResetCurrent();

private:
	Card ** m_deck;

	Random rand;

	int m_currentCard;
	
};
#endif 