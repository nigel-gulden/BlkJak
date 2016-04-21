#include "Player.h"

/************************************************************************
*	Purpose:	Adds cards to Hand
*
*	Entry:		passes in card to add
*
*	Exit:		Calls the Hand's Hit.
*				
************************************************************************/

void Player::Hit(const Card & dealt)
{
	mHand.Hit(dealt);
}

/************************************************************************
*	Purpose:	Polymorphic function that finds if Player wants to hit
*
*	Entry:		none
*
*	Exit:		Prompts if player wants to hit, and while valid value 
*				isn't entered, reads in hs, if h, bReturn is true, and
*				check is true, or if s, check is true, or if neither, 
*				inform player of faulty enter, and return if player 
*				wants to hit or not.
*
************************************************************************/

bool Player::HitStay()
{
	//character that's read in
	char hs = '\0';

	//boolean hit or stay
	bool bReturn = false;

	//check if proper value
	bool check = false;

	cout << "Do you wish to hit or stay? h=hit, s=stay: ";

	//while valid value is false
	while (check == false)
	{
		//read in character
		hs = _getch();

		
		switch (hs)
		{
		//if hs is h
		case 'h':
			
			//player wants to hit
			bReturn = true;

			//valid value entered
			check = true;
			break;

		//if hs is s
		case 's':

			//valid value is true
			check = true;
			break;

		//if neither, inform user
		default:
			cout << "Error, please enter again: ";
		}
	}

	//returns if player wants to hit or not
	return bReturn;
}

/************************************************************************
*	Purpose:	Polymorphic function that displays hand
*
*	Entry:		none
*
*	Exit:		Displays every card in Hand
*
************************************************************************/

void Player::DisplayHand()
{
	//for each card in Hand, display card
	for (int i = 0; i < mHand.GetmCount(); i++)
	{
		cout << '[';
		mHand.DisplayCard(i);
		cout << ']';
	}
}

/************************************************************************
*	Purpose:	Polymorphic function that displays hand
*
*	Entry:		none
*
*	Exit:		Displays every card in Hand
*
************************************************************************/

int Player::FindTotal()
{
	return mHand.FindCardTotal();
}

void Player::ClearHand()
{
	mHand.~Hand();
}