#ifndef COUNTER_H
#define COUNTER_H

/**
 * @brief Class representing a counter for clock cycles.
 */
class Counter {
private:
    int clockCycles; ///< Number of clock cycles

public:
    /**
     * @brief Constructor for Counter class.
     * @details Initializes clockCycles to 0.
     */
    Counter() : clockCycles(0) {}

    /**
     * @brief Increments the clock cycle counter by 1.
     */
    void incrementCycle() {
        clockCycles++;
    }

    /**
     * @brief Retrieves the current count of clock cycles.
     * @return Current count of clock cycles.
     */
    int getCycles() const {
        return clockCycles;
    }
};

#endif // COUNTER_H
