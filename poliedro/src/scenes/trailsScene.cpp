//
//  trailsScene.cpp
//  poliedro
//
//  Created by ojack on 11/22/16.
//
//

#include "trailsScene.h"


//---------------------------------------------------------------
void trailsScene::setup(){
   if(ofIsGLProgrammableRenderer()){
        shader.load("shaders/GL3/trails");
    }else{
        shader.load("shaders/GL2/trails");
    }
    maskFbo.allocate(width, height);
    maskFbo.begin();
    ofClear(0,0,0,0);
    maskFbo.end();
    
    contourFbo.allocate(width, height);
    contourFbo.begin();
    ofClear(0,0,0,0);
    contourFbo.end();
}


//---------------------------------------------------------------
void trailsScene::update(){
    for(int j = 0; j < CTVector->size(); j++){
        contourTracker CT = CTVector->at(j);
    
        if (CT.resampleSmoothed.size() == 100){
            for (int i = 0; i < 100; i++){
                trails[j][i].addVertex(CT.resampleSmoothed[i]);
                
                if (trails[j][i].size() > 50){
                   trails[j][i].getVertices().erase(trails[j][i].getVertices().begin());
                }
            }
            
        }

    }
    contourFbo.begin();
      ofClear(0, 0, 0, 0);
    ofPushStyle();
    ofSetColor(255, 255, 255, 255);
    
    for (int i = 0; i < CTVector->size(); i++){
        CTVector->at(i).draw();
        
    }
    ofFill();
    ofPopStyle();
    contourFbo.end();
}


//---------------------------------------------------------------
void trailsScene::draw(){
    //image0->draw(0,0);
    // HERE the shader-masking happends
    maskFbo.begin();
    // Cleaning everthing with alpha mask on 0 in order to make it transparent by default
    ofClear(0, 0, 0, 0);
    
    shader.begin();
    // here is where the fbo is passed to the shader
    shader.setUniformTexture("maskTex", contourFbo.getTextureReference(), 1 );
    
    image1->draw(0,0);
    ofDrawRectangle(0, 0, width, height);
   
    shader.end();
    maskFbo.end();
      ofSetColor(255, 255, 255, 255);
    maskFbo.draw(0, 0);
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(25, 149, 122, 200);
    for(int j = 0; j < 2; j++){
        for (int i = 0; i < 100; i++){
            trails[j][i].draw();
        }
    }
    ofPopStyle();
   // contourFbo.draw(0, 0);
    //image2->draw(0,0);
}