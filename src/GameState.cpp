#include "GameState.hpp"

#include <print>
void GameState::recordOut() {
    // std::println("out!");
    outs++;
    outs %= OUTS_PER_INNING;
    if (outs == 0) {
        inning++;
        bases.endOfInning();
        // std::println("end of {}th", inning);
    }
    if (inning == NUM_INNINGS) {
        over = true;
        // std::println("end of game!");
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
            // std::println("{} base hit!", numBases);
            bases.advance(numBases);
            break;
        default:
            break;
    }
    runs += bases.getNumRuns();
    // std::println("{} runs scored", runs);
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
