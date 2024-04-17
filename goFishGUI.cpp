
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>
#include <time.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>

#include "goFishGUI.h"
#include "state.h"

using namespace std;

string message = " testing text location ";
bool hasHandUpdated = false;
bool messageUpdated = false;


Rank goFishGUI_state::convertStringToRank(string theAsk){
  Rank result;
  char firstvalue = theAsk[0];
  switch (firstvalue){
    case 'a':
    case 'A':
      result = Rank::Ace; break;
    case '2':
      result = Rank::Two; break;
    case '3':
      result = Rank::Three; break;
    case '4':
      result = Rank::Four; break;
    case '5':
      result = Rank::Five; break;
    case '6':
      result = Rank::Six; break;
    case '7':
      result = Rank::Seven; break;
    case '8':
      result = Rank::Eight; break;
    case '9':
      result = Rank::Nine; break;
    case '1':
      result = Rank::Ten; break;
    case 'j':
    case 'J':
      result = Rank::Jack; break;
    case 'q':
    case 'Q':
      result = Rank::Queen; break;
    case 'k':
    case 'K':
      result = Rank::King; break;
    default: break;
  }
  return result;
}

Suit ConvertStringToSuit(string theCard){
  Suit result;
  char firstvalue = theCard[0];
  switch (firstvalue){
    case 'C': result = Suit::Clubs; break;
    case 'H': result = Suit::Hearts; break;
    case 'S': result = Suit::Spades; break;
    case 'D': result = Suit::Diamonds; break;
    default: break;
  }
  return result;
}

int getRankIntPos(string theCard){
  int result = 0;
  char firstvalue = theCard[0];
  switch (firstvalue){
    case 'a':
    case 'A':
      result = 0; break;
    case '2':
      result = 1; break;
    case '3':
      result = 2; break;
    case '4':
      result = 3; break;
    case '5':
      result = 4; break;
    case '6':
      result = 5; break;
    case '7':
      result = 6; break;
    case '8':
      result = 7; break;
    case '9':
      result = 8; break;
    case '1':
      result = 9; break;
    case 'j':
    case 'J':
      result = 10; break;
    case 'q':
    case 'Q':
      result = 11; break;
    case 'k':
    case 'K':
      result = 12; break;
    default: break;
  }
  return result;
}

int getSuitIntPos(string theCard){
  int result = 0;
  char firstvalue = theCard[0];
  switch (firstvalue){
    case 'C': result = 3; break;
    case 'H': result = 1; break;
    case 'S': result = 2; break;
    case 'D': result = 0; break;
    default: break;
  }
  return result;
}

