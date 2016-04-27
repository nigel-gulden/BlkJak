/************************************************************************
* Class: Card
*
* Constructors:
*	Card(Rank rank = ACE, Suit suit = SPADE)
*		constructs a new card with passed in Rank and Suit, otherwise
*		initialized to ACE of SPADES
*
* Mutators:
*	void SetRank(Rank rank);
*		Initializes m_rank to rank
*	void SetSuit(Suit suit);
*		Initializes m_suit to suit
*	Rank GetRank();
*		Returns the value in m_rank
*	Suit GetSuit();
*		Returns the value in m_suit
* Methods
*	void DisplayCard()
*		Displays the information of the card
*************************************************************************/

#ifndef CARD_H
#define CARD_H

#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
using std::left;

//enumerated data types for rank and suit
enum Rank { ACE = 1, DEUCE, TREY, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
enum Suit { HEART = 1, DIAMOND, CLUB, SPADE };

class Card
{
	
public:
	/**************************************************************
	*	Purpose:  Constructs the Card object
	*
	*	Entry:  Rank rank and Suit suit, defaulted to ACE and SPADES
	*
	*	 Exit:  Sets m_rank and m_suit to assigned values
	****************************************************************/
    Card(Rank rank = ACE, Suit suit = SPADE) : m_rank(rank), m_suit(suit){}

    Card(const Card & card);

	//displays data in Card
	void DisplayCard();
	
	//mutators for class
	void SetRank(Rank rank);
	void SetSuit(Suit suit);
	Rank GetRank();
	Suit GetSuit();

	void operator= (const Card & rhs);

private:
	Rank m_rank;
	Suit m_suit;
};

#endif
