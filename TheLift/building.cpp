#include "building.h"

#include <algorithm>

Building::Building(const std::vector<std::vector<int>> &queues, QObject *parent)
    : QObject(parent), mQueues{queues}
{
}

bool Building::noPersonWaitingForLift() const
{
    return std::all_of(mQueues.begin(), mQueues.end(),
                       [](auto const &queue) { return queue.empty(); });
}

std::optional<int> Building::highestFloorAboveLiftPushedDown(int liftPos) const
{
    for (std::size_t i = mQueues.size() - 1;
         i != static_cast<std::size_t>(liftPos); --i) {
        for (const auto &person : mQueues[i]) {
            if (static_cast<std::size_t>(person) <
                i) { // person wants to go down
                return {i};
            }
        }
    }
    return {};
}

std::optional<int> Building::nextFloorAboveLiftPushedUp(int liftPos) const
{
    if (std::size_t(liftPos) >= mQueues.size() - 2) {
        return {};
    }
    for (std::size_t i = liftPos + 1; i < mQueues.size(); ++i) {
        for (const auto &person : mQueues[i]) {
            if (static_cast<std::size_t>(person) > i) {
                return {i};
            }
        }
    }
    return {};
}

std::optional<int> Building::nextFloorUnderLiftPushedDown(int liftPos) const
{
    if (liftPos <= 1) {
        return {};
    }
    for (std::size_t i = liftPos - 1; i != static_cast<std::size_t>(0) - 1;
         --i) {
        for (const auto &person : mQueues[i]) {
            if (static_cast<std::size_t>(person) < i) {
                return {i};
            }
        }
    }
    return {};
}

std::optional<int> Building::lowestFloorUnderLiftPushedUp(int liftPos) const
{
    for (std::size_t i = 0; i < static_cast<std::size_t>(liftPos); ++i) {
        for (const auto &person : mQueues[i]) {
            if (static_cast<std::size_t>(person) > i) { // person wants to go up
                return {i};
            }
        }
    }
    return {};
}

std::vector<int> Building::peopleOnFloorWaiting(int floor) const
{
    assert(floor >= 0 && floor < static_cast<int>(mQueues.size()));
    return mQueues[floor];
}

bool Building::removePersonFromFloor(int floor, int person)
{
    assert(floor >= 0 && floor < static_cast<int>(mQueues.size()));

    auto it = std::find(mQueues[floor].begin(), mQueues[floor].end(), person);
    if (it == mQueues[floor].end()) {
        return false;
    }
    mQueues[floor].erase(it);
    return true;
}

int Building::floorsCount() const
{
    return mQueues.size();
}
