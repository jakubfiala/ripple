#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxMaxim.h"
#include "button.h"


class ofApp : public ofBaseApp{
    
public:
    ~ofApp();/* deconsructor is very useful */
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
    
    void audioRequested 	(float * input, int bufferSize, int nChannels); /* output method */
    void audioReceived 	(float * input, int bufferSize, int nChannels); /* input method */
    
    int		initialBufferSize; /* buffer size */
    int		sampleRate;
    
    
    /* stick you maximilian stuff below */
    
    double wave,sample,outputs[2];
    ofxMaxiMix mymix;
    ofxMaxiOsc sine1;
    ofxMaxiSample beats,beat;
    
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
    void beatp();
    double getBeatTime(double tempo);
    
};

#endif
