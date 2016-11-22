#include "ofApp.h"

#include "velocityScene.h"
#include "paintScene.h"

//--------------------------------------------------------------
void ofApp::setup(){
    panel.setup();
    IM.panel = &panel;
    motion.panel = &panel;
    
    content.setup(PROJECTOR_RESOLUTION_X, PROJECTOR_RESOLUTION_Y);
    IM.setup();
    
    SM.scenes.push_back(new paintScene());
    SM.scenes.push_back(new velocityScene());
    
    // share a pointer to the CT object
    motion.CTVector = &CTVector;
    motion.setup(PROJECTOR_RESOLUTION_X, PROJECTOR_RESOLUTION_Y);

    for (int i = 0; i < NUM_CONTOURS; i++){
        CTVector.push_back(contourTracker());
    }

    for (int i = 0; i < SM.scenes.size(); i++){
        SM.scenes[i]->image0 = content.image0;
        SM.scenes[i]->image1 = content.image1;
        SM.scenes[i]->width = PROJECTOR_RESOLUTION_X;
        SM.scenes[i]->height = PROJECTOR_RESOLUTION_Y;
        SM.scenes[i]->motionFbo = &motion.motionFbo;
    }
    
    
    SM.setup();
   
    
    bDrawDebug = false;
    
    panel.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    
    IM.update();
    
    
    ofRectangle input(0,0,IM.medianFilteredResult.getWidth(), IM.medianFilteredResult.getHeight());
    ofRectangle output(0,0, ofGetWidth(), ofGetHeight());
    
    ofRectangle inputScaled = input;
    inputScaled.scaleTo(output);
    
    
    
   
    for(int j = 0; j < NUM_CONTOURS; j++){
        if (IM.finder.size() > j){
            ofPolyline tempLine = IM.finder.getPolyline(j);
            /*scale kinect input to size of output*/
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
        }
    }
    motion.update();
    SM.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0,0,0);
    string  info  = "FPS:        "+ofToString(ofGetFrameRate(),0);
    ofSetWindowTitle(info);
    if (bDrawDebug){
       
        IM.draw();
        panel.draw();
        motion.motionFbo.draw(300, 400, 400, 300);
    }else {
       SM.draw();
      // motion.draw();
    }

   // IM.finder.draw();
   
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == OF_KEY_RIGHT){
        SM.nextScene();
    }
    
    if (key == ' '){
        bDrawDebug = !bDrawDebug;
    }
    
    if (key == 'f'){
        ofToggleFullscreen();
    }
    
    if  (key == 'c'){
        motion.clear();
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