void goFishGUI_state::gameSetup(int numCards){
  // create deck //
  gameOver = false;
  Card currentCard;
  const vector<string> ranks {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
  const vector<string> suits {"Hearts", "Diamonds", "Clubs", "Spades"};

  for (auto suit : suits) {
      for (auto rank : ranks) {
          currentCard.suit = suit;
          currentCard.rank = rank;
          deck.push_back(currentCard);
      }
  }

  // to shuffle deck //
  random_device rd;
  mt19937 g(rd());
  shuffle(deck.begin(), deck.end(), g);

  // deal cards to player and comp//
  for (int i = 0; i < numCards; ++i) {
      cout << deck.back().rank << " " << deck.back().suit << endl;
      playerHand.push_back(deck.back());
      deck.pop_back();
      computerHand.push_back(deck.back());
      deck.pop_back();
  }
  // so computer has option to ask for cards //
  for(int i = 0; i < computerHand.size(); i++){
    possibleComputerAsks.push_back((computerHand.at(i)).rank);
  }

  message += " after deck init ";
  hasHandUpdated = true;

}

bool sortCardHandBySuit(const Card& lhs, const Card& rhs) {
    Suit suitOfCurrentCard = ConvertStringToSuit(lhs.suit);
    Suit suitOfNextCard = ConvertStringToSuit(rhs.suit);
    return static_cast<int>(suitOfCurrentCard) < static_cast<int>(suitOfNextCard);
}

void goFishGUI_state::sortCardHand(){
  sort(playerHand.begin(), playerHand.end(), sortCardHandBySuit);
  for(int i = 0; i <  playerHand.size(); i++){
    for(int j = 0; j <  playerHand.size() - 1; j++){
      Rank rankOfCurrentCard = convertStringToRank( playerHand.at(i).rank);
      Rank rankOfNextCard = convertStringToRank( playerHand.at(j).rank);
      if(static_cast<int>(rankOfCurrentCard) < static_cast<int>(rankOfNextCard)){
        swap(playerHand.at(i),  playerHand.at(j));
      } // end if
    } // end for j
  } // end for i
  hasHandUpdated = true;
}

bool goFishGUI_state::checkCardInHand(int playerTurn, string cardAskedFor){
  bool haveCard = false;
  if(playerTurn == player){
    for(int i = 0; i < playerHand.size(); i++){
      if(cardAskedFor == (playerHand.at(i)).rank){
        haveCard = true;
        break;
      }
    }
  } else {
      for(int i = 0; i < computerHand.size(); i++){
        if(cardAskedFor == (computerHand.at(i)).rank){
          haveCard = true;
          break;
        }
      }
  }
  return haveCard;
}

bool goFishGUI_state::askForCard(int playerAsking, int opponent){
  bool result = true;
  if(playerAsking == player){
    for(int i = 0; i < computerHand.size(); i++){
      if(cardAskedFor == computerHand.at(i).rank){
         playerHand.push_back(computerHand.at(i));
         cout << "Opponent has card" << endl;
         computerHand.erase(computerHand.begin() + i,  computerHand.begin() + i + 1);

        result = false;
      }
    }
  } else {
    for(int i = 0; i < playerHand.size(); i++){
      if(cardAskedFor == playerHand.at(i).rank){
         computerHand.push_back(playerHand.at(i));
         cout << "Opponent has card" << endl;
         playerHand.erase(playerHand.begin() + i,  playerHand.begin() + i + 1);
        result = false;
      }
    }
  }
  return result;
}

bool goFishGUI_state::goFish(int playerGF, string cardAskedFor){
  bool match = false;
  if(deck.back().rank == cardAskedFor){
    match = true;
  }

  if(playerGF == player){
    playerHand.push_back(deck.back());
    deck.pop_back();
  } else{
    computerHand.push_back(deck.back());
    deck.pop_back();
  }

  numCardsLeft--;

  return match;
}

bool goFishGUI_state::checkForBook(int playerCheckingBook, string cardAskedFor){
  bool result = false;
  int numOfCard = 0;
  if(playerCheckingBook == player){
    for(int i = 0; i < playerHand.size(); i++){
      if(cardAskedFor == (playerHand.at(i)).rank){
        numOfCard++;
      }
    }
  } else{
    for(int i = 0; i < computerHand.size(); i++){
      if(cardAskedFor == (computerHand.at(i)).rank){
        numOfCard++;
      }
    }
  }
  if(numOfCard == 4){
    result = true;
  }
  return result;
}

void goFishGUI_state::removeBookFromHand(int playerHasBook, string cardToBeRemoved){
  if(playerHasBook == player){
    int numCards = playerHand.size();
    for(int i = 0; i < numCards; i++){
      if(cardToBeRemoved == playerHand.at(i).rank){
        playerHand.erase(playerHand.begin() + i, playerHand.begin() + i + 1);
        i -= 1;
        numCards -= 1;
      } // end if
    } // end for
    playerBooks++;
  } else {
    int numCards = computerHand.size();
    for(int i = 0; i < numCards; i++){
      if(cardToBeRemoved == computerHand.at(i).rank){
        computerHand.erase(computerHand.begin() + i, computerHand.begin() + i + 1);
        i -= 1;
        numCards -= 1;
      } // end if
    } // end for
      compBooks++;
    }
}

void goFishGUI_state::takeTurn(int whosTurn, bool& playerTurn, bool& computerTurn){
  fshCardMatch = false;
  gofsh = false;
  haveCard = false;
  string cardAskedFor;
  int opponent, cardAskedForLoc;

  if(whosTurn == player){
    opponent = comp;
    cout << "Card rank being asked for: ";
    cin >> cardAskedFor;

    haveCard = checkCardInHand(player, cardAskedFor);

    if(!haveCard){
      cout << "Must have card being asked for, try again" << endl;
      cout << "Card rank being asked for: ";
      cin >> cardAskedFor;
      haveCard = checkCardInHand(player, cardAskedFor);
    }
  } else {
    opponent = player;
    cardAskedForLoc = rand() % computerHand.size();
    haveCard = checkCardInHand(comp, computerHand.at(cardAskedForLoc).rank);
    cardAskedFor = computerHand.at(cardAskedForLoc).rank;
    cout << "computer asks for " << cardAskedFor << endl;
  }

  gofsh = askForCard(whosTurn, opponent);

  if(checkForBook(player, cardAskedFor) && whosTurn == player){
      removeBookFromHand(player, cardAskedFor);
      cout << "Player got a book" << endl;
  } else if(checkForBook(comp, cardAskedFor) && whosTurn == comp){
        removeBookFromHand(comp, cardAskedFor);
        cout << "computer got a book" << endl;
  }

  if(gofsh){
    cout << "Go Fish" << endl;
    fshCardMatch = goFish(whosTurn, cardAskedFor);
    if(!fshCardMatch && whosTurn == player){
      cout << "Did not draw matching card" << endl;
      playerTurn = false;
      computerTurn = true;
    } else if (!fshCardMatch && whosTurn == comp){
        cout << "Did not draw matching card" << endl;
        playerTurn = true;
        computerTurn = false;
    } else {
      cout << "Drew matching card, go again" << endl;
    }
  }

  if(checkForBook(whosTurn, playerHand.back().rank) && whosTurn == player){
      removeBookFromHand(whosTurn, playerHand.back().rank);
      cout << "Player got a book" << endl;
  } else if(checkForBook(whosTurn, computerHand.back().rank) && whosTurn == comp){
        removeBookFromHand(whosTurn, computerHand.back().rank);
        cout << "computer got a book" << endl;
  }

  sortCardHand();

  if(rand() % 100 > 25 && whosTurn == player){ // for computer ai, will remember the card being asked for 75% of the time
    possibleComputerAsks.push_back(cardAskedFor);
  }

  // case if player or computer hand is empty but the go fish pile isn't empty
  if(playerHand.empty() && numCardsLeft > 0){
    playerHand.push_back(deck.back());
    deck.pop_back();
    numCardsLeft--;
  }

  if(computerHand.empty() && numCardsLeft > 0){
    computerHand.push_back(deck.back());
    deck.pop_back();
    numCardsLeft--;
  }

}

void goFishGUI_state::checkGameOver(){
  if( playerHand.empty() || computerHand.empty() || numCardsLeft == 0 || playerBooks >= 7 || compBooks >= 7){
    gameOver = true;
  }
}

goFishGUI_state::goFishGUI_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, TTF_Font *font) : state(rend, win, s, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */
     SDL_initFramerate(&fps);

     srand(time(nullptr));

     gt = IMG_Load("GameTable.png");
     tgt = SDL_CreateTextureFromSurface(rend, gt);
     SDL_FreeSurface(gt);
     gt = nullptr;

     o = IMG_Load("Overlay.png");
     to = SDL_CreateTextureFromSurface(rend, o);
     SDL_FreeSurface(o);
     o = nullptr;

     doc = IMG_Load("Deckofcards.png");

     //card.x = 0;
     //card.y = 0;
     CARDWIDTH = doc->w / 13;
     CARDHEIGHT = doc->h / 4;

     tdoc = SDL_CreateTextureFromSurface(rend, doc);
     SDL_FreeSurface(doc);
     doc = nullptr;
}

