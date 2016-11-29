#pragma once
#include "baseScene.h"
#include "contourTracker.h"
#include "motionTracker.h"


class baseContourScene : public baseScene{
    public:
        void setupContour(int numContours);
        void processContour();
    
       
        vector<contourTracker>  CTVector;
        motionTracker           motion;
};