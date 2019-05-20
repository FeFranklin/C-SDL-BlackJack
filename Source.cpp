#include <SDL.h>
#include <stdio.h>
#include "Deck.h"
#include "Card.h"
#include "Dealer.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

///Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int nCards = 52;/*!< Since we do not need the joker, there will be only 52 cards in our Deck */

SDL_Window* janela = NULL; /*!< The window we'll be rendering to*/

SDL_Surface* superficie = NULL;/*!< The surface contained by the window*/

///Function responsible to initialize the SDL components
///The window that opens and the main surface of this window
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not initialize! SDL Error:"<< SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Create window
		janela = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (janela == NULL)
		{
			cout<< "Window could not be created! SDL Error: "<< SDL_GetError()<< endl;
			success = false;
		}
		else
		{
			//Get window surface
			superficie = SDL_GetWindowSurface(janela);
		}
	}

	return success;
}

///Frees media and shuts down SDL
void close(SDL_Window* gWindow) {
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[]) {
	srand(time(0));/*!< Variable to generate random numbers*/
	
	SDL_Surface* ibagem_atual = NULL;/*!< Current displayed image*/

	SDL_Surface* ibagems[3]; /*!Initial MENU images*/
	ibagems[0] = SDL_LoadBMP("imgs/initial_page.bmp");
	ibagems[1] = SDL_LoadBMP("imgs/therules.bmp");
	ibagems[2] = SDL_LoadBMP("imgs/backgroundforplay.bmp");

	SDL_Surface* dealer_cards[2]; /*!< Surface containing the cards' images of the dealer*/

	SDL_Surface* backOfCard = NULL;/*!< Surface containing the card's BACK*/

	SDL_Rect dealerCardPlaceSecond = { 200,10,100,100 }; /*!< SDL Object that indicates the location of the image for the SECOND dealer card*/

	SDL_Surface* player_cards[5];/*!< Surface that contain the cards' images of the player*/

	SDL_Rect player_card_one_place = { 100,400,100,100 };/*!< SDL Object that indicates the location of the image*/

	/*----------------------------------------------------*/
	Deck mainDeck;/*!< Creates the fixed size deck and shuffle the cards*/

	///Shufles the deck
	mainDeck.shuffle();

	Player playerOne(mainDeck);/*!< Creates the player*/

	Dealer dealerOne(mainDeck);/*!< Creates the dealer and deal 2 cards to it*/

	///Start up SDL and create window
	if (!init())
	{
		cout << "Failed to initialize!\n"<< endl;
	}
	else {
		///Main loop flag
		bool quit = false; /*!< Flag to show rules and never again after skipped*/
		
		bool rules = false;/*!< Flag to skip the reules screen after*/
		
		bool game_start = false;/*!< Flag to start game*/		

		bool pera = false;/*!< Flag to stop showing menu image*/
		
		bool reset = false;/*!< Flag to reset the game when lose or win*/

		bool bust = false;/*!< Flag to verify if player went BUST*/
		
		bool stand = false;/*!< Flag when player stand*/
		
		bool wait = false;/*!< Flag to wait response of player*/

		SDL_Event e;/*!< Event handler*/		

		ibagem_atual = ibagems[0];/*!< Setting the MENU to be displayed*/

		while (!quit) {

			while(SDL_PollEvent(&e) != 0) {
				///In case of event Quit
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				///In case of any keyboard event
				else if(e.type == SDL_KEYDOWN){
					switch (e.key.keysym.sym)
					{
					///Start the game and sets the rules and afterwards skip the rules
					case SDLK_p:
						if (rules == false) {
							ibagem_atual = ibagems[1];
							rules = true;
						}							
						else {
							ibagem_atual = ibagems[2];
							game_start = true;
						}							
						break;
					///Player asks for a card
					case SDLK_DOWN:
						if (bust != true && stand != true) {
							playerOne.SetCards(mainDeck);
							wait = false;
						}					
						break;
					///Player stands
					case SDLK_UP:
						if (bust != true) {
							stand = true;
							wait = false;
						}
						break;
					///Restarts the game
					case SDLK_LEFT:
						pera = false;
						game_start = false;
						reset = true;
						break;
					default:
						break;
					}
				}
			}

			if(pera == false)
				SDL_BlitSurface(ibagem_atual, NULL, superficie, NULL);

			///after reading the rules and pressing p, the cards will be dealt
			///and the game starts
			if (game_start == true && wait == false) {
				
				pera = true;/*!< flag that clears the surcafe*/

				SDL_Rect dealerCardPlace = { 100,10,100,100 };/*!< SDL object with the coordinates to where the image should be placed*/

				///Gets the path to the 2 cards of the dealer and load into SDL surfaces
				///And also load the back of the card to another surface since one of them
				///is hidden in the beginning of the game
				std::string path_dealer_Card_one = dealerOne.getCard(0);
				std::string path_dealer_Card_two = dealerOne.getCard(1);
				dealer_cards[0] = SDL_LoadBMP(path_dealer_Card_one.c_str());
				dealer_cards[1] = SDL_LoadBMP(path_dealer_Card_two.c_str());
				backOfCard = SDL_LoadBMP("imgs/backofthe_cards.bmp");
				
				SDL_BlitSurface(dealer_cards[0], NULL, superficie, &dealerCardPlace);

				///If player chooses to stand, show the Dealer's hidden card
				///In case the game is still on, show the back of the second card
				if (stand == false)
					SDL_BlitSurface(backOfCard, NULL, superficie, &dealerCardPlaceSecond);
				else
					SDL_BlitSurface(dealer_cards[1], NULL, superficie, &dealerCardPlaceSecond);				

				///Logic to show the player's cards
				for (int cnt = 0; cnt < playerOne.card_num; cnt++) {
					std::string player_path = playerOne.playerCartas[cnt].toString();
					player_cards[cnt] = SDL_LoadBMP(player_path.c_str());

					SDL_Rect player_card_two_place = { 100+cnt*90,350,100,100 };

					SDL_BlitSurface(player_cards[cnt], NULL, superficie, &player_card_two_place);
				}

				wait = true;/*!< flag to wait the action of the player*/

				///Logic if the next card drwan makes the player lose
				bust = playerOne.bust();
				if (bust == true) {
					SDL_Rect busted_rect = { SCREEN_WIDTH / 2-150,SCREEN_HEIGHT / 2-84,300,300 };
					SDL_Surface* busted = SDL_LoadBMP("imgs/busted.bmp");

					SDL_BlitSurface(busted, NULL, superficie, &busted_rect);
				}

				///Logic to solve if player standed and give result if win or lose
				if (stand == true) {
					if (dealerOne.getPoints()> playerOne.points) {
						SDL_Rect lose_rect = { SCREEN_WIDTH / 2 - 150,SCREEN_HEIGHT / 2 - 84,300,300 };
						SDL_Surface* lose = SDL_LoadBMP("imgs/lose.bmp");
						SDL_BlitSurface(lose, NULL, superficie, &lose_rect);

					}
					else {
						SDL_Rect win_rect = { SCREEN_WIDTH / 2 - 150,SCREEN_HEIGHT / 2 - 84,300,300 };
						SDL_Surface* win = SDL_LoadBMP("imgs/win.bmp");
						SDL_BlitSurface(win, NULL, superficie, &win_rect);
					}
				}

			}	

			if (reset == true) {

				SDL_BlitSurface(ibagems[2], NULL, superficie, NULL);/*!< flag to clean the surface back to false*/

				///Reset the flags that end the game
				bust = false;
				stand = false;

				///Set new cards to the dealer and update points
				dealerOne.reset(mainDeck);

				///Updates points, set new cards and delete the other cards
				playerOne.resetP(mainDeck);

				///Update the flags
				game_start = true;
				wait = false;
				reset = false;

			}

			///Function to update the Window
			SDL_UpdateWindowSurface(janela);
		}
	}
	///calling the destructor of the class to delete the dynamically allocated memory
	playerOne.~Player();

	close(janela);

	return 0;
}