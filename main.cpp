#include "ItemTracker.h"

int main()
{
    // Instantiate tracker object (reads data and creates frequency.dat automatically)
    ItemTracker tracker;

    // Launch the menu-driven application loop
    tracker.run();

    return 0;
}