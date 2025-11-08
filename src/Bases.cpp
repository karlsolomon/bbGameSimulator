module;
#include <cstdint>
export module Bases;
export class Bases {
 private:
    static constexpr uint8_t FIRST_BASE = 0b00000001;   // Bit 0
    static constexpr uint8_t SECOND_BASE = 0b00000010;  // Bit 1
    static constexpr uint8_t THIRD_BASE = 0b00000100;   // Bit 2
    static constexpr uint8_t BASE_MASK = 0b00000111;    // Bits 0-2
    static constexpr uint8_t RUN_MASK = 0b01111000;     // Bits 3-6

    const uint8_t runMask = 0x78;  // [7] ignore, [6-3] runners who scored, [2-0] runners on bases 3-1
    uint8_t baseList;

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
    uint8_t mask = FIRST_BASE;
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
    uint8_t mask = RUN_MASK;
    uint8_t runs = mask & baseList;
    while (runs > 0) {
        if ((runs & 0x01) != 0) {
            ++res;
        }
        runs >>= 1;
    }
    return res;
}
void Bases::clearRunnersWhoScored() { baseList &= ~RUN_MASK; }
void Bases::endOfInning() { baseList = 0; }
