void gameSetup(int numCards){
      // create deck //
      gameOver = false;
      Card currentCard;
      const vector<string> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
      const vector<string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};

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

      // deal cards //
      for (int i = 0; i < numCards; ++i) {
          playerHands[player].push_back(deck.back());
          deck.pop_back();
          playerHands[comp].push_back(deck.back());
          deck.pop_back();
      }
}
