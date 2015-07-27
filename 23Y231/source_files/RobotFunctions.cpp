#include "RobotFunctions.h"

/* Fleet's initializing function. */
vector <Vehicle*> createRobotFleet(MapPosition m[XMAP][YMAP]){
    /* Temporary vector for vehicles. */
    vector <Vehicle*> rf;

    /* Random numbers of vehicles. */
    int number_of_research = getIntRandomNumber(2,6);
    int number_of_analysis = getIntRandomNumber(4,6);
    int number_of_rescue = getIntRandomNumber(4,6);

    /* Initializing several research robots. */
    for(int i=0; i<number_of_research; i++){
        ResearchRobot* newResearchRobot = new ResearchRobot(3,false,0.5);
        int temp_x = getIntRandomNumber(0,XMAP-1);
        int temp_y = getIntRandomNumber(0,YMAP-1);
        bool is_position_taken = m[temp_x][temp_y].getTaken();
        while(is_position_taken){ /* Checking if temporary position is taken, until a free one is found. */
            temp_x = getIntRandomNumber(0,XMAP-1);
            temp_y = getIntRandomNumber(0,YMAP-1);
            is_position_taken = m[temp_x][temp_y].getTaken();
        }
        newResearchRobot->setXY(temp_x,temp_y); /* Specifying coordinates and updating position. */
        m[temp_x][temp_y].setDisplayName(newResearchRobot->getName());
        m[temp_x][temp_y].setCurrentVehicleID(newResearchRobot->getID());
        m[temp_x][temp_y].setTaken(true);

        /* Adding robot to the vehicle vector. */
        rf.push_back(newResearchRobot);
    }

    /* Initializing several analysis robots. */
    for(int i=0; i<number_of_analysis; i++){
        AnalysisRobot* newAnalysisRobot = new AnalysisRobot(1,false,0.4);
        int temp_x = getIntRandomNumber(0,XMAP-1);
        int temp_y = getIntRandomNumber(0,YMAP-1);
        bool is_position_taken = m[temp_x][temp_y].getTaken();
        while(is_position_taken){ /* Checking if temporary position is taken, until a free one is found. */
            temp_x = getIntRandomNumber(0,XMAP-1);
            temp_y = getIntRandomNumber(0,YMAP-1);
            is_position_taken = m[temp_x][temp_y].getTaken();
        }
        newAnalysisRobot->setXY(temp_x,temp_y); /* Specifying coordinates and updating position. */
        m[temp_x][temp_y].setDisplayName(newAnalysisRobot->getName());
        m[temp_x][temp_y].setCurrentVehicleID(newAnalysisRobot->getID());
        m[temp_x][temp_y].setTaken(true);

        /* Adding robot to the vehicle vector. */
        rf.push_back(newAnalysisRobot);
    }

    /* Initializing several rescue robots. */
    for(int i=0; i<number_of_rescue; i++){
        RescueRobot* newRescueRobot = new RescueRobot(2,false,0.7);
        int temp_x = getIntRandomNumber(0,XMAP-1);
        int temp_y = getIntRandomNumber(0,YMAP-1);
        bool is_position_taken = m[temp_x][temp_y].getTaken();
        while(is_position_taken){ /* Checking if temporary position is taken, until a free one is found. */
            temp_x = getIntRandomNumber(0,XMAP-1);
            temp_y = getIntRandomNumber(0,YMAP-1);
            is_position_taken = m[temp_x][temp_y].getTaken();
        }
        newRescueRobot->setXY(temp_x,temp_y); /* Specifying coordinates and updating position. */
        m[temp_x][temp_y].setDisplayName(newRescueRobot->getName());
        m[temp_x][temp_y].setCurrentVehicleID(newRescueRobot->getID());
        m[temp_x][temp_y].setTaken(true);

        /* Adding robot to the vehicle vector. */
        rf.push_back(newRescueRobot);
    }
    /* Printing out statistics after initialization. */
    cout << " >>> ----------------------------------------------------------------" << endl;
    cout << " >>> ROBOT FLEET CREATION -------------------------------------------" << endl;
    cout << " >>> --| |A| for research - |B| for analysis - |C| for rescue |------" << endl;
    cout << " >>> --| " << rf.size() << " robots created: ";
    cout << number_of_research << " research, ";
    cout << number_of_analysis << " analysis & ";
    cout << number_of_rescue << " rescue |------" << endl;

    /* Returning the vehicle vector with references to all created robots. */
    return rf;
}

