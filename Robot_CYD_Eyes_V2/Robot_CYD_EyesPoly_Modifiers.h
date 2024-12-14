#ifndef ROBOT_CYD_EYESPOLY_MODIFIERS_H
#define ROBOT_CYD_EYESPOLY_MODIFIERS_H
// MODIFIERS POLYLOGN DEFINIIONS
// CENTRAL COORDINATES !!! (middle of eye)

namespace RobotCYDEyesPoly {
namespace Mod {
  struct Point {
    float x, y;
  };

 // ***********************************************************************************************
  // ***********************************************************************************************

  // mdifier tall effect
  inline static const std::array<Point, 12> Nothing = {{
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
  }};
  // mdifier tall effect
  inline static const std::array<Point, 12>  Tall = {{
    { 0, -10 }, { 0, -10 }, { 0, -10 },  // LefTop ->RightTop
    { 0, -10 },
    { 0, -5 },
    { 0, 5 },  // RightTop ->RightBottom
    { 0, 10 },
    { 0, 10 },
    { 0, 10 },  // RightBottom ->LeftBottom
    { 0, 10 },
    { 0, 5 },
    { 0, -5 },  // LeftBottom ->LeftTop(start)
  }};

  // mdifier tall effect
  inline static const std::array<Point, 12> Taller= {{
    { 0, -20 }, { 0, -20 }, { 0, -20 },  // LefTop ->RightTop
    { 0, -20 },
    { 0, -10 },
    { 0, 10 },  // RightTop ->RightBottom
    { 0, 20 },
    { 0, 20 },
    { 0, 20 },  // RightBottom ->LeftBottom
    { 0, 20 },
    { 0, 10 },
    { 0, -10 },  // LeftBottom ->LeftTop(start)
  }};

}
}
#endif
