#ifndef ROBOT_CYD_EYESPOLY_FACES_H
#define ROBOT_CYD_EYESPOLY_FACES_H
// FACE POLYLOGN DEFINIIONS
// CENTRAL COORDINATES !!! (middle of eye)
#include <array> 

namespace RobotCYDEyesPoly {
namespace Eye {
struct Point {
  float x, y;
};
// default standard Eye squeare

inline static const std::array<Point, 12> Normal_Square = { {
  { -40, -40 }, { -20, -45 }, { 20, -45 }, { 40, -40 },  // TOP line
  { 45, -20 },
  { 45, 20 },  // Right side
  { 40, 40 },
  { 20, 45 },
  { -20, 45 },
  { -40, 40 },  // Bottom line
  { -45, 20 },
  { -45, -20 },  // leftside
} };

inline static const std::array<Point, 12> Sleep_Little = { {
  { -60, 30 }, { -35, 40 }, { 35, 40 }, { 60, 30 },  // TOP line
  { 50, 45 },
  { 45, 55 },  // Right side
  { 40, 60 },
  { 20, 65 },
  { -20, 65 },
  { -40, 60 },  // Bottom line
  { -45, 55 },
  { -50, 45 },  // leftside
} };

inline static const std::array<Point, 12> ERROR_DO_NOT_USE_130_minus_1f = { {
  { -60, 50 }, { -40, 55 }, { 40, 55 }, { 60, 50 },  // TOP line
  { 50, 60 },
  { 45, 60 },  // Right side
  { 40, 60 },
  { 20, 65 },
  { -20, 65 },
  { -40, 60 },  // Bottom line
  { -45, 60 },
  { -50, 60 },  // leftside
} };

inline static const std::array<Point, 12> Sleep_Down = { {
  { -60, 50 }, { -50, 35 }, { 50, 35 }, { 60, 50 },  // TOP line
  { 50, 50 },
  { 50, 50 },  // Right side
  { 40, 50 },
  { 30, 50 },
  { -30, 50 },
  { -40, 50 },  // Bottom line
  { -50, 50 },
  { -50, 50 },  // leftside
} };

inline static const std::array<Point, 12> Sleep_Down2 = { {
  { -60, 50 }, { -50, 25 }, { 50, 25 }, { 60, 50 },  // TOP line
  { 50, 50 },
  { 50, 50 },  // Right side
  { 40, 50 },
  { 30, 50 },
  { -30, 50 },
  { -40, 50 },  // Bottom line
  { -50, 50 },
  { -50, 50 },  // leftside
} };

inline static const std::array<Point, 12> Sleep_Half = { {
  { -60, 25 }, { -50, 15 }, { 50, 15 }, { 60, 25 },  // TOP line
  { 65, 30 },
  { 65, 35 },  // Right side
  { 60, 40 },
  { 55, 45 },
  { -55, 45 },
  { -60, 40 },  // Bottom line
  { -65, 35 },
  { -65, 30 },  // leftside
} };

inline static const std::array<Point, 12> Sleep_Normal = { {
  { -60, 60 }, { -50, 55 }, { 50, 55 }, { 60, 60 },  // TOP line
  { 60, 60 },
  { 60, 65 },  // Right side
  { 50, 65 },
  { 40, 65 },
  { -40, 65 },
  { -50, 65 },  // Bottom line
  { -60, 65 },
  { -60, 60 },  // leftside
} };

inline static const std::array<Point, 12> Left_Side = { {
  { -60, -40 }, { -30, -25 }, { 10, -5 }, { 20, -0 },  // TOP line
  { 40, 0 },
  { 40, 10 },  // Right side
  { 40, 40 },
  { 20, 45 },
  { -20, 45 },
  { -40, 40 },  // Bottom line
  { -60, 20 },
  { -65, -20 },  // leftside
} };

inline static const std::array<Point, 12> Right_Side = { {
  { -20, 0 }, { -10, -5 }, { 30, -25 }, { 60, -40 },  // TOP line
  { 65, -20 },
  { 60, 20 },  // Right side
  { 40, 40 },
  { 20, 45 },
  { -20, 45 },
  { -40, 40 },  // Bottom line
  { -40, 10 },
  { -40, 0 },  // leftside
} };


inline static const std::array<Point, 12> Heart_Normal = { {
  { -30, -30 }, { 0,0 }, { 0,0 }, { 30, -30 },  // TOP line
  { 60, -10 },
  { 40, 40 },  // Right side
  { 10, 70 },
  { 0, 80 },
  { 0, 80 },
  { -10, 70 },  // Bottom line
  { -40, 40 },
  { -60, -10 },  // leftside
} };


inline static const std::array<Point, 12> Cross_Normal = { {
  { -20, -30 }, { 0,-10 }, { 20,-30 }, { 30, -20 },  // TOP line
  { 10, 0 }, { 30, 20 },  // Right side
  { 20, 30 },  { 0, 10 },  { -20, 30 },  { -30, 20 },  // Bottom line
  { -10, 0 },  { -30, -20 },  // leftside
} };


// default standard Eye bold side
inline static const std::array<Point, 12> Tired_XXXXX = { {
  { -20, -20 }, { -10, -30 }, { 10, -30 }, { 20, -40 },  // TOP line
  { 60, -20 },
  { 60, 20 },  // Right side
  { 20, 40 },
  { 10, 40 },
  { -10, 40 },
  { -20, 40 },  // Bottom line
  { -60, 20 },
  { -60, -20 },  // leftside
} };

inline static const std::array<Point, 12> Number_Four = {{
    { 40,  20 }, { -40, 20 },   { 10, -30 },   // Horní oblouk
    { 10, 50 },   { 0, 50 },    // Přechod mezi oblouky
    { 0, -20 },   { -30, 0 },    { 40, 0 },   // Spodní oblouk
    { 40, 0 },{ 40, 0 },{ 40, 0 },{ 40, 0 }   // Spojení a zakončení
}};

inline static const std::array<Point, 12> Number_Three = {{
    { -40, -20 }, { 0, -40 },   { 40, -20 },   // Horní oblouk
    { 10, 0 },   { 45, 20 },    // Přechod mezi oblouky
    { 0, 50 },   { -45, 20 },    { 0, 40 },   // Spodní oblouk
    { 20, 20 },  { 0, 0 }, { 20, -20 },{0,-30}   // Spojení a zakončení
}};

inline static const std::array<Point, 12> Number_Two = {{
    { -40, -20 }, { 0, -40 },   { 40, -20 },   // Horní oblouk
    { 45, 0 },    { 20, 20 },    // Přechod dolů
    { 0, 30 },    { 40, 40 },   // Spodní oblouk
    { -45, 40 },  { -30, 10 },   // Ostré zakončení doleva
    { 0, 0 },     { 20, -10 },   { 0, -20 }    // Spojení
}};

inline static const std::array<Point, 12> Number_One = {{
    { 0, -45 },   { 10, -40 },  { 10, 40 },   // Hlavní vertikální čára
    { 0, 45 },    { -10, 40 },  { -10, -40 }, // Levý okraj čáry
    { -5, -45 },  { 0, -50 },   { 5, -45 },   // Vrchní "špička"
    { -5, 40 },   { 5, 40 },    { 0, 45 }     // Spodní zakončení
}};

}
}

#endif