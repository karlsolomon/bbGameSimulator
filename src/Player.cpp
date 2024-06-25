module;
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <functional>
#include <random>
#include <string>
#include <vector>

/*#include "action.h"*/
import action;
export module Player;

export class Player {
 private:
    int atBats;
    int singles;
    int doubles;
    int triples;
    int homeRuns;
    int walks;
    int outs;

    double pCumSingle;
    double pCumDouble;
    double pCumTriple;
    double pCumHomeRun;
    double pCumWalk;
    double pCumOut;

    void calculateCumulativeProbabilities();

 public:
    std::string name;
    explicit Player(std::vector<std::string>&);
    auto getRandomAction() -> action_e;
};

/*using std::bind;*/

void Player::calculateCumulativeProbabilities() {
    assert(atBats == (singles + doubles + triples + homeRuns + walks + outs));
    pCumOut = static_cast<double>(outs) / static_cast<double>(atBats);
    pCumWalk = pCumOut + (static_cast<double>(walks) / static_cast<double>(atBats));
    pCumSingle = pCumWalk + (static_cast<double>(singles) / static_cast<double>(atBats));
    pCumDouble = pCumSingle + (static_cast<double>(doubles) / static_cast<double>(atBats));
    pCumTriple = pCumDouble + (static_cast<double>(triples) / static_cast<double>(atBats));
    pCumHomeRun = pCumTriple + (static_cast<double>(homeRuns) / static_cast<double>(atBats));
}

Player::Player(std::vector<std::string>& stats) {
    this->name = stats[0];
    this->atBats = std::stoi(stats[1]);
    this->singles = std::stoi(stats[2]);
    this->doubles = std::stoi(stats[3]);
    this->triples = std::stoi(stats[4]);
    this->homeRuns = std::stoi(stats[5]);
    this->walks = std::stoi(stats[6]);
    this->outs = std::stoi(stats[7]);
    calculateCumulativeProbabilities();
}
auto Player::getRandomAction() -> action_e {
    action_e res = ACTION_COUNT;
    static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(seed);
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static auto rng = bind(distribution, generator);

    double p = rng();
    if (p < pCumOut) {
        res = ACTION_OUT;
    } else if (p < pCumWalk) {
        res = ACTION_WALK;
    } else if (p < pCumSingle) {
        res = ACTION_SINGLE;
    } else if (p < pCumDouble) {
        res = ACTION_DOUBLE;
    } else if (p < pCumTriple) {
        res = ACTION_TRIPLE;
    } else if (p < pCumHomeRun) {
        res = ACTION_HR;
    } else {
        res = ACTION_COUNT;  // shouldn't happen
    }
    return res;
}
