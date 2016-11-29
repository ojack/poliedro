#include "flowScene.h"

//---------------------------------------------------------------
void flowScene::setup(){
    if(ofIsGLProgrammableRenderer()){
        shader.load("shaders/GL3/paint");
    }else{
        shader.load("shaders/GL2/paint");
    }
    maskFbo.allocate(width, height);
    maskFbo.begin();
    ofClear(0,0,0,0);
    maskFbo.end();
    
    renderFbo.allocate(width, height);
    renderFbo.begin();
    ofClear(0,0,0,0);
    renderFbo.end();
    
    srcFbo.allocate(width, height);
    srcFbo.begin();
    ofClear(0,0,0,0);
    srcFbo.end();
    
  //  loadImages("content/explosion", &images);
    setupFlow();
  //  setVelocityMask(images.at(0).getTexture());
}


//---------------------------------------------------------------
void flowScene::update(){
    setVelocityMask(renderFbo.getTexture());
    updateFlow();
}

void flowScene::clear(){
    srcFbo.begin();
    ofClear(0, 0, 0, 0);
    srcFbo.end();
}

//---------------------------------------------------------------
void flowScene::draw(){
    srcFbo.begin();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(0, 0, 0, 1);
    ofDrawRectangle(0, 0, srcFbo.getWidth(), srcFbo.getHeight());
   // ofClear(0, 0, 0, 0);
     ofEnableBlendMode(OF_BLENDMODE_ADD);
     ofSetColor(255, 255, 255, 10);
 //   IM->medianFilteredResult.draw(0, 0, srcFbo.getWidth(), srcFbo.getHeight());
    drawFlow();
    srcFbo.end();
    maskFbo.begin();
    // Cleaning everthing with alpha mask on 0 in order to make it transparent by default
    ofClear(0, 0, 0, 0);
    
    shader.begin();
    // here is where the fbo is passed to the shader
   
    shader.setUniformTexture("maskTex", srcFbo.getTexture(), 1 );
    
   // images.at(0).draw(0, 0);
    CL->goodFbo.draw(0, 0);
    shader.end();
    maskFbo.end();
    
    renderFbo.begin();
    ofClear(0, 0, 0, 0);
    ofSetColor(255, 255, 255, 255);
    
    CL->badFbo.draw(0, 0);
   
   // images.at(1).draw(0, 0);
    maskFbo.draw(0, 0);
     ofSetColor(255, 255, 255, 255);
     ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    drawFlow();
    renderFbo.end();
    renderFbo.draw(0, 0);
    //srcFbo.draw(0,0);
    //images.at(0).draw(0, 0);
}

