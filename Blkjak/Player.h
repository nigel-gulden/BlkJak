/************************************************************************
* Class: Player
*
* Constructors: none

*
* Mutators:		none
*
* Methods:
*	void ClearHand()
*		Deallocates cards in Hand
*	int FindTotal()
*		Finds the total value of Cards in Hand
*	void Hit( const Card & dealt)
*		Adds cards to Hand
*	virtual bool HitStay()
*		Polymorphic function that finds if Player wants to hit
*	virtual void DisplayHand()
*		Polymorphic function that displays hand
*
* Members:	
*	Hand mHand
*		Holds the Player's hand
*
*************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "Hand.h"
#include <conio.h>
#include <iostream>
using std::cin;

class Player
{
public:
	void ClearHand();
	int FindTotal();
	void Hit( const Card & dealt);
	virtual bool HitStay();
	virtual void DisplayHand();

protected:

	Hand mHand;
};
#endif