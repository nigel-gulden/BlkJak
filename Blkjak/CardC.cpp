//card.cpp
#include "CardC.h"


void CardC::Copy(CardC card)
{
    m_rank = card.m_rank;
    m_suit = card.m_suit;
}

void CardC::SetRank( int rank )
{
	//sets m_rank
	m_rank = rank;
}



void CardC::SetSuit( int suit )
{
	//sets m_suit
	m_suit = suit;
}



int CardC::GetRank()
{
	//returns m_rank
	return m_rank;
}



int CardC::GetSuit()
{
	//returns m_suit
	return m_suit;
}

void CardC::operator= (const CardC & rhs)
{
	m_rank = rhs.m_rank;
	m_suit = rhs.m_suit;
}

CardC::CardC(const CardC & card) : QObject()
{
	m_rank = card.m_rank;
	m_suit = card.m_suit;
}
