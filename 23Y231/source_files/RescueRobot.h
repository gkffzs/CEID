#ifndef RESCUE_ROBOT_H
#define RESCUE_ROBOT_H

#include <vector>
#include "Globals.h"
#include "Vehicle.h"

class RescueRobot : public Vehicle{
    public:
        RescueRobot();
        RescueRobot(int =0, bool =false, float =0);
        virtual ~RescueRobot();

        void setNumberOfRepaired(int);
        int getNumberOfRepaired() const;

        void printVehicle();
        void doTask(MapPosition[XMAP][YMAP],vector<Vehicle*>);

    private:
        int vehicles_repaired;
};

#endif
