#include "Hand.h"

Hand::Hand() :QObject(),
    mCount(0)
{
	mCards = nullptr;
}
Hand::Hand(const Hand & rhs) : QObject()
{
     this->mCards = new CardC [rhs.mCount];

    for(int i = 0; i < rhs.mCount; i++)
    {
        mCards[i] = rhs.mCards[i];
    }
    mCount = rhs.mCount;

}

Hand& Hand::operator=(const Hand& rhs)
{
   if(this != &rhs)
   {
       delete [] mCards;
       mCards = new CardC [rhs.mCount];

       for(int i = 0; i < rhs.mCount; i++)
       {
          mCards[i] = rhs.mCards[i];
       }
       mCount = rhs.mCount;
   }
   return *this;
}

void Hand::Clear()
{
    delete[] mCards;
    mCards = nullptr;
    mCount = 0;
}

Hand::~Hand()
{

	delete[] mCards;
	mCards = nullptr;
	mCount = 0;
}

CardC* Hand::getCardAt(int index)
{
    return &mCards[index];
}

void Hand::Hit(const CardC & dealt)
{
    CardC * mTemp = new CardC [mCount + 1];

	for (int i = 0; i < mCount; i++)
	{
		mTemp[i] = mCards[i];
	}


    mTemp[mCount] = dealt;

	delete[] mCards;

	mCards = mTemp;
	mCount++;
}

int Hand::GetmCount()
{
	return mCount;
}


int Hand::FindCardTotal()
{
	int totalCount = 0;

	int aceCheck = 0;
	int optimalAce = 0;

    int rank = 0;

	for (int i = 0; i < mCount; i++)
	{
        rank = mCards[i].GetRank();
        rank++;
        if (rank > 1 && rank < 11)
		{
            totalCount += rank;
		}
        else if (rank == 1)
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
