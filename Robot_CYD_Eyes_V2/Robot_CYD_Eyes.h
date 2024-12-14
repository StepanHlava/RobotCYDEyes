#ifndef ROBOT_CYD_EYES_H
#define ROBOT_CYD_EYES_H

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
//#include "Robot_CYD_Core.h"

class RobotCYDEyes {

private:


    void fillSmoothRoundRect(TFT_eSprite *s,int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, int16_t ColorIndexStart,int16_t ColorIndexStop);
    void fillSmoothRoundRect(TFT_eSPI *tft,TFT_eSprite *s,int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t mainColor, uint16_t bgColor, int16_t borderWidth);
    int limitBetween(int min,int max,int value);
    int limitMax(int max,int value);
    int limitMin(int min,int value);
    int testColor=0;
    void testColors(TFT_eSprite *s);
    void resetMoodPosition(String mood);

    //*********************************************************************************************
    //  SETTERS METHODS
    //*********************************************************************************************

    //it is public ... void setFramerate(byte fps);
    void setWidth(byte leftEye, byte rightEye);
    void setHeight(byte leftEye, byte rightEye);
    void setBorderradius(byte leftEye, byte rightEye);
    void setSpacebetween(int space);
    void setMood(unsigned char mood);
    void setPosition(unsigned char position);
    void setAutoblinker(bool active, int interval, int variation);
    void setAutoblinker(bool active);
    void setIdleMode(bool active, int interval, int variation);
    void setIdleMode(bool active);
    void setCuriosity(bool curiousBit);
    void setCyclops(bool cyclopsBit);
    void setHFlicker (bool flickerBit, byte Amplitude);
    void setHFlicker (bool flickerBit);
    void setVFlicker (bool flickerBit, byte Amplitude);
    void setVFlicker (bool flickerBit);

    //*********************************************************************************************
    //  GETTERS METHODS
    //*********************************************************************************************
    int getScreenConstraint_X();
    int getScreenConstraint_Y();

    //*********************************************************************************************
    //  BASIC ANIMATION METHODS
    //*********************************************************************************************
    void close();
    void open();
    void blink();
    void close(bool left, bool right);
    void open(bool left, bool right);
    void blink(bool left, bool right);
    void anim_confused();
    void anim_laugh(); 

    //*********************************************************************************************
    //  PRE-CALCULATIONS AND ACTUAL DRAWINGS
    //*********************************************************************************************
    void drawEyes(TFT_eSPI* tft,TFT_eSprite* sprite);



    // Nová paleta s 16 odstíny modré barvy (od 0x0000FF po 0x0909FF)
    uint16_t Custom_4bit_palette[16] = {
      0x000000, //  0 - black
      0x000003, //  1 - blue 1
      0x000005, //  2 - blue 2
      0x000007, //  3 - blue 3
      0x000009, //  4 - blue 4
      0x00000A, //  5 - blue 5
      0x00000C, //  6 - blue 6
      0x00000D, //  7 - blue 7
      0x00000E, //  8 - blue 8
      0x00000F, //  9 - blue 9
      0xFF00FF, // 10 - Violet 1
      0xFF0088, // 11 - Violet 2
      0xFF0000, // 12 - Violet 3
      0xDDDDFF, // 13 - Gray 1
      0xEEEEFF, // 14 - Gray 2
      0xFFFFFF  // 15 - White
    };

    std::vector<std::vector<int>> phases; // Trajektorie fází

   
    // For general setup - screen size and max. frame rate
    int screenWidth = 320; // OLED display width, in pixels
    int screenHeight = 240; // OLED display height, in pixels
    int frameInterval = 20; // default value for 50 frames per second (1000/50 = 20 milliseconds)
    unsigned long fpsTimer = 0; // for timing the frames per second



    // Usage of monochrome display colors
    #define BGCOLOR 0 // background and overlays
    #define MAINCOLOR 1//0x0000FF // drawings
    #define HIGHLIGHT 13//0x0A0AFF // drawings

    // For mood type switch
    #define DEFAULT 0
    #define TIRED 1
    #define ANGRY 2
    #define HAPPY 3
    #define SUSPECT 4
    // For turning things on or off
    #define ON 1
    #define OFF 0

    // For switch "predefined positions"
    // N has colision... #define N 1 // north, top center
    #define NORTH 1 // (replaced) north, top center
    #define NE 2 // north-east, top right
    #define E 3 // east, middle right
    #define SE 4 // south-east, bottom right
    #define S 5 // south, bottom center
    #define SW 6 // south-west, bottom left
    #define W 7 // west, middle left
    #define NW 8 // north-west, top left 
    // for middle center set "DEFAULT"

    // For controlling mood types and expressions
    bool tired = 0;
    bool angry = 0;
    bool happy = 0;
    bool suspect = 0;
    bool curious = 0; // if true, draw the outer eye larger when looking left or right
    bool cyclops = 0; // if true, draw only one eye
    bool eyeL_open = 0; // left eye opened or closed?
    bool eyeR_open = 0; // right eye opened or closed?


    //*********************************************************************************************
    //  Eyes Geometry
    //*********************************************************************************************

    // EYE Shadow / highlight
    int eyeInnerShadowWidth = 5;
    int eyeInnerShadowHeight = 5;
    int eyeInnerShadowAlpha = 100;
    int eyeInnerShadowBorderRadiusDefault = 15;
    int eyeInnerShadowShiftHorizontal = 0;
    int eyeInnerShadowShiftVertical = -5;


    // EYE Shifthing
    int eyeShiftHorizontal = 0;
    int eyeShiftVertical =0;
    int eyeTilt = 0;
    int eyeRotate = 0;

