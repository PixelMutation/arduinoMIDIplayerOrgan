#include "testInterface.h"
#include <thread>

void testInterface() {
    int number, state, choice;
    choice = 0;
    cout << "Welcome to the Player Organ Test Interface! \nComment out (with //) #include \". /pluginModules/testInterface.h\" in \"modules.h\" to disable\n";
    while (choice != -1) {
        
        cout << "Choose testing options: 1. Simulate key / stop presses 2. Test key scheduling 3. Simulate MIDI input or -1. to end: ";
        cin >> choice;
        switch (choice) {
        case 1:
            choice = 0;
            while (choice != -1) {

                cout << "\n1. Keys or 2. Stops? or -1 to exit: ";
                cin >> choice;

                if (choice == 1) {
                    cout << "\nChoose item number (1-61) or -1 to stop: ";
                    cin >> number;
                    while (number != -1 and number > 0) {
                        cout << "Choose state: 0/1: ";
                        cin >> state;
                        cout << "\n";
                        keypressHandler(number, state);
                        cout << "\nthis key's buffer state: " << Keys.getState(number, "buffer") << "\n";
                        cout << "this key's system age  : " << Keys.getState(number, "system") << "\n";
                        cout << "this key's user state  : " << Keys.getState(number, "user") << "\n";
                        cout << "\n                        01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 ";
                        cout << "\nkey requests  buffer  : ";    Keys.getStatesVector("buffer", true, false);
                        cout << "\nkeys pressed by system: ";    Keys.getStatesVector("system", true, false);
                        cout << "\nkeys pressed by user  : ";    Keys.getStatesVector("user", true, false);
                        cout << "\nkeys pressed overall  : ";    Keys.getStatesVector("all", true, false);

                        while (not Keys.schedule.empty()) {
                            checkSchedule();
                            this_thread::sleep_for(chrono::milliseconds(200));
                        }

                        cout << "\n\nChoose item number (1-61) or -1 to stop.";
                        cin >> number;
                    }

                }
                else if (choice == 2) {
                    cout << "\nChoose item number (1-11) or -1 to stop: ";
                    cin >> number;
                    while (number != -1 and number > 0) {
                        cout << "\nChoose state: 0/1: ";
                        cin >> state;
                        cout << "\n";
                        Stops.setSensorState(number, state);
                        cout << "\nthis stop's buffer state: " << Stops.getState(number, "buffer") << "\n";
                        cout << "this stop's system age   : " << Stops.getState(number, "system") << "\n";
                        cout << "this stop's user state   : " << Stops.getState(number, "user") << "\n";
                        cout << "\n                       01 02 03 04 05 06 07 08 09 10 11";
                        cout << "\nstop requests buffer : ";       Stops.getStatesVector("buffer", true, false);
                        cout << "\nstops system vector  : ";       Stops.getStatesVector("system", true, false);
                        cout << "\nstops user   vector  : ";       Stops.getStatesVector("user", true, false);
                        cout << "\nstops pressed overall: ";    Stops.getStatesVector("all", true, true);

                        cout << "\n\nChoose item number (1-11) or -1 to stop: ";
                        cin >> number;
                    }


                }

            }
            cout << "Choose testing options: 1. Simulate key / stop presses 2. Test key scheduling 3. Simulate MIDI input or -1. to end: ";
            cin >> choice;
            break;
        case 2:
            choice = 0;
            int key;
            while (choice != -1) {
                
                cout << "type key number: ";
                cin >> key;
                keypressHandler(key, 1);
                cout << "\nkeys pressed overall  : ";    Keys.getStatesVector("all", true, false);
                cout << "\n";

                while (not Keys.schedule.empty()) {
                    checkSchedule();
                    this_thread::sleep_for(chrono::milliseconds(200));
                }

            }
            cout << "Choose testing options: 1. Simulate key / stop presses 2. Test key scheduling 3. Simulate MIDI input or -1. to end: ";
            cin >> choice;
            break;

        case 3:
            choice = 0;
            int status, data1, data2;

            while (choice != -1) {
                cout << "\n1. Raw MIDI data 2. Instrument change 3. Key on / off or -1 to exit: "; cin >> choice;
                
                switch (choice) {
                case 1:
                    cout << "\nStatus byte (1st nibble = command type, 2nd nibble = channel no.) e.g. 0x81, 127: "; 
                    cin >> hex >> status;
                    cout << "\nData1 byte (e.g. instrument number, note number) e.g. 48: "; 
                    cin >> hex >> data1;
                    cout << "\nData2 byte (e.g. velocity, other data) e.g. 100: "; 
                    cin >> hex >> data2;

                    MIDI.MIDIrecieve(status, data1, data2);
                    cout << "\n Current stops state: "; Stops.getStatesVector("all", true, true);
                    cout << "\n Current keys state : "; Keys.getStatesVector("all", true, true);
                    break;
                case 2:
                    cout << "Type instrument number (0-127): ";
                    cin >> choice;
                    MIDI.MIDIrecieve(0xC1, choice, 0);
                    cout << "\n Current stops state: "; Stops.getStatesVector("all", true, true);
                    break;
                }
                
            }
            cout << "Choose testing options: 1. Simulate key / stop presses 2. Test key scheduling 3. Simulate MIDI input or -1. to end: ";
            cin >> choice;
            break;
        case -1:
            break;
        }
    }
}
