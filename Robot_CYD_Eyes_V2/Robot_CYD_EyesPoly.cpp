#include "esp32-hal.h"
#include <algorithm>
#include "Robot_CYD_EyesPoly_Animations.h"
#include "Robot_CYD_EyesPoly_Faces.h"
#include "Robot_CYD_EyesPoly_Colors.h"
#include "Robot_CYD_EyesPoly_Files.h"
// ENGINE TO DRAW PREDEFINED FACES AND ANIMATIONS OF FACES

#include "Robot_CYD_EyesPoly.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
using RobotCYDEyesPoly::Poly;

// instance
Poly::Poly(TFT_eSprite* sprite) {
  memcpy(sourcePalette, Colors::Default_4bit_palette, sizeof(Colors::Default_4bit_palette));
  memcpy(targetPalette, Colors::Default_4bit_palette, sizeof(Colors::Default_4bit_palette));
}

// initialization
void Poly::init() {
}


void Poly::set(String Action, String Value1, String Value2) {

  Serial.print("[eyesPoly]");
  Serial.print("(setMood):");
  Serial.print(Action);

  int steps = 50;
  float speed = -4.0f;  // Zvyšuje zrychlení, negativní hodnota zpomaluje

if (Action=="testColors")
{
  memcpy(sourcePalette, targetPalette, sizeof(Colors::Default_4bit_palette));
  if (Value1 == "0") memcpy(targetPalette, Colors::Black_4bit_palette, sizeof(Colors::Default_4bit_palette));
  if (Value1 == "1") memcpy(targetPalette, Colors::Default_4bit_palette, sizeof(Colors::Default_4bit_palette));
  if (Value1 == "2") memcpy(targetPalette, Colors::Red_4bit_palette, sizeof(Colors::Red_4bit_palette));
  if (Value1 == "3") memcpy(targetPalette, Colors::Test_4bit_palette, sizeof(Colors::Test_4bit_palette));
  if (Value1 == "4") memcpy(targetPalette, Colors::Green_4bit_palette, sizeof(Colors::Green_4bit_palette));
  if (Value1 == "5") memcpy(targetPalette, Colors::Green2_4bit_palette, sizeof(Colors::Green2_4bit_palette));
  if (Value1 == "6") memcpy(targetPalette, Colors::White_4bit_palette, sizeof(Colors::White_4bit_palette));
  if (Value1 == "7") memcpy(targetPalette, Colors::White_4bit_palette, sizeof(Colors::White2_4bit_palette));
  if (Value1 == "+10") 
  {
    for(int x=0;x<16;x++)
    {
     currentPalette[x]+=16;
    }
  }
  testColorsPoly=1;

  if (Value2 == "0") colorBit=0;
  if (Value2 == "1") colorBit=1;
  if (Value2 == "2") colorBit=2;
  if (Value2 == "3") colorBit=3;
  if (Value2 == "4") colorBit=4;
  if (Value2 == "5") colorBit=5;
  if (Value2 == "6") colorBit=6;
  if (Value2 == "7") colorBit=7;
  if (Value2 == "8") colorBit=8;
}
else
{
  memcpy(currentPalette, Colors::Default_4bit_palette, sizeof(Colors::Default_4bit_palette));

  if (Value1 == "0")
  {
    // default hardcod loading
    if (Action=="tst")
      ActualAnimation = Anim::tst;
    else if (Action=="wakeup")
      ActualAnimation = Anim::Wake_UP;
    else  
      ActualAnimation = Anim::Normal_Square;
  }
  else
  {
    // fila loading
  Serial.printf("Free heap before: %d bytes\n", ESP.getFreeHeap());

  // Před alokací customEyes
  //customEyes.reset();  //= std::make_unique<std::unordered_map<std::string, std::array<Eye::Point, 12>>>();
  Serial.printf("Free heap after Eyes allocation: %d bytes\n", ESP.getFreeHeap());

    std::string test = Files::getDefaultTest();
    //Serial.println(test.c_str());
    //delay(2000);



  // Před alokací customAnimations
  //customAnimations.clear();
  Serial.printf("Free heap after Animations cleared: %d bytes\n", ESP.getFreeHeap());


   Anim::loadAnimations(test); // load test string

   // Vyprázdnění paměti, pokud už řetězec nepotřebujete
    test.clear();
    test.shrink_to_fit();
//    if (Anim::customAnimations && Anim::customAnimations->find(Value1) != Anim::customAnimations->end())
    // for (int A=0;A<Anim::customAnimations.size();A++)
    // {
    //   Serial.println("----------------------");
    //   Serial.println(Anim::customAnimations[A].key().c_str());
    //   Serial.println(Value1.c_str());
    //   if (Anim::customAnimations[A].key().c_str()==Value1.c_str() )
    //   {
    //     Serial.println("found");
    //   }

    // }
// for (const auto& item : Anim::customAnimations) {
//         // item.first je klíč
//         Serial.println("-------------------Key--------------------");
//        Serial.println(String(item.first.c_str()));

//         // // Volitelně můžeš projít i hodnoty (vektor AnimationStage)
//         // std::cout << "Values: " << std::endl;
//         // for (const auto& stage : item.second) {
//         //     std::cout << "  Frame: " << stage.frame 
//         //               << ", Description: " << stage.description << std::endl;
//         // }
//     }

    auto it = Anim::customAnimations.find(Value1.c_str()); // Hledání klíče
    if (it != Anim::customAnimations.end())
    {
       Serial.println("FOUND");
      ActualAnimation=Anim::customAnimations[Value1.c_str()];//Value1.c_str()]; //select first animation
    }
    else
    {
       Serial.println("NOT FOUND!!!");
      ActualAnimation=Anim::customAnimations["testAnim1"];
    }
  }
}
 // Zavolání funkce pro morfing mezi dvěma polygonu
    animationIDX = -1;
    TransBetweenAnimations=true;
    setAnimationNextStage();

    Serial.printf("Free heap: %d bytes\n", ESP.getFreeHeap());
  Serial.printf("Largest free block: %d bytes\n", ESP.getMaxAllocHeap());


}

