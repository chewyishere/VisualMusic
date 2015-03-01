#include "ofApp.h"

const int N = 20;		//Number of bands in spectrum
float spectrum[ N ];	//Smoothed spectrum values

//--------------------------------------------------------------
void ofApp::setup(){

    sound.loadSound( "02DirtyOrchestra.mp3" );
    
    sound.setLoop( true );
    sound.play();
    
    
    for (int i=0; i<N; i++) {
        spectrum[i] = 0.0f;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate();
    
    float *val = ofSoundGetSpectrum( N );      // get valume from each bandwidth
    
    for ( int i=0; i<N; i++ ) {
        spectrum[i] *= 0.97;   //decreasing value
        spectrum[i] = max( spectrum[i], val[i] );
        
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    ofFill();
    
    ofPushMatrix();
    ofTranslate(ofGetWindowWidth()/4,ofGetWindowHeight()/2+100);
    
    //Draw spectrum
    
    for (int i=0; i<N; i++) {
        
        ofSetColor(100);
        
        //        x1 = distance between each bandwidth
        //        y1 = height of the spectrum
        //        w = width of each bandwidth
        //        h = - amplitude
        //        i = number of bandwidth
        
        
        // ofRect(x1,y1,w,h);
        ofRect( i*25, 0, 20,-300);  //background
        
        ofSetColor(255);
        ofRect( i*25, 0, 20, -spectrum[i] * 300 );
    }
    
    ofPopMatrix();
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
