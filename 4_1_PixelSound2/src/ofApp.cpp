#include "ofApp.h"



const int N = 30;		//Number of bands in spectrum
float spectrum[ N ];	//Smoothed spectrum values

int z = 5;		//Band index in spectrum, affecting something;
//int size = 10;		//Band index in spectrum, affecting something else;



//--------------------------------------------------------------
void ofApp::setup(){
    //cam.rotate(180, 1.0, 0, 0);
    ofBackground(0,0,0);
    
    image.loadImage("squirrel.png");
    texture.loadImage("texture.png");
    texture.setImageType(OF_IMAGE_GRAYSCALE);

    ofSetHexColor(0x666666);

    sound.loadSound("sound.mp3");
    sound.play();
    
    for (int i=0; i<N; i++) {
       spectrum[i] = 0.0f;
    }
   
    ofSetFrameRate(15);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    ////////////////////////////////////////////////////
    
    ofSoundUpdate();
    
    
    float *val = ofSoundGetSpectrum( N );
    
    for ( int i=0; i<N; i++ ) {
        spectrum[i] *= 0.75;	//decreasing number
        spectrum[i] = max( spectrum[i], val[i] );
    }
    
    ////////////////////////////////////////////////////
    
    ofLog()<<"z="+ ofToString(spectrum[z]);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();

    ofTranslate(-image.width*1.5,-image.height*1.5);
   //image.draw(0,0);
    
	unsigned char * graypixels = texture.getPixels();
    unsigned char * pixels = image.getPixels();

    for (int i = 0; i < image.width; i+=2){
		for (int j = 0; j < image.height; j+=2){
            
			int value = graypixels[j * image.width + i];
            int effectZ = ofMap(spectrum[z], 0, 0.2, 0,-50);
    
            // ofSetColor(value, value, value);
            
            // the z
            int pct = int (ofMap(value, 0,255, 0, 127));
            
            // color value from pixel
            int red = pixels[ (j * image.width + i) * 3];
			int green = pixels[ (j * image.width + i) * 3 + 1];
			int blue = pixels[ (j * image.width + i) * 3 + 2];
            
            
            ofSetColor(red,green,blue);

            // draw x,y,z for circle
            ofCircle(i*3, j*3, pct*effectZ, 2);
		
        }
	}
   
    cam.end();
    
    
    // Draw spectrum at the left bottom corner for visual reference
    
    ofFill();
    ofSetColor(200);
    for (int i=0; i<N; i++) {
        
        ofRect( 10 + i * 12, 700, 10, -spectrum[i] * 200 );
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
