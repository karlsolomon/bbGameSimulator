module;
#include <cstdint>
export module Bases;
export class Bases {
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

Bases::Bases() : baseList(0) {}
void Bases::advance(int numBaseHit) {
    baseList <<= numBaseHit;              // existing runners
    baseList |= (1 << (numBaseHit - 1));  // hitter
}
void Bases::walk() {
    uint8_t mask = 0x01;
    for (int i = 0; i < 4; i++) {
        if ((mask & baseList) == 0) {
            baseList |= mask;
            break;
        }
        mask <<= 1;
    }
}
[[nodiscard]] auto Bases::getNumRuns() const -> int {
    int res = 0;
    uint8_t mask = runMask;
    uint8_t runs = mask & baseList;
    while (runs > 0) {
        if ((runs & 0x01) != 0) {
            ++res;
        }
        runs >>= 1;
    }
    return res;
}
void Bases::clearRunnersWhoScored() { baseList &= ~runMask; }
void Bases::endOfInning() { baseList = 0; }
