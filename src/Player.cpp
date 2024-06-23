#include <cstdlib>
export module Player;
import action;
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

    void calculateCumulativeProbabilities() {
        ASSERT(atBats == (singles + doubles + triples + homeRuns + walks + outs));
        pCumOut = static_cast<double>(outs) / static_cast<double>(atBats);
        pCumWalk = pCumOut + (static_cast<double>(walk) / static_cast<double>(atBats));
        pCumSingle = pCumWalk + (static_cast<double>(singles) / static_cast<double>(atBats));
        pCumDouble = pCumSingle + (static_cast<double>(doubles) / static_cast<double>(atBats));
        pCumTriple = pCumDouble + (static_cast<double>(triples) / static_cast<double>(atBats));
        pCumHomeRun = pCumTriple + (static_cast<double>(homeRuns) / static_cast<double>(atBats));
    }

 public:
    export Player(int atBats, int singles, int doubles, int triples, int homeRuns, int walks, int outs) {
        this->atBats = atBats;
        this->singles = singles;
        this->doubles = doubles;
        this->triples = triples;
        this->homeRuns = homeRuns;
        this->walks = walks;
        this->outs = outs;
        calculateCumulativeProbabilities();
    }
    export action_e getRandomAction() {
        action_e res = ACTION_COUNT;
        double p = static_cast<double>(std::rand()) / 100.0;
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
        } else if (p < pCumHR) {
            res = ACTION_HR;
        } else {
            res = ACTION_COUNT;  // shouldn't happen
        }
        return res;
    }
};
