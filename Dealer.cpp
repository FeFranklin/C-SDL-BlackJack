#include "Dealer.h"
//! Starts the Dealer with the deck as parameter to deal the 2 cards
Dealer::Dealer(Deck& deckParam)
{
	dealerCards[0] = deckParam.dealCard();
	dealerCards[1] = deckParam.dealCard();
	points = dealerCards[0].getPoint() + dealerCards[1].getPoint();
}
///Return the dealer's points as it is private since it
///sgould not be visible to anyone
int Dealer::getPoints()
{
	return points;
}

//! Reset the Dealer after the round finishes
void Dealer::reset(Deck& decko)
{
	dealerCards[0] = decko.dealCard();
	dealerCards[1] = decko.dealCard();

	points = dealerCards[0].getPoint() + dealerCards[1].getPoint();
}

//! Get the string of the dealer's cards with param
std::string Dealer::getCard(int param)
{
	std::string tmp;
	tmp = dealerCards[param].toString();
	return tmp;
}
