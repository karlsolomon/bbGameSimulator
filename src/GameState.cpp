module;
#include <vector>
import action;
import Bases;
import Player;
export module GameState;
export class GameState {
 private:
    int player;
    int inning;
    int outs;
    int runs;
    bool over;
    Bases bases;
    std::vector<Player> players;
    void recordOut();
    void recordAction(action_e);

 public:
    static const int NUM_PLAYERS = 9;
    static const int NUM_INNINGS = 9;
    static const int OUTS_PER_INNING = 3;
    explicit GameState(std::vector<Player>&);
    auto playGameGetRunsAtBats() -> std::pair<int, int>;
};

void GameState::recordOut() {
    outs++;
    outs %= OUTS_PER_INNING;
    if (outs == 0) {
        inning++;
        bases.endOfInning();
    }
    if (inning == NUM_INNINGS) {
        over = true;
    }
}

void GameState::recordAction(action_e action) {
    int numBases = 0;
    switch (action) {
        case ACTION_OUT:
            recordOut();
            break;
        case ACTION_WALK:
            bases.walk();
            break;
        case ACTION_HR:
            numBases++;
        case ACTION_TRIPLE:
            numBases++;
        case ACTION_DOUBLE:
            numBases++;
        case ACTION_SINGLE:
            numBases++;
            bases.advance(numBases);
            break;
        default:
            break;
    }
    runs += bases.getNumRuns();
    bases.clearRunnersWhoScored();
}
GameState::GameState(std::vector<Player>& players) : players(players) {
    this->runs = 0;
    this->inning = 0;
    this->outs = 0;
    this->player = 0;
    this->over = false;
}
auto GameState::playGameGetRunsAtBats() -> std::pair<int, int> {
    std::pair<int, int> res;
    while (!this->over) {
        Player p = players[(player % GameState::NUM_PLAYERS)];
        player++;
        recordAction(p.getRandomAction());
    }
    res.first = this->runs;
    res.second = this->player;
    this->inning = 0;
    this->outs = 0;
    this->player = 0;
    this->over = false;
    this->runs = 0;
    return res;
}