/* Moving function for the robot fleet. */
void moveRobotFleet(vector <Vehicle*> rf, MapPosition m[XMAP][YMAP]){
    cout << " >>> ----------------------------------------------------------------" << endl;
    for(unsigned int i=0; i<rf.size(); i++){
        rf[i]->moveVehicle(m);
    }
    cout << " >>> ----------------------------------------------------------------" << endl;
}

/* Operating function for the robot fleet. */
void operateRobotFleet(vector <Vehicle*> rf, MapPosition m[XMAP][YMAP]){
    cout << " >>> ----------------------------------------------------------------" << endl;
    for(unsigned int i=0; i<rf.size(); i++){
        rf[i]->doTask(m,rf);
    }
    cout << " >>> ----------------------------------------------------------------" << endl;
}

/* Printing every information about all robots in the  fleet. */
void printRobotFleet(vector <Vehicle*> rf, MapPosition m[XMAP][YMAP]){
    cout << " >>> ----------------------------------------------------------------" << endl;
    for(unsigned int i=0; i<rf.size(); i++){
        rf[i]->printVehicle();
        if(i!=(rf.size()-1)){cout << " >>>" << endl;}
    }
    cout << " >>> ----------------------------------------------------------------" << endl;
}

/* Printing out statistics for the robot fleet. */
void printRobotStats(vector <Vehicle*> rf, MapPosition m[XMAP][YMAP]){
    /* Checking out how many vehicles are broken. */
    int total_breakdowns = 0;
    for(unsigned int i=0; i<rf.size(); i++){
        total_breakdowns = total_breakdowns + rf[i]->getBrokenTimes();
    }

    /* Checking out how many flags are set. */
    int number_of_flags = 0;
    for(unsigned int i=0; i<rf.size(); i++){
        if(strcmp(rf[i]->getName(),"|A|") == 0){
            number_of_flags = number_of_flags + dynamic_cast<ResearchRobot*>(rf[i])->getNumberOfFlags();
        }
    }

    /* Checking out how much of the metals was excavated. */
    int total_carriage = 0;
    for(unsigned int i=0; i<rf.size(); i++){
        if(strcmp(rf[i]->getName(),"|B|") == 0){
            total_carriage = total_carriage + dynamic_cast<AnalysisRobot*>(rf[i])->getTotalCollected();
        }
    }

    /* Printing out statistics. */
    cout << " >>> ----------------------------------------------------------------" << endl;
    cout << " >>> FLEET STATISTICS -----------------------------------------------" << endl;
    cout << " >>> --| Number of robots: " << rf.size() << endl;
    cout << " >>> --| Breakdowns so far: " << total_breakdowns << endl;
    cout << " >>> --| Total flags: " << number_of_flags << endl;
    cout << " >>> --| Total excavated quantity: " << total_carriage << endl;
}

/* Function that prints the data of a specific robot on the map. */
void printRobotData(vector <Vehicle*> rf, MapPosition m[XMAP][YMAP]){
    int n_x, n_y;
    cout << " >>> Please, enter the position of the robot you wish to print:" << endl;
    cout << " >>> --- x: "; cin >> n_x;
    cout << " >>> --- y: "; cin >> n_y;

    int veh_id = m[n_x][n_y].getCurrentVehicleID();
    while(veh_id == 0){
        printMap(m);
        cout << " >>> There is no vehicle at the given position. Please, enter a new one:" << endl;
        cout << " >>> --- x: "; cin >> n_x;
        cout << " >>> --- y: "; cin >> n_y;
        veh_id = m[n_x][n_y].getCurrentVehicleID();
    }

    for(unsigned int i=0; i<rf.size(); i++){
        if(veh_id == rf[i]->getID()){
            rf[i]->printVehicle();
        }
    }
}