    // EYE LEFT - size and border radius
    int eyeLwidthDefault = 120;
    int eyeLheightDefault = 120;
    int eyeLwidthCurrent = eyeLwidthDefault;
    int eyeLheightCurrent = 1; // start with closed eye, otherwise set to eyeLheightDefault
    int eyeLwidthNext = eyeLwidthDefault;
    int eyeLheightNext = eyeLheightDefault;
    int eyeLheightOffset = 0;
    // Border Radius
    byte eyeLborderRadiusDefault = 15;
    byte eyeLborderRadiusCurrent = eyeLborderRadiusDefault;
    byte eyeLborderRadiusNext = eyeLborderRadiusDefault;

    // EYE RIGHT - size and border radius
    int eyeRwidthDefault = eyeLwidthDefault;
    int eyeRheightDefault = eyeLheightDefault;
    int eyeRwidthCurrent = eyeRwidthDefault;
    int eyeRheightCurrent = 1; // start with closed eye, otherwise set to eyeRheightDefault
    int eyeRwidthNext = eyeRwidthDefault;
    int eyeRheightNext = eyeRheightDefault;
    int eyeRheightOffset = 0;
    // Border Radius
    byte eyeRborderRadiusDefault = 15;
    byte eyeRborderRadiusCurrent = eyeRborderRadiusDefault;
    byte eyeRborderRadiusNext = eyeRborderRadiusDefault;

    // EYE LEFT - Coordinates
    int eyeLxDefault = ((screenWidth)-(eyeLwidthDefault+spaceBetweenDefault+eyeRwidthDefault))/2;
    int eyeLyDefault = ((screenHeight-eyeLheightDefault)/2);
    int eyeLx = eyeLxDefault;
    int eyeLy = eyeLyDefault;
    int eyeLxNext = eyeLx;
    int eyeLyNext = eyeLy;

    // EYE RIGHT - Coordinates
    int eyeRxDefault = eyeLx+eyeLwidthCurrent+spaceBetweenDefault;
    int eyeRyDefault = eyeLy;
    int eyeRx = eyeRxDefault;
    int eyeRy = eyeRyDefault;
    int eyeRxNext = eyeRx;
    int eyeRyNext = eyeRy;

    // BOTH EYES 
    // Eyelid top size
    byte eyelidsHeightMax = eyeLheightDefault/2; // top eyelids max height
    byte eyelidsTiredHeight = 0;
    byte eyelidsTiredHeightNext = eyelidsTiredHeight;
    byte eyelidsAngryHeight = 0;
    byte eyelidsAngryHeightNext = eyelidsAngryHeight;
    byte eyelidsLaughHeight = 0;
    byte eyelidsLaughHeightNext = eyelidsLaughHeight;
    byte eyelidsSuspectHeight = 0;
    byte eyelidsSuspectHeightNext = eyelidsSuspectHeight;
    // Bottom happy eyelids offset
    byte eyelidsHappyBottomOffsetMax = (eyeLheightDefault/2)+3;
    byte eyelidsHappyBottomOffset = 0;
    byte eyelidsHappyBottomOffsetNext = 0;
    // Space between eyes
    int spaceBetweenDefault = 10;
    int spaceBetweenCurrent = spaceBetweenDefault;
    int spaceBetweenNext = 10;


    //*********************************************************************************************
    //  Macro Animations
    //*********************************************************************************************

    // Animation - horizontal flicker/shiver
    bool hFlicker = 0;
    bool hFlickerAlternate = 0;
    byte hFlickerAmplitude = 2;

    // Animation - vertical flicker/shiver
    bool vFlicker = 0;
    bool vFlickerAlternate = 0;
    byte vFlickerAmplitude = 10;

    // Animation - auto blinking
    bool autoblinker = 0; // activate auto blink animation
    int blinkInterval = 1; // basic interval between each blink in full seconds
    int blinkIntervalVariation = 4; // interval variaton range in full seconds, random number inside of given range will be add to the basic blinkInterval, set to 0 for no variation
    unsigned long blinktimer = 0; // for organising eyeblink timing

    // Animation - idle mode: eyes looking in random directions
    bool idle = 0;
    int idleInterval = 1; // basic interval between each eye repositioning in full seconds
    int idleIntervalVariation = 3; // interval variaton range in full seconds, random number inside of given range will be add to the basic idleInterval, set to 0 for no variation
    unsigned long idleAnimationTimer = 0; // for organising eyeblink timing

    // Animation - eyes confused: eyes shaking left and right
    bool confused = 0;
    unsigned long confusedAnimationTimer = 0;
    int confusedAnimationDuration = 500;
    bool confusedToggle = 1;

    // Animation - eyes laughing: eyes shaking up and down
    bool laugh = 0;
    unsigned long laughAnimationTimer = 0;
    int laughAnimationDuration = 500;
    bool laughToggle = 1;
public:

    //RobotCYDEyes(const TFT_eSPI& tft,const TFT_eSprite& sprite);
    RobotCYDEyes(TFT_eSPI *tft,TFT_eSprite* sprite);

//    void initialize(const TFT_eSPI& tft,const TFT_eSprite& sprite,const int Width,const int Heigh,const int frameRate);
    void initialize(TFT_eSPI* tft, TFT_eSprite* sprite,const int Width,const int Heigh,const int frameRate);


//    void update(const TFT_eSPI& tft,const TFT_eSprite& sprite);
    void update(TFT_eSPI* tft,TFT_eSprite* sprite);

    void setFramerate(byte fps);
    void set(String Action,String Value1,String Value2);

};

#endif