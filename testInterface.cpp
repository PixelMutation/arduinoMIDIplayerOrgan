#include "testInterface.h"
//#include <thread>

void testInterface() {
    int number, state, choice;
    choice = 0;
    Serial.println("\nWelcome to the Player Organ Test Interface!");
    while (choice != -1) {
        
        cout << "\nChoose testing options: 1. Simulate key / stop presses 2. Test key scheduling 3. Simulate MIDI input 4. Test hall sensors or -1. to end: ";
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
                        printKeyStates("header");
                        printKeyStates();

                        while (! Keys.schedule.empty()) {
                            checkSchedule();
                            delay(200);
                            //this_thread::sleep_for(chrono::milliseconds(200));
                        }
                        cout << "\nkeys pressed overall  : ";    Keys.getStatesVector("all", true, true);

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

                        printStopStates("header");
                        printKeyStates();

                        cout << "\n\nChoose item number (1-11) or -1 to stop: ";
                        cin >> number;
                    }


                }

            }
            cout << "\nChoose testing options: 1. Simulate key / stop presses 2. Test key scheduling 3. Simulate MIDI input or -1. to end: ";
            cin >> choice;
            break;
        case 2:
            choice = 0;
            int key;
            while (choice != -1) {
                
                cout << "\ntype key number: ";
                cin >> key;
                keypressHandler(key, 1);
                printKeyStates("overall");
                cout << "\n";

                while (! Keys.schedule.empty()) {
                    checkSchedule();
                    //this_thread::sleep_for(chrono::milliseconds(200));
                    delay(200);
                }
                printKeyStates("overall");

            }
            cout << "\nChoose testing options: 1. Simulate key / stop presses 2. Test key scheduling 3. Simulate MIDI input or -1. to end: ";
            cin >> choice;
            break;

        case 3:
            choice = 0;
            
            int status, data1, data2;

            while (choice != -1) {
                cout << "\n1. Raw MIDI data 2. Instrument change 3. Key on / off or -1 to exit: "; cin >> choice;
                
                switch (choice) {
                case 1:

                    cout << "\nStatus byte (1st nibble = command type, 2nd nibble = channel no.) e.g. 0x81: "; 
                    cin >> hex >> status;
                    cout << status;
                    cout << "\nData1 byte (e.g. instrument number, note number) e.g. 48: "; 
                    cin  >> dec >> data1;
                    cout << data1;
                    cout << "\nData2 byte (e.g. velocity, other data) e.g. 100: "; 
                    cin >> dec >> data2;
                    cout << data2 << "\n\n";


                    MIDI.MIDIrecieve(status, data1, data2);
                    printStopStates("overall");
                    printKeyStates("system");
                    break;
                case 2:
                    cout << "Type instrument number (0-127): ";
                    cin >> choice;
                    MIDI.MIDIrecieve(0xC1, choice, 0);
                    printStopStates("overall");
                    break;
                }
                
            }
            cout << "Choose testing options: 1. Simulate key / stop presses 2. Test key scheduling 3. Simulate MIDI input or -1. to end: ";
            cin >> choice;
            break;
        case 4:
            while (true) {
                cout << testMux.muxRead(8,true,false) << "\n ";
            }
            break;
        case -1:
            break;
        }
    }
    printKeyStates("header");
}