goFishGUI_state::~goFishGUI_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */

     deck.clear();
     playerHand.clear();
     computerHand.clear();
     possibleComputerAsks.clear();

     SDL_DestroyTexture(tgt);
     tgt = nullptr;

     SDL_DestroyTexture(to);
     to = nullptr;

     SDL_DestroyTexture(tdoc);
     tdoc = nullptr;

     IMG_Quit();
}

bool goFishGUI_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */
    gameSetup(7);
    return true;
}

bool goFishGUI_state::leave() {
    /*
     * Called whenever we are transitioning out of this state.
     */

   deck.clear();
   playerHand.clear();
   computerHand.clear();
   possibleComputerAsks.clear();

   return true;
}

bool goFishGUI_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */

     SDL_GetMouseState(&MouseX, &MouseY);

     // go fish code workings //

/*

     char playAgain;
     bool restart;

     if(compBooks < playerBooks){
       cout << "Player wins! Go again? Y/N" << endl;
     } else if (playerBooks < compBooks){
       cout << "Computer wins! try again? Y/N" << endl;
     } else {
       cout << "its a draw, try again? Y/N" << endl;
     }
     cin >> playAgain;

     switch(playAgain){
       case 'N':
       case 'n':
         restart = false;
         break;
       case 'Y':
       case 'y':
         restart = true;
         break;
       default:
         cout << "Not understood try again";
     }
*/

    sortCardHand();
