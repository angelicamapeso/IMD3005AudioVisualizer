#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//screen setup
	ofSetVerticalSync(true);
	ofSetWindowShape(960, 720);
	ofSetBackgroundColor(ofColor::black);
	
	//sound player setup
	//music: FakeLove (makaihbeats.net) by Makaih Beats, downloaded from http://freemusicarchive.org
	//soundPlayer.load("FAKE LOVE"); <-- since I modified the audio file, I cannot include it here. But, this is where it would go.
	soundPlayer.setLoop(true);
	soundPlayer.play();

	//audio analyser
	audioAnalyser.init(&soundPlayer, 20);

	//font
	font.load("fonts/font.ttf", 12, true);

	//debug
	debugOn = false;
	paused = false;

	//colour setup
	ofColor ColTone1 = ofColor(178,82,109);
	ofColor ColTone2 = ofColor(5, 47, 59);
	ofColor ColTone3 = ofColor(135,4,69);
	ofColor ColTone4 = ofColor(1, 122, 138);
	ofColor gray = ofColor(68, 68, 68);

	//initializing elements
	elementVec.push_back(Element(0,gray));
	elementVec.push_back(Element(0, ColTone1));
	elementVec.push_back(Element(0, ColTone2));
	elementVec.push_back(Element(0, ColTone3));
	elementVec.push_back(Element(0, ColTone4));

	//center
	center = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);

}

//--------------------------------------------------------------
void ofApp::update(){
	audioAnalyser.update();
	position = soundPlayer.getPosition() * 30;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetCircleResolution(180);

	//captured linear averages
	float bass = audioAnalyser.getLinearAverage(0); //200-260
	
	float tone1 = audioAnalyser.getLinearAverage(17);
	float tone2 = audioAnalyser.getLinearAverage(13);
	float tone3 = audioAnalyser.getLinearAverage(6);
	float tone4 = audioAnalyser.getLinearAverage(4);

	//map linear averages
	float mappedBass = ofMap(bass, 100, 260, 0.0, 1.0, true);

	float mappedTone1 = ofMap(tone1, 40, 45, 0.0, 1.0, true);
	float mappedTone2 = ofMap(tone2, 25, 35, 0.0, 1.0, true);
	float mappedTone3 = ofMap(tone3, 25, 35, 0.0, 1.0, true);
	float mappedTone4 = ofMap(tone4, 60, 70, 0.0, 1.0, true);

	//save to elements
	elementVec[0].setTone(mappedBass);
	elementVec[1].setTone(mappedTone1);
	elementVec[2].setTone(mappedTone2);
	elementVec[3].setTone(mappedTone3);
	elementVec[4].setTone(mappedTone4);

	//background	
	ofSetBackgroundColor(28,28,28);

	float incrementTime = 30 / 15;

	//graphics
	ofFill();
	if (position >= 0 && position < incrementTime) {
		//intro phase1
		intro(false);
	}
	else if (position >= incrementTime  && position < incrementTime*2) {
		//intro phase2
		intro(true);
	}
	else if (position >= incrementTime * 2 && position < incrementTime* 3) {
		//verse1 phase1
		verse1(false);
	}
	else if (position >= incrementTime * 3 && position < incrementTime * 4) {
		//verse1 phase2
		verse1(true);
	}
	else if (position >= incrementTime * 4 && position < incrementTime * 5) {
		//prechor phase1
		prechorus1(false);
	}
	else if (position >= incrementTime * 5 && position < incrementTime * 6) {
		//prechor phase2
		prechorus1(true);
	}
	else if (position >= incrementTime * 6 && position < incrementTime * 7) {
		//chor 1
		chorus1();
	}
	else if (position >= incrementTime * 7 && position < incrementTime * 8) {
		//verse2 
		verse2();
	}
	else if (position >= incrementTime * 8 && position < incrementTime * 9) {
		//prechor phase1
		prechorus2(false);
	}
	else if (position >= incrementTime * 9 && position < incrementTime * 10) {
		//prechor phase2
		prechorus2(true);
	}
	else if (position >= incrementTime * 10 && position < incrementTime * 11) {
		//chor2
		chorus2();
	}
	else if (position >= incrementTime * 11 && position < incrementTime * 12) {
		//bridge phase1
		bridge(false);
	}
	else if (position >= incrementTime * 12 && position < incrementTime * 13) {
		//bridge phase2
		bridge(true);
	}
	else if (position >= incrementTime * 13 && position < incrementTime * 14) {
		//chor3 phase1
		chorus3(false);
	}
	else if (position >= incrementTime * 14 && position < incrementTime * 15) {
		//chor3 phase2
		chorus3(true);
	}


	
	if (debugOn) {
		debugScreen();
	}
}

