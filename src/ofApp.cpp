/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */


#include "ofApp.h"



//-------------------------------------------------------------
ofApp::~ofApp() {
    
    /*you should probably delete myData for any sample object
     that you've created in ofApp.h*/
    
}


//--------------------------------------------------------------
void ofApp::setup(){
    /* some standard setup stuff*/
    
    ofEnableAlphaBlending();
    ofSetupScreen();
    ofBackground(200);
    ofSetVerticalSync(true);
    
    //create buttons
    for(int x = 0; x < 28; x++)
        for (int y = 0; y < 16; y++) {
            buttons[x][y] = *new Button;
            buttons[x][y].create(25+x*35, 45+y*35, 30, 30, "rect");
        }
    play = *new Button;
    play.create(25, 5, 30, 30, "tri");
    playback = false;
    
    //load font and stuff
    text.loadFont("verdana.ttf",20,true,true);
    text.setLineHeight(25.0f);
    text.setLetterSpacing(1.037);
    
    //init time stuff
    startTime = 0.0;
    bpm = 120;
    newWave.isOn = false;
    
    
    sampleRate 			= 44100; /* Sampling Rate */
    initialBufferSize	= 512;
    
    
    ofSoundStreamSetup(2,0,this, sampleRate, initialBufferSize, 4);}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    for(int x = 0; x < 28; x++)
        for (int y = 0; y < 16; y++) {
            buttons[x][y].display();
        }
    play.display();
    text.drawString("RIPPLE", 900, 35);
    if (playback && fmod((ofGetElapsedTimeMillis() - startTime), getBeatTime(bpm)) <= 10.0) {
        beatp();
    }
    
}

void ofApp::beatp() {
    printf("%i",newWave.iteration);
    if (newWave.isOn) {
        if (newWave.iteration < 14) {
            newWave.iteration++;
            for(int x = 0; x < 28; x++)
                for (int y = 0; y < 16; y++) {
                    //monstrous statement to select buttons corresponding to the current iteration
                    if (((x <= newWave.startX + newWave.iteration) && (x >= newWave.startX - newWave.iteration)) && ((y <= newWave.startY + newWave.iteration) && (y >= newWave.startY - newWave.iteration)) && !(((x < newWave.startX + newWave.iteration) && (x > newWave.startX - newWave.iteration)) && ((y < newWave.startY + newWave.iteration) && (y > newWave.startY - newWave.iteration)))) {
                        
                        buttons[x][y].lightUp();
                    }
                }
        }
        else {
            newWave.isOn = false;
        }
    }
}

double ofApp::getBeatTime(double tempo) {
    return 60000/tempo;
}



//--------------------------------------------------------------
void ofApp::audioRequested 	(float * output, int bufferSize, int nChannels){
    
    for (int i = 0; i < bufferSize; i++){
        
        
        
        
    }
    
}

//--------------------------------------------------------------
void ofApp::audioReceived 	(float * input, int bufferSize, int nChannels){
    
    
    /* You can just grab this input and stick it in a double, then use it above to create output*/
    
    for (int i = 0; i < bufferSize; i++){
        
        /* you can also grab the data out of the arrays*/
        
        
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
void ofApp::mouseDragged(int mx, int my, int button){
    if (!playback) {
        for(int x = 0; x < 28; x++)
            for (int y = 0; y < 16; y++) {
                if (buttons[x][y].checkIfPressed(mx, my) && !buttons[x][y].checkIfOn()) {
                    buttons[x][y].toggleButton();
                };
            }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int mx, int my, int button){
    if (!playback) {
        //turn on the corresponding button
        for(int x = 0; x < 28; x++)
            for (int y = 0; y < 16; y++) {
                if (buttons[x][y].checkIfPressed(mx, my)) {
                    buttons[x][y].toggleButton();
                };
            }
    }
    else {
        //begin the ripple
        for(int x = 0; x < 28; x++)
            for (int y = 0; y < 16; y++) {
                if (buttons[x][y].checkIfPressed(mx, my)) {
                    buttons[x][y].lightUp();
                    newWave.isOn = true;
                    newWave.startX = x;
                    newWave.startY = y;
                    newWave.iteration = 0;
                };
            }
    }
    
    
    if (play.checkIfPressed(mx, my)) {
        play.toggleButton();
        playback = !playback;
        startTime = ofGetElapsedTimeMillis();
    };
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

