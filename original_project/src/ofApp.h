#pragma once

#include "ofMain.h"
#include "AudioAnalyser.h"

class Element {
public:
	float tone;
	ofColor color;

	Element() : tone(0), color(ofColor::white) {};
	Element(float tone, ofColor color) : tone(tone), color(color) {};
	float getTone() { return tone; }
	ofColor getColor() { return color; }
	void setTone(float tone) { this->tone = tone; }
	void setColor(ofColor color) { this->color = color; }
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		//toggle debug screen
		bool debugOn;				//debug screen controller
		bool paused;
		void keyPressed(int key);
		void debugScreen();			//draw debug screen

		//audio 
		ofFmodSoundPlayer soundPlayer;
		AudioAnalyser audioAnalyser; 
		ofTrueTypeFont font;

		//time
		float position;
		
		//Element vec
		std::vector<Element> elementVec;
		int getMaxElement();
		
		//center of screen
		ofVec2f center;
		
		//different phases
		void intro(bool phase2);
		void verse1(bool phase2);
		void verse2();
		void prechorus1(bool phase2);
		void prechorus2(bool phase2);
		void chorus1();
		void chorus2();
		void chorus3(bool phase2);
		void bridge(bool phase2);

		//bass animations
		void bassFourSquare();
		void bassCircle();

		//tone animations
		void allToneOneCircle(bool move);
		void ToneCircle(int tone1, int tone2);
		void ToneCircle(int tone1, int tone2, int tone3);
		void ToneCircle(int tone1, int tone2, int tone3, int tone4);
		void ToneWings(float tone1, float tone2, ofColor color1, ofColor color2);
		void allToneSquares();

};