void Poly::testColors(TFT_eSprite *s)
{
  for (int i = 0; i <= 15; i++) {
        s->fillRect(320/16*i,0,320/16,240,i);
        }
}

void Poly::setAnimationNextStage() {

  //int steps = 4;
  //float speed = -1.0f;//-4.0f;  // Zvyšuje zrychlení, negativní hodnota zpomaluje

  // Zavolání funkce pro morfing mezi dvěma polygonu
  //animationIDX = 0;
  

  transitionStepIDX = 0;
  //transitionStepCount = steps;
  //transitionSpeed = speed;
//  transitionSteps = morphPolygons(Eye::Right_Side, Eye::Left_Side, transitionStepCount, transitionSpeed);

if (TransBetweenAnimations==false)
{
  //standard transition between animation stages
  if (animationIDX<ActualAnimation.size()-1)
   {
    animationIDX++;
   }
   else
   {
    animationIDX=0;
   }
   int nextIdx=(animationIDX+1) % ActualAnimation.size();
  //  Serial.print("AnimationIDX:");
  //  Serial.print(animationIDX);
  //  Serial.print(",items:");
  //  Serial.print(Anim::Wake_UP.size());
  //  Serial.print(",steps:");
  //  Serial.print(Anim::Wake_UP[animationIDX].steps);
  //  Serial.println();
 //  L_transitionSteps = morphPolygons(Eye::Right_Side, Eye::Left_Side, 50,transitionSpeed);//, Anim::Wake_UP[animationIDX].transitionSpeed);
//   L_transitionSteps = morphPolygons(Anim::Wake_UP[animationIDX].L_facePoly, Anim::Wake_UP[nextIdx].L_facePoly, Anim::Wake_UP[nextIdx].steps,Anim::Wake_UP[nextIdx].transitionSpeed);
//   R_transitionSteps = morphPolygons(Anim::Wake_UP[animationIDX].R_facePoly, Anim::Wake_UP[nextIdx].R_facePoly, Anim::Wake_UP[nextIdx].steps,Anim::Wake_UP[nextIdx].transitionSpeed);

   L_transitionSteps = morphPolygons(ActualAnimation[animationIDX].L_eye, ActualAnimation[nextIdx].L_eye, ActualAnimation[nextIdx].steps,ActualAnimation[nextIdx].transitionSpeed);
   R_transitionSteps = morphPolygons(ActualAnimation[animationIDX].R_eye, ActualAnimation[nextIdx].R_eye, ActualAnimation[nextIdx].steps,ActualAnimation[nextIdx].transitionSpeed);
   L_actualColor = ActualAnimation[animationIDX].L_color;
   R_actualColor = ActualAnimation[animationIDX].R_color;

   transitionStepCount =L_transitionSteps.size();
   //Serial.println(transitionStepCount);
  }
else
  {
    //special transition phase between actual shape and new defined animation
    TransBetweenAnimations=false; //reset
    std::array<RobotCYDEyesPoly::Eye::Point, 12> LL_EyeShape;
    std::array<RobotCYDEyesPoly::Eye::Point, 12> RR_EyeShape;

    shiftPoints(L_EyeShape, -90, -100);
    shiftPoints(R_EyeShape, -90, -100);

    for (size_t i = 0; i < L_EyeShape.size(); ++i) {
        LL_EyeShape[i] = {L_EyeShape[i].x, L_EyeShape[i].y};
        RR_EyeShape[i] = {R_EyeShape[i].x, R_EyeShape[i].y};
    }

    L_transitionSteps = morphPolygons(LL_EyeShape, ActualAnimation[0].L_eye, ActualAnimation[0].steps,ActualAnimation[0].transitionSpeed);
    R_transitionSteps = morphPolygons(RR_EyeShape, ActualAnimation[0].R_eye, ActualAnimation[0].steps,ActualAnimation[0].transitionSpeed);
    L_actualColor = ActualAnimation[animationIDX].L_color;
    R_actualColor = ActualAnimation[animationIDX].R_color;

    

    transitionStepCount =L_transitionSteps.size();
  }

  memcpy(currentPalette, sourcePalette, sizeof(Colors::Default_4bit_palette));
  memcpy(sourcePalette,targetPalette, sizeof(Colors::Default_4bit_palette));
  memcpy(targetPalette,currentPalette,  sizeof(Colors::Default_4bit_palette));
}

