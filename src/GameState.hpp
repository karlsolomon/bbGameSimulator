#include <vector>

#include "Bases.hpp"
#include "Player.hpp"
class GameState {
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
