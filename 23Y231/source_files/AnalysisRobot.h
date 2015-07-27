#ifndef ANALYSIS_ROBOT_H
#define ANALYSIS_ROBOT_H

#include <vector>
#include <cstdlib>
#include "RandomNumbers.h"
#include "Vehicle.h"

using namespace std;

class AnalysisRobot : public Vehicle{
    public:
        AnalysisRobot();
        AnalysisRobot(int =0, bool =false, float =0);
        virtual ~AnalysisRobot();

        void setLoadSize(int);
        void setPalLoad(int);
        void setIriLoad(int);
        void setPlaLoad(int);
        void setMaxPal(int);
        void setMaxIri(int);
        void setMaxPla(int);
        void setTotalPal(int);
        void setTotalIri(int);
        void setTotalPla(int);

        int getLoadSize() const;
        int getPalLoad() const;
        int getIriLoad() const;
        int getPlaLoad() const;
        int getMaxPal() const;
        int getMaxIri() const;
        int getMaxPla() const;
        int getTotalPal() const;
        int getTotalIri() const;
        int getTotalPla() const;
        int getTotalCollected() const;

        void printVehicle();
        void doTask(MapPosition[XMAP][YMAP],vector<Vehicle*>);
        void goBackToBase(MapPosition[XMAP][YMAP]);
        void unloadMetals(MapPosition[XMAP][YMAP],int,int);

    private:
        int load_size;
        int pal_load;
        int iri_load;
        int pla_load;
        int max_pal;
        int max_iri;
        int max_pla;
        int total_pal_collected;
        int total_iri_collected;
        int total_pla_collected;
};

#endif


