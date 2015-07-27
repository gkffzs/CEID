#include "Vehicle.h"
#include "AnalysisRobot.h"

AnalysisRobot::AnalysisRobot(): Vehicle(1,false,0.4){
    Vehicle::setName((char*) "|B|");
    load_size = 40;
    pal_load = 0;
    iri_load = 0;
    pla_load = 0;
    max_pal = 150;
    max_iri = 150;
    max_pla = 150;
    total_pal_collected = 0;
    total_iri_collected = 0;
    total_pla_collected = 0;
}

AnalysisRobot::AnalysisRobot(int s, bool b, float a): Vehicle(s, b, a){
    Vehicle::setName((char*) "|B|");
    load_size = 40;
    pal_load = 0;
    iri_load = 0;
    pla_load = 0;
    max_pal = 150;
    max_iri = 150;
    max_pla = 150;
    total_pal_collected = 0;
    total_iri_collected = 0;
    total_pla_collected = 0;
}

AnalysisRobot::~AnalysisRobot(){}

void AnalysisRobot::setLoadSize(int ls){load_size = ls;}
void AnalysisRobot::setPalLoad(int pl){pal_load = pl;}
void AnalysisRobot::setIriLoad(int il){iri_load = il;}
void AnalysisRobot::setPlaLoad(int pl){pla_load = pl;}
void AnalysisRobot::setMaxPal(int mp){max_pal = mp;}
void AnalysisRobot::setMaxIri(int mi){max_iri = mi;}
void AnalysisRobot::setMaxPla(int mp){max_pla = mp;}
void AnalysisRobot::setTotalPal(int tpc){total_pal_collected = tpc;}
void AnalysisRobot::setTotalIri(int tic){total_iri_collected = tic;}
void AnalysisRobot::setTotalPla(int tpc){total_pla_collected = tpc;}

int AnalysisRobot::getLoadSize() const {return load_size;}
int AnalysisRobot::getPalLoad() const {return pal_load;}
int AnalysisRobot::getIriLoad() const {return iri_load;}
int AnalysisRobot::getPlaLoad() const {return pla_load;}
int AnalysisRobot::getMaxPal() const {return max_pal;}
int AnalysisRobot::getMaxIri() const {return max_iri;}
int AnalysisRobot::getMaxPla() const {return max_pla;}
int AnalysisRobot::getTotalPal() const {return total_pal_collected;}
int AnalysisRobot::getTotalIri() const {return total_iri_collected;}
int AnalysisRobot::getTotalPla() const {return total_pla_collected;}
int AnalysisRobot::getTotalCollected() const {
    return (total_pal_collected + total_iri_collected + total_pla_collected);
}

/* Enhanced print function. */
void AnalysisRobot::printVehicle(){
    Vehicle::printVehicle();
    cout << " >>> --- Palladium: " << pal_load << "/" << max_pal;
    cout << " (total " << total_pal_collected << ")" << endl;
    cout << " >>> --- Iridium: " << iri_load << "/" << max_iri;
    cout << " (total " << total_iri_collected << ")" << endl;
    cout << " >>> --- Platinum: " << pla_load << "/" << max_pla;
    cout << " (total " << total_pla_collected << ")" << endl;
}

