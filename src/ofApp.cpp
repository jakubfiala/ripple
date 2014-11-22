#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(200);
    for(int x = 0; x < 28; x++)
        for (int y = 0; y < 16; y++) {
            buttons[x][y] = *new Button;
            buttons[x][y].create(25+x*35, 30+y*35, 30, 30);
        }
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
    for(int x = 0; x < 28; x++)
        for (int y = 0; y < 16; y++) {
            if (buttons[x][y].checkIfPressed(mx, my) && !buttons[x][y].checkIfOn()) {
                buttons[x][y].toggleButton();
            };
        }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int mx, int my, int button){
    for(int x = 0; x < 28; x++)
        for (int y = 0; y < 16; y++) {
            if (buttons[x][y].checkIfPressed(mx, my)) {
                buttons[x][y].toggleButton();
            };
        }

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
