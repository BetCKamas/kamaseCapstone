
#ifndef __GOFISHGUI_H__
#define __GOFISHGUI_H__

#include <vector>
#include <SDL.h>
#include <SDL2_framerate.h>

#include "state.h"

using namespace std;

const int player = 0;
const int comp = 1;

enum class Rank{
  Ace,
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King
};

enum class Suit{
  Clubs,
  Diamonds,
  Hearts,
  Spades
};

struct Card {
    string rank;
    string suit;
};

class goFishGUI_state : public state {
public:
    goFishGUI_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, TTF_Font *font);
    ~goFishGUI_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    Rank convertStringToRank(string theAsk);
    void gameSetup(int numCards);
    void sortCardHand();
    bool checkCardInHand(int playerTurn, string cardAskedFor);
    bool askForCard(int playerAsking, int opponent);
    bool goFish(int playerGF, string cardAskedFor);
    bool checkForBook(int playerCheckingBook, string cardAskedFor);
    void removeBookFromHand(int playerHasBook, string cardToBeRemoved);
    void takeTurn();
    void checkGameOver();

    vector<Card> deck;
    vector<Card> playerHand;
    vector<Card> computerHand;
    vector<string> possibleComputerAsks;
    vector<SDL_Rect> cardsOnScreen;
    string cardRanksOnScreen[52];

    SDL_Surface *gt = nullptr;
    SDL_Texture *tgt = nullptr;
    SDL_Surface *o = nullptr;
    SDL_Texture *to = nullptr;
    SDL_Surface *doc = nullptr;
    SDL_Texture *tdoc = nullptr;
    SDL_Surface *pb = nullptr;
    SDL_Texture *tpb = nullptr;
    SDL_Surface *cb = nullptr;
    SDL_Texture *tcb = nullptr;
    FPSmanager fps;

    bool gameOver = false;
    const int numPlayers = 2;
    const int numCardsPerPlayer = 7;
    const int numCardsTotal = 52;
    string cardAskedFor;
    bool haveCard, gofsh, fshCardMatch, book;
    bool playerTurn = true;
    bool computerTurn = false;
    int playerBooks = 0;
    int compBooks = 0;
    int cardAskedForLoc;
    int numCardsLeft = numCardsTotal - (numCardsPerPlayer * numPlayers);
    string cardGotFromGoFishing;

    int CARDWIDTH;
    int CARDHEIGHT;
    int PLAYERBOOKWIDTH;
    int PLAYERBOOKHEIGHT;
    int COMPUTERBOOKWIDTH;
    int COMPUTERBOOKHEIGHT;
    int modRank;
    int suitRank;
    int MouseX, MouseY;
    int space = 0;

    string waysToAsk[3] = {"Do you have any ", "Any ", "What about any "};
    string goFishResponse[3] = {"None, go fish.", "Nada, go fish.", "Go fish."};
    string bookRemarks[3] = {"Got one!", "I got a book!", "A book for me!"};

    Uint32 WHITE = 0xffffffff;
    Uint32 GREEN = 0xddbbffff;
    Uint32 textColor;

};

#endif  /* __GOFISHGUI_H__ */
