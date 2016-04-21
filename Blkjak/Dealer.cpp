#include "Dealer.h"

/************************************************************************
*	Purpose:	Finds if dealer wants to hit or stay
*
*	Entry:		none
*
*	Exit:		If dealer's hand is less than 17, hit. Return if dealer
*				wants to hit
************************************************************************/

bool Dealer::HitStay()
{
	//case if dealer wants to hit or stay
	bool hitStay = false;

	//if hand's total is less than 17
	if (mHand.FindCardTotal() < 17)
	{
		//hit
		hitStay = true;
	}
	//returns if dealer wants to hit or stay
	return hitStay;
}

/************************************************************************
*	Purpose:	Displays formatted Dealer hand, with hidden first card
*
*	Entry:		none
*
*	Exit:		if first card, display blank card, or else display card
************************************************************************/

void Dealer::DisplayHand()
{
	//for each card in hand
	for (int i = 0; i < mHand.GetmCount(); i++)
	{
		//if not the first card, display card
		if (i > 0)
		{
			cout << '[';
			mHand.DisplayCard(i);
			cout << ']';
		}
		//or else display blank card
		else
		{
			cout << "[card]";
		}
	}
}