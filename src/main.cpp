import GameState;
import Player;
#include <numeric>
#include <vector>
#define NUM_GAMES 100
char* csvList = {"astros.csv", "fff.csv", "lbl.csv";
auto main() -> int {
    for (file : csvList) {
        // TODO: Read CSV
        std::vector<int> scores(NUM_GAMES);
        std::vector<player> players(Player::NUM_PLAYERS);

        GameState gs = GameState();
        for (int i = 0; i < NUM_GAMES; i++) {
            scores[i] = gs.playGameGetRuns();
        }

        // Do Avg/StDev
        template <typename T>
        T variance(const std::vector<T>& vec) {
            const size_t sz = vec.size();
            if (sz <= 1) {
                return 0.0;
            }

            // Calculate the mean
            const T mean = std::accumulate(scores.begin(), scores.end(), 0.0) / sz;

            // Now calculate the variance
            auto variance_func = [&mean, &sz](T accumulator, const T& val) {
                return accumulator + ((val - mean) * (val - mean) / (sz - 1));
            };

            auto variance = std::accumulate(scores.begin(), scores.end(), 0.0, variance_func);

            printf("%s, runs = %lf, variance = %lf\n", file, mean, variance););
        }

        return 0;
    }
