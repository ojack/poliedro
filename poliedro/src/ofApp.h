#pragma once

#include "ofMain.h"
#include "ofxCv.h"
//#include "contourTracker.h"
#include "sceneManager.h"
#include "baseScene.h"
#include "inputManager.h"
//#include "motionTracker.h"
#include "contentLoader.h"
#include "ofxGui.h"

#define NUM_CONTOURS 2
#define PROJECTOR_RESOLUTION_X 1280
#define PROJECTOR_RESOLUTION_Y 720
#define KINECT_WIDTH 512
#define KINECT_HEIGHT 424
#define KINECT_MAX_DIST 4000
#define KINECT_MIN_DIST 500

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    
        inputManager            IM;
    
      //  contourTracker          CT;
       // vector<contourTracker>  CTVector;
       // motionTracker           motion;
        sceneManager            SM;
        contentLoader           content;
        bool bDrawDebug;
        bool bDrawFigure;
        ofxPanel panel;
    
        int angle;
    
};
