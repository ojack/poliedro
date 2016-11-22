

#include "velocityScene.h"

//---------------------------------------------------------------
void velocityScene::setup(){
    
    for (int i = 0; i < 100; i++){
        velocitiesSmoothed[i].set(0,0);
        
    }
    motionFbo.allocate(ofGetWidth(), ofGetHeight());
    motionFbo.begin();
    ofClear(0,0,0,0);
    motionFbo.end();
}


//---------------------------------------------------------------
void velocityScene::update(){
   
}


//---------------------------------------------------------------
void velocityScene::draw(){
   
}