//--------------------------------------------------------------
void ofApp::debugScreen() {
	ofSetRectMode(OF_RECTMODE_CORNER);

	//Set background
	ofSetColor(0, 0, 0, 200);
	ofFill();
	ofDrawRectangle(0, 0, 960, 360);

	//volume
	ofSetColor(255, 255, 255, 255);
	font.drawString("Volume", 84, 40);
	font.drawString("Left", 20, 95);
	font.drawString("Mix", 20, 187);
	font.drawString("Right", 20, 277);

	ofDrawCircle(115, 90, audioAnalyser.getLeftLevel() * 90);
	ofDrawCircle(115, 180, audioAnalyser.getMixLevel() * 90);
	ofDrawCircle(115, 270, audioAnalyser.getRightLevel() * 90);

	//linear averages
	audioAnalyser.drawLinearAverages(210, 40, 690, 80);

	//indicators

	//drum
	ofSetColor(elementVec[0].getColor(), elementVec[0].getTone() * 255);
	ofDrawRectangle(230, 270, 40, 40);

	ofSetColor(255, 255, 255, 255);
	font.drawString("Drums", 230, 330);

	//tones
	ofSetColor(elementVec[1].getColor(), elementVec[1].getTone() * 255);
	ofDrawRectangle(310, 220, 40, 40);

	ofSetColor(elementVec[2].getColor(), elementVec[2].getTone() * 255);
	ofDrawRectangle(360, 220, 40, 40);

	ofSetColor(elementVec[3].getColor(), elementVec[3].getTone() * 255);
	ofDrawRectangle(310, 270, 40, 40);

	ofSetColor(elementVec[4].getColor(), elementVec[4].getTone() * 255);
	ofDrawRectangle(360, 270, 40, 40);


	ofSetColor(255, 255, 255, 255);
	font.drawString("Tones", 310, 330);

	//time
	font.drawString("Current Time: " + ofToString(position) + "s", 700, 340);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') {
		debugOn = !debugOn;
	}
	if (key == 'k' || key == 'K') {
		paused = !paused;
		soundPlayer.setPaused(paused);
	}
	if (key == 'j' || key == 'J') {
		float position = soundPlayer.getPosition();
		soundPlayer.setPosition(position - 0.05);
	}
	if (key == 'l' || key == 'L') {
		float position = soundPlayer.getPosition();
		soundPlayer.setPosition(position + 0.05);
	}

}

//--------------------------------------------------------------
int ofApp::getMaxElement() {
	float maxValue = 0;
	int maxElement = 1;
	for (int i = 1; i < 5; i++) {
		if (elementVec[i].getTone() > maxValue) {
			maxValue = elementVec[i].getTone();
			maxElement = i;
		}
	}
	return maxElement;
}

//--------------------------------------------------------------
void ofApp::intro(bool phase2) {
	if (phase2) {
		bassFourSquare();
		allToneOneCircle(true);
	}
	else {
		allToneOneCircle(false);
	}
}

//--------------------------------------------------------------
void ofApp::verse1(bool phase2) {
	if (phase2) {
		bassFourSquare();
		ToneWings(elementVec[1].getTone(), elementVec[2].getTone(),
			elementVec[0].getColor(), elementVec[0].getColor());
		ofPushMatrix();
			ofTranslate(0, elementVec[0].getTone() * 50);
			bassCircle();
			ToneCircle(3, 4);
		ofPopMatrix();
	}
	else {
		bassFourSquare();
		bassCircle();
		ToneCircle(3, 4);
	}
}

//--------------------------------------------------------------
void ofApp::prechorus1(bool phase2) {
	if (phase2) {
		allToneSquares();
		ofSetColor(elementVec[0].getColor(), audioAnalyser.getMixLevel() * 300);
		ofDrawCircle(center.x-200, center.y, audioAnalyser.getLeftLevel() * 300);
		ofDrawCircle(center.x + 200, center.y, audioAnalyser.getRightLevel() * 300);
		ofPushMatrix();
			ofTranslate(0, elementVec[0].getTone() * 50);
			allToneOneCircle(true);
		ofPopMatrix();
	}
	else {
		allToneSquares();
		ofSetColor(elementVec[0].getColor(), audioAnalyser.getMixLevel() * 300);
		ofDrawCircle(center.x - 200, center.y, audioAnalyser.getLeftLevel() * 300);
		ofDrawCircle(center.x + 200, center.y, audioAnalyser.getRightLevel() * 300);
		allToneOneCircle(false);
	}

}

