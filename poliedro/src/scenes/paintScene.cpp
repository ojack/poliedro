#include "paintScene.h"

//---------------------------------------------------------------
void paintScene::setup(){
    setupContour(2);
    if(ofIsGLProgrammableRenderer()){
        shader.load("shaders/GL3/paint");
    }else{
        shader.load("shaders/GL2/paint");
    }
    maskFbo.allocate(width, height);
    maskFbo.begin();
    ofClear(0,0,0,0);
    maskFbo.end();
}


//---------------------------------------------------------------
void paintScene::update(){
    processContour();
}


//---------------------------------------------------------------
void paintScene::draw(){
    CL->badFbo.draw(0,0);
    // HERE the shader-masking happends
    maskFbo.begin();
    // Cleaning everthing with alpha mask on 0 in order to make it transparent by default
    ofClear(0, 0, 0, 0);
    
    shader.begin();
    // here is where the fbo is passed to the shader
    shader.setUniformTexture("maskTex", motion.motionFbo.getTextureReference(), 1 );
    
    CL->goodFbo.draw(0,0);
    
    shader.end();
    maskFbo.end();
    
    ofSetColor(255, 255, 255, 255);
    
    maskFbo.draw(0, 0);
   
    ofSetColor(255, 230, 0, 160);

    ofPushStyle();
    // ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
      for (int i = 0; i < CTVector.size(); i++){
        CTVector.at(i).draw();
        
    }
    ofPopStyle();

}