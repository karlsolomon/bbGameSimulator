class Player {
 private:
    double pSingle;
    double pDouble;
    double pTriple;
    double pHomeRun;
    double pWalk;
    double pOut;

 public:
    Player() = default;
    void setPSingle(double pSingle) { this->pSingle = pSingle; }
    void setPDouble(double pDouble) { this->pDouble = pDouble; }
    void setPTriple(double pTriple) { this->pTriple = pTriple; }
    void setPHomeRun(double pHomeRun) { this->pHomeRun = pHomeRun; }
    void setPWalk(double pWalk) { this->pWalk = pWalk; }
    void setPOut(double pOut) { this->pOut = pOut; }
    [[nodiscard]] auto getPSingle() const -> double { return pSingle; }
    [[nodiscard]] auto getPDouble() const -> double { return pDouble; }
    [[nodiscard]] auto getPTriple() const -> double { return pTriple; }
    [[nodiscard]] auto getPHomeRun() const -> double { return pHomeRun; }
    [[nodiscard]] auto getPWalk() const -> double { return pWalk; }
    [[nodiscard]] auto getPOut() const -> double { return pOut; }
};
