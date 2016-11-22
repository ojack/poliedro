#include "paintScene.h"

//---------------------------------------------------------------
void paintScene::setup(){
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
    
}


//---------------------------------------------------------------
void paintScene::draw(){
    image0->draw(0,0);
    // HERE the shader-masking happends
    maskFbo.begin();
    // Cleaning everthing with alpha mask on 0 in order to make it transparent by default
    ofClear(0, 0, 0, 0);
    
    shader.begin();
    // here is where the fbo is passed to the shader
    shader.setUniformTexture("maskTex", motionFbo->getTextureReference(), 1 );
    
    image1->draw(0,0);
    
    shader.end();
    maskFbo.end();

    maskFbo.draw(0, 0);
}