void Poly::drawOneEye(TFT_eSprite* sprite,std::array<Point, 12> Eye,int ShiftEye,int colorNumber)
{
  
  int splinePointCount = 1;
  Point* splinePoints = new Point[MAX_POINTS];  
  getSplinePoints(Eye, polygonPoints, splinePoints, splinePointCount);
  // Vyplnění oblasti
  fillPolygon(sprite, splinePoints, splinePointCount, colorNumber,ShiftEye);
  delete[] splinePoints;

}


void Poly::drawEyes(TFT_eSprite* sprite) {
  // EYE_Normal_Square[1]
  transitionStepIDX++;
  //Serial.println(transitionStepIDX);
  if (transitionStepIDX >= transitionStepCount) {
    setAnimationNextStage();
    transitionStepIDX = 0;  // bacha od 1cky :DDD
  }
 // const auto& currentStep = transitionSteps[transitionStepIDX];
  L_EyeShape = L_transitionSteps[transitionStepIDX];
  R_EyeShape = R_transitionSteps[transitionStepIDX];
  
//  uint16_t currentPalette[16];
  //calculateTransitionPalette(Anim::sourcePalette, Anim::targetPalette,currentPalette, transitionStepCount, transitionStepIDX);
//  interpolatePalette5bit(Anim::Black_4bit_palette, targetPalette,currentPalette, transitionStepCount, transitionStepIDX);
  Colors::interpolatePalette(sourcePalette, targetPalette,currentPalette, transitionStepIDX,transitionStepCount, colorBit, colorBit, colorBit,-4.0f);
//  sprite->createPalette(currentPalette);  //0-15 odstinu modre

  sprite->fillSprite(0x0000);
  sprite->createPalette(currentPalette);
 // if (testColorsPoly==1) testColors(sprite);

  drawOneEye(sprite,L_EyeShape,0,L_actualColor);
  drawOneEye(sprite,R_EyeShape,140,R_actualColor);
  // int splinePointCount = 1;
  // Point* splinePoints = new Point[1000];
  // sprite->fillSprite(0x0000);
  // getSplinePoints(L_EyeShape, polygonPoints, splinePoints, splinePointCount);
  // // Vyplnění oblasti
  // fillPolygon(sprite, splinePoints, splinePointCount, 10);
  // delete[] splinePoints;
  sprite->drawNumber(L_actualColor, 1, 1);
  //sprite->drawString("0x" + String(Anim::Test_4bit_palette[L_actualColor], HEX), 1, 15);
  sprite->drawNumber(R_actualColor, 140, 1);
  //sprite->drawString("0x" + String(Anim::Test_4bit_palette[L_actualColor], HEX), 140, 15);

  for (int i = 0; i < polygonPoints; i++) {
//    sprite->drawCircle(currentStep[i].x, currentStep[i].y, 10, 15);
//     Serial.printf(",Point[%d]{%.2f,%.2f}\n", i, L_EyeShape[i].x, L_EyeShape[i].y);
    sprite->drawCircle(L_EyeShape[i].x, L_EyeShape[i].y, 2, 15);
  }
//  Serial.println();
  sprite->pushSprite(0, 0);
}

