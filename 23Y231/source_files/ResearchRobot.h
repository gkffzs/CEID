#ifndef RESEARCH_ROBOT_H
#define RESEARCH_ROBOT_H

#include <vector>
#include "Globals.h"
#include "Vehicle.h"

class ResearchRobot : public Vehicle{
    public:
        ResearchRobot();
        ResearchRobot(int =0, bool =false, float =0);
        virtual ~ResearchRobot();

        void setNumberOfFlags(int);
        int getNumberOfFlags() const;

        void printVehicle();
        void doTask(MapPosition[XMAP][YMAP],vector<Vehicle*>);

    private:
        int number_of_flags;
};

#endif

