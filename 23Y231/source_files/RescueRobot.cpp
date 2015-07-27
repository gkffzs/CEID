#include "Vehicle.h"
#include "RescueRobot.h"

RescueRobot::RescueRobot(): Vehicle(2,false,0.7){
    Vehicle::setName((char*) "|C|");
    vehicles_repaired = 0;
}

RescueRobot::RescueRobot(int s, bool b, float a): Vehicle(s, b, a){
    Vehicle::setName((char*) "|C|");
    vehicles_repaired = 0;
}

RescueRobot::~RescueRobot(){}

void RescueRobot::setNumberOfRepaired(int nor){vehicles_repaired = nor;}
int RescueRobot::getNumberOfRepaired() const {return vehicles_repaired;}

/* Enhanced print function. */
void RescueRobot::printVehicle(){
    Vehicle::printVehicle();
    cout << " >>> --- Vehicles Repaired: " << vehicles_repaired << endl;
}

/* doTask() for RescueRobot. */
void RescueRobot::doTask(MapPosition m[XMAP][YMAP],vector<Vehicle*> rf){
    if(getBroken() == false){ /* Checking if the robot is broken. */
        int broken_x = 0;
        int broken_y = 0;
        int cur_vehicle_id = 0;
        bool is_broken = false;
        bool fixed_a_vehicle = false;

        /* Loop that scans the area around the robot, to see if any robot there is broken. */
        for (int i = (x-1); i <= (x+1); i++){
            for (int j = (y-1); j <= (y+1); j++){
                if ( i == x && j == y){ /* Except for the position of the robot. */
                    continue;
                } else if (i == XMAP || i == -1){ /* Except for values that point outside the map. */
                    continue;
                } else if (j == YMAP || j == -1){ /* Except for values that point outside the map. */
                    continue;
                }

                broken_x = 0;
                broken_y = 0;
                is_broken = false;
                /* If position is taken, check the vehicle in it. */
                if(m[i][j].getTaken() == true){
                    cur_vehicle_id = m[i][j].getCurrentVehicleID();
                    /* Getting vehicle's information through searching in the vector. */
                    for(unsigned int k=0; k<rf.size(); k++){
                        if(cur_vehicle_id == rf[k]->getID()){
                            is_broken = rf[k]->getBroken();
                            /* If the vehicle is broken, fix it and exit. */
                            if(is_broken == true){
                                broken_x = i;
                                broken_y = j;
                                /* Repairing the vehicle. */
                                rf[k]->setBroken(false);
                                rf[k]->setRoundsBroken(0);
                                /* Increasing counter of repaired vehicles. */
                                setNumberOfRepaired(getNumberOfRepaired()+1);
                                fixed_a_vehicle = true;
                                goto end_of_repair;
                            }
                        }
                    }
                }
            }
        }

        end_of_repair: /* If the robot fixed something, then the message below is printed. */
                if(fixed_a_vehicle == true){
                    cout << " >>> " << getName() << "(#" << getID() << ") just repaired a vehicle at (" << broken_x << "," << broken_y << ")." << endl;
                }
    } else {
        cout << " >>> " << getName() << "(#" << getID() << ") at (" << x << "," << y << ") cannot perform any tasks due to breakdown." << endl;
    }
}
