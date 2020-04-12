#include "testInterface.h"

void testInterface() {
    cout << "Welcome to the Player Organ Test Interface!\n";
    stateManager Keys("keys", 61, 5);
    stateManager Stops("stops", 11, 11);
    int number, state, choice;
    char run;
    cout << "Continue? y/n\n";
    cin >> run;
    while (run == 'y') {
        cout << "\n1. Keys or 2. Stops? : ";
        cin >> choice;
        
        if (choice == 1) {
            cout << "\nChoose item number (1-61) or -1 to stop: ";
            cin >> number;
            while (number != -1 and number > 0) {
                cout << "Choose state: 0/1: ";
                cin >> state;
                cout << "\n";
                Keys.requestSystemState(number, state);
                cout << "\nthis key's buffer state: " << Keys.getState(number, "buffer") << "\n";
                cout << "this key's system age  : " << Keys.getState(number, "system") << "\n";
                cout << "\n                        01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 ";
                cout << "\nkey requests  buffer  : ";    Keys.getStatesVector("buffer", true);
                cout << "\nkeys pressed by system: ";    Keys.getStatesVector("system", true);

                cout << "\n\nChoose item number (1-61) or -1 to stop.";
                cin >> number;
            }

        }
        else {
            cout << "\nChoose item number (1-11) or -1 to stop: ";
            cin >> number;
            while (number != -1 and number > 0) {
                cout << "\nChoose state: 0/1: ";
                cin >> state;
                cout << "\n";
                Stops.requestSystemState(number, state);
                cout << "\nthis stop's buffer state: " << Stops.getState(number, "buffer") << "\n";
                cout << "this stop's system age  : " << Stops.getState(number, "system") << "\n";
                cout << "\n                      01 02 03 04 05 06 07 08 09 10 11";
                cout << "\nstop requests buffer: ";       Stops.getStatesVector("buffer", true);
                cout << "\nstops system vector : ";       Stops.getStatesVector("system", true);

                cout << "\n\nChoose item number (1-11) or -1 to stop: ";
                cin >> number;
            }


        }
        cout << "Continue? y/n\n";
        cin >> run;


    }
}
