//
//  sceneManager.cpp
//  d4nSFPCRunner
//
//  Created by zach on 11/14/15.
//
//

#include "sceneManager.h"
#include "exampleScene.h"
#include "triangleScene.h"
#include "veraAnimatedScene.h"
#include "robbyMolnarScene.h"
#include "robbyRileyScene.h"
#include "yeseulWhitneyScene.h"
#include "johnWhitneyShader01.h"
#include "johnWhitneyShader02.h"
#include "RoyWhitney1.h"
#include "veraFscene.h"
#include "anastasisRileyScene.h"
#include "loloWhitney.h"
#include "loloVera.h"
#include "andyMenkmanDataBendsJpg.h"
#include "andyMenkmanDataBendsPng.h"
#include "andyMenkmanDataBendsTif.h"
#include "CooperBauhaus.h"
#include "memoAktenScene.h"
#include "submotionOrchestraScene.h"
#include "manfredMohrP196A.h"
#include "chrisMurielCooper.h"
#include "chrisRileyCascando.h"
#include "veraMolnarTrapezium.h"
#include "loloVera2.h"
#include "cantusFirmusRiley.h"
#include "chrisVeraInterruptions.h"
#include "aaronMarcusHieroglyphB.h"
#include "veraMolnarLines68.h"
#include "Cooper3dText.h"
#include "alexLissamojiWhitney.h"
#include "janVantommeScene.h"
#include "rodrigoBelfort.h"
#include "rachelScene.h"
#include "RileyArcsRoy.h"
#include "robbyMenkmanScene.h"
#include "yosukeVeraSansTitre.h"
#include "alexGifPaletteDitherMenkman.h"
#include "yeseulMenkmanInstitution.h"
#include "yeseulCooperMessages.h"
#include "yosukeJohnWhitneyMatrix.h"
#include "mgsCooperSymbols.h"
#include "mgsRileyDiamonds.h"
#include "mgsRileyEllipsesAndSquares.h"
#include "mgsVeraMolnarLineStudy.h"
#include "mgsMaedaTimePainter.h"
#include "olegVeraV.h"
#include "sarahgpRileyCircle.h"
#include "mwalczykVeraSquares.h"

