#include "Robot_CYD_Eyes.h"


// instance
//RobotCYDEyes::RobotCYDEyes(const TFT_eSPI& tft,const TFT_eSprite& sprite) 
RobotCYDEyes::RobotCYDEyes(TFT_eSPI* tft,TFT_eSprite* sprite) 
    //: 
    //currentPhaseIndex(0), totalSteps(0), stepsRemaining(0), accelerationFactor(0) {
    {
     // tft = TFT_eSPI(); // esp
      //sprite = TFT_eSprite(&tft); //CYD speed buffer
    }
// RobotCYDEyes::RobotCYDEyes() 
//     //: 
//     //currentPhaseIndex(0), totalSteps(0), stepsRemaining(0), accelerationFactor(0) {
//     {
//      // tft = TFT_eSPI(); // esp
//       //sprite = TFT_eSprite(&tft); //CYD speed buffer
//     }


//void RobotCYDEyes::initialize(const TFT_eSPI& tft,const TFT_eSprite& sprite,const int Width,const int Heigh,const int frameRate){
void RobotCYDEyes::initialize(TFT_eSPI* tft,TFT_eSprite* sprite,const int Width,const int Heigh,const int frameRate){
    screenWidth = Width;
    screenHeight = Heigh;

    eyeLheightCurrent = 1; // start with closed eyes
    eyeRheightCurrent = 1; // start with closed eyes

    setAutoblinker(true, 1, 4);
    }

//void RobotCYDEyes::update(const TFT_eSPI& tft,const TFT_eSprite& sprite){
void RobotCYDEyes::update(TFT_eSPI* tft, TFT_eSprite* sprite){
  // Limit drawing updates to defined max framerate
  if(millis()-fpsTimer >= frameInterval){
    if (testColor==1)
    {
        testColors(sprite);
        sprite->pushSprite(0,0);
    }
    else
    {

        //Serial.print("e");
        drawEyes(tft,sprite);
        fpsTimer = millis();
    }
  }  
}

void RobotCYDEyes::set(String Action,String Value1,String Value2){
  
    Serial.print("[eyes]");
    Serial.print("(setMood):");
    Serial.print(Action);
    testColor=0;
    if (Action=="normal") setMood(DEFAULT);
    else if (Action=="default") setMood(DEFAULT);
    else if (Action=="tired") setMood(TIRED);
    else if (Action=="angry") setMood(ANGRY);
    else if (Action=="happy") setMood(HAPPY);
    else if (Action=="suspect") setMood(SUSPECT);
    else if (Action=="close") close();
    else if (Action=="open") open();
    else if (Action=="closeL") close(true,false);
    else if (Action=="closeR") close(false,true);
    else if (Action=="openL") open(false,true);
    else if (Action=="openR") open(true,false);
    else if (Action=="blink") blink();
    else if (Action=="blinkL") blink(true,false);
    else if (Action=="blinkR") blink(false,true);
    else if (Action=="testColors") testColor=1;
}


//*********************************************************************************************
//  SETTERS METHODS
//*********************************************************************************************

// Calculate frame interval based on defined frameRate
void RobotCYDEyes::setFramerate(byte fps){
  frameInterval = 1000/fps;
}

void RobotCYDEyes::setWidth(byte leftEye, byte rightEye) {
	eyeLwidthNext = leftEye;
	eyeRwidthNext = rightEye;
  eyeLwidthDefault = leftEye;
  eyeRwidthDefault = rightEye;
}

void RobotCYDEyes::setHeight(byte leftEye, byte rightEye) {
	eyeLheightNext = leftEye;
	eyeRheightNext = rightEye;
  eyeLheightDefault = leftEye;
  eyeRheightDefault = rightEye;
}

// Set border radius for left and right eye
void RobotCYDEyes::setBorderradius(byte leftEye, byte rightEye) {
	eyeLborderRadiusNext = leftEye;
	eyeRborderRadiusNext = rightEye;
  eyeLborderRadiusDefault = leftEye;
  eyeRborderRadiusDefault = rightEye;
}

// Set space between the eyes, can also be negative
void RobotCYDEyes::setSpacebetween(int space) {
  spaceBetweenNext = space;
  spaceBetweenDefault = space;
}

// Set mood expression
void RobotCYDEyes::setMood(unsigned char mood)
  {
    switch (mood)
    {
    case TIRED:
      tired=1; 
      angry=0; 
      happy=0;
	  suspect=0;
      break;
    case ANGRY:
      tired=0; 
      angry=1; 
      happy=0;
	  suspect=0;
      break;
    case HAPPY:
      tired=0; 
      angry=0; 
      happy=1;
	  suspect=0;
      break;
    case SUSPECT:
      tired=0; 
      angry=0; 
      happy=0;
	  suspect=1;
      break;
    default:
      tired=0; 
      angry=0; 
      happy=0;
	  suspect=0;
      break;
    }
  }

