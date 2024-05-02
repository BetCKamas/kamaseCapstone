
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>
#include <time.h>

#include <SDL.h>

#include "goFishGUI.h"
#include "state.h"

using namespace std;

bool hasHandUpdated = false;
bool messageUpdated = false;
bool booksUpdated = false;
bool askedForCard = false;

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

void goFishGUI_state::sortCardHand(){
  Suit suitOfNextCard, suitOfCurrentCard;
  Rank rankOfCurrentCard, rankOfNextCard ;

  for(int i = 0; i <  playerHand.size(); i++){
    for(int j = 0; j <  playerHand.size() - 1; j++){
      rankOfCurrentCard = convertStringToRank( playerHand.at(i).rank);
      rankOfNextCard = convertStringToRank( playerHand.at(j).rank);
      if(static_cast<int>(rankOfCurrentCard) < static_cast<int>(rankOfNextCard)){
        swap(playerHand.at(i),  playerHand.at(j));
      } // end if
    } // end for j
  } // end for i

  for(int i = 0; i <  playerHand.size(); i++){
    for(int j = 0; j <  playerHand.size() - 1; j++){
      suitOfCurrentCard = ConvertStringToSuit(playerHand.at(i).suit);
      suitOfNextCard = ConvertStringToSuit(playerHand.at(j).suit);
      rankOfCurrentCard = convertStringToRank( playerHand.at(i).rank);
      rankOfNextCard = convertStringToRank( playerHand.at(j).rank);
      if(static_cast<int>(suitOfCurrentCard) < static_cast<int>(suitOfNextCard)
        && rankOfCurrentCard == rankOfNextCard){
        swap(playerHand.at(i),  playerHand.at(j));
      }
    }
  }

  hasHandUpdated = true;
}

