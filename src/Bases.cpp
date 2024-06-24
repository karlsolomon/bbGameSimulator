#include "Bases.hpp"

#include <cstdio>
#include <print>
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
