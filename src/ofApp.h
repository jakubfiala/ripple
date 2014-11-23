#pragma once

#include "ofMain.h"
#include "button.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    protected:
        Button buttons[28][16];
        Button play;
        Boolean playback;
        ofTrueTypeFont text;
        double startTime, bpm;
        void beat();
        double getBeatTime(double tempo);
		
};