/* Function that adds a new robot to the fleet. */
vector <Vehicle*> addRobotToFleet(vector <Vehicle*> rf, MapPosition m[XMAP][YMAP]){
    int type_of_robot;
    int n_x, n_y;
    cout << " >>> TYPES ----------------------------------------------------------" << endl;
    cout << " >>> + + 1. Research robot" << endl;
    cout << " >>> + + 2. Analysis robot" << endl;
    cout << " >>> + + 3. Rescue robot" << endl;
    cout << " >>> Please, choose the type of vehicle: ";
    cin >> type_of_robot;
    cout << " >>> Please, enter the position you wish to place it:" << endl;
    cout << " >>> --- x: "; cin >> n_x;
    cout << " >>> --- y: "; cin >> n_y;

    switch(type_of_robot){
        case 1:{
            ResearchRobot* newResearchRobot = new ResearchRobot(3,false,0.5);
            bool is_position_taken = m[n_x][n_y].getTaken();
            while(is_position_taken){ /* Checking if temporary position is taken, until a free one is found. */
                cout << " >>> Error: position (" << n_x << "," << n_y << ") is taken." << endl;
                cout << " >>> Please, enter a new one:" << endl;
                cout << " >>> --- x: "; cin >> n_x;
                cout << " >>> --- y: "; cin >> n_y;
                is_position_taken = m[n_x][n_y].getTaken();
            }
            newResearchRobot->setXY(n_x,n_y); /* Specifying coordinates and updating position. */
            m[n_x][n_y].setDisplayName(newResearchRobot->getName());
            m[n_x][n_y].setCurrentVehicleID(newResearchRobot->getID());
            m[n_x][n_y].setTaken(true);

            /* Adding robot to the vehicle vector. */
            rf.push_back(newResearchRobot);
            cout << " >>> A new research robot was added successfully at (" << n_x << "," << n_y << ")!" << endl;
            break;}
        case 2:{
            AnalysisRobot* newAnalysisRobot = new AnalysisRobot(1,false,0.4);
            bool is_position_taken = m[n_x][n_y].getTaken();
            while(is_position_taken){ /* Checking if temporary position is taken, until a free one is found. */
                cout << " >>> Error: position (" << n_x << "," << n_y << ") is taken." << endl;
                cout << " >>> Please, enter a new one:" << endl;
                cout << " >>> --- x: "; cin >> n_x;
                cout << " >>> --- y: "; cin >> n_y;
                is_position_taken = m[n_x][n_y].getTaken();
            }
            newAnalysisRobot->setXY(n_x,n_y); /* Specifying coordinates and updating position. */
            m[n_x][n_y].setDisplayName(newAnalysisRobot->getName());
            m[n_x][n_y].setCurrentVehicleID(newAnalysisRobot->getID());
            m[n_x][n_y].setTaken(true);

            /* Adding robot to the vehicle vector. */
            rf.push_back(newAnalysisRobot);
            cout << " >>> A new analysis robot was added successfully at (" << n_x << "," << n_y << ")!" << endl;
            break;}
        case 3:{
            RescueRobot* newRescueRobot = new RescueRobot(2,false,0.7);
            bool is_position_taken = m[n_x][n_y].getTaken();
            while(is_position_taken){ /* Checking if temporary position is taken, until a free one is found. */
                cout << " >>> Error: position (" << n_x << "," << n_y << ") is taken." << endl;
                cout << " >>> Please, enter a new one:" << endl;
                cout << " >>> --- x: "; cin >> n_x;
                cout << " >>> --- y: "; cin >> n_y;
                is_position_taken = m[n_x][n_y].getTaken();
            }
            newRescueRobot->setXY(n_x,n_y); /* Specifying coordinates and updating position. */
            m[n_x][n_y].setDisplayName(newRescueRobot->getName());
            m[n_x][n_y].setCurrentVehicleID(newRescueRobot->getID());
            m[n_x][n_y].setTaken(true);

            /* Adding robot to the vehicle vector. */
            rf.push_back(newRescueRobot);
            cout << " >>> A new rescue robot was added successfully at (" << n_x << "," << n_y << ")!" << endl;
            break;}
        default:
            cout << " >>> Error: your choice is invalid. Returning to main menu..." << endl;
    }
    return rf;
}

