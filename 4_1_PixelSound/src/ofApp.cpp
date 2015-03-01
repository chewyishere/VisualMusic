#include "ofApp.h"


////////////////////
const int N = 20;		//Number of bands in spectrum
float spectrum[ N ];	//Smoothed spectrum values

int BandAlpha = 3;		//Band index in spectrum, affect something
int BandSize = 0;		//Band index in spectrum, affect something else

//--------------------------------------------------------------
void ofApp::setup(){
    
    //image
    
    ofEnableAlphaBlending();
    img.setAnchorPercent(0.5, 0.5);
    ofBackground(255);
    img.loadImage("dog.jpg");
    w = img.width;
    h = img.height;
    img.allocate(w, h,OF_IMAGE_COLOR);
    
    alpha = 100;
    pixelSize = 3;
    
    //sound
    sound.loadSound( "astral.mp3" );
    
    sound.setLoop( false );
    sound.play();
    
    //spectrum
    
    for (int i=0; i<N; i++) {
        spectrum[i] = 0.0f;
    }


}

//--------------------------------------------------------------
void ofApp::update(){

    
    alpha = ofMap(spectrum[BandAlpha], 0,0.2, 50, 255);
    pixelSize = ofMap(spectrum[BandSize],0, 0.8, 2, 10);
    
    
   
    ////////////////////////////////////////////////////
    
    ofSoundUpdate();
    
    
    float *val = ofSoundGetSpectrum( N );
    
    for ( int i=0; i<N; i++ ) {
        spectrum[i] *= 0.95;	//decreasing number
        spectrum[i] = max( spectrum[i], val[i] );
    }
    
    ////////////////////////////////////////////////////

    ofLog()<<"BandAlpha = " + ofToString(spectrum[BandAlpha])
    + "BandSize =" + ofToString(spectrum[BandSize]);
    

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // get pixel information
    unsigned char * pixels = img.getPixels();
    
    int skip = 10;

    for (int i=0; i <w; i= i+skip){
        for( int j=0; j<h; j = j+skip){
            
     int r = pixels[j * w * 3 + i * 3];
     int g = pixels[j * w * 3 + i * 3 + 1];
     int b = pixels[j * w * 3 + i * 3 + 2];
    
     ofColor sampleColor (r,g,b);
    
     float brightness = sampleColor.getBrightness();
     float pct = 1.0 - brightness / 255.0f;  //get dark value
            
    pct += ofMap(ofNoise(i, j, ofGetFrameNum()*0.01)*spectrum[BandAlpha]*10, 0, 1, -3, 3);
            
    ofSetColor(r, g, b,alpha);
   
    // ofSetColor(brightness,brightness,brightness, alpha);
           
    ofSetRectMode(OF_RECTMODE_CENTER); //set rectangle mode to the center
    ofRect(i, j,pixelSize*pct,pixelSize*pct);
            
    //ofCircle(i, j,pixelSize*pct);
            
        }
    }
    
    
    ////////////////////////////////////////////////////
    // Draw spectrum at the left bottom corner for visual reference
    
    ofFill();
    ofSetColor(200);
    for (int i=0; i<N; i++) {
        
        ofRect( 10 + i * 5, 700, 4, -spectrum[i] * 200 );
    }
    ////////////////////////////////////////////////////


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
