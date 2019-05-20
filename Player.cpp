#include "Player.h"
/*!Player constructor receiving the deck as parameter to deal the cards
and dynamically allocating memory
*/
Player::Player(Deck& decko)
{
	playerCartas = new Card[2];
	playerCartas[0] = decko.dealCard();
	playerCartas[1] = decko.dealCard();
	card_num = 2;
	points = playerCartas[0].getPoint() + playerCartas[1].getPoint();
}

///Destructor of the class deleting the dynamic memory
Player::~Player()
{
	delete[] playerCartas;
}


///Function responsible to add a card to the player
void Player::SetCards(Deck& theDeck)
{
	card_num++;
	Card* tmp = new Card[card_num];
	int i = 0;
	for (i = 0; i < card_num - 1; i++) {
		tmp[i] = playerCartas[i];
	}
	tmp[i] = theDeck.dealCard();
	points += tmp[i].getPoint();
	playerCartas = tmp;
}

///Function that verifies if the player lost because it has more than 21 points
bool Player::bust()
{
	if (points > 21)
		return true;

	return false;
}

void Player::resetP(Deck & decko)
{

	///Set new cards and update points and number of cards
	Card* tmp = new Card[2];
	playerCartas = tmp;
	playerCartas[0] = decko.dealCard();
	playerCartas[1] = decko.dealCard();

	card_num = 2;
	points = playerCartas[0].getPoint() + playerCartas[1].getPoint();
}