void goFishGUI_state::gameSetup(int numCards){
  // create deck //
  gameOver = false;
  Card currentCard;
  const vector<string> ranks {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
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
      //cout << deck.back().rank << " " << deck.back().suit << endl;
      playerHand.push_back(deck.back());
      deck.pop_back();
      computerHand.push_back(deck.back());
      deck.pop_back();
  }
  // so computer has option to ask for cards //
  for(int i = 0; i < computerHand.size(); i++){
    possibleComputerAsks.push_back((computerHand.at(i)).rank);
  }

  //message += " after deck init ";
  sortCardHand();
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
         computerHand.erase(computerHand.begin() + i,  computerHand.begin() + i + 1);
         i--;
         result = false;
      }
    }
  } else {
    for(int i = 0; i < playerHand.size(); i++){
      if(cardAskedFor == playerHand.at(i).rank){
         computerHand.push_back(playerHand.at(i));
         playerHand.erase(playerHand.begin() + i,  playerHand.begin() + i + 1);
         i--;
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
    cardGotFromGoFishing = deck.back().rank;
    playerHand.push_back(deck.back());
    sortCardHand();
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

void goFishGUI_state::takeTurn(){

  int opponent, cardAskedForLoc;

  if(playerTurn && !gameOver){
      fshCardMatch = false;
      gofsh = false;
      haveCard = false;
      opponent = comp;

      gofsh = askForCard(player, opponent);
      sortCardHand();

      if(gofsh){
        message = goFishResponse[rand()%3];
        textColor = goatmanC;
        messageUpdated = true;
        draw();
        SDL_Delay(1500);
        fshCardMatch = goFish(player, cardAskedFor);
        if(!fshCardMatch){
          playerTurn = false;
          computerTurn = true;
        } else {
          message = "Got a match!";
          messageUpdated = true;
          textColor = mothmanC;
          draw();
          SDL_Delay(1500);
        }
      } else {
        message = "Here you go.";
        textColor = goatmanC;
        draw();
        SDL_Delay(1500);

        if(checkForBook(player, cardAskedFor)){
             SDL_Delay(1500);
             removeBookFromHand(player, cardAskedFor);
             message = bookRemarks[rand()%3];
             messageUpdated = true;
             textColor = mothmanC;
             draw();
             SDL_Delay(1500);
        }
      }

      if(checkForBook(player, cardGotFromGoFishing)){
          SDL_Delay(1500);
          removeBookFromHand(player, cardGotFromGoFishing);
          message = bookRemarks[rand()%3];
          textColor = mothmanC;
          messageUpdated = true;
          draw();
          SDL_Delay(1500);
      }

      if(rand() % 100 > 25){ // for computer ai, will remember the card being asked for 75% of the time
        possibleComputerAsks.push_back(cardAskedFor);
      }

      // case if player or computer hand is empty but the go fish pile isn't empty
      if(playerHand.empty() && numCardsLeft > 0){
        playerHand.push_back(deck.back());
        deck.pop_back();
        numCardsLeft--;
        hasHandUpdated = true;
        sortCardHand();
        draw();
        SDL_Delay(1500);
      }

      checkGameOver();

  }
  while(computerTurn && !gameOver){
      fshCardMatch = false;
      gofsh = false;
      haveCard = false;
      opponent = player;
      cardAskedForLoc = rand() % computerHand.size();
      haveCard = checkCardInHand(comp, computerHand.at(cardAskedForLoc).rank);
      cardAskedFor = computerHand.at(cardAskedForLoc).rank;
      message =  waysToAsk[rand() % 3];
      message += cardAskedFor;
      message += "'s?";
      messageUpdated = true;
      textColor = goatmanC;
      draw();
      SDL_Delay(1500);

      gofsh = askForCard(comp, opponent);

      if(gofsh){
        message = goFishResponse[rand()%3];
        messageUpdated = true;
        textColor = mothmanC;
        draw();
        SDL_Delay(1500);
        fshCardMatch = goFish(comp, cardAskedFor);
        if (!fshCardMatch){
            playerTurn = true;
            computerTurn = false;
        } else {
          message = "Got a match!";
          messageUpdated = true;
          textColor = goatmanC;
          draw();
          SDL_Delay(1500);
        }
      } else {
        textColor = mothmanC;
        message = "Here you go.";
        messageUpdated = true;
        draw();
        SDL_Delay(1500);

        if(checkForBook(comp, cardAskedFor)){
              removeBookFromHand(comp, cardAskedFor);
              message = bookRemarks[rand()%3];
              messageUpdated = true;
              textColor = goatmanC;
              draw();
              SDL_Delay(1500);
        }
      }

      if(checkForBook(comp, computerHand.back().rank)){
          removeBookFromHand(comp, computerHand.back().rank);
          message = bookRemarks[rand()%3];
          messageUpdated = true;
          textColor = goatmanC;
          draw();
          SDL_Delay(1500);
      }

      if(computerHand.empty() && numCardsLeft > 0){
        computerHand.push_back(deck.back());
        deck.pop_back();
        numCardsLeft--;
      }

      checkGameOver();

  }

}

void goFishGUI_state::checkGameOver(){
  if( playerHand.empty() || computerHand.empty() || numCardsLeft == 0 || playerBooks >= 7 || compBooks >= 7){
    //message = "game over";
    //messageUpdated = true;
    draw();
    SDL_Delay(1500);
    gameOver = true;
    if(playerBooks > compBooks){
      winnerGoFish = 'p';
    } else if(playerBooks < compBooks){
      winnerGoFish = 'c';
    } else {
      winnerGoFish = 't';
    }
    //cout << winnerGoFish << endl;
  }

}

goFishGUI_state::goFishGUI_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */
     //SDL_initFramerate(&fps);

     //srand(time(nullptr));

     gt = IMG_Load("./gameImages/GameTable.png");
     tgt = SDL_CreateTextureFromSurface(rend, gt);
     SDL_FreeSurface(gt);
     gt = nullptr;

     doc = IMG_Load("./gameImages/Deckofcards.png");
     CARDWIDTH = doc->w / 13;
     CARDHEIGHT = doc->h / 4;
     tdoc = SDL_CreateTextureFromSurface(rend, doc);
     SDL_FreeSurface(doc);
     doc = nullptr;

     pb = IMG_Load("./gameImages/playerBooks.png");
     PLAYERBOOKWIDTH = pb->w / 7;
     PLAYERBOOKHEIGHT = pb->h;
     tpb = SDL_CreateTextureFromSurface(rend, pb);
     SDL_FreeSurface(pb);
     pb = nullptr;

     cb = IMG_Load("./gameImages/computerBooks.png");
     COMPUTERBOOKWIDTH = cb->w / 7;
     COMPUTERBOOKHEIGHT = cb->h;
     tcb = SDL_CreateTextureFromSurface(rend, cb);
     SDL_FreeSurface(cb);
     cb = nullptr;

     gameOver = false;
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

     SDL_DestroyTexture(tdoc);
     tdoc = nullptr;

     SDL_DestroyTexture(tpb);
     tpb = nullptr;

     SDL_DestroyTexture(tcb);
     tcb = nullptr;

     IMG_Quit();
}

bool goFishGUI_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */

     for(int i = 67; i > 0; i--){
         //cout << "alpha" << endl;
         SDL_RenderClear(rend);
         SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
         SDL_RenderCopy(rend, tgt, nullptr, &imageRect); // display game image
         Uint8 a =  Uint8(i*2);
         SDL_SetSurfaceBlendMode(rectSurface, SDL_BLENDMODE_BLEND);
         SDL_SetSurfaceAlphaMod(rectSurface, a);
         SDL_FillRect(rectSurface, NULL, SDL_MapRGBA(rectSurface->format, 0, 0, 0, a));
         rectTexture[i] = SDL_CreateTextureFromSurface(rend, rectSurface);
         SDL_RenderCopy(rend, rectTexture[i], NULL, &imageRect);
         SDL_RenderPresent(rend);
         SDL_Delay(5);
         SDL_SetSurfaceBlendMode(rectSurface, SDL_BLENDMODE_NONE);
         SDL_DestroyTexture(rectTexture[i]);
     }

    playerBooks = 0;
    compBooks = 0;

    message = "You can go first Investagator";
    textColor = goatmanC;
    gameOver = false;
    winnerGoFish = '\0';
    numCardsLeft = 38;

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
   cardsOnScreen.clear();

   booksUpdated = false;
   hasHandUpdated = false;
   messageUpdated = false;
   gameOver = true;
   message = "";

   for(int i = 0; i < 67; i++){
       Uint8 a =  Uint8(i*2);
       SDL_SetSurfaceBlendMode(rectSurface, SDL_BLENDMODE_BLEND);
       SDL_SetSurfaceAlphaMod(rectSurface, a);
       SDL_FillRect(rectSurface, NULL, SDL_MapRGBA(rectSurface->format, 0, 0, 0, a));
       rectTexture[i] = SDL_CreateTextureFromSurface(rend, rectSurface);
       SDL_RenderCopy(rend, rectTexture[i], NULL, &imageRect);
       SDL_RenderPresent(rend);
       SDL_Delay(5);
       SDL_SetSurfaceBlendMode(rectSurface, SDL_BLENDMODE_NONE);
       SDL_DestroyTexture(rectTexture[i]);
   }

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
      if(!gameOver){
        if(hasHandUpdated || messageUpdated || booksUpdated){
          SDL_RenderClear(rend);
          SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
          SDL_RenderCopy(rend, tgt, nullptr, &imageRect); // display game image

          SDL_Rect playerBooksScreen {0, 0, PLAYERBOOKWIDTH, PLAYERBOOKHEIGHT}; // the rect showing the books
          SDL_Rect playerBooksShown {imageRect.x+145, imageRect.y+325, 0, PLAYERBOOKHEIGHT}; // the rect position being displayed on screen

          switch(playerBooks){
            case 7:
                playerBooksShown.w =  PLAYERBOOKWIDTH*7;
                playerBooksScreen.w =  PLAYERBOOKWIDTH*7;
                break;
            case 6:
                playerBooksShown.w =  PLAYERBOOKWIDTH*6;
                playerBooksScreen.w =  PLAYERBOOKWIDTH*6;
                break;
            case 5:
                playerBooksShown.w =  PLAYERBOOKWIDTH*5;
                playerBooksScreen.w =  PLAYERBOOKWIDTH*5;
                break;
            case 4:
                playerBooksShown.w =  PLAYERBOOKWIDTH*4;
                playerBooksScreen.w =  PLAYERBOOKWIDTH*4;
                break;
            case 3:
                playerBooksShown.w =  PLAYERBOOKWIDTH*3;
                playerBooksScreen.w =  PLAYERBOOKWIDTH*3;
                break;
            case 2:
                playerBooksShown.w =  PLAYERBOOKWIDTH*2;
                playerBooksScreen.w =  PLAYERBOOKWIDTH*2;
                break;
            case 1:
                playerBooksShown.w =  PLAYERBOOKWIDTH;
                break;
            default: break;
          }

          SDL_RenderCopy(rend, tpb, &playerBooksScreen, &playerBooksShown);

          SDL_Rect computerBooksScreen {COMPUTERBOOKWIDTH*6, 0, COMPUTERBOOKWIDTH, COMPUTERBOOKHEIGHT}; // the rect showing the books
          SDL_Rect computerBooksShown {imageRect.x+816, imageRect.y+25, 0, COMPUTERBOOKHEIGHT}; // the rect position being displayed on screen

          switch(compBooks){
            case 7:
                computerBooksShown.w =  COMPUTERBOOKWIDTH*7;
                computerBooksScreen.w =  COMPUTERBOOKWIDTH*7;
                computerBooksShown.x = computerBooksShown.x - (COMPUTERBOOKWIDTH*6);
                computerBooksScreen.x =  computerBooksScreen.x - (COMPUTERBOOKWIDTH*6);
                break;
            case 6:
                computerBooksShown.w =  COMPUTERBOOKWIDTH*6;
                computerBooksScreen.w =  COMPUTERBOOKWIDTH*6;
                computerBooksShown.x = computerBooksShown.x - (COMPUTERBOOKWIDTH*5);
                computerBooksScreen.x =  computerBooksScreen.x - (COMPUTERBOOKWIDTH*5);
                break;
            case 5:
                computerBooksShown.w =  COMPUTERBOOKWIDTH*5;
                computerBooksScreen.w =  COMPUTERBOOKWIDTH*5;
                computerBooksShown.x = computerBooksShown.x - (COMPUTERBOOKWIDTH*4);
                computerBooksScreen.x =  computerBooksScreen.x - (COMPUTERBOOKWIDTH*4);
                break;
            case 4:
                computerBooksShown.w =  COMPUTERBOOKWIDTH*4;
                computerBooksScreen.w =  COMPUTERBOOKWIDTH*4;
                computerBooksShown.x = computerBooksShown.x - (COMPUTERBOOKWIDTH*3);
                computerBooksScreen.x =  computerBooksScreen.x - (COMPUTERBOOKWIDTH*3);
                break;
            case 3:
                computerBooksShown.w =  COMPUTERBOOKWIDTH*3;
                computerBooksScreen.w =  COMPUTERBOOKWIDTH*3;
                computerBooksShown.x = computerBooksShown.x - (COMPUTERBOOKWIDTH*2);
                computerBooksScreen.x =  computerBooksScreen.x - (COMPUTERBOOKWIDTH*2);
                break;
            case 2:
                computerBooksShown.w =  COMPUTERBOOKWIDTH*2;
                computerBooksScreen.w =  COMPUTERBOOKWIDTH*2;
                computerBooksShown.x = computerBooksShown.x - (COMPUTERBOOKWIDTH);
                computerBooksScreen.x =  computerBooksScreen.x - (COMPUTERBOOKWIDTH);
                break;
            case 1:
                computerBooksShown.w =  COMPUTERBOOKWIDTH;
                break;
            default: break;
          }

          SDL_RenderCopy(rend, tcb, &computerBooksScreen, &computerBooksShown);


          cardsOnScreen.clear();
          for(int i = 0; i <  playerHand.size(); i++){
             modRank = getRankIntPos(playerHand.at(i).rank);
             suitRank = getSuitIntPos(playerHand.at(i).suit);
             if(i > 0){
               if(playerHand.at(i).rank == playerHand.at(i-1).rank){
                 space = (cardsOnScreen.at(i-1).x) + 25;
               } else {
                 space += 80;
               }
             } else {
               space = (w/10) - 25;
             }
             SDL_Rect card {(modRank*CARDWIDTH), (suitRank*CARDHEIGHT), CARDWIDTH, CARDHEIGHT};
             SDL_Rect placeOnScreen {space, ((h-h/3) - 55), 100, 125};
             cardsOnScreen.push_back(placeOnScreen);
             cardRanksOnScreen[i] = playerHand.at(i).rank;
             SDL_RenderCopy(rend, tdoc, &card, &placeOnScreen); // display card image
          } // end for

          stringColor(rend, textX, textY, message.c_str(), textColor);
          SDL_RenderPresent(rend);
          hasHandUpdated = false;
          messageUpdated = false;
        }
      } else {
        transition("resultGoFish");
      }

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
          case SDLK_SPACE:  transition("resultGoFish"); result = true;   break;
          default:  break;
        } break;
      case SDL_MOUSEBUTTONDOWN:
        switch (e.button.button){
  			     case SDL_BUTTON_LEFT:
                // make rects in drawing loop add to a vector
                // loop through checking if mouse is colliding with any of the rects
                // display message with rank of rect being hovered over, ignore if not on a rect
                for(int i = 0; i < cardsOnScreen.size(); i++){
                  if(checkCollision(MouseX, MouseY, cardsOnScreen.at(i))){
                    cardAskedFor = cardRanksOnScreen[i];
                    cardAskedForLoc = i;
                    askedForCard = true;
                    playerTurn = true;
                  }
                }
                if(askedForCard){
                  message = waysToAsk[rand() % 3];
                  message += cardRanksOnScreen[cardAskedForLoc];
                  message += "'s?";
                  messageUpdated = true;
                  textColor = mothmanC;
                  draw();
                  SDL_Delay(1500);
                  takeTurn();
                  askedForCard = false;
                }
                checkGameOver();
                result = true;
                break;
  		  } break;
    default:  break;
    }

    SDL_FlushEvents(SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONDOWN + 1);

    return result;
}
