
#ifndef ROBOT_CYD_EYESPOLY_EFFECTS_H
#define ROBOT_CYD_EYESPOLY_EFFECTS_H
// animation EFFECTS defined by sequence of modifiers or deformations
// like Breathig effects when stage wait time is defined (like 3000ms of breahing)
// effects are deployed to both eyes together and
// it has been repeating until time exceed and next face/eye/stage/shape begin
#include "Robot_CYD_EyesPoly_Modifiers.h"
#include <vector>

namespace RobotCYDEyesPoly {
namespace Effect {

struct Point {
  float x, y;
};

struct EffectStage {
  float transitionSpeed = 0;                    // -1 = slower end, (+)1 = faster end, 0= constant speed
  int steps = 10;                             // number of steps to change next Stage
  // std::array<Face::Point, 12> L_facePoly;     // Left Eye : Face definition for this stage
  // std::array<Mod::Point, 12> L_modifierPoly;  // Left Eye : Mdifier definition of Left Eye for this stage
  // int L_flip = 0;                             // horizontal flip for Left Eye - 1= true
  // std::array<Face::Point, 12> R_facePoly;     // Right Eye : Face definition for this stage
  // std::array<Mod::Point, 12> R_modifierPoly;  // Right Eye : Mdifier definition of Right Eye for this stage
  // int R_flip = 1;                             // horizontal flip for Right Eye - 1= true
  // Face::Point L_offset;                       // Left Eye offset for this stage, if next stage has offset 0,0 it means it will return to default position automatically
  // Face::Point R_offset;                       // Right Eye offset for this stage, if next stage has offset 0,0 it means it will return to default position automatically
  // int waitTimeMS;                             // number of ms waiting before next stage
  // int repeatLastStages;                       // number of stages to repeat animation again (do it only on the end of whole animation)
};

//inline static Face::Point REOffset = { 100, 0 };  // RIGHT EYE OFFSET - default offset to right Eye compared to left eye - (center point)
//inline static Face::Point NOffset = { 0, 0 };     // No Offset

inline static std::vector<EffectStage> Nothing = {

};

}

}

#endif