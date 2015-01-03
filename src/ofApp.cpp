#include "ofApp.h"



//-------------------------------------------------------------
ofApp::~ofApp() {
    
    
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
            buttons[x][y].create(25+x*35, 45+y*35, 30, 30, "rect", x + y + 48);
        }
    play = *new Button;
    play.create(25, 5, 30, 30, "tri", 0);
    playback = false;
    
    midiOn = *new Button;
    midiOn.create(100, 5, 15, 15, "rect", 0);
    isMidi = false;
    
    mappingButton = *new Button;
    mappingButton.create(100, 25, 15, 15, "rect", 0);
    mapping = "standard";
    
    waveButton = *new Button;
    waveButton.create(450, 5, 15, 15, "rect", 0);
    wavetype = "square";
    
    tempoSlider.setup("Tempo:", 120.0, 30.0, 240.0);
    tempoSlider.addListener(this, & ofApp::tempoChanged);
    tempoSlider.setPosition(450, 25);
    tempo = 120.0;
    
    //load font and stuff
    text.loadFont("verdana.ttf",20,true,true);
    text.setLineHeight(25.0f);
    text.setLetterSpacing(1.037);
    
    smalltext.loadFont("verdana.ttf",10,true,true);
    smalltext.setLineHeight(17.0f);
    smalltext.setLetterSpacing(1.037);
    
    //init time stuff
    startTime = 0.0;
    bpm = 120;
    newWave.isOn = false;
    ptime = time = 0;
    
    curNote = 48;
    voiceCount = 0;
    
    sampleRate 			= 44100; /* Sampling Rate */
    initialBufferSize	= 512;
    
    
    //init midi
    midiOut.listPorts();
    
    midiOut.openPort(0);
    
    ofSoundStreamSetup(2,0,this, sampleRate, initialBufferSize, 4);
    
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
    midiOn.display();
    mappingButton.display();
    waveButton.display();
    tempoSlider.draw();
    if (playback) ofSetColor(0, 255, 0);
    else ofSetColor(0);
    text.drawString("RIPPLE", 900, 35);
    ofSetColor(0);
    smalltext.drawString("midi off/on (on disables in-app sound)", 120, 15);
    smalltext.drawString("mapping standard/one octave", 120, 35);
    smalltext.drawString("wave square/line", 470, 15);
}

void ofApp::beat() {
    if (newWave.isOn) {
        if (newWave.iteration < 14) {
            newWave.iteration++;
            for(int x = 0; x < 28; x++)
                for (int y = 0; y < 16; y++) {
                    //monstrous statement to select buttons corresponding to the current iteration
                    if (wavetype == "square")
                    {
                        if (((x <= newWave.startX + newWave.iteration) && (x >= newWave.startX - newWave.iteration)) && ((y <= newWave.startY + newWave.iteration) && (y >= newWave.startY - newWave.iteration)) && !(((x < newWave.startX + newWave.iteration) && (x > newWave.startX - newWave.iteration)) && ((y < newWave.startY + newWave.iteration) && (y > newWave.startY - newWave.iteration))))
                        {
                            triggerStuff(x,y);
                            
                        }
                    }
                    else if (wavetype == "line")
                    {
                        if (x == newWave.startX + newWave.iteration)
                        {
                            triggerStuff(x,y);
                        }
                    }
                    
                }
        }
        else {
            newWave.isOn = false;
        }
    }
}

void ofApp::triggerStuff(int x, int y) {
    buttons[x][y].lightUp();
    if (buttons[x][y].checkIfOn()) {
        curNote = buttons[x][y].getNote();
        Voice v = *new Voice(curNote, adsrData);
        
        //if we're using all voices, delete the first one so we can add the new one
        if (voices.size() >= 16) {
            voices.pop_front();
        }
        
        v.start();
        voices.push_back(v);
        
        if (isMidi) midiOut.sendNoteOn(1, curNote);
    }
}



//--------------------------------------------------------------
void ofApp::audioRequested 	(float * output, int bufferSize, int nChannels){
    
    
    
    
    for (int i = 0; i < bufferSize; i++){
        
        //run timer with a phasor
        time = timer.phasor(tempo/60, 0, 16);
        //check if we should play on-beat
        if (playback && time == 16) beat();
        //previous time will be current time next time
        ptime = time;
        
        double out = 0;
        for (int v = 0; v < voices.size(); v++) {
            if (voices[v].isActive() && voices[v].env.valindex >= 6) {
                
                if (isMidi) {
                    voices[v].stop();
                    midiOut.sendNoteOff(1, voices[v].note);
                }
            }
            double oscOut = voices[v].oscOut("sine");
            if (!isMidi) out += oscOut;
        }
        
        
        mix.stereo(out, outputs, 0.5);
        
        output[i*nChannels] = outputs[0];
        output[i*nChannels+1] = outputs[1];
        
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
    if (key == 32) {
        play.toggleButton();
        playback = !playback;
        startTime = ofGetElapsedTimeMillis();
    }
        
}

void ofApp::tempoChanged(double & t) {
    tempo = t;
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
        newWave.iteration = 0;
        if (!playback) newWave.isOn = false;
        startTime = ofGetElapsedTimeMillis();
    };
    
    if (midiOn.checkIfPressed(mx, my)) {
        isMidi = !isMidi;
        midiOn.toggleButton();
    };
    
    if (mappingButton.checkIfPressed(mx, my)) {
        mappingButton.toggleButton();
        if (mapping == "standard")
        {
            mapping = "1octave";
            for(int x = 0; x < 28; x++)
                for (int y = 0; y < 16; y++) {
                    buttons[x][y].setNote((x*(y-1) + x) % 12 + 60);
                }
        }
        else
        {
            mapping = "standard";
            for(int x = 0; x < 28; x++)
                for (int y = 0; y < 16; y++) {
                    buttons[x][y].setNote(x + y + 24);
                }
        }
    }
    
    if (waveButton.checkIfPressed(mx, my)) {
        waveButton.toggleButton();
        if (wavetype == "square")
        {
            wavetype = "line";
        }
        else
        {
            wavetype = "square";
        }
    };
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

void ofApp::exit() {
    
    // clean up
    midiOut.closePort();
}

