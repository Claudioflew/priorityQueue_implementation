#ifndef STATE_H
#define STATE_H

#include <string>

/*
 * struct State needs to overload some operators so that comparison in
 * PriorityQ works.
 */
struct State {
public:
    State(std::string name, int evCounts) : name{name}, evCounts{evCounts} {}

    std::string getName() { return name; }
    int getEvCounts() { return evCounts; }

    bool operator==(const State& other) const {
        return evCounts == other.evCounts;
    }

    bool operator>(const State& other) const {
        return evCounts > other.evCounts;
    }

    bool operator<=(const State& other) const {
        return !(*this > other);
    }

    bool operator<(const State& other) const {
        return evCounts < other.evCounts;
    }

    bool operator>=(const State& other) const {
        return !(*this < other);
    }

private:
    std::string name;
    int evCounts;
};

#endif
