#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   
    ofEnableAlphaBlending();
    img.setAnchorPercent(0.5, 0.5);
    ofBackground(0);
    img.loadImage("dog.jpg");
    w = img.width;
    h = img.height;
    img.allocate(w, h,OF_IMAGE_COLOR);
    
    alpha = 100;
    size = 1;
    pixelSize = 3;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    alpha = ofMap(mouseY, 0, ofGetWindowHeight(), 50, 250);
    pixelSize = ofMap(mouseX,0,ofGetWindowWidth(), 3, 15);
    
  //  pixelSize = ofMap(mouseY,ofGetWindowHeight(),0, 10,0);

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // img.draw(ofGetWindowWidth()/2-w/2,ofGetWindowHeight()/2-h/2);
    
    // get pixel information
    unsigned char * pixels = img.getPixels();
    
    // scan pixels w and h and redraw the picture
    
    // set skip number
    int skip = 15;

    for (int i=0; i <w; i= i+skip){
        for( int j=0; j<h; j = j+skip){

    float brightness = pixels[j*w + i];
    float rad = ofMap(brightness, 255, 0, 0, 15);

   // float pct = 1.0 - brightness / 255.0f;
    
     int r = pixels[j * w * 3 + i * 3];
     int g = pixels[j * w * 3 + i * 3 + 1];
     int b = pixels[j * w * 3 + i * 3 + 2];
   
      rad += ofMap(ofNoise(i, j, ofGetFrameNum()*0.01), 0, 1, -3, 3);
            
            
    ofSetColor(r, g, b,alpha);
    // ofSetColor(brightness,brightness,brightness, alpha);
    
    size = ofMap(brightness,0,255,0,1);
            
    //draw Rect pixels
            
    ofSetRectMode(OF_RECTMODE_CENTER); //set rectangle mode to the center
    ofRect(i, j,pixelSize*rad,pixelSize*rad);
    
            
        }
    }
}
    

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
