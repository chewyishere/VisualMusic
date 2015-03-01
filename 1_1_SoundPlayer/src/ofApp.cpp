#include "ofApp.h"
int r;
int g;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate (60); // speed drawing frame
    ofSetBackgroundAuto (false); // turn off background erase
    ofBackground (0);
    
    sound.loadSound("guitar.wav"); // load Sound
    sound.setVolume(0.75f);  // set Volume
    sound.setMultiPlay(false);  //multiple layer of sound
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

    ofSoundUpdate();  //update sound engine

    ofLog()<<ofToString(r)+'/'+ofToString(g);


}

//--------------------------------------------------------------
void ofApp::draw(){
   
    ofEnableAlphaBlending();
    
    if (sound.getIsPlaying ()) { // if playing sound, do something
        
        ofSetColor (ofRandom(255), 20);
        ofCircle (p.x, p.y, rad);  // set interative parameter to the circle
    }

    ofDisableAlphaBlending ();
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
    float h = ofGetHeight (); // screen height
    
    
    float speed = (h - y) / h * 3.0;
    if (speed> 0) {
        sound.play ();// Start of a new sample
        sound.setSpeed(speed); // Set the playback speed
       
        // Remember the point and the radius of the circle to draw
        p = ofPoint (x, y);
        rad = (3 - speed);
        rad = 10 * rad * rad;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}
//-------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