//--------------------------------------------------------------
void ofApp::chorus1() {
	allToneSquares();
	bassCircle();
	ToneWings(audioAnalyser.getLeftLevel(), audioAnalyser.getRightLevel(),
		ofColor::white, ofColor::white);
	ToneCircle(1, 2, 3);
}

//--------------------------------------------------------------
void ofApp::verse2() {
	bassFourSquare();
	ToneWings(elementVec[1].getTone(), elementVec[2].getTone(),
		elementVec[0].getColor(), elementVec[0].getColor());
	ofPushMatrix();
	ofTranslate(0, elementVec[0].getTone() * 50);
		allToneOneCircle(true);
		ToneCircle(1, 2, 3);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::prechorus2(bool phase2) {
	if (phase2) {
		allToneSquares();
		ofPushMatrix();
		ofTranslate(0, audioAnalyser.getMixLevel() * 100);
		ToneWings(audioAnalyser.getLeftLevel(), audioAnalyser.getRightLevel(), ofColor::white, ofColor::white);
		allToneOneCircle(true);
		ofPopMatrix();
	}
	else {
		allToneSquares();
		bassFourSquare();
		allToneOneCircle(true);
	}
}

//--------------------------------------------------------------
void ofApp::chorus2() {
	allToneSquares();
	bassFourSquare();
	ofPushMatrix();
	ofTranslate(0, elementVec[0].getTone() * 50);
		bassCircle();
		ToneCircle(1, 2, 3, 4);
	ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::bridge(bool phase2) {
	if (phase2) {
		bassFourSquare();
		bassCircle();
		ofPushMatrix();
		ofTranslate(0, audioAnalyser.getMixLevel() * 50);
			ToneWings(audioAnalyser.getLeftLevel(), audioAnalyser.getRightLevel(), ofColor::white, ofColor::white);
			ToneCircle(2, 1,3);
		ofPopMatrix();
	}
	else {
		bassFourSquare();
		ofPushMatrix();
		ofTranslate(0, audioAnalyser.getMixLevel() * 50);
		ToneWings(audioAnalyser.getLeftLevel(), audioAnalyser.getRightLevel(), ofColor::white, ofColor::white);
			ToneCircle(3,4);
		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void ofApp::chorus3(bool phase2) {
	if (phase2) {
		allToneSquares();
		bassFourSquare();
		ToneWings(audioAnalyser.getLeftLevel() +1, audioAnalyser.getRightLevel() +1, elementVec[getMaxElement()].getColor(), elementVec[getMaxElement()].getColor());
		ofPushMatrix();
			ofTranslate(0, audioAnalyser.getMixLevel() * 50);
			bassCircle();
			ToneCircle(1, 2, 3, 4);
		ofPopMatrix();
		
	}
	else {
		allToneSquares();
		bassFourSquare();
		bassCircle();
		ofPushMatrix();
			ofTranslate(0, audioAnalyser.getMixLevel() * 50);
			ToneWings(audioAnalyser.getLeftLevel() +1, audioAnalyser.getRightLevel() +1, elementVec[getMaxElement()].getColor(), elementVec[getMaxElement()].getColor());
			ToneCircle(0, 0);
		ofPopMatrix();
	}
}



//--------------------------------------------------------------
					//BASS ANIMATIONS
//--------------------------------------------------------------
void ofApp::bassFourSquare() {
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofFill();

	ofPushMatrix();
	ofSetColor(elementVec[0].getColor(), (elementVec[0].getTone() * 255) - 100);
	ofDrawRectangle(center.x - 220, center.y - 220, 200, 200);
	ofDrawRectangle(center.x - 220, center.y + 20, 200, 200);
	ofDrawRectangle(center.x + 20, center.y - 220, 200, 200);
	ofDrawRectangle(center.x + 20, center.y + 20, 200, 200);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::bassCircle() {
	ofFill();

	ofSetColor(255, 255, 255, (elementVec[0].getTone() * 100) + 50);
	ofPushMatrix();
	ofTranslate(center);
	ofDrawCircle(0, 0, elementVec[0].getTone() * 50 + 100);
	ofPopMatrix();
}



//--------------------------------------------------------------
					//TONE ANIMATIONS
//--------------------------------------------------------------
void ofApp::allToneOneCircle(bool move) {
	int maxIndex = getMaxElement();
	ofFill();

	ofPushMatrix();
	ofSetColor(elementVec[maxIndex].getColor());
	ofTranslate(center);
	if (move) {
		ofTranslate(0, -25);
		ofTranslate(0, elementVec[maxIndex].getTone() * 50);
	}
	ofDrawCircle(0, 0, audioAnalyser.getMixLevel() * 300);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::ToneWings(float tone1, float tone2, ofColor color1, ofColor color2) {
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofFill();

	ofSetColor(color1, tone1 * 100);
	ofDrawRectangle(center.x - 260, center.y - 50, 100, 100);
	ofDrawRectangle(center.x - 370, center.y - 160, 100, 100);
	ofDrawRectangle(center.x - 370, center.y + 60, 100, 100);

	ofSetColor(color1, tone2 * 100);
	ofDrawRectangle(center.x + 160, center.y - 50, 100, 100);
	ofDrawRectangle(center.x + 270, center.y - 160, 100, 100);
	ofDrawRectangle(center.x + 270, center.y + 60, 100, 100);
}

//--------------------------------------------------------------
void ofApp::allToneSquares() {
	ofSetRectMode(OF_RECTMODE_CENTER);
	
	//squares behind
	ofFill();
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 10; j++) {
			ofSetColor(elementVec[0].getColor(), 80);
			for (int a = 1; a < 5; a++) {
				if (elementVec[a].getTone() > 0) {
					if (a == 1
						&& (j == 2 || j == 7)) {
						ofSetColor(elementVec[a].getColor());
					}
					if (a == 2
						&& (j == 4 || j == 6 || j == 8)) {
						ofSetColor(elementVec[a].getColor());
					}
					if (a == 3
						&& (j == 1 || j == 0 || j == 5)) {
						ofSetColor(elementVec[a].getColor());
					}
					if (a == 4
						&& (j == 3 || j == 9)) {
						ofSetColor(elementVec[a].getColor());
					}
				}
			}
			float rectangleDimension = elementVec[0].getTone() * 50 + 43;
			ofDrawRectangle(96 / 2 * (2 * j + 1), 24 + (96 / 2 * (2 * i + 1)), rectangleDimension, rectangleDimension);
		}
	}

	//overlay
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetColor(10, 10, 10, (100 - elementVec[0].getTone() * 700));
	ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

//--------------------------------------------------------------
void ofApp::ToneCircle(int tone1, int tone2) {
	int entry[2] = { tone1, tone2 };

	ofSetColor(elementVec[0].getColor(), elementVec[0].getTone() * 255);
	ofSetLineWidth(5);
	ofNoFill();

	ofPushMatrix();
		ofTranslate(center);
		ofDrawCircle(0, 0, 200);
	ofPopMatrix();
	
	ofFill();
	for (int i = 0; i < 2; i++) {
		ofSetColor(elementVec[entry[i]].getColor());
		ofPushMatrix();
			ofTranslate(center);
			ofRotate((position * 50) + 360/2*i);
			ofTranslate(0, 200);
			ofDrawCircle(0, 0, elementVec[entry[i]].getTone() *50 + 50);
		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void ofApp::ToneCircle(int tone1, int tone2, int tone3) {
	int entry[3] = { tone1, tone2, tone3 };

	ofSetColor(elementVec[0].getColor() , elementVec[0].getTone() * 255);
	ofSetLineWidth(5);
	ofNoFill();

	std::vector<ofVec2f> ballPositions;
	for (int i = 0; i < 3; i++) {
		ballPositions.push_back(ofVec2f(center.x + 200 * cos(ofDegToRad(position*50 + (360/3 * i))), 
			center.y + 200 * sin(ofDegToRad(position * 50 + (360 / 3 * i)))));
	}

	ofDrawTriangle(ballPositions[0].x, ballPositions[0].y, 
					ballPositions[1].x, ballPositions[1].y, 
					ballPositions[2].x, ballPositions[2].y);

	ofFill();
	for (int i = 0; i < 3; i++) {
		ofSetColor(elementVec[entry[i]].getColor());
		ofDrawCircle(ballPositions[i].x, ballPositions[i].y, elementVec[entry[i]].getTone() * 50 + 50);
	}
}

//--------------------------------------------------------------
void ofApp::ToneCircle(int tone1, int tone2, int tone3, int tone4) {
	ofSetRectMode(OF_RECTMODE_CENTER);
	int entry[4] = { tone1, tone2, tone3, tone4 };

	ofSetColor(elementVec[0].getColor(), elementVec[0].getTone() * 255);
	ofSetLineWidth(5);
	ofNoFill();

	ofPushMatrix();
		ofTranslate(center);
		ofRotate(position * 50);
		ofDrawRectangle(0, 0, 400, 400);
	ofPopMatrix();

	ofFill();
	for (int i = 0; i < 4; i++) {
		ofSetColor(elementVec[entry[i]].getColor());
		ofPushMatrix();
		ofTranslate(center);
		ofRotate(position * 50 + (360 / 4 * i));
		ofTranslate(0, 200);
		ofDrawCircle(0, 0, elementVec[entry[i]].getTone() * 50 + 50);
		ofPopMatrix();
	}
}