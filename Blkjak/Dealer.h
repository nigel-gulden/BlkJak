/************************************************************************
* Class: Dealer : inherits from Player.h
*
* Constructors: none

*
* Mutators:		none
*
* Methods:
*	bool HitStay()
*		Finds if dealer wants to hit or stay
*	void DisplayHand()
*		Displays formatted Dealer hand, with hidden first card
*
* Members:	none
*
*************************************************************************/

#ifndef DEALER_H
#define DEALER_H

#include "Deck.h"
#include "Player.h"

class Dealer: public Player
{
public:
	bool HitStay();

	void DisplayHand();
};

#endif