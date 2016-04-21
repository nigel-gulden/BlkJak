#ifndef HAND_H
#define HAND_H
#include "Card.h"
class Hand
{
public:
	Hand();
	virtual ~Hand();

	int GetmCount();

	void Hit(const Card & dealt);
	Rank GetRank(int cardNum);
	void DisplayCard(int i);
	int FindCardTotal();

private:
	Card ** mCards;
	int mCount;
};

#endif