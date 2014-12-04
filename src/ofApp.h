#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"
#include "button.h"


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
    
    
protected:
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
    struct voice {
        maxiOsc osc;
        maxiEnv env;
        double vol;
        Boolean isOn;
    };
    maxiOsc timer;
    int time, ptime;
    voice voices[64];
};

#endif