/* doTask() for AnalysisRobot. */
void AnalysisRobot::doTask(MapPosition m[XMAP][YMAP],vector<Vehicle*> rf){
    if(getBroken() == false){ /* Checking if the robot is broken. */
        /* Checking if the robot is full of metals. If yes, it goes to the base. */
        if(pal_load == max_pal && iri_load == max_iri && pla_load == max_pla){
            cout << " >>> " << getName() << "(#" << getID() << ") at (" << x << "," << y << ") is full and is returning to base." << endl;
            goBackToBase(m);
        } else { /* If it's not full, it's going to excavate. */
            int current_pal = m[x][y].getPalladium();
            int current_iri = m[x][y].getIridium();
            int current_pla = m[x][y].getPlatinum();
            int temp_load = 0;
            int previous_pal = pal_load;
            int previous_iri = iri_load;
            int previous_pla = pla_load;

            /* Calculating total quantity of metals to see if we should proceed with the excavation. */
            int total_quantity = current_pal + current_iri + current_pla;

            /* Checking if total quantity is more than 3 times the load size of the robot. */
            if(total_quantity > 3*load_size){ /* If yes, proceed with the excavation. */
                /* For palladium excavation. */
                if (pal_load >= max_pal){ /* If the robot is full of palladium. */
                    cout << " >>> INFO: " << getName() << "(#" << getID() << ") is full of palladium, no need to excavate." << endl;
                } else if (current_pal == 0){ /* If current position has no palladium left. */
                    cout << " >>> WARNING: position (" << x << "," << y << ") has no palladium left." << endl;
                } else if (pal_load < max_pal && (max_pal-pal_load) >= load_size && current_pal > 0){
                    /* If the robot needs more palladium than the load size. */
                    if(current_pal >= load_size){ /* More palladium in current position than load size. */
                        m[x][y].setPalladium(current_pal-load_size);
                        pal_load = pal_load + load_size;
                    } else { /* Less palladium in current position than load size. */
                        m[x][y].setPalladium(0);
                        pal_load = pal_load + current_pal;
                    }
                } else if (pal_load < max_pal && (max_pal-pal_load) < load_size && current_pal > 0){
                    /* If the robot needs less palladium than the load size. */
                    temp_load = max_pal - pal_load;
                    if(current_pal >= temp_load){ /* More palladium in current position than temporary load size. */
                        m[x][y].setPalladium(current_pal-temp_load);
                        pal_load = pal_load + temp_load;
                    } else { /* Less palladium in current position than temporary load size. */
                        m[x][y].setPalladium(0);
                        pal_load = pal_load + current_pal;
                    }
                }

                /* For iridium excavation. */
                temp_load = 0;
                if (iri_load >= max_iri){ /* If the robot is full of iridium. */
                    cout << " >>> INFO: " << getName() << "(#" << getID() << ") is full of iridium, no need to excavate." << endl;
                } else if (current_iri == 0){ /* If current position has no iridium left. */
                    cout << " >>> WARNING: position (" << x << "," << y << ") has no iridium left." << endl;
                } else if (iri_load < max_iri && (max_iri-iri_load) >= load_size && current_iri > 0){
                    /* If the robot needs more iridium than the load size. */
                    if(current_iri >= load_size){ /* More iridium in current position than load size. */
                        m[x][y].setIridium(current_iri-load_size);
                        iri_load = iri_load + load_size;
                    } else { /* Less iridium in current position than load size. */
                        m[x][y].setIridium(0);
                        iri_load = iri_load + current_iri;
                    }
                } else if (iri_load < max_iri && (max_iri-iri_load) < load_size && current_iri > 0){
                    temp_load = max_iri - iri_load;
                    if(current_iri >= temp_load){ /* More iridium in current position than temporary load size. */
                        m[x][y].setIridium(current_iri-temp_load);
                        iri_load = iri_load + temp_load;
                    } else { /* Less iridium in current position than temporary load size. */
                        m[x][y].setIridium(0);
                        iri_load = iri_load + current_iri;
                    }
                }

                /* For platinum excavation. */
                temp_load = 0;
                if (pla_load >= max_pla){ /* If the robot is full of platinum. */
                    cout << " >>> INFO: " << getName() << "(#" << getID() << ") is full of platinum, no need to excavate." << endl;
                } else if (current_pla == 0){ /* If current position has no platinum left. */
                    cout << " >>> WARNING: position (" << x << "," << y << ") has no platinum left." << endl;
                } else if (pla_load < max_pla && (max_pla-pla_load) >= load_size && current_pla > 0){
                    /* If the robot needs more platinum than the load size. */
                    if(current_pla >= load_size){ /* More platinum in current position than load size. */
                        m[x][y].setPlatinum(current_pla-load_size);
                        pla_load = pla_load + load_size;
                    } else { /* Less platinum in current position than load size. */
                        m[x][y].setPlatinum(0);
                        pla_load = pla_load + current_pla;
                    }
                } else if (pla_load < max_pla && (max_pla-pla_load) < load_size && current_pla > 0){
                    temp_load = max_pla - pla_load;
                    if(current_pla >= temp_load){ /* More platinum in current position than temporary load size. */
                        m[x][y].setPlatinum(current_pla-temp_load);
                        pla_load = pla_load + temp_load;
                    } else { /* Less platinum in current position than temporary load size. */
                        m[x][y].setPlatinum(0);
                        pla_load = pla_load + current_pla;
                    }
                }

                /* Updating total excavated quantity counters. */
                setTotalPal(getTotalPal()+pal_load-previous_pal);
                setTotalIri(getTotalIri()+iri_load-previous_iri);
                setTotalPla(getTotalPla()+pla_load-previous_pla);

                /* Printing out excavated metals' quantities. */
                cout << " >>> " << getName() << "(#" << getID() << ") at (" << x << "," << y << ") has now ";
                cout << "pal(" << previous_pal << "+" << (pal_load-previous_pal) << "), ";
                cout << "iri(" << previous_iri << "+" << (iri_load-previous_iri) << "), ";
                cout << "pla(" << previous_pla << "+" << (pla_load-previous_pla) << ")." << endl;

                /* Calculating the probability of breaking after an excavation. */
                int break_after_exc = getIntRandomNumber(0,15);
                if(break_after_exc > 13){
                    setBroken(true);
                    setBrokenTimes(getBrokenTimes()+1);
                    cout << " >>> ''' BREAKDOWN: " << getName() << "(#" << getID() << ") broke after excavation at (" << x << "," << y <<")." << endl;
                }
            } else {
                cout << " >>> " << getName() << "(#" << getID() << "): the total quantity of metals is too low to risk." << endl;
            }
        }
    } else {
        cout << " >>> " << getName() << "(#" << getID() << ") at (" << x << "," << y << ") cannot perform any tasks due to breakdown." << endl;
    }
}

