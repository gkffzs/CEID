#ifndef VEHICLE_H
#define VEHICLE_H

#include <vector>
#include <iostream>
#include "Globals.h"
#include "MapFunctions.h"

using namespace std;

int newVehicleID();

class Vehicle{
    public:
        Vehicle();
        Vehicle(int =0, bool =false, float =0);
        Vehicle(char* =(char*) "|V|", int =0, bool =false, float =0);
        virtual ~Vehicle();

        int x, y;

        void setName(char*);
        void setSpeed(int);
        void setBroken(bool);
        void setApproachCapability(float);
        void setMovesMade(int);
        void setBrokenTimes(int);
        void setRoundsBroken(int);

        void setXY(int, int);

        int getID() const;
        char* getName() const;
        int getSpeed() const;
        bool getBroken() const;
        float getApproachCapability() const;
        int getMovesMade() const;
        int getBrokenTimes() const;
        int getRoundsBroken() const;

        void virtual printVehicle();
        void moveVehicle(MapPosition[XMAP][YMAP]);
        void virtual doTask(MapPosition[XMAP][YMAP],vector<Vehicle*>);

    private:
        const int id;
        char* name;
        int speed;
        bool broken;
        float approach_capability;
        int moves_made;
        int broken_times;
        int rounds_broken;
};

#endif
