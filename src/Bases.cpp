#include <cstdint>
export module Bases;
export class Bases {
 private:
    const uint8_t runMask = 0x78;  // [7] ignore, [6-3] runners who scored, [2-0] runners on bases 3-1
    uint8_t baseList;
    const int numBases = 3;

 public:
    Bases() { baseList = 0; }
    constexpr void advance(int numBaseHit) {
        baseList <<= numBaseHit;              // existing runners
        baseList |= (1 << (numBaseHit - 1));  // hitter
    }
    constexpr void walk() {
        // TODO(ksolomon): implement walk logic
        uint8_t mask = 0x01;
        for (int i = 0; i < 4; i++) {
            if ((mask & baseList) == 0) {
                baseList |= mask;
                break;
            }
            mask <<= 1;
        }
    }
    [[nodiscard]] auto getNumRuns() const -> int {
        int res = 0;
        uint8_t mask = runMask;
        while (mask > 0) {
            if ((baseList & mask) != 0) {
                ++res;
            }
            mask >>= 1;
        }
        return res;
    }
    void clearRunnersWhoScored() { baseList &= ~runMask; }
    void constexpr endOfInning() { baseList = 0; }
};