/*
    while(!gameOver){// while loop for game
      while(playerTurn && !gameOver){    // while loop for player turn
        takeTurn(player, playerTurn, computerTurn);
        checkGameOver();
        sortCardHand(); // to update player hand with new card
      } // endl while for player turn
      while(computerTurn && !gameOver){ // while loop for computer turn
        takeTurn(comp, playerTurn, computerTurn);
        checkGameOver();
        sortCardHand(); // to update player hand with computer taken cards
      }  // endl comp turn while loop
    } // end game while loop
*/
    //while(!gameOver){
        if(hasHandUpdated || messageUpdated){
          SDL_RenderClear(rend);
          SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
          SDL_RenderCopy(rend, tgt, nullptr, &imageRect); // display game image

          cardsOnScreen.clear();
          for(int i = 0; i <  playerHand.size(); i++){
             modRank = getRankIntPos(playerHand.at(i).rank);
             suitRank = getSuitIntPos(playerHand.at(i).suit);
             if(i > 0){
               if(playerHand.at(i).rank == playerHand.at(i-1).rank){
                 space = (cardsOnScreen.at(i-1).x) + 40;
               } else {
                 space += 100;
               }
             } else {
               space = (w/10);
             }
             SDL_Rect card {(modRank*CARDWIDTH), (suitRank*CARDHEIGHT), CARDWIDTH, CARDHEIGHT};
             SDL_Rect placeOnScreen {space, ((h-h/3) - 55), 100, 125};
             cardsOnScreen.push_back(placeOnScreen);
             cardRanksOnScreen[i] = playerHand.at(i).rank;
             SDL_RenderCopy(rend, tdoc, &card, &placeOnScreen); // display card image
          } // end for

          stringColor(rend, textX, textY, message.c_str(), 0xffffffff);
          SDL_RenderPresent(rend);
          hasHandUpdated = false;
          messageUpdated = false;
        }
      //}


      return true;


}

bool goFishGUI_state::handle_event(const SDL_Event &e) {
    /*
     * Remember to set the result to true if your state ends up
     * handling whatever this event is.  If not, the event may be
     * handled by the state framework.  In the case of an SDL_Quit
     * event, that means it will exit the app.
     */
    bool result = false;

    switch(e.type) {
      case SDL_KEYDOWN:
          switch(e.key.keysym.sym) {
          //case SDLK_SPACE:  transition("mainArea"); result = true;   break;
          default:  break;
        } break;
      case SDL_MOUSEBUTTONDOWN:
        switch (e.button.button){
  			     case SDL_BUTTON_LEFT:
                message = "click";
                // make rects in drawing loop add to a vector
                // loop through checking if mouse is colliding with any of the rects
                // display message with rank of rect being hovered over, ignore if not on a rect
                for(int i = 0; i < cardsOnScreen.size(); i++){
                  if(checkCollision(MouseX, MouseY, cardsOnScreen.at(i))){
                    message += " on card ";
                    message += cardRanksOnScreen[i];
                    messageUpdated = true;
                  }
                }
                messageUpdated = true;
                result = true;
                break;
  		  } break;
    default:  break;
    }

    return result;
}