// ********************************************************* SPLINE DRAW POLGON **************************************************************************


// Funkce pro výpočet Catmull-Rom interpolace
Poly::Point Poly::catmullRom2(Point p0, Point p1, Point p2, Point p3, float t) {
  float t2 = t * t;
  float t3 = t2 * t;

  float x = 0.5 * ((2 * p1.x) + (-p0.x + p2.x) * t + (2 * p0.x - 5 * p1.x + 4 * p2.x - p3.x) * t2 + (-p0.x + 3 * p1.x - 3 * p2.x + p3.x) * t3);
  float y = 0.5 * ((2 * p1.y) + (-p0.y + p2.y) * t + (2 * p0.y - 5 * p1.y + 4 * p2.y - p3.y) * t2 + (-p0.y + 3 * p1.y - 3 * p2.y + p3.y) * t3);

  return { int(x), int(y) };
}

// Funkce pro získání bodů uzavřené Catmull-Rom křivky s adaptivním vzorkováním
void Poly::getSplinePoints(const std::array<Point, 12>& points, int numPoints, Point* result, int& resultCount, float step) {
  resultCount = 0;
  //  Serial.println("point.size");
  //  Serial.println(points.size());
  for (int i = 0; i < numPoints; i++) {
    /*    Serial.print("Point[");
    Serial.print(i);
    Serial.print("]{");
    Serial.print(points[i].x);
    Serial.print(",");
    Serial.print(points[i].y);
    Serial.println("}");
  }
*/
    Point p0 = points[(i - 1 + numPoints) % numPoints];
    Point p1 = points[i];
    Point p2 = points[(i + 1) % numPoints];
    Point p3 = points[(i + 2) % numPoints];

    Point lastPoint = p1;
    //result[resultCount++] = p1;
     if (resultCount < MAX_POINTS) {
              result[resultCount++] = p1;
            } else {
              Serial.println("Error: result array overflow");
              return;  // Zabrání dalšímu přidávání bodů
            }
    //    Serial.println("stage1.1");
  

    for (float t = step; t <= 1; t += step) {

      Point currentPoint = catmullRom2(p0, p1, p2, p3, t);

      // Adaptivní vzorkování podle vzdálenosti bodů
      if (abs(currentPoint.x - lastPoint.x) > 2 || abs(currentPoint.y - lastPoint.y) > 2) {
        //Serial.println("stage1.2");

        if (resultCount < MAX_POINTS) {
          result[resultCount++] = currentPoint;
        } else {
          Serial.println("Error: result array overflow");
          return;  // Zabrání dalšímu přidávání bodů
        }

        //result[resultCount++] = currentPoint;
        lastPoint = currentPoint;
      }
    }
  }
}

