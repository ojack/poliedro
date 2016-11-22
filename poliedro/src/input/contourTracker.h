#pragma once

#include "ofMain.h"

class contourTracker {
    
public:
    
    void setup();
    void analyze( ofPolyline & curFrame );
    void draw();
    void reset();
    
    ofPolyline prevFrame;
    ofPolyline prevSmoothed;
    ofPolyline resampleSmoothed;
    
    
};