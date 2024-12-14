#ifndef ROBOT_CYD_CORE_H
#define ROBOT_CYD_CORE_H

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "Robot_CYD_Eyes.h"
#include "Robot_CYD_EyesPoly.h"
#include "bitmaps.h"


class RobotCYDCore {

private:
    void initSprite();

    String LastActionType="";
int shift=0;
    TFT_eSPI tft = TFT_eSPI();
    TFT_eSprite sprite=TFT_eSprite(&tft);
    RobotCYDEyes eyes=RobotCYDEyes(&tft,&sprite);
    RobotCYDEyesPoly::Poly eyesPoly=RobotCYDEyesPoly::Poly(&sprite);

int polygonpoints=12;

int steps =10;
 // Struktura pro body
      struct Point {
        float x, y;
      };

RobotCYDCore::Point polygonA[12] = {
   // {100, 100},{100, 100},
    {100, 100}, {130, 80}, {160, 120},  // Horní hrana
    {190, 100}, {190, 130}, {190, 160},  // Pravá hrana
    {190, 190}, {160, 190}, {130, 190}, 
    {100, 190}, {100, 160}, {100, 130},  // Mezi-hrany
   //{100, 100},{100, 100}
  };


  RobotCYDCore::Point polygonVector[12] = {
   // {0, 0},{0, 0},
    {0, 0}, {0, 0}, {0, 0},  // Horní hrana
    {0, 0}, {0, 0}, {0, 0},  // Pravá hrana
    {0, 0}, {0, 0}, {0, 0}, 
    {0, 0}, {0, 0}, {0, 0},  // Mezi-hrany
    //{0, 0},{0, 0}
  };

  RobotCYDCore::Point polygonB[12] = {
   // {100, 50},{100, 50},
    {100, 50}, {130, 70}, {160, 30},  // Horní hrana
    {190, 60}, {200, 120}, {180, 160},  // Pravá hrana
    {200, 220}, {150, 200}, {140, 180}, 
    {60, 210}, {40, 170}, {30, 100},  // Mezi-hrany
    //{100, 50},{100, 50}
  };

  RobotCYDCore::Point polygon[12] = {
   // {100, 50},{100, 50},
    {100, 50}, {130, 70}, {160, 30},  // Horní hrana
    {190, 60}, {200, 120}, {180, 160},  // Pravá hrana
    {200, 220}, {150, 200}, {140, 180}, 
    {60, 210}, {40, 170}, {30, 100},  // Mezi-hrany
    //{100, 50},{100, 50}
  };
      // Barva výplně polygonu
      #define FILL_COLOR TFT_BLUE

     
    void drawSpline(Point *points, int numPoints, uint16_t color); 
    void fillPolygon(Point *points, int numPoints, uint16_t fillColor);
    void drawClosedSpline(Point *points, int numPoints, uint16_t color,Point* pointsVector);
    void drawRoundedPolygon(Point *polygon, int numPoints, float radius, uint16_t color);
    void drawArc(Point center, float radius, float startAngle, float endAngle, uint16_t color);
    float angleBetween(Point p1, Point p2, Point p3);
    float distance(Point p1, Point p2);
    RobotCYDCore::Point catmullRom(Point p0, Point p1, Point p2, Point p3, float t);
//    void getSplinePoints(Point* points, int numPoints, Point* result, int& resultCount, float step = 0.05);
    void getSplinePoints(Point* points, int numPoints, Point* result, int& resultCount, float step = 0.05);
    RobotCYDCore::Point catmullRom2(Point p0, Point p1, Point p2, Point p3, float t);

    void B_getBezierPoints(Point* points, int numPoints, Point* result, int& resultCount, float step = 0.05);
    RobotCYDCore::Point  B_bezierPoint(Point p0, Point p1, Point p2, Point p3, float t);
    void B_fillPolygon(Point* points, int numPoints, uint16_t fillColor);
    // // Nová paleta s 16 odstíny modré barvy (od 0x0000FF po 0x0909FF)
    // uint16_t Custom_4bit_palette[16] = {
    //   0xaa0000, //  0 - black
    //   0x0000E4, //  1 - blue 1
    //   0x0000EA, //  2 - blue 2
    //   0x0000F5, //  3 - blue 3
    //   0x0000F6, //  4 - blue 4
    //   0x0000F7, //  5 - blue 5
    //   0x0000F8, //  6 - blue 6
    //   0x0000F9, //  7 - blue 7
    //   0x0000FD, //  8 - blue 8
    //   0x0000FE, //  9 - blue 9
    //   0x0000FF, // 10 - Violet 1
    //   0x00F00F, // 11 - Violet 2
    //   0x00F000, // 12 - Violet 3
    //   0xDDDDFF, // 13 - Gray 1
    //   0xEEEEFF, // 14 - Gray 2
    //   0xFFFFFF  // 15 - White
    // };
    // Nová paleta s 16 odstíny modré barvy (od 0x0000FF po 0x0909FF)
    // uint16_t Custom_4bit_palette[16] = {
    //   0xaa0000, //  0 - black
    //   0x0000E0, //  1 - blue 1
    //   0x0000E8, //  2 - blue 2
    //   0x0000EA, //  3 - blue 3
    //   0x0000EB, //  4 - blue 4
    //   0x0000ED, //  5 - blue 5
    //   0x0000F1, //  6 - blue 6
    //   0x0000F5, //  7 - blue 7
    //   0x0000FD, //  8 - blue 8
    //   0x0000FE, //  9 - blue 9
    //   0x0000FF, // 10 - Violet 1
    //   0x00F00F, // 11 - Violet 2
    //   0x00F000, // 12 - Violet 3
    //   0xDDDDFF, // 13 - Gray 1
    //   0xEEEEFF, // 14 - Gray 2
    //   0xFFFFFF  // 15 - White
    // };

public:
    RobotCYDCore();

    void initialize();
    void update();

    void setFramerate(byte fps);

    void set(String ActionType,String Action,String Value1,String Value2);
    // Nastavení serv
   
    
    // // Nastavení serv
    // void set(const int s1,const int s2,const int s3,const int s4);
    
    // // Načtení fází
    // void loadPhases(const std::vector<std::vector<int>>& newPhases);

    // // Zahájení pohybu
    // void startPhase();

    // // Provádění jedné iterace pohybu
    // void setPhasePosition();

    // // Kontrola, zda je pohyb dokončen
    // bool isPhaseComplete() const;
};

#endif