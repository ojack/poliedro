#include "ofApp.h"

//#include "velocityScene.h"
#include "paintScene.h"
#include "greenScene.h"
#include "birdScene.h"
#include "flowScene.h"
#include "trailsScene.h"

//--------------------------------------------------------------
void ofApp::setup(){
    panel.setup();
    panel.loadFromFile("settings.xml");
    group.setName("scene");
    group.add(cycleTime.set("cycleTime", 60, 5, 400));
    panel.add(group);
    IM.panel = &panel;
   // motion.panel = &panel;
    
    content.setup(PROJECTOR_RESOLUTION_X, PROJECTOR_RESOLUTION_Y);
    IM.setup(KINECT_MIN_DIST, KINECT_MAX_DIST);
    
    
  
    SM.scenes.push_back(new paintScene());
    SM.scenes.push_back(new flowScene());
  //  SM.scenes.push_back(new greenScene());
 //   SM.scenes.push_back(new birdScene());
    SM.scenes.push_back(new trailsScene());
    
    // share a pointer to the CT object
  /*  motion.CTVector = &CTVector;
    motion.setup(PROJECTOR_RESOLUTION_X, PROJECTOR_RESOLUTION_Y);

    for (int i = 0; i < NUM_CONTOURS; i++){
        CTVector.push_back(contourTracker());
    }*/

    for (int i = 0; i < SM.scenes.size(); i++){
        SM.scenes[i]->image0 = content.image0;
        SM.scenes[i]->CL = &content;
        SM.scenes[i]->image1 = content.image1;
        SM.scenes[i]->image2 = content.image2;
         SM.scenes[i]->panel = &panel;
        SM.scenes[i]->width = PROJECTOR_RESOLUTION_X;
        SM.scenes[i]->height = PROJECTOR_RESOLUTION_Y;
      //  SM.scenes[i]->motionFbo = &motion.motionFbo;
      //  SM.scenes[i]->CTVector = &CTVector;
        SM.scenes[i]->IM = &IM;
    }
    
    
    SM.setup();
   
    
    bDrawDebug = false;
    bDrawFigure = true;
    
    

    
    int angle = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    IM.update();
    
    
   /* ofRectangle input(0,0,IM.medianFilteredResult.getWidth(), IM.medianFilteredResult.getHeight());
    ofRectangle output(0,0, ofGetWidth(), ofGetHeight());
    
    ofRectangle inputScaled = input;
    inputScaled.scaleTo(output);
    
    
    
   
    for(int j = 0; j < NUM_CONTOURS; j++){
        if (IM.finder.size() > j){
            ofPolyline tempLine = IM.finder.getPolyline(j);
            //scale kinect input to size of output
            for (int i = 0; i < tempLine.size(); i++){
                float x = tempLine[i].x;
                float y = tempLine[i].y;
                float newX = ofMap(x, input.x, input.x + input.width,
                               inputScaled.x + inputScaled.width, inputScaled.x);
                float newY = ofMap(y, input.y, input.y + input.height,
                               inputScaled.y, inputScaled.y + inputScaled.height);
                tempLine[i].set(newX, newY);
            
            }
            CTVector.at(j).analyze(tempLine);
        } else {
            CTVector.at(j).reset();
        }
    }
    motion.update();*/
    SM.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(ofGetElapsedTimeMillis() > cycleTime*1000){
        goToRandomScene();
        ofResetElapsedTimeCounter();
    }
    
    ofBackground(0,0,0);
     ofSetColor(255, 255, 255, 255);
    string  info  = "FPS:        "+ofToString(ofGetFrameRate(),0);
    ofSetWindowTitle(info);
    if (bDrawDebug){
       
        IM.draw();
        panel.draw();
        //motion.motionFbo.draw(300, 400, 400, 300);
    }else {
       SM.draw();
      // motion.draw();
    }

   
   // IM.finder.draw();
   // motion.draw();
    
}

void ofApp::goToRandomScene(){
    SM.randomScene();
    content.randomIndex();
    SM.clear();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == OF_KEY_RIGHT){
        SM.nextScene();
        SM.clear();
        content.updateIndex();
      //  motion.clear();

    }
    
    if (key == ' '){
        bDrawDebug = !bDrawDebug;
    }
    
    if (key == 'f'){
        ofToggleFullscreen();
    }
    
    if  (key == 'c'){
       SM.clear();
    }
    
    if (key == '1'){
        content.updateIndex();
    }
    
    if (key == OF_KEY_UP){
        angle++;
        if(angle>30) angle=30;
        IM.setAngle(angle);
    }
    
    if (key == OF_KEY_DOWN){
        angle--;
        if(angle<-30) angle=-30;
        IM.setAngle(angle);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
