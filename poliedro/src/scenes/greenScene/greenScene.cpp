#include "greenScene.h"

//---------------------------------------------------------------
void greenScene::setup(){
    if(ofIsGLProgrammableRenderer()){
        shader.load("shaders/GL3/paint");
    }else{
        shader.load("shaders/GL2/paint");
    }
    maskFbo.allocate(width, height);
    maskFbo.begin();
    ofClear(0,0,0,0);
    maskFbo.end();
    
    loadImages("content/explosion", &images);
}


//---------------------------------------------------------------
void greenScene::update(){
    
}


//---------------------------------------------------------------
void greenScene::draw(){
    images.at(1).draw(0,0);
    // HERE the shader-masking happends
    maskFbo.begin();
    // Cleaning everthing with alpha mask on 0 in order to make it transparent by default
    ofClear(0, 0, 0, 0);
    
    shader.begin();
    // here is where the fbo is passed to the shader
    shader.setUniformTexture("maskTex", motionFbo->getTextureReference(), 1 );
    
    images.at(0).draw(0,0);
    
    shader.end();
    maskFbo.end();
    
    ofSetColor(255, 255, 255, 255);
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_SCREEN);
    maskFbo.draw(0, 0);
   
    ofSetColor(0, 130, 130, 160);

    
    // ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
      for (int i = 0; i < CTVector->size(); i++){
        CTVector->at(i).draw();
        
    }
    ofPopStyle();

}

void greenScene::loadImages(string path, vector<ofImage> *images){
    ofDirectory dir;
    
    dir.listDir(path);
    dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
    ofLogNotice() << "loading directory " << path << " size: " << dir.size();
    //allocate the vector to have as many ofImages as files
    if( dir.size() ){
        images->assign(dir.size(), ofImage());
        
    }
    
    // you can now iterate through the files and load them into the ofImage vector
    for(int i = 0; i < (int)dir.size(); i++){
        ofLogNotice() << "loading" << dir.getPath(i);
        (*images)[i].load(dir.getPath(i));
        (*images)[i].resize(width, height);
    }
    
    
}