// Set predefined position
void RobotCYDEyes::setPosition(unsigned char position)
  {
    switch (position)
    {
    case NORTH:
      // North, top center
      eyeLxNext = getScreenConstraint_X()/2;
      eyeLyNext = 0;
      break;
    case NE:
      // North-east, top right
      eyeLxNext = getScreenConstraint_X();
      eyeLyNext = 0;
      break;
    case E:
      // East, middle right
      eyeLxNext = getScreenConstraint_X();
      eyeLyNext = getScreenConstraint_Y()/2;
      break;
    case SE:
      // South-east, bottom right
      eyeLxNext = getScreenConstraint_X();
      eyeLyNext = getScreenConstraint_Y();
      break;
    case S:
      // South, bottom center
      eyeLxNext = getScreenConstraint_X()/2;
      eyeLyNext = getScreenConstraint_Y();
      break;
    case SW:
      // South-west, bottom left
      eyeLxNext = 0;
      eyeLyNext = getScreenConstraint_Y();
      break;
    case W:
      // West, middle left
      eyeLxNext = 0;
      eyeLyNext = getScreenConstraint_Y()/2;
      break;
    case NW:
      // North-west, top left
      eyeLxNext = 0;
      eyeLyNext = 0;
      break;
    default:
      // Middle center
      eyeLxNext = getScreenConstraint_X()/2;
      eyeLyNext = getScreenConstraint_Y()/2;
      break;
    }
  }

// Set automated eye blinking, minimal blink interval in full seconds and blink interval variation range in full seconds
void RobotCYDEyes::setAutoblinker(bool active, int interval, int variation){
  autoblinker = active;
  blinkInterval = interval;
  blinkIntervalVariation = variation;
}
void RobotCYDEyes::setAutoblinker(bool active){
  autoblinker = active;
}

// Set idle mode - automated eye repositioning, minimal time interval in full seconds and time interval variation range in full seconds
void RobotCYDEyes::setIdleMode(bool active, int interval, int variation){
  idle = active;
  idleInterval = interval;
  idleIntervalVariation = variation;
}
void RobotCYDEyes::setIdleMode(bool active) {
  idle = active;
}

// Set curious mode - the respectively outer eye gets larger when looking left or right
void RobotCYDEyes::setCuriosity(bool curiousBit) {
  curious = curiousBit;
}

// Set cyclops mode - show only one eye 
void RobotCYDEyes::setCyclops(bool cyclopsBit) {
  cyclops = cyclopsBit;
}

// Set horizontal flickering (displacing eyes left/right)
void RobotCYDEyes::setHFlicker (bool flickerBit, byte Amplitude) {
  hFlicker = flickerBit; // turn flicker on or off
  hFlickerAmplitude = Amplitude; // define amplitude of flickering in pixels
}
void RobotCYDEyes::setHFlicker (bool flickerBit) {
  hFlicker = flickerBit; // turn flicker on or off
}


// Set vertical flickering (displacing eyes up/down)
void RobotCYDEyes::setVFlicker (bool flickerBit, byte Amplitude) {
  vFlicker = flickerBit; // turn flicker on or off
  vFlickerAmplitude = Amplitude; // define amplitude of flickering in pixels
}
void RobotCYDEyes::setVFlicker (bool flickerBit) {
  vFlicker = flickerBit; // turn flicker on or off
}


//*********************************************************************************************
//  GETTERS METHODS
//*********************************************************************************************

// Returns the max x position for left eye
int RobotCYDEyes::getScreenConstraint_X(){
  return screenWidth-eyeLwidthCurrent-spaceBetweenCurrent-eyeRwidthCurrent;
} 

// Returns the max y position for left eye
int RobotCYDEyes::getScreenConstraint_Y(){
 return screenHeight-eyeLheightDefault; // using default height here, because height will vary when blinking and in curious mode
}


//*********************************************************************************************
//  BASIC ANIMATION METHODS
//*********************************************************************************************

// BLINKING FOR BOTH EYES AT ONCE
// Close both eyes
void RobotCYDEyes::close() {
	eyeLheightNext = 1; // closing left eye
  eyeRheightNext = 1; // closing right eye
  eyeL_open = 0; // left eye not opened (=closed)
	eyeR_open = 0; // right eye not opened (=closed)
}

// Open both eyes
void RobotCYDEyes::open() {
  eyeL_open = 1; // left eye opened - if true, drawEyes() will take care of opening eyes again
	eyeR_open = 1; // right eye opened
}

// Trigger eyeblink animation
void RobotCYDEyes::blink() {
  close();
  open();
}

