#include "testInterface.h"

#include "midiManager.h"
#include "stateManager.h"
#include "console.h"


void testInterface() {
    /*
    int number, state, choice;
    choice = 0;
    Serial.println("\nWelcome to the Player Organ Test Interface!");
    while (choice != -1) {
        
        Serial.println("Choose testing options: 1. Simulate key / stop presses 2. Test key scheduling 3. Simulate MIDI input 4. Test hall sensors or -1. to end: ");
        cin >> choice;
        switch (choice) {
        case 1:
            choice = 0;
            while (choice != -1) {

                Serial.println("1. Keys or 2. Stops? or -1 to exit: ");
                cin >> choice;

                if (choice == 1) {
                    Serial.println("Choose item number (1-61) or -1 to stop: ");
                    cin >> number;
                    while (number != -1 and number > 0) {
                        Serial.println("Choose state: 0/1: ");
                        cin >> state;
                        Serial.println("");
                        //stateManager->keys.setSensorState(number, state);
                        //printKeyStates("header");
                        //printKeyStates();
                        
                        while (! Keys.schedule.empty()) {
                            //checkSchedule();
                            delay(200);
                            //this_thread::sleep_for(chrono::milliseconds(200));
                        }
                        
                        Serial.println("keys pressed overall  : ");    //Keys.getStatesVector("all", true, true);

                        Serial.println("Choose item number (1-61) or -1 to stop: ");
                        cin >> number;
                    }

                }
                else if (choice == 2) {
                    Serial.println("Choose item number (1-61) or -1 to stop: ");
                    cin >> number;
                    while (number != -1 and number > 0) {
                        Serial.println("Choose state: 0/1: ");
                        cin >> state;
                        Serial.println("");
                        //stateManager.stops.setSensorState(number, state);

                        //printStopStates("header");
                        //printKeyStates();

                        Serial.print("Choose item number (1-61) or -1 to stop: ");
                        cin >> number;
                    }


                }

            }
            Serial.println("Choose testing options: 1. Simulate key / stop presses 2. Test key scheduling 3. Simulate MIDI input 4. Test hall sensors or -1. to end: ");
            cin >> choice;
            break;
        case 2:
            choice = 0;
            int key;
            while (choice != -1) {
                
                Serial.println("type key number: ");
                cin >> key;
                //stateManager->keys.setSensorState(key, 1);
                //printKeyStates("overall");
                Serial.println("");
                
                while (! Keys.schedule.empty()) {
                    //checkSchedule();
                    //this_thread::sleep_for(chrono::milliseconds(200));
                    delay(200);
                }
                
                //printKeyStates("overall");

            }
            Serial.println("Choose testing options: 1. Simulate key / stop presses 2. Test key scheduling 3. Simulate MIDI input 4. Test hall sensors or -1. to end: ");
            cin >> choice;
            break;

        case 3:
            choice = 0;
            
            int status, data1, data2;

            while (choice != -1) {
                Serial.println("1. Raw MIDI data 2. Instrument change 3. Key on / off or -1 to exit: "); cin >> choice;
                
                switch (choice) {
                case 1:

                    Serial.println("Status byte (1st nibble = command type, 2nd nibble = channel no.) e.g. 0x81: "); 
                    cin >> hex >> status;
                    cout << status;
                    Serial.println("Data1 byte (e.g. instrument number, note number) e.g. 48: "); 
                    cin  >> dec >> data1;
                    cout << data1;
                    Serial.println("Data2 byte (e.g. velocity, other data) e.g. 100: "); 
                    cin >> dec >> data2;
                    cout << data2 << "\n\n";


                    MIDI.MIDIreceive(status, data1, data2);
                    //printStopStates("overall");
                    //printKeyStates("system");
                    break;
                case 2:
                    cout << "Type instrument number (0-127): ";
                    cin >> choice;
                    MIDI.MIDIreceive(0xC1, choice, 0);
                    //printStopStates("overall");
                    break;
                }
                
            }
            Serial.println("Choose testing options: 1. Simulate key / stop presses 2. Test key scheduling 3. Simulate MIDI input 4. Test hall sensors or -1. to end: ");
            cin >> choice;
            break;
        case 4:
            while (true) {
                Serial.println("testMux.muxRead(8,true,false)");
            }
            break;
        case -1:
            break;
        }
    }
    //printKeyStates("header");
    */
}