void sceneManager::setup(){
    
    font.load("fonts/ProggySmall.fon", 8, false ,false, false, 0, 96);

    scenes.push_back(new CooperBauhaus());  // this might make for a good start scene -Robby & Becca
    scenes.push_back(new RileyArcsRoy());
    scenes.push_back(new rachelScene());
    scenes.push_back(new rodrigoBelfort());
    scenes.push_back(new Cooper3dText());
    scenes.push_back(new chrisVeraInterruptions());
    scenes.push_back(new johnWhitneyShader02());
    scenes.push_back(new chrisRileyCascando());
    scenes.push_back(new memoAktenScene());
    scenes.push_back(new submotionOrchestraScene());
    scenes.push_back(new RoyWhitney1());
    scenes.push_back(new veraFscene());
    scenes.push_back(new robbyMolnarScene() );
    scenes.push_back(new veraAnimatedScene() );
    scenes.push_back(new robbyRileyScene() );
    scenes.push_back(new robbyMenkmanScene());
    scenes.push_back(new yeseulWhitneyScene() );
    scenes.push_back(new johnWhitneyShader01());
    scenes.push_back(new anastasisRileyScene());
    scenes.push_back(new loloWhitney());
    scenes.push_back(new loloVera());
    scenes.push_back(new andyMenkmanDataBendsJpg());
    scenes.push_back(new andyMenkmanDataBendsPng());
    scenes.push_back(new andyMenkmanDataBendsTif());
    scenes.push_back(new manfredMohrP196A());
    scenes.push_back(new veraMolnarTrapezium());
    scenes.push_back(new loloVera2());
    scenes.push_back(new cantusFirmusRiley());
    scenes.push_back(new aaronMarcusHieroglyphB());
    scenes.push_back(new veraMolnarLines68());
    scenes.push_back(new alexLissamojiWhitney());
    scenes.push_back(new yosukeVeraSansTitre());
    scenes.push_back(new alexGifPaletteDitherMenkman());
    scenes.push_back(new yeseulMenkmanInstitution());
    scenes.push_back(new yeseulCooperMessages());
    scenes.push_back(new yosukeJohnWhitneyMatrix());
    scenes.push_back(new mgsCooperSymbols());
    scenes.push_back(new mgsRileyDiamonds());
    scenes.push_back(new mgsRileyEllipsesAndSquares());
    scenes.push_back(new mgsVeraMolnarLineStudy());
    scenes.push_back(new mgsMaedaTimePainter());
    scenes.push_back(new olegVeraV());
    scenes.push_back(new sarahgpRileyCircle());
    scenes.push_back(new mwalczykVeraSquares());
    
    // Duplicate with rodrigoBelfort
    // scenes.push_back(new janVantommeScene());
    
    // Not using
    // scenes.push_back(new chrisMurielCooper());
    
    sceneFbo.allocate(VISUALS_WIDTH, VISUALS_HEIGHT, GL_RGBA, 4);
    codeFbo.allocate(VISUALS_WIDTH, VISUALS_HEIGHT, GL_RGB, 1);
    
#ifdef USE_MIDI_PARAM_SYNC
    sync.setup(0);
#endif
    
#ifdef USE_EXTERNAL_SOUNDS
    // open an outgoing connection to HOST:PORT
    oscSender.setup(HOST, PORT);
#endif
    
    // disney
    for (auto scene : scenes){
        scene->dimensions.set(0,0,VISUALS_WIDTH, VISUALS_HEIGHT);
        scene->setup();
    }
    
    
    //    for (int i = 0; i< scenes.size(); i++){
    //        scenes[i]->setup();
    //    }
    
    currentScene = 0;
    
    panel = new ofxPanel();
    panel->setup("scene settings");
    panel->add(scenes[currentScene]->parameters);
    panel->setPosition(520+504+20, 20);
    
    startScene(currentScene);

#ifdef USE_EXTERNAL_SOUNDS
    ofxOscMessage m;
    m.setAddress("/d4n/sceneStart");
    m.addStringArg(ofToString(currentScene) + ": "
                   + scenes[currentScene]->originalArtist
                   + " (recoded by " + scenes[currentScene]->author + ")");
    oscSender.sendMessage(m, false);
#else
    loop.load("sounds/drawbar_c4_a.aif");
    loop.setLoop(true);
    loop.play();
    loop.setVolume(0);
    
    TM.loadSounds();
#endif
}

void sceneManager::startScene(int whichScene){
    scenes[currentScene]->reset();
    TM.setup( (scenes[currentScene]), 7.5);
    lettersLastFrame = 0;
    lastPlayTime = 0;
    lastLetterHeight = 0;
    didTriggerCodeFinishedAnimatingEvent = false;
#ifdef USE_MIDI_PARAM_SYNC
    sync.setSyncGroup(scenes[currentScene]->parameters, true);
    sync.enableMidi();
#endif
}


