#include "ofApp.h"



const int N = 10;		//Number of bands in spectrum
float spectrum[ N ];	//Smoothed spectrum values
float rad = 20;		//Cloud raduis parameter
float color = 20;		//Cloud points velocity parameter
int bandRad = 1;		//Band index in spectrum, affecting Rad value
int bandColor = 4;		//Band index in spectrum, affecting Color value

//--------------------------------------------------------------
void ofApp::setup(){
    
    
	sound.loadSound( "06Fireball.mp3" );
	sound.setLoop( true );
	sound.play();
    
    // get the spectrum
	for (int i=0; i<N; i++) {
		spectrum[i] = 0.0f;
	}

}

//--------------------------------------------------------------
void ofApp::update(){
    
    ////////////////////////////////////////////////////
    
	ofSoundUpdate();
    
	float *val = ofSoundGetSpectrum( N );
    
	for ( int i=0; i<N; i++ ) {
		spectrum[i] *= 0.97;	//Slow decreasing
		spectrum[i] = max( spectrum[i], val[i] );
	}
    
    ////////////////////////////////////////////////////
	//Update rad and color from spectrum
    
	rad = ofMap( spectrum[ bandRad ], 0, 0.8, 10, 400, true );
	color = ofMap( spectrum[ bandColor ], 0, 0.45, 0, 255 );

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
	ofBackground( 0, 0, 0);	//Set up the background
    
    ofDrawBitmapStringHighlight("bandRad ="+ ofToString(spectrum[ bandRad ]), 10, 20);
    ofDrawBitmapStringHighlight("bandColor ="+ofToString(spectrum[ bandColor ]), 10, 50);
    
	ofFill();
    
    //Draw spectrum
    
	for (int i=0; i<N; i++) {
        ofSetColor( 200 );
		ofRect( 10 + i * 6, 700, 5, -spectrum[i] * 200 );
	}
    
    // draw the visualization
    
    ofSetColor(color,50,80,200);
    ofCircle(ofGetWindowSize()/2, rad);
	
    

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
