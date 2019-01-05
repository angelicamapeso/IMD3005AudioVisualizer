# IMD3005AudioVisualizer

This contains the Demo and the Original code for the Audio Visualizer.

I could not include the actual audio files. 

To run the code, the following are required:
- Visual Studio
- OpenFrameworks for Visual Studio (https://openframeworks.cc/download/)
- https://github.com/kylemcdonald/ofxFft (OpenFrameworks Addon) 

BEFORE STARING:
You'll need to add in your own music file into the bin > data folder, then go into the ofApp.cpp file and link your audio file where indicated.

ex. soundPlayer.load("mySong.mp3"); 

1. In the OpenFrameworks root folder,search for the projectGenerator-vs
2. Run the projectGenerator application.
3. Import the project file (either the "demo_project" folder or the "original_project" folder)
4. **!!IMPORTANT** Select the ofxFft Addon
5. Click Update
6. Open in IDE 
7. Before you run it, Debug in x64