void sceneManager::update(){
    
    
#ifdef TYPE_ANIMATION
    // this is copied from below...  should be abstracted out.
    float pctDelay = (ofGetElapsedTimef() - TM.setupTime) / (TM.animTime+0.5);
    if (pctDelay > 0.99){
        scenes[currentScene]->update();
    }
#else
    scenes[currentScene]->update();
#endif
    
    
    ofParameter < float > floatParam;

    if (TM.paramChangedEnergy.size() > 0) {
        
        for (int i = 0; i < TM.paramChangedEnergy.size(); i++) {
    
            if (TM.paramChangedEnergy[i] > 0) {
            
                ofParameter<float> t = scenes[currentScene]->parameters[i].cast<float>();

                float minVal = t.getMin();
                float maxVal = t.getMax();
                float val = t;
        
                float pct  = (t - minVal) / (float)(maxVal - minVal);
        
                if (pct > 1) pct = 1;
                if (pct < 0) pct = 0;

#ifdef USE_EXTERNAL_SOUNDS
                oscMessage.clear();
                oscMessage.setAddress("/d4n/param/" + ofToString(i) + "/energy");
                oscMessage.addStringArg(scenes[currentScene]->parameters[i].getName());
                oscMessage.addFloatArg(TM.paramChangedEnergy[i]);
                oscSender.sendMessage(oscMessage, false);

                oscMessage.clear();
                oscMessage.setAddress("/d4n/param/" + ofToString(i) + "/value");
                oscMessage.addStringArg(scenes[currentScene]->parameters[i].getName());
                oscMessage.addFloatArg(pct);
                oscSender.sendMessage(oscMessage, false);
#else
                loop.setVolume(TM.paramChangedEnergy[i]);
                loop.setSpeed( ofMap(pct, 0, 1, 0.3, 1.0) );
#endif
            }
        }
    } else {
#ifndef USE_EXTERNAL_SOUNDS
        loop.setVolume(0);
#endif
    }
    
    
}

void sceneManager::draw(){
    
    
    
    sceneFbo.begin();
    ofClear(0,0,0,255);
    ofPushStyle();
    scenes[currentScene]->draw();
    ofPopStyle();
    ofClearAlpha();
    sceneFbo.end();
    
    
    ofSetColor(255,255,255);
    
    codeFbo.begin();
    
    float pct = (ofGetElapsedTimef() - TM.setupTime) / TM.animTime;
    
    if (pct > 1) pct = 1;
    if (pct < 0) pct = 0;
    
    if (pct < 0.5){
        pct *= 2;
        pct  = powf(pct, 3.0);
        pct *= 0.5;
    } else {
        
        pct -= 0.5;
        pct *= 2.0;
        pct  = powf(pct, 1.0/3.0);
        pct *= 0.5;
        pct += 0.5;
        
    }
    
#ifdef USE_EXTERNAL_SOUNDS
    if (pct == 1 && !didTriggerCodeFinishedAnimatingEvent) {
        oscMessage.clear();
        oscMessage.setAddress("/d4n/codeFinishedAnimating");
        oscMessage.addTriggerArg();
        oscSender.sendMessage(oscMessage, false);
        didTriggerCodeFinishedAnimatingEvent = true;
    }
#endif


    ofClear(0,0,0,255);
    vector < codeLetter > letters = TM.getCodeWithParamsReplaced(scenes[currentScene]);
    
    ofSetColor(255);
    //font.drawString(codeReplaced, 40, 40);
    //ofDrawBitmapString(codeReplaced, 40,40);
    
    
    bool bShiftUp = false;
    
    if (lastLetterHeight > (504-20)){
        bShiftUp = true;
        
    }
    
    if (bShiftUp){
        float dx = lastLetterHeight - (504-20);
        ofPushMatrix();
        ofTranslate(0,-dx);
    }
    
    
    int countLetters = 0;
    int x = 10;
    int y = 10 + 13;
    for (int i = 0; i < letters.size() * pct; i++){
        
        
        if (letters[i].idOfChar == -1) ofSetColor(127);
        if (letters[i].idOfChar != -1) ofSetColor(127 + ofClamp(TM.paramChangedEnergy[letters[i].idOfChar], 0, 1) * 127);
        
        string s = "";
        s += (char)(letters[i].character);
        font.drawString(s , (int)x, (int)y);
        
        
        if (letters[i].character != ' ' &&
            letters[i].character != '\n' &&
            letters[i].character != '\t') countLetters++;
        
        x += 7;
        if (letters[i].character == '\n'){
            y += 13;
            x = 10;
        }
        
        lastLetterHeight = y;
    }
    
    if (bShiftUp){
        ofPopMatrix();
    }
    
    
    codeFbo.end();
    
    ofSetColor(255);
    codeFbo.draw(CODE_X_POS, 0, VISUALS_WIDTH, VISUALS_HEIGHT);
    
#ifdef TYPE_ANIMATION
    float pctDelay = (ofGetElapsedTimef() - TM.setupTime) / (TM.animTime+0.5);
    if (pctDelay > 0.99){
        sceneFbo.draw(0,0,VISUALS_WIDTH, VISUALS_HEIGHT);
    } else {
        
        ofSetColor(0);
        ofFill();
        ofDrawRectangle(0,0,VISUALS_WIDTH, VISUALS_HEIGHT);
        int diff = (countLetters - (int)lettersLastFrame);
        if (diff > 0 && (ofGetElapsedTimeMillis()-lastPlayTime > ofRandom(50,87))) {
            // cout << diff << enld;
            lastPlayTime = ofGetElapsedTimeMillis();
            
            if (ofNoise(pct*10, ofGetElapsedTimef()/10.0) > 0.5) {
#ifdef USE_EXTERNAL_SOUNDS
                oscMessage.clear();
                oscMessage.setAddress("/d4n/keyPressed");
                oscMessage.addStringArg("a");
                oscSender.sendMessage(oscMessage, false);
#else
                TM.clickb.play();
                TM.clickb.setSpeed(ofRandom(0.9, 1.1));
#endif
            } else {
#ifdef USE_EXTERNAL_SOUNDS
                oscMessage.clear();
                oscMessage.setAddress("/d4n/keyPressed");
                oscMessage.addStringArg("b");
                oscSender.sendMessage(oscMessage, false);
#else
                TM.clicka.play();
                TM.clicka.setSpeed(ofRandom(0.9, 1.1));
#endif
            }
            
        }
        lettersLastFrame = countLetters;
        
    }
#else
    sceneFbo.draw(0,0,VISUALS_WIDTH, VISUALS_HEIGHT);
#endif
    
    
    
    panel->draw();
    
    
    // let's draw some info!
    
    ofSetColor(255);
    
    ofDrawBitmapString("drawing scene " + ofToString(currentScene) + "\t\t(" + scenes[currentScene]->author  + ", " + scenes[currentScene]->originalArtist + ")", 20, VISUALS_HEIGHT + 50);

    
}

