#include "ofApp.h"


ofImage image;		//Original image
ofImage image2;		//Modified image

////////////////////
const int N = 64;		//Number of bands in spectrum
float spectrum[ N ];	//Smoothed spectrum values

int DistortionX = 2;		//Band index in spectrum, affecting distortion X
int DistortionY = 4;		//Band index in spectrum, affecting distortion Y

//--------------------------------------------------------------
void ofApp::setup(){

    image.loadImage( "monroe.jpg" );	//Load image
    image2.clone( image ); //Copy image to image2
    
    ofSetWindowShape(image.width, image.height);
    
    sound.loadSound( "vox6.wav" );
    
    sound.setLoop( false );
    sound.play();
    
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
        spectrum[i] *= 0.95;	//decreasing number
        spectrum[i] = max( spectrum[i], val[i] );
    }
    ////////////////////////////////////////////////////
    
    
    for (int y=0; y<image.height; y++) {
        for (int x=0; x<image.width; x++) {
            
            float sinAmp = ofNoise(ofGetElapsedTimef())*0.05; // noise value
           
            //float ampX = sin( x * sinAmp ) * spectrum[DistortionX]; // PLAY WITH THIS!
            // float ampY = tanf( y * sinAmp ) * spectrum[DistortionY]; // PLAY WITH THIS!
           
            float ampX = sin( x * sinAmp ) * spectrum[DistortionX]; // PLAY WITH THIS!
            float ampY = sin( y * sinAmp ) * spectrum[DistortionY]; // PLAY WITH THIS!
            
            int x1 = x + ampX*100;
            int y1 = y + ampY*100;
            
           //Clamp x1 to range [0, image.width-1]
            x1 = ofClamp( x1, 0, image.width - 1 );
            y1 = ofClamp( y1, 0, image.height - 1 );
            
            //Set image2(x, y) equal to image(x1, y)

            ofColor color = image.getColor( x1, y1 );
            
            image2.setColor( x, y, color );    //Build image2 using image
        }
    }
    image2.update();
    


}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
    image2.draw( 0, 0 );
    
    ////////////////////////////////////////////////////
    ofDrawBitmapStringHighlight("DistortionX ="+ ofToString(spectrum[DistortionX]/2), 10, 20);
    ofDrawBitmapStringHighlight("DistortionY ="+ofToString(spectrum[DistortionY]*2), 10, 50);

    // Draw spectrum at the left bottom corner for visual reference
    
    ofFill();
    ofSetColor(200);
    for (int i=0; i<N; i++) {
    
        ofRect( 10 + i * 6, 600, 5, -spectrum[i] * 100 );
    }
    ////////////////////////////////////////////////////
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key ==  '1') {
        sound.loadSound( "vox1.wav" );
                sound.play();
    }
    
    if (key ==  '2') {
        sound.loadSound( "vox2.wav" );
                sound.play();
        }

    if (key ==  '3') {
        sound.loadSound( "vox3.wav" );
                sound.play();
        }
    if (key ==  '4') {
        sound.loadSound( "vox4.wav" );
                sound.play();
        }
    if (key ==  '5') {
        sound.loadSound( "vox5.wav" );
                sound.play();
        }
    if (key ==  '6') {
        sound.loadSound( "vox6.wav" );
                sound.play();
        }
    if (key ==  ' ') {
        sound.loadSound( "uto.mp3" );
        sound.play();
    }
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