// BLINKING FOR SINGLE EYES, CONTROL EACH EYE SEPARATELY
// Close eye(s)
void RobotCYDEyes::close(bool left, bool right) {
  if(left){
    eyeLheightNext = 1; // blinking left eye
    eyeL_open = 0; // left eye not opened (=closed)
  }
  if(right){
      eyeRheightNext = 1; // blinking right eye
      eyeR_open = 0; // right eye not opened (=closed)
  }
}

// Open eye(s)
void RobotCYDEyes::open(bool left, bool right) {
  if(left){
    eyeL_open = 1; // left eye opened - if true, drawEyes() will take care of opening eyes again
  }
  if(right){
    eyeR_open = 1; // right eye opened
  }
}

// Trigger eyeblink(s) animation
void RobotCYDEyes::blink(bool left, bool right) {
  close(left, right);
  open(left, right);
}


//*********************************************************************************************
//  MACRO ANIMATION METHODS
//*********************************************************************************************

// Play confused animation - one shot animation of eyes shaking left and right
void RobotCYDEyes::anim_confused() {
	confused = 1;
}

// Play laugh animation - one shot animation of eyes shaking up and down
void RobotCYDEyes::anim_laugh() {
  laugh = 1;
}








void RobotCYDEyes::drawEyes(TFT_eSPI* tft,TFT_eSprite* sprite)
{

  //// PRE-CALCULATIONS - EYE SIZES AND VALUES FOR ANIMATION TWEENINGS ////

  // Vertical size offset for larger eyes when looking left or right (curious gaze)
  if(curious){
    if(eyeLxNext<=10){eyeLheightOffset=8;}
    else if (eyeLxNext>=(getScreenConstraint_X()-10) && cyclops){eyeLheightOffset=8;}
    else{eyeLheightOffset=0;} // left eye
    if(eyeRxNext>=screenWidth-eyeRwidthCurrent-10){eyeRheightOffset=8;}else{eyeRheightOffset=0;} // right eye
  }
  // Left eye height
  eyeLheightCurrent = (eyeLheightCurrent + eyeLheightNext + eyeLheightOffset)/2;
  eyeLy+= ((eyeLheightDefault-eyeLheightCurrent)/2); // vertical centering of eye when closing
  eyeLy-= eyeLheightOffset/2;
  // Right eye height
  eyeRheightCurrent = (eyeRheightCurrent + eyeRheightNext + eyeRheightOffset)/2;
  eyeRy+= (eyeRheightDefault-eyeRheightCurrent)/2; // vertical centering of eye when closing
  eyeRy-= eyeRheightOffset/2;


  // Open eyes again after closing them
	if(eyeL_open){
  	if(eyeLheightCurrent <= 1 + eyeLheightOffset){eyeLheightNext = eyeLheightDefault;} 
  }
  if(eyeR_open){
  	if(eyeRheightCurrent <= 1 + eyeRheightOffset){eyeRheightNext = eyeRheightDefault;} 
  }

  // Left eye width
  eyeLwidthCurrent = (eyeLwidthCurrent + eyeLwidthNext)/2;
  // Right eye width
  eyeRwidthCurrent = (eyeRwidthCurrent + eyeRwidthNext)/2;


  // Space between eyes
  spaceBetweenCurrent = (spaceBetweenCurrent + spaceBetweenNext)/2;

  // Left eye coordinates
  eyeLx = (eyeLx + eyeLxNext)/2;
  eyeLy = (eyeLy + eyeLyNext)/2;
  // Right eye coordinates
  eyeRxNext = eyeLxNext+eyeLwidthCurrent+spaceBetweenCurrent; // right eye's x position depends on left eyes position + the space between
  eyeRyNext = eyeLyNext; // right eye's y position should be the same as for the left eye
  eyeRx = (eyeRx + eyeRxNext)/2;
  eyeRy = (eyeRy + eyeRyNext)/2;

  // Left eye border radius
  eyeLborderRadiusCurrent = (eyeLborderRadiusCurrent + eyeLborderRadiusNext)/2;
  // Right eye border radius
  eyeRborderRadiusCurrent = (eyeRborderRadiusCurrent + eyeRborderRadiusNext)/2;
  

  //// APPLYING MACRO ANIMATIONS ////

	if(autoblinker){
		if(millis() >= blinktimer){
		blink();
		blinktimer = millis()+(blinkInterval*1000)+(random(blinkIntervalVariation)*1000); // calculate next time for blinking
		}
	}

  // Laughing - eyes shaking up and down for the duration defined by laughAnimationDuration (default = 500ms)
  if(laugh){
    if(laughToggle){
      setVFlicker(1, 5);
      laughAnimationTimer = millis();
      laughToggle = 0;
    } else if(millis() >= laughAnimationTimer+laughAnimationDuration){
      setVFlicker(0, 0);
      laughToggle = 1;
      laugh=0; 
    }
  }

  // Confused - eyes shaking left and right for the duration defined by confusedAnimationDuration (default = 500ms)
  if(confused){
    if(confusedToggle){
      setHFlicker(1, 20);
      confusedAnimationTimer = millis();
      confusedToggle = 0;
    } else if(millis() >= confusedAnimationTimer+confusedAnimationDuration){
      setHFlicker(0, 0);
      confusedToggle = 1;
      confused=0; 
    }
  }

  // Idle - eyes moving to random positions on screen
  if(idle){
    if(millis() >= idleAnimationTimer){
      eyeLxNext = random(getScreenConstraint_X());
      eyeLyNext = random(getScreenConstraint_Y());
      idleAnimationTimer = millis()+(idleInterval*1000)+(random(idleIntervalVariation)*1000); // calculate next time for eyes repositioning
    }
  }

  // Adding offsets for horizontal flickering/shivering
  if(hFlicker){
    if(hFlickerAlternate) {
      eyeLx += hFlickerAmplitude;
      eyeRx += hFlickerAmplitude;
    } else {
      eyeLx -= hFlickerAmplitude;
      eyeRx -= hFlickerAmplitude;
    }
    hFlickerAlternate = !hFlickerAlternate;
  }

  // Adding offsets for horizontal flickering/shivering
  if(vFlicker){
    if(vFlickerAlternate) {
      eyeLy += vFlickerAmplitude;
      eyeRy += vFlickerAmplitude;
    } else {
      eyeLy -= vFlickerAmplitude;
      eyeRy -= vFlickerAmplitude;
    }
    vFlickerAlternate = !vFlickerAlternate;
  }

  // Cyclops mode, set second eye's size and space between to 0
  if(cyclops){
    eyeRwidthCurrent = 0;
    eyeRheightCurrent = 0;
    spaceBetweenCurrent = 0;
  }

  //// ACTUAL DRAWINGS ////
// original
// original  display.clearDisplay(); // start with a blank screen
// original
// original  // Draw basic eye rectangles
// original  display.fillRoundRect(eyeLx, eyeLy, eyeLwidthCurrent, eyeLheightCurrent, eyeLborderRadiusCurrent, MAINCOLOR); // left eye
// original  if (!cyclops){
// original    display.fillRoundRect(eyeRx, eyeRy, eyeRwidthCurrent, eyeRheightCurrent, eyeRborderRadiusCurrent, MAINCOLOR); // right eye
// original  }
// original
// original  // Prepare mood type transitions
// original  if (tired){eyelidsTiredHeightNext = eyeLheightCurrent/2; eyelidsAngryHeightNext = 0;} else{eyelidsTiredHeightNext = 0;}
// original  if (angry){eyelidsAngryHeightNext = eyeLheightCurrent/2; eyelidsTiredHeightNext = 0;} else{eyelidsAngryHeightNext = 0;}
// original  if (happy){eyelidsHappyBottomOffsetNext = eyeLheightCurrent/2;} else{eyelidsHappyBottomOffsetNext = 0;}
// original
// original  // Draw tired top eyelids 
// original    eyelidsTiredHeight = (eyelidsTiredHeight + eyelidsTiredHeightNext)/2;
// original    if (!cyclops){
// original      display.fillTriangle(eyeLx, eyeLy-1, eyeLx+eyeLwidthCurrent, eyeLy-1, eyeLx, eyeLy+eyelidsTiredHeight-1, BGCOLOR); // left eye 
// original      display.fillTriangle(eyeRx, eyeRy-1, eyeRx+eyeRwidthCurrent, eyeRy-1, eyeRx+eyeRwidthCurrent, eyeRy+eyelidsTiredHeight-1, BGCOLOR); // right eye
// original    } else {
// original      // Cyclops tired eyelids
// original      display.fillTriangle(eyeLx, eyeLy-1, eyeLx+(eyeLwidthCurrent/2), eyeLy-1, eyeLx, eyeLy+eyelidsTiredHeight-1, BGCOLOR); // left eyelid half
// original      display.fillTriangle(eyeLx+(eyeLwidthCurrent/2), eyeLy-1, eyeLx+eyeLwidthCurrent, eyeLy-1, eyeLx+eyeLwidthCurrent, eyeLy+eyelidsTiredHeight-1, BGCOLOR); // right eyelid half
// original    }
// original
// original  // Draw angry top eyelids 
// original    eyelidsAngryHeight = (eyelidsAngryHeight + eyelidsAngryHeightNext)/2;
// original    if (!cyclops){ 
// original      display.fillTriangle(eyeLx, eyeLy-1, eyeLx+eyeLwidthCurrent, eyeLy-1, eyeLx+eyeLwidthCurrent, eyeLy+eyelidsAngryHeight-1, BGCOLOR); // left eye
// original      display.fillTriangle(eyeRx, eyeRy-1, eyeRx+eyeRwidthCurrent, eyeRy-1, eyeRx, eyeRy+eyelidsAngryHeight-1, BGCOLOR); // right eye
// original    } else {
// original      // Cyclops angry eyelids
// original      display.fillTriangle(eyeLx, eyeLy-1, eyeLx+(eyeLwidthCurrent/2), eyeLy-1, eyeLx+(eyeLwidthCurrent/2), eyeLy+eyelidsAngryHeight-1, BGCOLOR); // left eyelid half
// original      display.fillTriangle(eyeLx+(eyeLwidthCurrent/2), eyeLy-1, eyeLx+eyeLwidthCurrent, eyeLy-1, eyeLx+(eyeLwidthCurrent/2), eyeLy+eyelidsAngryHeight-1, BGCOLOR); // right eyelid half
// original    }
// original
// original  // Draw happy bottom eyelids
// original    eyelidsHappyBottomOffset = (eyelidsHappyBottomOffset + eyelidsHappyBottomOffsetNext)/2;
// original    display.fillRoundRect(eyeLx-1, (eyeLy+eyeLheightCurrent)-eyelidsHappyBottomOffset+1, eyeLwidthCurrent+2, eyeLheightDefault, eyeLborderRadiusCurrent, BGCOLOR); // left eye
// original    if (!cyclops){ 
// original      display.fillRoundRect(eyeRx-1, (eyeRy+eyeRheightCurrent)-eyelidsHappyBottomOffset+1, eyeRwidthCurrent+2, eyeRheightDefault, eyeRborderRadiusCurrent, BGCOLOR); // right eye
// original    }
// original
// original  display.display(); // show drawings on display



  sprite->fillSprite(BGCOLOR);   
  
  if (eyeInnerShadowAlpha==0 ) // no graient, just solid color
	{
    // Draw basic eye rectangles
    sprite->fillSmoothRoundRect(eyeLx, eyeLy, eyeLwidthCurrent, eyeLheightCurrent, eyeLborderRadiusCurrent, 10,BGCOLOR); // left eye
    //fillSmoothRoundRect(sprite,eyeLx,eyeLy, eyeLwidthCurrent, eyeLheightCurrent, eyeLborderRadiusCurrent,1,3); // left eye
    if (!cyclops){	  
      sprite->fillSmoothRoundRect(eyeRx, eyeRy, eyeRwidthCurrent, eyeRheightCurrent, eyeRborderRadiusCurrent, 10,BGCOLOR); // left eye
      //  fillSmoothRoundRect(sprite,eyeRx,eyeRy, eyeLwidthCurrent, eyeRheightCurrent, eyeRborderRadiusCurrent,1,3); // left eye
    }
  }
  else
	{
   // shadown borders
		int _eyeLXShadow = limitMin(eyeLx,eyeLx+eyeInnerShadowWidth+eyeInnerShadowShiftHorizontal); //limit to original eye left
		int _eyeRXShadow = limitMin(eyeRx,eyeRx+eyeInnerShadowWidth+eyeInnerShadowShiftHorizontal); //limit to original eye left
		int _eyeLYShadow = limitMin(eyeLy,eyeLy+eyeInnerShadowHeight+eyeInnerShadowShiftVertical); //limit to original eye top
		int _eyeRYShadow = limitMin(eyeRy,eyeRy+eyeInnerShadowHeight+eyeInnerShadowShiftVertical); //limit to original eye top
		
		int _eyeLWShadow = limitMax(eyeLwidthCurrent,eyeLwidthCurrent-eyeInnerShadowWidth*2+eyeInnerShadowShiftHorizontal); //limit to original eye width
		int _eyeRWShadow = limitMax(eyeRwidthCurrent,eyeRwidthCurrent-eyeInnerShadowWidth*2+eyeInnerShadowShiftHorizontal); //limit to original eye width
		int _eyeLHShadow = limitBetween(1,limitMin(2,eyeLheightCurrent),eyeLheightCurrent-eyeInnerShadowHeight*2+eyeInnerShadowShiftVertical); //limit to original eye width
		int _eyeRHShadow = limitBetween(1,limitMin(2,eyeRheightCurrent),eyeRheightCurrent-eyeInnerShadowHeight*2+eyeInnerShadowShiftVertical); //limit to original eye width
    //Serial.println(eyeLheightCurrent);
		if (eyeL_open==1)
		{
		    fillSmoothRoundRect(sprite,_eyeLXShadow,_eyeLYShadow, _eyeLWShadow, _eyeLHShadow, eyeInnerShadowBorderRadiusDefault,1,10); // left eye
//		    fillSmoothRoundRect(sprite,eyeLx,eyeLy, eyeLwidthCurrent, eyeLheightCurrent, eyeLborderRadiusCurrent,4,9); // left eye
		}
		
		if (eyeR_open==1)
		{
			if (!cyclops){ 
		  fillSmoothRoundRect(sprite,_eyeRXShadow,_eyeRYShadow, _eyeRWShadow,_eyeRHShadow, eyeInnerShadowBorderRadiusDefault, 1,10); // right eye
//			  fillSmoothRoundRect(sprite,_eyeRXShadow,_eyeRYShadow, _eyeRWShadow,_eyeRHShadow, eyeInnerShadowBorderRadiusDefault, 4,9); // right eye
		  }
		}
	}

  // Prepare mood type transitions
 
  byte LIDCOLOR = BGCOLOR;

	  // if (tired){eyelidsTiredHeightNext = eyeLheightCurrent/2; eyelidsAngryHeightNext = 0;} else{eyelidsTiredHeightNext = 0;}
	  // if (angry){eyelidsAngryHeightNext = eyeLheightCurrent/2; eyelidsTiredHeightNext = 0;} else{eyelidsAngryHeightNext = 0;}
	  // if (happy){eyelidsHappyBottomOffsetNext = eyeLheightCurrent/2;} else{eyelidsHappyBottomOffsetNext = 0;}
	  // //if(happy){eyelidsLaughHeightNext = eyeLheightCurrent/2; eyelidsAngryHeightNext = 0;eyelidsTiredHeightNext = 0;}else{eyelidsLaughHeightNext=0;}
	  // if (suspect){eyelidsSuspectHeightNext = eyeLheightCurrent/2; } else{eyelidsSuspectHeightNext = 0;}

	  if (tired){eyelidsTiredHeightNext = eyeLheightCurrent/2; } else{resetMoodPosition("tired");}
	  if (angry){eyelidsAngryHeightNext = eyeLheightCurrent/2; } else{resetMoodPosition("angry");}
	  if (happy){eyelidsHappyBottomOffsetNext = eyeLheightCurrent/2;} else{resetMoodPosition("happy");}
	  //if(happy){eyelidsLaughHeightNext = eyeLheightCurrent/2; eyelidsAngryHeightNext = 0;eyelidsTiredHeightNext = 0;}else{eyelidsLaughHeightNext=0;}
	  if (suspect){eyelidsSuspectHeightNext = eyeLheightCurrent/2; } else{resetMoodPosition("suspect");}

	  
  // Draw tired top eyelids 
  if (tired){
    eyelidsTiredHeight = (eyelidsTiredHeight + eyelidsTiredHeightNext)/2;
    if (!cyclops){
      sprite->fillTriangle(eyeLx, eyeLy-1, eyeLx+eyeLwidthCurrent, eyeLy-1, eyeLx, eyeLy+eyelidsTiredHeight-1, LIDCOLOR); // left eye 
      sprite->fillTriangle(eyeRx, eyeRy-1, eyeRx+eyeRwidthCurrent, eyeRy-1, eyeRx+eyeRwidthCurrent, eyeRy+eyelidsTiredHeight-1, LIDCOLOR); // right eye
    } else {
      // Cyclops tired eyelids
      sprite->fillTriangle(eyeLx, eyeLy-1, eyeLx+(eyeLwidthCurrent/2), eyeLy-1, eyeLx, eyeLy+eyelidsTiredHeight-1, LIDCOLOR); // left eyelid half
      sprite->fillTriangle(eyeLx+(eyeLwidthCurrent/2), eyeLy-1, eyeLx+eyeLwidthCurrent, eyeLy-1, eyeLx+eyeLwidthCurrent, eyeLy+eyelidsTiredHeight-1, LIDCOLOR); // right eyelid half
    }
  }
  
  if(angry)
  {
  // Draw angry top eyelids 
    eyelidsAngryHeight = (eyelidsAngryHeight + eyelidsAngryHeightNext)/2;
    if (!cyclops){ 
      sprite->fillTriangle(eyeLx, eyeLy-1, eyeLx+eyeLwidthCurrent, eyeLy-1, eyeLx+eyeLwidthCurrent, eyeLy+eyelidsAngryHeight-1, LIDCOLOR); // left eye
      sprite->fillTriangle(eyeRx, eyeRy-1, eyeRx+eyeRwidthCurrent, eyeRy-1, eyeRx, eyeRy+eyelidsAngryHeight-1, LIDCOLOR); // right eye
    } else {
      // Cyclops angry eyelids
      sprite->fillTriangle(eyeLx, eyeLy-1, eyeLx+(eyeLwidthCurrent/2), eyeLy-1, eyeLx+(eyeLwidthCurrent/2), eyeLy+eyelidsAngryHeight-1, LIDCOLOR); // left eyelid half
      sprite->fillTriangle(eyeLx+(eyeLwidthCurrent/2), eyeLy-1, eyeLx+eyeLwidthCurrent, eyeLy-1, eyeLx+(eyeLwidthCurrent/2), eyeLy+eyelidsAngryHeight-1, LIDCOLOR); // right eyelid half
  }
  }
  
  if (happy)
  {
  // Draw happy bottom eyelids
     eyelidsHappyBottomOffset = (eyelidsHappyBottomOffset + eyelidsHappyBottomOffsetNext)/2;
     sprite->fillRoundRect(eyeLx-1, (eyeLy+eyeLheightCurrent)-eyelidsHappyBottomOffset+1, eyeLwidthCurrent+2, eyeLheightDefault, eyeLborderRadiusCurrent*3, LIDCOLOR); // left eye
     if (!cyclops){ 
       sprite->fillRoundRect(eyeRx-1, (eyeRy+eyeRheightCurrent)-eyelidsHappyBottomOffset+1, eyeRwidthCurrent+2, eyeRheightDefault, eyeRborderRadiusCurrent*3, LIDCOLOR); // right eye
     }
	
   
  }
  
  if (suspect)
  {
  // Draw happy bottom eyelids
     eyelidsSuspectHeight = (eyelidsSuspectHeight + eyelidsSuspectHeightNext)/2;
     sprite->fillRect(eyeLx-1, eyeLy-1, eyeLwidthCurrent+2,eyelidsSuspectHeight-10, LIDCOLOR); // left eye
     sprite->fillRect(eyeLx-1, (eyeLy+eyeLheightCurrent)-eyelidsSuspectHeight+1+10, eyeLwidthCurrent+2, eyeLheightDefault, LIDCOLOR); // left eye
     if (!cyclops){ 
//       sprite.fillRect(eyeRx-1, (eyeRy+eyeRheightCurrent)-eyelidsHappyBottomOffset+1, eyeRwidthCurrent+2, eyeRheightDefault, BGCOLOR); // right eye
		sprite->fillRect(eyeRx-1, eyeRy-1, eyeRwidthCurrent+2,eyelidsSuspectHeight-10, LIDCOLOR); // left eye
		sprite->fillRect(eyeRx-1, (eyeRy+eyeRheightCurrent)-eyelidsSuspectHeight+1+10, eyeRwidthCurrent+2, eyeRheightDefault, LIDCOLOR); // left eye
     }
	
   
  }
  
  if (laugh)
  {
	  if (angry) {	
	  eyelidsLaughHeight = eyelidsAngryHeight;
			// orezani zespodu
		  sprite->fillTriangle(eyeLx, eyeLy+1+eyeLheightCurrent, eyeLx+eyeLwidthCurrent, eyeLy+1+eyeLheightCurrent, eyeLx, eyeLy-eyelidsLaughHeight+1+eyeLheightCurrent+10, LIDCOLOR); // left eye
		  sprite->fillTriangle(eyeRx, eyeRy+1+eyeRheightCurrent, eyeRx+eyeRwidthCurrent, eyeRy+1+eyeRheightCurrent, eyeRx+eyeRwidthCurrent, eyeRy-eyelidsLaughHeight+1+eyeRheightCurrent+10, LIDCOLOR); // right eye
		  }
	  
	  if (happy) {
		  eyelidsLaughHeight = (eyelidsLaughHeight + eyelidsLaughHeightNext)/2;
		   if (!cyclops){
			  sprite->fillTriangle(eyeLx, eyeLy-1, eyeLx+eyeLwidthCurrent, eyeLy-1, eyeLx, eyeLy+eyelidsLaughHeight-1, LIDCOLOR); // left eye 
			  sprite->fillTriangle(eyeRx, eyeRy-1, eyeRx+eyeRwidthCurrent, eyeRy-1, eyeRx+eyeRwidthCurrent, eyeRy+eyelidsLaughHeight-1, LIDCOLOR); // right eye

			  sprite->fillTriangle(eyeLx, eyeLy+1+eyeLheightCurrent, eyeLx+eyeLwidthCurrent, eyeLy+1+eyeLheightCurrent, eyeLx+eyeLwidthCurrent, eyeLy-eyelidsLaughHeight+1+eyeLheightCurrent+10, LIDCOLOR); // left eye
			  sprite->fillTriangle(eyeRx, eyeRy+1+eyeRheightCurrent, eyeRx+eyeRwidthCurrent, eyeRy+1+eyeRheightCurrent, eyeRx, eyeRy-eyelidsLaughHeight+1+eyeRheightCurrent+10, LIDCOLOR); // right eye

			} else {
			  // Cyclops Laugh eyelids
			  sprite->fillTriangle(eyeLx, eyeLy-1, eyeLx+(eyeLwidthCurrent/2), eyeLy-1, eyeLx, eyeLy+eyelidsLaughHeight-1, LIDCOLOR); // left eyelid half
			  sprite->fillTriangle(eyeLx+(eyeLwidthCurrent/2), eyeLy-1, eyeLx+eyeLwidthCurrent, eyeLy-1, eyeLx+eyeLwidthCurrent, eyeLy+eyelidsLaughHeight-1, LIDCOLOR); // right eyelid half
			}
			  }
  }	
	
	
	// #############################################################################################
	
	 // Zkopíruj celý sprite na displej
    sprite->pushSprite(0, 0);        // (x, y) jsou souřadnice na displeji
//	eyeLsprite->pushSprite(eyeLx, eyeLy);
	if (!cyclops){ 
	//eyeRsprite.pushSprite(eyeRx, eyeRy);
	}
 // }
} // end of drawEyes method

