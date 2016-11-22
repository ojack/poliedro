#include "ofMain.h"
#include "contourTracker.h"
#include "ofxGui.h"

class motionTracker {
    
    public:
    void setup(int width, int height);
    void update();
    void draw();
    void clear();
    
    vector<contourTracker> * CTVector;
    ofFbo motionFbo;
    ofFbo pixelFbo;
    
    ofxPanel * panel;
    ofParameterGroup params;
    ofParameter <int> op;
    ofParameter <float> cutoff;
    ofParameter <float> radius;
    
    
};