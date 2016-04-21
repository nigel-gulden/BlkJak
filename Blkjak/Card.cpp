//card.cpp
#include "Card.h"

//const words for enum list
const char * rank_txt[] = { "A", "2", "3", "4", "5", "6", "7", "8",
"9", "10", "J", "Q", "K" };

const char * suit_txt[] = { "\x03", "\x04", "\x05", "\x06" };




/**************************************************************
*	Purpose: Displays information in Card
*
*	Entry:  none
*
*	 Exit:  Prints rank_txt and suit_txt to screen
****************************************************************/

void Card::DisplayCard()
{
	//displays current card
	cout  << left << setw(3)
		<< rank_txt[m_rank - 1];
	cout << suit_txt[m_suit - 1];
}

/**************************************************************
*	Purpose:  Sets m_rank
*
*	Entry: Rank rank
*
*	 Exit:  sets m_rank to rank
****************************************************************/

void Card::SetRank( Rank rank )
{
	//sets m_rank
	m_rank = rank;
}

/**************************************************************
*	Purpose:  Sets m_suit
*
*	Entry: Suit suit
*
*	 Exit:  sets m_suit to suit
****************************************************************/

void Card::SetSuit( Suit suit )
{
	//sets m_suit
	m_suit = suit;
}

/**************************************************************
*	Purpose:  Gets m_rank
*
*	Entry: none
*
*	 Exit:  returns m_rank
****************************************************************/

Rank Card::GetRank()
{
	//returns m_rank
	return m_rank;
}

/**************************************************************
*	Purpose:  Gets m_suit
*
*	Entry: none
*
*	 Exit:  returns m_suit
****************************************************************/

Suit Card::GetSuit()
{
	//returns m_suit
	return m_suit;
}

void Card::operator= (const Card & rhs)
{
	m_rank = rhs.m_rank;
	m_suit = rhs.m_suit;
}

Card::Card(const Card & card)
{
	m_rank = card.m_rank;
	m_suit = card.m_suit;
}