#include "Deck.h"

/*! Set of static variables to help with the creation of cards afterwards*/
const int SPADE = 4;
const int HEART = 3;
const int CLUB = 2;
const int DIAMOND = 1;

//!Simple initialization of the Deck and the 52 cards
Deck::Deck()
{
	int i = 0;
	int CardSuit;
	int CardRank;
	for (CardSuit = DIAMOND; CardSuit <= SPADE; CardSuit++)
		for (CardRank = 1; CardRank <= 13; CardRank++){
			allCards[i] = Card(CardSuit, CardRank);
			i++;
		}
			

	currentCard = 0;
}
//!Return the current card
Card Deck::dealCard()
{
	///If the number of cards dealt go to 52, since the last card is 51
	///The deck is shuffled again and the current card is reset to zero
	if (currentCard == 52) {
		this->shuffle();
		currentCard = 0;
	}
	Card ret = allCards[currentCard];
	currentCard++;
	return ret;
}
//!Shuffle the deck
void Deck::shuffle()
{
	for (int k = 0; k < 200; k++) {
		int i, j;
		j = rand() % 52;
		i = rand() % 52;

		Card tmp = allCards[i];
		allCards[i] = allCards[j];
		allCards[j] = tmp;
	}	
}
