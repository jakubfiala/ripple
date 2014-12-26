#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxMaxim.h"
#include "button.h"
#include "voice.h"
#include <deque>


class ofApp : public ofBaseApp{
    
public:
    ~ofApp();
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    void audioRequested 	(float * input, int bufferSize, int nChannels);
    void audioReceived 	(float * input, int bufferSize, int nChannels);
    
    int		initialBufferSize;
    int		sampleRate;
    
    double outputs[2];
    ofxMaxiMix mix;
    
    //void exit();
   // void guiEvent(ofxUIEventArgs &e);
    
    
protected:
   // ofxUICanvas *gui;
    
    Button buttons[28][16];
    Button play;
    Boolean playback;
    ofTrueTypeFont text;
    double startTime, bpm;
    struct wave {
        Boolean isOn;
        int startX;
        int startY;
        int iteration;
    } newWave;
    void beat();
    double getBeatTime(double tempo);
    maxiOsc timer, synth;
    int time, ptime, voiceCount, curNote;
    maxiEnvelope adsr;
    convert converter;
    deque<Voice> voices;
    double adsrData[8] = {0,1,1.0,20,0.125,125,0,500};
    
};

#endif
