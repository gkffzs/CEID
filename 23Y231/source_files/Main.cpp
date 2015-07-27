/* Including required libraries and header files. */
#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include "MapFunctions.h"
#include "RobotFunctions.h"

/* Specifying namespace for commonly used members of std. */
using namespace std;

int main(){
    cout << "---------------------------------------------------------------------" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << "-----------[ C++ PROJECT 2013-2014 ][ 3873 - 4465 - 4651 ]-----------" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << "---------------------[ ROBOT FLEET ON A PLANET ]---------------------" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    /* Seeding for random numbers. */
    srand(time(NULL));

    /* Initializing planet map. */
    MapPosition planet[XMAP][YMAP];
    initializeMap(planet);

    /* Initializing vector for robots. */
    vector<Vehicle*> robot_fleet;
    robot_fleet = createRobotFleet(planet);

    /* Printing initial state of the map. */
    printMapStats(planet);
    printMap(planet);
    cout << "---------------------------------------------------------------------" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << " /// ---------------------------------------------------[ NEW ROUND ]" << endl;
    /* Running the simulation for the first round. */
    moveRobotFleet(robot_fleet,planet);
    operateRobotFleet(robot_fleet,planet);
    printMap(planet);

    int choice;
    int subchoice_print;
    int subchoice_insert;
    int check_status;
    while(1){
        /* Checking if the simulation should end. */
        check_status = checkMapStatus(robot_fleet,planet);
        if(check_status == 1){
            cout << "---------------------------------------------------------------------" << endl;
            cout << " >>> FAILURE: all vehicles are broken!" << endl;
            cout << "---------------------------------------------------------------------" << endl;
            exit(1);
        } else if(check_status == 2){
            cout << "---------------------------------------------------------------------" << endl;
            cout << " >>> SUCCESS: all required metals have been collected!" << endl;
            cout << "---------------------------------------------------------------------" << endl;
            exit(2);
        }

        cout << " /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << " >>> ---------------------------[ MENU ]-----------------------------" << endl;
        cout << " >>> --| 1) Run another round of simulation." << endl;
        cout << " >>> --| 2) Print planet map." << endl;
        cout << " >>> --| 3) Print the robot fleet." << endl;
        cout << " >>> --| 4) Display planet statistics." << endl;
        cout << " >>> --| 5) Display fleet statistics." << endl;
        cout << " >>> --| 6) Print data of a vehicle or position." << endl;
        cout << " >>> --| 7) Insert data to the simulation." << endl;
        cout << " >>> --| 8) Clear the screen." << endl;
        cout << " >>> --| 0) Exit the simulation." << endl;
        cout << " >>> ----------------------------------------------------------------" << endl;
        cout << " >>> Please, enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                cout << " /// ---------------------------------------------------[ NEW ROUND ]" << endl;
                robot_fleet = seekAndDestroyBrokens(robot_fleet,planet);
                moveRobotFleet(robot_fleet,planet);
                operateRobotFleet(robot_fleet,planet);
                printMap(planet);
                break;
            case 2:
                printMap(planet);
                break;
            case 3:
                printRobotFleet(robot_fleet,planet);
                break;
            case 4:
                printMapStats(planet);
                break;
            case 5:
                printRobotStats(robot_fleet,planet);
                break;
            case 6:
                cout << " >>> ---- Print Data ------------------------------------------------" << endl;
                cout << " >>> -----| 1. Print data of a vehicle." << endl;
                cout << " >>> -----| 2. Print data of a map position." << endl;
                cout << " >>> -----| 0. Return to main menu." << endl;
                cout << " >>> Please, enter your choice: ";
                cin >> subchoice_print;

                switch(subchoice_print){
                    case 1:
                        printRobotData(robot_fleet,planet);
                        break;
                    case 2:
                        printPlanetPosition(planet);
                        break;
                    case 0:
                        break;
                    default:
                        cout << " >>> Warning: invalid choice, returning to main menu." << endl;
                }
                break;
            case 7:
                cout << " >>> ---- Data Insertion --------------------------------------------" << endl;
                cout << " >>> -----| 1. Insert a new vehicle." << endl;
                cout << " >>> -----| 2. Edit a position on the planet." << endl;
                cout << " >>> -----| 3. Fix or break a vehicle." << endl;
                cout << " >>> -----| 0. Return to main menu." << endl;
                cout << " >>> Please, enter your choice: ";
                cin >> subchoice_insert;

                switch(subchoice_insert){
                    case 1:
                        robot_fleet = addRobotToFleet(robot_fleet,planet);
                        break;
                    case 2:
                        editMapPosition(planet);
                        break;
                    case 3:
                        causeOrFixBreakdown(robot_fleet,planet);
                        break;
                    case 0:
                        break;
                    default:
                        cout << " >>> Warning: invalid choice, returning to main menu." << endl;
                }
                break;
            case 8:
                system("cls");
                break;
            case 0:
                cout << "---------------------------------------------------------------------" << endl;
                cout << " >>> Simulation was terminated successfully." << endl;
                cout << "---------------------------------------------------------------------" << endl;
                exit(0);
            default:
                cout << " >>> Warning: invalid choice, please enter an appropriate number." << endl;
        }
    }
    return 0;
}
