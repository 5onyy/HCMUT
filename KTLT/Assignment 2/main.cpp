#include "knight2.h"

int main(int argc, char ** argv) {
    string file_armyknights, file_events;
    if (argc == 1) {
        file_armyknights = "tc1_armyknights"; // hard-code
        file_events = "tc1_events";
    }
    else if (argc == 3) {
        file_armyknights = argv[1];
        file_events = argv[2];
    }
    else {
        cout << "Error number of arguments" << endl;
        exit(1);
    }

    // BEBGIN
    KnightAdventure * knightadventure = new KnightAdventure();
    knightadventure->loadArmyKnights(file_armyknights);
    knightadventure->loadEvents(file_events);
    knightadventure->run();

    delete knightadventure;

    return 0;
}