export module GameState;
import Bases;
export class GameState {
 private:
    int player;
    int inning;
    int outs;
    int runs;
    bool over;
    Bases bases;
    std::vector<Player> players;

    void recordOut() {
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

    void recordAction(action_e action) {
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
        player++;
        player %= NUM_PLAYERS;
        runs += bases.getNumRuns();
        bases.clearRunnersWhoScored();
    }

 public:
    static const int NUM_PLAYERS = 9;
    static const int NUM_INNINGS = 9;
    static const int OUTS_PER_INNING = 3;

    export GameState(std::vector<Player>& players) : players(players) {
        this->runs = 0;
        this->inning = 0;
        this->outs = 0;
        this->over = false;
        this->bases = Bases();
    }
    export int playGameGetRuns() {
        Player p;
        while (!this->over) {
            p = players[player];
            recordAction(p.getRandomAction());
        }
        return getRuns();
    }
};