void sceneManager::nextScene(bool forward){
    if (forward){
        currentScene ++;
        currentScene %= scenes.size();
    } else {
        currentScene --;
        if (currentScene < 0){
            currentScene = scenes.size() - 1;
        }
    }
    
    startScene(currentScene);
    
#ifdef USE_EXTERNAL_SOUNDS
    oscMessage.clear();
    oscMessage.setAddress("/d4n/sceneStart");
    oscMessage.addStringArg(ofToString(currentScene) + ": "
                   + scenes[currentScene]->originalArtist
                   + " (recoded by " + scenes[currentScene]->author + ")");
    oscSender.sendMessage(oscMessage, false);
#endif
    
    delete panel;
    panel = new ofxPanel();
    panel->setup("scene settings");
    panel->add(scenes[currentScene]->parameters);
    
    panel->setPosition(520+504+20, 20);
};

void sceneManager::advanceScene(){
    nextScene(true);
};

void sceneManager::regressScene(){
    nextScene(false);
};

void sceneManager::screenGrab() {
    string path = "screengrabs/";
    ofImage sceneImg;
    ofImage codeImg;
    
    sceneFbo.readToPixels(sceneImg.getPixels());
    codeFbo.readToPixels(codeImg.getPixels());
    
    sceneImg.save(path+ofGetTimestampString()+"_scene.png");
    codeImg.save(path+ofGetTimestampString()+"_code.png");
    
}
