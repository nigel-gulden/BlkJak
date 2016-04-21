#include "Hand.h"

Hand::Hand() :mCount(0)
{
	mCards = nullptr;
}

Hand::~Hand()
{
	for (int i = 0; i < mCount; i++)
	{
		delete[] mCards[i];
	}
	delete[] mCards;
	mCards = nullptr;
	mCount = 0;
}

void Hand::Hit(const Card & dealt)
{
	Card ** mTemp = new Card *[mCount + 1];

	for (int i = 0; i < mCount; i++)
	{
		mTemp[i] = mCards[i];
	}
	mTemp[mCount] = new Card;

	*mTemp[mCount] = dealt;

	delete[] mCards;

	mCards = mTemp;
	mCount++;
}

int Hand::GetmCount()
{
	return mCount;
}

Rank Hand::GetRank(int cardNum)
{
	return mCards[cardNum]->GetRank();
}

void Hand::DisplayCard(int i)
{
	mCards[i]->DisplayCard();
}

int Hand::FindCardTotal()
{
	int totalCount = 0;

	int aceCheck = 0;
	int optimalAce = 0;

	int rank = 0;

	for (int i = 0; i < mCount; i++)
	{
		rank = mCards[i]->GetRank();

		if (rank > ACE && rank < TEN)
		{
			totalCount += rank;
		}
		else if (rank == ACE)
		{
			aceCheck++;
		}
		else
		{
			totalCount += 10;
		}

	}

	//multiplies number of aces with 11
	optimalAce = aceCheck * 11;

	//adds aces value to total value
	totalCount += optimalAce;

	//for each ace in hand
	for (int i = 0; i < aceCheck; i++)
	{
		//if the total value is greater than 21
		if (totalCount > 21)
		{
			//make one of the aces a 1
			totalCount -= 10;
		}
	}

	return totalCount;
}