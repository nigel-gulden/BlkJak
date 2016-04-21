#ifndef BANKROLL_H
#define BANKROLL_H
class Bankroll
{
	friend Bankroll operator- (const Bankroll & lhs, const Bankroll & rhs);
	friend Bankroll operator+ (const Bankroll & lhs, const Bankroll & rhs);

public:
    Bankroll() : mTotal(0){}
    Bankroll(int bankroll) :mTotal(bankroll){}
	
	Bankroll& operator= (const Bankroll & rhs);
	int GetmTotal();
private:
	int mTotal;
	
};
#endif
