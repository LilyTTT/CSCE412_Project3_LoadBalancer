#ifndef COUNTER_H
#define COUNTER_H

class Counter {
private:
    int clockCycles;

public:
    Counter() : clockCycles(0) {}

    void incrementCycle() {
        clockCycles++;
    }

    int getCycles() const {
        return clockCycles;
    }
};

#endif // CLOCKCOUNTER_H