/* Function that returns the robot near the base, in order to unload its carriage. */
void AnalysisRobot::goBackToBase(MapPosition m[XMAP][YMAP]){
    int base_x = 0;
    int base_y = 0;
    int go_to_x = 0;
    int go_to_y = 0;
    bool found_position = false;

    /* Searching base's coordinates. */
    for (int i=0; i<XMAP; i++){
        for (int j=0; j<YMAP; j++){
            if(strcmp(m[i][j].getDisplayName(),"###") == 0){
                base_x = i;
                base_y = j;
            }
        }
    }

    /* Scanning positions around the base to find a free one. */
    for (int i = (base_x-1); i <= (base_x+1); i++){
        for (int j = (base_y-1); j <= (base_y+1); j++){
            if ( i == base_x && j == base_y){ /* Except for the position of the robot. */
                continue;
            } else if (i == XMAP || i == -1){ /* Except for values that point outside the map. */
                continue;
            } else if (j == YMAP || j == -1){ /* Except for values that point outside the map. */
                continue;
            }

            if(m[i][j].getTaken() == false && m[i][j].getFlag() == false){
                go_to_x = i;
                go_to_y = j;
                found_position = true;
                goto check_result;
            }
        }
    }

    check_result: /* If a free position was found, the robot is transferred there. */
        if(found_position == true){
            m[x][y].resetDisplayName();
            m[x][y].setCurrentVehicleID(0);
            m[x][y].setTaken(false);

            m[go_to_x][go_to_y].setDisplayName(getName());
            m[go_to_x][go_to_y].setCurrentVehicleID(getID());
            m[go_to_x][go_to_y].setTaken(true);
            setXY(go_to_x,go_to_y);

            cout << " >>> " << getName() << "(#" << getID() << ") moved near base, at (" << x << "," << y << ")." << endl;

            /* The robot unloads its carriage. */
            unloadMetals(m,base_x,base_y);

            cout << " >>> " << getName() << "(#" << getID() << ") successfully unloaded all of its carriage. ";
            cout << "(" << pal_load << "," << iri_load << "," << pla_load << ")" << endl;
        } else {
            cout << " >>> " << getName() << "(#" << getID() << ") couldn't reach base. Waiting until next round." << endl;
        }
}