// void Poly::getSplinePoints(const std::array<Point, 12>& points, int numPoints, Point* result, int& resultCount, float step) {
//     resultCount = 0;
// //    Serial.println("point.size");
// //    Serial.println(points.size());
//     Serial.printf("Free stack: %d bytes\n", uxTaskGetStackHighWaterMark(NULL));
//     for (int i = 0; i < numPoints; i++) {
//       // // Reset watchdog timeru
//       //   if (i % 2 == 0) {  // Krmíme watchdog každé dva průchody
//       //       esp_task_wdt_reset();
//       //   }
//       /// delay(1000);

//        Serial.printf("Point[%d]{%.2f,%.2f}\n", i, points[i].x, points[i].y);
//     }
// }

// Optimalizovaný Scanline algoritmus pro vyplnění oblasti
void Poly::fillPolygon(TFT_eSprite* sprite, Point* points, int numPoints, uint16_t fillColor,int shiftEye) {
  // Najdeme minimální a maximální y-ové souřadnice
  int minY = points[0].y, maxY = points[0].y;
  for (int i = 1; i < numPoints; i++) {
    if (points[i].y < minY) minY = points[i].y;
    if (points[i].y > maxY) maxY = points[i].y;
  }

  // Vyplňování pomocí horizontálních čar
  for (int y = minY; y <= maxY; y++) {
    int intersections[20];
    int count = 0;

    // Najdeme průsečíky se scanline
    for (int i = 0; i < numPoints; i++) {
      Point p1 = points[i];
      Point p2 = points[(i + 1) % numPoints];
      if ((p1.y <= y && p2.y > y) || (p2.y <= y && p1.y > y)) {
        float t = float(y - p1.y) / float(p2.y - p1.y);
        intersections[count++] = p1.x + t * (p2.x - p1.x);
      }
    }

    // Seřadíme průsečíky podle x
    for (int i = 0; i < count - 1; i++) {
      for (int j = i + 1; j < count; j++) {
        if (intersections[i] > intersections[j]) {
          int temp = intersections[i];
          intersections[i] = intersections[j];
          intersections[j] = temp;
        }
      }
    }

    // Vykreslíme čáry mezi dvojicemi průsečíků
    for (int i = 0; i < count; i += 2) {
      sprite->drawFastHLine(intersections[i]+shiftEye, y, intersections[i + 1] - intersections[i], fillColor);
      //      sprite.drawFastHLine(intersections[i], y, intersections[i + 1] - intersections[i], fillColor);
    }

    
  }
}

// *******************************************************************************************************************************************************


// Funkce pro posunutí všech bodů o danou hodnotu
void Poly::shiftPoints(std::array<Poly::Point, 12>& points, int shiftX, int shiftY) {
  // Projdeme každý bod v poli
  for (int i = 0; i < points.size(); ++i) {
    points[i].x += shiftX;  // Posuneme bod v ose X
    points[i].y += shiftY;  // Posuneme bod v ose Y
  }
 }


// std::vector<std::array<Poly::Point, 12>> Poly::morphPolygons(const std::array<RobotCYDEyesPoly::Eye::Point, 12>& startPolygon, const std::array<RobotCYDEyesPoly::Eye::Point, 12>& endPolygon, int steps, float tspeed) {
//     std::vector<std::array<Poly::Point, 12>> stepsArray;

