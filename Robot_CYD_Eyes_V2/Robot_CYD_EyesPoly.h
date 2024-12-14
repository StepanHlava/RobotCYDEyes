#ifndef ROBOT_CYD_EYESPOLY_H
#define ROBOT_CYD_EYESPOLY_H

#include <TFT_eSPI.h>  // Hardware-specific library
#include <SPI.h>
//#include "Robot_CYD_EyesPoly_Faces.h"
#include "Robot_CYD_EyesPoly_Animations.h"

namespace RobotCYDEyesPoly {


class Poly {

private:
  struct Point {
    float x, y;
  };

  //Anim::AnimationStage fromStage;
  //Anim::AnimationStage toStage;

  std::array<Point, 12> L_EyeShape;
  std::array<Point, 12> R_EyeShape;
  int L_actualColor = 10;
  int R_actualColor = 10;
  bool TransBetweenAnimations=false; // indicator, when one animation ends and the new animation want to start (transition between actual morph step and new idx=0 animation stage)
  const int MAX_POINTS=500;
  const int polygonPoints=12;
  int animationIDX = 0;
  int transitionStepIDX=0;
  int transitionStepCount=0;
  float transitionSpeed=0;
  std::vector<std::array<Point, 12>> L_transitionSteps;
  std::vector<std::array<Point, 12>> R_transitionSteps;
  uint16_t sourcePalette[16];
  uint16_t targetPalette[16];
  uint16_t currentPalette[16];
  int testColorsPoly=0;
  int colorBit=4;

  std::vector<Anim::AnimationStage> ActualAnimation;

  void testColors(TFT_eSprite *s);

  Point catmullRom2(Point p0, Point p1, Point p2, Point p3, float t);
  void getSplinePoints(const std::array<Point, 12>& points, int numPoints, Point* result, int& resultCount, float step=0.1f);
  void fillPolygon(TFT_eSprite* sprite,Point* points, int numPoints, uint16_t fillColor,int shiftEye);
  std::vector<std::array<Point, 12>> morphPolygons(const std::array<RobotCYDEyesPoly::Eye::Point, 12>& startPolygon, const std::array<RobotCYDEyesPoly::Eye::Point, 12>& endPolygon, int steps, float transitionSpeed);
  float correctInterpolation(float currentValue, float startValue, float endValue);
  void shiftPoints(std::array<Point, 12>& points, int shiftX, int shiftY);
  void setAnimationNextStage(); 
  void drawOneEye(TFT_eSprite* sprite,std::array<Point, 12> Eye,int ShiftEye,int colorNumber);
public:
  Poly(TFT_eSprite* sprite);

  //*********************************************************************************************
  //  PRE-CALCULATIONS AND ACTUAL DRAWINGS
  //*********************************************************************************************
  void init();
  void set(String Action, String Value1, String Value2);
  void drawEyes(TFT_eSprite* sprite);
};

}

#endif