/* Function that unloads the metals from the robot to the base. */
void AnalysisRobot::unloadMetals(MapPosition m[XMAP][YMAP], int base_x, int base_y){
    /* Unloading palladium to the base. */
    int cur_load_pal = m[base_x][base_y].getPalladium();
    int temp_load_pal = cur_load_pal + pal_load;
    if(cur_load_pal < MAXPAL){ /* If palladium store is not filled, the robot unloads whatever can be unloaded. */
        if (temp_load_pal <= MAXPAL){ /* If the quantity to be added is less than what it needs to be filled. */
            m[base_x][base_y].setPalladium(temp_load_pal);
            pal_load = 0;
        } else { /* If the quantity to be added fills completely palladium store. */
            temp_load_pal = MAXPAL;
            m[base_x][base_y].setPalladium(temp_load_pal);
            pal_load = cur_load_pal + pal_load - MAXPAL;
        }
        cout << " >>> ^^^ " << getName() << "(#" << getID() << ") unloaded " << temp_load_pal-cur_load_pal << " palladium." << endl;
    } else { /* In case palladium store is full. */
        cout << " >>> /// (#" << getID() << ") Unable to unload: palladium stores are already full." << endl;
    }

    /* Unloading iridium to the base. */
    int cur_load_iri = m[base_x][base_y].getIridium();
    int temp_load_iri = cur_load_iri + iri_load;
    if(cur_load_iri < MAXIRI){ /* If iridium store is not filled, the robot unloads whatever can be unloaded. */
        if (temp_load_iri <= MAXIRI){ /* If the quantity to be added is less than what it needs to be filled. */
            m[base_x][base_y].setIridium(temp_load_iri);
            iri_load = 0;
        } else { /* If the quantity to be added fills completely iridium store. */
            temp_load_iri = MAXIRI;
            m[base_x][base_y].setIridium(temp_load_iri);
            iri_load = iri_load - MAXIRI + cur_load_iri;
        }
        cout << " >>> ^^^ " << getName() << "(#" << getID() << ") unloaded " << temp_load_iri-cur_load_iri << " iridium." << endl;
    } else { /* In case iridium store is full. */
        cout << " >>> /// (#" << getID() << ") Unable to unload: iridium stores are already full." << endl;
    }

    /* Unloading platinum to the base. */
    int cur_load_pla = m[base_x][base_y].getPlatinum();
    int temp_load_pla = cur_load_pla + pla_load;
    if(cur_load_pla < MAXPLA){ /* If platinum store is not filled, the robot unloads whatever can be unloaded. */
        if (temp_load_pla <= MAXPLA){ /* If the quantity to be added is less than what it needs to be filled. */
            m[base_x][base_y].setPlatinum(temp_load_pla);
            pla_load = 0;
        } else { /* If the quantity to be added fills completely platinum store. */
            temp_load_pla = MAXPLA;
            m[base_x][base_y].setPlatinum(temp_load_pla);
            pla_load = cur_load_pla + pla_load - MAXPLA;
        }
        cout << " >>> ^^^ " << getName() << "(#" << getID() << ") unloaded " << temp_load_pla-cur_load_pla << " platinum." << endl;
    } else { /* In case platinum store is full. */
        cout << " >>> /// (#" << getID() << ") Unable to unload: platinum stores are already full." << endl;
    }
}
