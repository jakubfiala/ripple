#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(200);
    
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
    bpm = 180;
    
}

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
        beat();
    }
}

void ofApp::beat() {
    printf("beat \n");
}

double ofApp::getBeatTime(double tempo) {
    return 60000/tempo;
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
void ofApp::mouseReleased(int mx, int my, int button){
    if (playback) {
        
    }
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