/* Function to fix or break a specific vehicle. */
void causeOrFixBreakdown(vector <Vehicle*> rf, MapPosition m[XMAP][YMAP]){
    int fix_or_break;
    int n_x, n_y;
    cout << " >>> Please, choose what you want to do:" << endl;
    cout << " >>> 1. Fix a vehicle." << endl;
    cout << " >>> 2. Break a vehicle." << endl;
    cout << " >>> Your choice: "; cin >> fix_or_break;
    cout << " >>> Please, enter the position of the vehicle that you want to fix/break:" << endl;
    cout << " >>> --- x: "; cin >> n_x;
    cout << " >>> --- y: "; cin >> n_y;

    int veh_id = m[n_x][n_y].getCurrentVehicleID();
    while(veh_id == 0){
        printMap(m);
        cout << " >>> There is no vehicle at the specific position. Please, enter a new one:" << endl;
        cout << " >>> --- x: "; cin >> n_x;
        cout << " >>> --- y: "; cin >> n_y;
        veh_id = m[n_x][n_y].getCurrentVehicleID();
    }

    for(unsigned int i=0; i<rf.size(); i++){
        if(veh_id == rf[i]->getID()){
            switch(fix_or_break){
                case 1:
                    if(rf[i]->getBroken() == true){
                        rf[i]->setBroken(false);
                        rf[i]->setRoundsBroken(0);
                        cout << " >>> Robot with ID #" << veh_id << " was successfully repaired." << endl;
                    } else {
                        cout << " >>> Robot with ID #" << veh_id << " is not broken, so nothing to repair here." << endl;
                    }
                    rf[i]->printVehicle();
                    break;
                case 2:
                    if(rf[i]->getBroken() == false){
                        rf[i]->setBroken(true);
                        cout << " >>> Robot with ID #" << veh_id << " is now broken." << endl;
                    } else {
                        cout << " >>> Robot with ID #" << veh_id << " is already broken!" << endl;
                    }
                    rf[i]->printVehicle();
                    break;
                default:
                    cout << " >>> Error: wrong choice. Returning to main menu." << endl;
            }
        }
    }
}

/* Function to check whether we should terminate the simulation. */
int checkMapStatus(vector <Vehicle*> rf, MapPosition m[XMAP][YMAP]){
    /* Checking if all vehicles are broken. */
    bool are_all_broken = true;
    for(unsigned int i=0; i<rf.size(); i++){
        if(rf[i]->getBroken() == false){
            are_all_broken = false;
        }
    }

    /* Checking if base is full of the metals we want. */
    int base_x, base_y;
    bool is_base_full = false;
    for (int i=0; i<XMAP; i++){
        for (int j=0; j<YMAP; j++){
            if(strcmp(m[i][j].getDisplayName(),"###") == 0){
                base_x = i;
                base_y = j;
            }
        }
    }
    int gathered_pal = m[base_x][base_y].getPalladium();
    int gathered_iri = m[base_x][base_y].getIridium();
    int gathered_pla = m[base_x][base_y].getPlatinum();
    if(gathered_pal == MAXPAL && gathered_iri == MAXIRI && gathered_pla == MAXPLA){
       is_base_full = true;
    }

    /* Returning the result. */
    if(are_all_broken == true){
        return 1;
    } else if (is_base_full == true){
        return 2;
    } else {
        return 0;
    }
}

/* Function that searches for broken vehicles and checks whether they should be destroyed or not. */
vector <Vehicle*> seekAndDestroyBrokens(vector <Vehicle*> rf, MapPosition m[XMAP][YMAP]){
    /* Checking every broken vehicle and its rounds. */
    int d_x, d_y;
    Vehicle* to_be_deleted;
    for(unsigned int i=0; i<rf.size(); i++){
        if(rf[i]->getBroken() == true){
            /* If 10 rounds have passed, destroy the vehicle. */
            if(rf[i]->getRoundsBroken() == 10){
                cout << " >>> 10 rounds passed: " << rf[i]->getName() << "(#" << rf[i]->getID() << ") will be destroyed!" << endl;
                d_x = rf[i]->x;
                d_y = rf[i]->y;
                to_be_deleted = rf[i];
                /* Deleting the vehicle and its position in the vector. */
                delete to_be_deleted;
                rf.erase(rf.begin()+i);
                /* Restoring position. */
                m[d_x][d_y].setDisplayName((char*) " * ");
                m[d_x][d_y].setCurrentVehicleID(0);
                m[d_x][d_y].setTaken(false);
            }
        }
    }
    return rf;
}
