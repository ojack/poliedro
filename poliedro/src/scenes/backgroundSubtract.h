#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "inputManager.h"

class backgroundSubtract {
    
public:
    void setup(int width, int height);
    void update();
    void draw();
    void clear();
    
    ofFbo motionFbo;
    
    ofxPanel * panel;
    ofParameterGroup params;
    ofParameter<bool> resetBackground;
    ofParameter<float> learningTime, thresholdValue;
     ofParameter<float>          eraseAmount;
    inputManager * IM;
    
    ofImage motionImage;
    ofImage * medianFilteredResult;
    ofxCv::RunningBackground background;
    
    
};