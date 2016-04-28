#ifndef HAND_H
#define HAND_H
#include "CardC.h"
#include <QObject>

class Hand : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int mCount READ GetmCount)
public:
	Hand();
    Hand(const Hand & rhs);
    ~Hand();
    Hand& operator= (const Hand& rhs);

public slots:
    CardC* getCardAt(int index);
	int GetmCount();


    void Hit(const CardC & dealt);

	int FindCardTotal();


private:

    CardC * mCards;
	int mCount;
};
Q_DECLARE_METATYPE(Hand)
#endif

//prob done
