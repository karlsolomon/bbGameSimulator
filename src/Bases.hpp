#include <cstdint>
class Bases {
 private:
    const uint8_t runMask = 0x78;  // [7] ignore, [6-3] runners who scored, [2-0] runners on bases 3-1
    uint8_t baseList;
    const int numBases = 3;

 public:
    Bases();
    void advance(int /*numBaseHit*/);
    void walk();
    [[nodiscard]] auto getNumRuns() const -> int;
    void clearRunnersWhoScored();
    void endOfInning();
};
