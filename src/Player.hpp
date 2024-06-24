#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>

#include "action.h"

class Player {
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