//     for (int i = 0; i < steps; ++i) {
//         float t = (float)i / (steps - 1);  // T od 0 do 1 pro každý krok

//         // Použijeme TransitionSpeed pro úpravu t
//         if (tspeed > 0) {
//             // Zrychlení - ke konci se rychlost zvyšuje
//             t = pow(t, tspeed);
//         } else {
//             // Zpomalení - ke konci se rychlost zpomaluje
//             t = 1.0f - pow(1.0f - t, -tspeed);
//         }

//         // Ujisti se, že t je mezi 0 a 1 (občas to může být mimo tento rozsah při extrémních hodnotách tspeed)
//         t = constrain(t, 0.0f, 1.0f);

//         // Vytvoření nového polygonu pro tento krok
//         std::array<Poly::Point, 12> currentStep;

//         for (int j = 0; j < 12; ++j) {
//             // Interpolace mezi start a end hodnotami
//             currentStep[j].x = startPolygon[j].x + (endPolygon[j].x - startPolygon[j].x) * t;
//             currentStep[j].y = startPolygon[j].y + (endPolygon[j].y - startPolygon[j].y) * t;

//             // Oprava skoků v interpolaci
//             currentStep[j].x = correctInterpolation(currentStep[j].x, startPolygon[j].x, endPolygon[j].x);
//             currentStep[j].y = correctInterpolation(currentStep[j].y, startPolygon[j].y, endPolygon[j].y);
//         }

//         shiftPoints(currentStep, 100, 100);
//         // Přidání do výsledného vektoru
//         stepsArray.push_back(currentStep);
//     }

//     return stepsArray;
// }

// Funkce pro opravu interpolace, pokud dojde k extrémnímu skoku
float Poly::correctInterpolation(float currentValue, float startValue, float endValue) {
    // Pokud je rozdíl mezi startem a koncem extrémní, opravíme hodnotu
    float diffStartEnd = std::abs(endValue - startValue);
    float diffCurrent = std::abs(currentValue - startValue);

    // Korekce skoků - pokud je rozdíl příliš velký, opravíme hodnotu
    if (diffCurrent > diffStartEnd * 5.0f) {  // Faktor, který určuje maximální přípustný rozdíl
        currentValue = startValue + (endValue - startValue) * 0.5f;  // Oprava na střední hodnotu
    }

    return currentValue;
}


// Funkce pro výpočet morfingu mezi dvěma polygonu
std::vector<std::array<Poly::Point, 12>> Poly::morphPolygons(const std::array<RobotCYDEyesPoly::Eye::Point, 12>& startPolygon, const std::array<RobotCYDEyesPoly::Eye::Point, 12>& endPolygon, int steps, float tspeed) {
  std::vector<std::array<Poly::Point, 12>> stepsArray;

  for (int i = 0; i < steps; ++i) {
    float t = (float)i / (steps - 1);  // T od 0 do 1 pro každý krok

    // Použijeme TransitionSpeed pro úpravu t
    if (tspeed > 0) {
      // Zrychlení - ke konci se rychlost zvyšuje
      t = pow(t, tspeed);
    } else {
      // Zpomalení - ke konci se rychlost zpomaluje
      t = 1.0f - pow(1.0f - t, -tspeed);
    }

    // Vytvoření nového polygonu pro tento krok
    std::array<Poly::Point, 12> currentStep;

    for (int j = 0; j < 12; ++j) {
      currentStep[j].x = startPolygon[j].x + (endPolygon[j].x - startPolygon[j].x) * t;
      currentStep[j].y = startPolygon[j].y + (endPolygon[j].y - startPolygon[j].y) * t;
    }

    shiftPoints(currentStep, 90, 100);
    // Přidání do výsledného vektoru
    stepsArray.push_back(currentStep);
  }

  return stepsArray;
}