void RobotCYDEyes::resetMoodPosition(String mood)
{
  if (mood=="angry") {eyelidsAngryHeight=0;eyelidsAngryHeightNext=0;}
  if (mood=="tired") {eyelidsTiredHeight=0;eyelidsTiredHeightNext=0;}
  if (mood=="happy") {eyelidsHappyBottomOffset=0;eyelidsHappyBottomOffsetNext=0;}
  if (mood=="suspect") {eyelidsSuspectHeight=0;eyelidsSuspectHeightNext=0;}
 
} 

int RobotCYDEyes::limitMin(int min,int value)
{
	 if (value<min) return min;
	 return value;
}

int RobotCYDEyes::limitMax(int max,int value)
{
	 if (value>max) return max;
	 return value;
}
int RobotCYDEyes::limitBetween(int min,int max,int value)
{
	 if (value<min) return min;
	 if (value>max) return max;
	 return value;
}


void RobotCYDEyes::fillSmoothRoundRect(TFT_eSPI *tft, TFT_eSprite *s,int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t mainColor, uint16_t bgColor, int16_t borderWidth) {
    // Počet kroků pro přechod barvy
    int steps = borderWidth;
	
    // Postupné vykreslování přechodových vrstev
    for (int i = 0; i < steps; i++) {
        // Interpolace barvy mezi hlavní barvou a barvou pozadí
        uint8_t ratio = 5*i;// / steps;
         // uint16_t blendedColor = tft.color565(
         // ((mainColor >> 11) * (255 - ratio) + (bgColor >> 11) * ratio) / 255,
         // (((mainColor >> 5) & 0x3f) * (255 - ratio) + ((bgColor >> 5) & 0x3f) * ratio) / 255,
         // ((mainColor & 0x1f) * (255 - ratio) + (bgColor & 0x1f) * ratio) / 255
		 // );
		uint16_t blendedColor = tft->alphaBlend(ratio, mainColor, bgColor,2);
		//Serial.println(blendedColor);
        // Vykreslení vrstvy se zaoblenými rohy
        s->drawRoundRect(x + i, y + i, w - 2 * i, h - 2 * i,r, blendedColor);
    }

    // Vykreslíme hlavní obdélník uprostřed
   s->fillRoundRect(x + borderWidth, y + borderWidth, w - 2 * borderWidth, h - 2 * borderWidth, r - borderWidth, mainColor);
}

