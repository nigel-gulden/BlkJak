#include "Bankroll.h"

Bankroll operator- (const Bankroll & lhs, const Bankroll & rhs)
{
	return Bankroll(lhs.mTotal - rhs.mTotal);
}

Bankroll operator+ (const Bankroll & lhs, const Bankroll & rhs)
{
	return Bankroll(lhs.mTotal + rhs.mTotal);
}

Bankroll& Bankroll::operator= (const Bankroll & rhs)
{
	mTotal = rhs.mTotal;

	return *this;
}

int Bankroll::GetmTotal()
{
	return mTotal;
}