void RobotCYDEyes::testColors(TFT_eSprite *s)
{
  for (int i = 0; i <= 15; i++) {
        s->fillRect(320/16*i,0,320/16,240,i);
        }
}

void RobotCYDEyes::fillSmoothRoundRect(TFT_eSprite *s,int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, int16_t ColorIndexStart,int16_t ColorIndexStop) {
    // Počet kroků pro přechod barvy
	int inc=1;
    // Postupné vykreslování přechodových vrstev
    if (h>2*(ColorIndexStop-ColorIndexStart))
    {
      for (int i = 0; i <= ColorIndexStop-ColorIndexStart; i++) {
        s->fillRoundRect(limitMin(x,x + i*inc),limitMin(y,y + i*inc), limitBetween(0,w,w - 2 * i*inc),limitBetween(0,h, h - 2 * i*inc),r, i+ColorIndexStart);
        //s->fillSmoothRoundRect(limitMin(x,x + i*inc),limitMin(y,y + i*inc), limitBetween(0,w,w - 2 * i*inc),limitBetween(0,h, h - 2 * i*inc),r, i+ColorIndexStart,BGCOLOR);
        }
    }
    else
    {
     // Serial.println("blink:");
     // Serial.println(y);
     // Serial.println(h);
        s->fillSmoothRoundRect(x, y, w, h, r, 9,BGCOLOR);
    }
    // Vykreslíme hlavní obdélník uprostřed
	//sprite.fillRoundRect(x + ColorIndexStop, y + steps, w - 2 * steps, h - 2 * steps, r , ColorIndexStop);
}