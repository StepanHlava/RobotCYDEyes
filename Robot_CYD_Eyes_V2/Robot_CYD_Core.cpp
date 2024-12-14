#include "Robot_CYD_Core.h"
#include "Robot_CYD_EyesPoly_Colors.h"

// instance
RobotCYDCore::RobotCYDCore()
//:
//currentPhaseIndex(0), totalSteps(0), stepsRemaining(0), accelerationFactor(0) {
{
  // tft = TFT_eSPI(); // esp
  //sprite = TFT_eSprite(&tft); //CYD speed buffer
}

// Nastavení

void RobotCYDCore::initialize() {
  tft.init();                 // init TFT screen - Check setup from TFT_espi() user settings
  tft.setRotation(1);         // horizontal
  tft.fillScreen(TFT_BLACK);  // clear screen

  initSprite();  // init CYD fast sprite

  eyes.initialize(&tft, &sprite, 320, 240, 25);  // init Eyes Effects
}

void RobotCYDCore::initSprite() {

  // tft.fillCircleHelper(40,40,40,20,5,0x0000ff);
  // tft.fillCircleHelper(40,80,40,40,5,0x0000ff);
  // tft.fillCircleHelper(80,40,40,20,20,0x0000ff);
  // tft.fillCircleHelper(80,80,40,20,40,0x0000ff);
  // tft.fillCircleHelper(160,160,40,40,40,0x0000ff);
  // tft.fillCircleHelper(160,160,40,50,50,0x0000ff);
  //tft.drawBitmap(10,10,moon3,150,150,0xffffff,0x000000);
  tft.pushImage(10, 10, 150, 150, moon);
  tft.drawWedgeLine(165, 160, 175, 160, 30, 40, TFT_BLUE, TFT_WHITE);
  //tft.pushImage(160,10,150,150,moon3);
}

void RobotCYDCore::setFramerate(byte frameRate)  // calculate frame interval based on defined frameRate
{
  eyes.setFramerate(frameRate);
}

void RobotCYDCore::set(String ActionType, String Action, String Value1, String Value2) {
  Serial.print("[core]");

  if (ActionType == "eyes") {
    if (LastActionType != "eyes") {
      sprite.setColorDepth(4);
      sprite.createSprite(320, 240);              // Nastavení rozměrů sprite (třeba 240x240 pixelů)
      sprite.createPalette(RobotCYDEyesPoly::Colors::Default_4bit_palette);  //0-15 odstinu modre
    }
    eyes.set(Action, Value1, Value2);
  } else if (ActionType == "weather") {
  } else if (ActionType == "moon") {
    sprite.fillSprite(0x000000);
    sprite.setColorDepth(16);
    sprite.createSprite(150, 150);
    sprite.drawBitmap(0, 0, moon3_sprite, 150, 150, 0xffffff, 0x000000);
    sprite.pushSprite(0, 0);
    //tft.pushImage(10,10,150,150,moon3);
  } else if (ActionType == "poly") {
    sprite.setColorDepth(4);
    sprite.createSprite(320, 240);              // Nastavení rozměrů sprite (třeba 240x240 pixelů)
    sprite.createPalette(RobotCYDEyesPoly::Colors::Default_4bit_palette);  //0-15 odstinu modre
   eyesPoly.set(Action, Value1, Value2);
    //drawRoundedPolygon(polygon, 12, 10, TFT_WHITE);
  } else if (ActionType == "fpoly") {

    shift = 0;
    sprite.setColorDepth(4);
    sprite.createSprite(320, 240);              // Nastavení rozměrů sprite (třeba 240x240 pixelů)
    sprite.createPalette(RobotCYDEyesPoly::Colors::Default_4bit_palette);  //0-15 odstinu modre
    // Vykreslení obrysu spline
    drawSpline(polygon, polygonpoints, TFT_WHITE);

    tft.fillScreen(TFT_BLACK);

    drawClosedSpline(polygon, polygonpoints, TFT_WHITE, polygonVector);
    sprite.pushSprite(0, 0);

    //definovani vektoru

    for (int i = 0; i < polygonpoints; i++) {
      polygonVector[i].x = (polygonB[i].x - polygonA[i].x) / steps;
      polygonVector[i].y = (polygonB[i].y - polygonA[i].y) / steps;
      polygon[i].x = polygonA[i].x;
      polygon[i].y = polygonA[i].y;
    }
  } else if (ActionType == "bpoly") {

    shift = 0;
    sprite.setColorDepth(4);
    sprite.createSprite(320, 240);              // Nastavení rozměrů sprite (třeba 240x240 pixelů)
    sprite.createPalette(RobotCYDEyesPoly::Colors::Default_4bit_palette);  //0-15 odstinu modre
    // Vykreslení obrysu spline
    drawSpline(polygon, polygonpoints, TFT_WHITE);

    tft.fillScreen(TFT_BLACK);

    drawClosedSpline(polygon, polygonpoints, TFT_WHITE, polygonVector);
    sprite.pushSprite(0, 0);

    //definovani vektoru

    for (int i = 0; i < polygonpoints; i++) {
      polygonVector[i].x = (polygonB[i].x - polygonA[i].x) / steps;
      polygonVector[i].y = (polygonB[i].y - polygonA[i].y) / steps;
      polygon[i].x = polygonA[i].x;
      polygon[i].y = polygonA[i].y;
    }
  }

  LastActionType = ActionType;
}


// ***********************************************************************************************************************************************


void RobotCYDCore::update() {
  // Serial.print("c");
  if (LastActionType == "eyes") eyes.update(&tft, &sprite);
  if (LastActionType == "moon") {}  // tft.pushImage(10,10,150,150,moon);
  if (LastActionType == "poly") {
      eyesPoly.drawEyes(&sprite);
  }

  if (LastActionType == "fpoly") {

    shift++;


    //posuneme o vektor
    for (int i = 0; i < polygonpoints; i++) {
      polygon[i].x += polygonVector[i].x;
      polygon[i].y += polygonVector[i].y;
    }

    if (shift == steps) {

      for (int i = 0; i < polygonpoints; i++) {
        polygonVector[i].x = (polygonA[i].x - polygonB[i].x) / steps;
        polygonVector[i].y = (polygonA[i].y - polygonB[i].y) / steps;
        polygon[i].x = polygonB[i].x;
        polygon[i].y = polygonB[i].y;
      }
    }
    if (shift >= 2 * steps) {

      shift = 0;
      for (int i = 0; i < polygonpoints; i++) {
        polygonVector[i].x = (polygonB[i].x - polygonA[i].x) / steps;
        polygonVector[i].y = (polygonB[i].y - polygonA[i].y) / steps;
        polygon[i].x = polygonA[i].x;
        polygon[i].y = polygonA[i].y;
      }
    }
    int splinePointCount = 1;
    Point splinePoints[500];
    sprite.fillSprite(0x0000);
    // drawClosedSpline(polygon, 12, TFT_WHITE, polygonVector);
    getSplinePoints(polygon, polygonpoints, splinePoints, splinePointCount);
    // Vyplnění oblasti
    fillPolygon(splinePoints, splinePointCount, 10);

    for (int i = 0; i < polygonpoints; i++) {

      sprite.drawCircle(polygon[i].x, polygon[i].y, 20, 15);
    }
    sprite.pushSprite(0, 0);
  }

  if (LastActionType == "bpoly") {

    shift++;


    //posuneme o vektor
    for (int i = 0; i < polygonpoints; i++) {
      polygon[i].x += polygonVector[i].x;
      polygon[i].y += polygonVector[i].y;
    }

    if (shift == steps) {

      for (int i = 0; i < polygonpoints; i++) {
        polygonVector[i].x = (polygonA[i].x - polygonB[i].x) / steps;
        polygonVector[i].y = (polygonA[i].y - polygonB[i].y) / steps;
        polygon[i].x = polygonB[i].x;
        polygon[i].y = polygonB[i].y;
      }
    }
    if (shift >= 2 * steps) {

      shift = 0;
      for (int i = 0; i < polygonpoints; i++) {
        polygonVector[i].x = (polygonB[i].x - polygonA[i].x) / steps;
        polygonVector[i].y = (polygonB[i].y - polygonA[i].y) / steps;
        polygon[i].x = polygonA[i].x;
        polygon[i].y = polygonA[i].y;
      }
    }
    int splinePointCount = 1;
    Point splinePoints[500];
    sprite.fillSprite(0x0000);
    // drawClosedSpline(polygon, 12, TFT_WHITE, polygonVector);
    B_getBezierPoints(polygon, polygonpoints, splinePoints, splinePointCount);
    // Vyplnění oblasti
    B_fillPolygon(splinePoints, splinePointCount, 10);

    for (int i = 0; i < polygonpoints; i++) {

      sprite.drawCircle(polygon[i].x, polygon[i].y, 20, 15);
    }
    sprite.pushSprite(0, 0);
  }
}






// // Funkce pro vykreslení uzavřené Catmull-Rom spline
// void RobotCYDCore::drawClosedSpline(Point *points, int numPoints, uint16_t color) {
//   const int segments = 20;  // Počet segmentů mezi body
//   Point extendedPoints[numPoints + 3];

//   // Rozšíření pole bodů pro uzavřenou křivku
//   extendedPoints[0] = points[numPoints - 1];  // Předchozí bod
//   for (int i = 0; i < numPoints; i++) {
//     extendedPoints[i + 1] = points[i];
//   }
//   extendedPoints[numPoints + 1] = points[0];  // Začátek na konec
//   extendedPoints[numPoints + 2] = points[1];  // Další bod po začátku

//   // Vykreslení křivky
//   for (int i = 1; i < numPoints + 2; i++) {  // Přechod přes všechny body
//     for (int j = 0; j < segments; j++) {
//       float t = (float)j / (float)segments;

//       // Catmull-Rom interpolace
//       float t2 = t * t;
//       float t3 = t2 * t;
//       float b0 = -0.5 * t3 + t2 - 0.5 * t;
//       float b1 = 1.5 * t3 - 2.5 * t2 + 1.0;
//       float b2 = -1.5 * t3 + 2.0 * t2 + 0.5 * t;
//       float b3 = 0.5 * t3 - 0.5 * t2;

//       float x = b0 * extendedPoints[i - 1].x + b1 * extendedPoints[i].x + b2 * extendedPoints[i + 1].x + b3 * extendedPoints[i + 2].x;
//       float y = b0 * extendedPoints[i - 1].y + b1 * extendedPoints[i].y + b2 * extendedPoints[i + 1].y + b3 * extendedPoints[i + 2].y;

//       // Spojení bodů čarou
//       if (j > 0) {
//         tft.drawLine(
//           (int)extendedPoints[i - 1].x, (int)extendedPoints[i - 1].y,
//           (int)x, (int)y,
//           color
//         );
//       }

//       // Aktualizace posledního bodu
//       extendedPoints[i - 1].x = x;
//       extendedPoints[i - 1].y = y;
//     }
//   }
// }



// Funkce pro vykreslení Catmull-Rom spline
void RobotCYDCore::drawSpline(Point* points, int numPoints, uint16_t color) {
  const int segments = 10;  // Počet segmentů mezi body
                            //  for (int i = 0; i < numPoints ; i++) {
  for (int i = 1; i < numPoints - 2; i++) {
    for (int j = 0; j < segments; j++) {
      float t = (float)j / (float)segments;

      // Catmull-Rom interpolace
      float t2 = t * t;
      float t3 = t2 * t;
      float b0 = -0.5 * t3 + t2 - 0.5 * t;
      float b1 = 1.5 * t3 - 2.5 * t2 + 1.0;
      float b2 = -1.5 * t3 + 2.0 * t2 + 0.5 * t;
      float b3 = 0.5 * t3 - 0.5 * t2;

      float x = b0 * points[i - 1].x + b1 * points[i].x + b2 * points[i + 1].x + b3 * points[i + 2].x;
      float y = b0 * points[i - 1].y + b1 * points[i].y + b2 * points[i + 1].y + b3 * points[i + 2].y;

      // Spojení bodů čarou
      if (j > 0) {
        tft.drawLine(points[i - 1].x, points[i - 1].y, x, y, color);
      }

      // Aktualizace posledního bodu
      points[i - 1].x = x;
      points[i - 1].y = y;
    }
  }
}

// // Funkce pro výplň polygonu triangulací
// void RobotCYDCore::fillPolygon(Point *points, int numPoints, uint16_t fillColor) {
//   for (int i = 1; i < numPoints - 1; i++) {
//     sprite.fillTriangle(
//       points[0].x, points[0].y,
//       points[i].x, points[i].y,
//       points[i + 1].x, points[i + 1].y,
//       fillColor);
//   }
// }



// Funkce pro výpočet vzdálenosti mezi dvěma body
float RobotCYDCore::distance(Point p1, Point p2) {
  return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// Funkce pro výpočet úhlu mezi třemi body
float RobotCYDCore::angleBetween(Point p1, Point p2, Point p3) {
  float dx1 = p2.x - p1.x;
  float dy1 = p2.y - p1.y;
  float dx2 = p3.x - p2.x;
  float dy2 = p3.y - p2.y;
  float dot = dx1 * dx2 + dy1 * dy2;
  float mag1 = sqrt(dx1 * dx1 + dy1 * dy1);
  float mag2 = sqrt(dx2 * dx2 + dy2 * dy2);
  return acos(dot / (mag1 * mag2)) * 180.0 / PI;
}

// Funkce pro vykreslení oblouku
void RobotCYDCore::drawArc(Point center, float radius, float startAngle, float endAngle, uint16_t color) {
  for (float theta = startAngle; theta <= endAngle; theta += 1) {
    float rad = theta * PI / 180.0;
    int x = center.x + radius * cos(rad);
    int y = center.y + radius * sin(rad);
    tft.drawPixel(x, y, color);
  }
}

// Funkce pro vykreslení zaobleného polygonu
void RobotCYDCore::drawRoundedPolygon(Point* polygon, int numPoints, float radius, uint16_t color) {
  for (int i = 0; i < numPoints; i++) {
    Point prev = polygon[(i - 1 + numPoints) % numPoints];  // Předchozí bod
    Point curr = polygon[i];                                // Aktuální bod
    Point next = polygon[(i + 1) % numPoints];              // Následující bod

    float ang = angleBetween(prev, curr, next);

    if (ang < 180.0) {
      // Vypočítejte normálové směry
      float dx1 = curr.x - prev.x, dy1 = curr.y - prev.y;
      float dx2 = next.x - curr.x, dy2 = next.y - curr.y;
      float len1 = sqrt(dx1 * dx1 + dy1 * dy1);
      float len2 = sqrt(dx2 * dx2 + dy2 * dy2);
      dx1 /= len1;
      dy1 /= len1;
      dx2 /= len2;
      dy2 /= len2;

      // Vypočítejte střed oblouku
      Point arcCenter = { curr.x - radius * (dx1 - dx2), curr.y - radius * (dy1 - dy2) };

      // Vypočítejte úhly pro oblouk
      float startAngle = atan2(-dy1, -dx1) * 180.0 / PI;
      float endAngle = atan2(-dy2, -dx2) * 180.0 / PI;
      if (endAngle < startAngle) endAngle += 360.0;

      // Vykreslete oblouk
      drawArc(arcCenter, radius, startAngle, endAngle, color);

      // Spojte předchozí bod s obloukem
      tft.drawLine(prev.x, prev.y, curr.x - radius * dx1, curr.y - radius * dy1, color);
      // Spojte oblouk s dalším bodem
      tft.drawLine(curr.x - radius * dx2, curr.y - radius * dy2, next.x, next.y, color);
    } else {
      // Přímé spojení, pokud není roh
      tft.drawLine(prev.x, prev.y, curr.x, curr.y, color);
    }
  }
}


// Funkce pro výpočet Catmull-Rom interpolace
RobotCYDCore::Point RobotCYDCore::catmullRom(Point p0, Point p1, Point p2, Point p3, float t) {
  float t2 = t * t;
  float t3 = t2 * t;

  float x = 0.5 * ((2 * p1.x) + (-p0.x + p2.x) * t + (2 * p0.x - 5 * p1.x + 4 * p2.x - p3.x) * t2 + (-p0.x + 3 * p1.x - 3 * p2.x + p3.x) * t3);
  float y = 0.5 * ((2 * p1.y) + (-p0.y + p2.y) * t + (2 * p0.y - 5 * p1.y + 4 * p2.y - p3.y) * t2 + (-p0.y + 3 * p1.y - 3 * p2.y + p3.y) * t3);

  return { int(x), int(y) };
}

// Funkce pro vykreslení uzavřené Catmull-Rom křivky
void RobotCYDCore::drawClosedSpline(Point* points, int numPoints, uint16_t color, Point* pointsVector) {


  int lastX = points[0].x;
  int lastY = points[0].y;
  for (int i = 0; i < numPoints; i++) {
    // Získání čtyř bodů pro aktuální segment
    Point p0;
    if (i == 0) {
      p0 = points[numPoints - 1];
    } else {
      p0 = points[i - 1];
    }

    Point p1 = points[i];
    Point p2;
    Point p3;
    if (i < numPoints - 2) {
      p2 = points[i + 1];
      p3 = points[i + 2];
    } else if (i < numPoints - 1) {
      p2 = points[i + 1];
      p3 = points[0];
    } else if (i < numPoints) {
      p2 = points[0];
      p3 = points[1];
    }

    // Vykreslení segmentu mezi p1 a p2
    //    for (float t = 0; t <= 1; t += 0.05) {
    for (float t = 0; t <= 1; t += 0.5) {
      Point p = catmullRom(p0, p1, p2, p3, t);
      //sprite.drawPixel(p.x, p.y, color);
      //tft.drawLine(lastX,lastY,p.x,p.y,color); //slow
      sprite.drawWideLine(lastX - 60, lastY, p.x - 60, p.y, 1, color);    //slow
      sprite.drawWideLine(lastX + 100, lastY, p.x + 100, p.y, 1, color);  //slow
      //sprite.drawWedgeLine(lastX, lastY, p.x, p.y, 5, 5, color);  //slow
      lastX = p.x;
      lastY = p.y;
    }
  }

  for (int i = 0; i < numPoints; i++) {
    sprite.drawCircle(points[i].x - 60, points[i].y, 10, 10);
  }
}



//88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888


// // Funkce pro výpočet Catmull-Rom interpolace
// RobotCYDCore::Point RobotCYDCore::catmullRom2(Point p0, Point p1, Point p2, Point p3, float t) {
//   float t2 = t * t;
//   float t3 = t2 * t;

//   float x = 0.5 * ((2 * p1.x) +
//                    (-p0.x + p2.x) * t +
//                    (2 * p0.x - 5 * p1.x + 4 * p2.x - p3.x) * t2 +
//                    (-p0.x + 3 * p1.x - 3 * p2.x + p3.x) * t3);
//   float y = 0.5 * ((2 * p1.y) +
//                    (-p0.y + p2.y) * t +
//                    (2 * p0.y - 5 * p1.y + 4 * p2.y - p3.y) * t2 +
//                    (-p0.y + 3 * p1.y - 3 * p2.y + p3.y) * t3);

//   return {int(x), int(y)};
// }

// // Funkce pro získání bodů uzavřené Catmull-Rom křivky
// void RobotCYDCore::getSplinePoints(Point* points, int numPoints, Point* result, int& resultCount, float step) {
//   resultCount = 0;
//   for (int i = 0; i < numPoints; i++) {
//     Point p0 = points[(i - 1 + numPoints) % numPoints];
//     Point p1 = points[i];
//     Point p2 = points[(i + 1) % numPoints];
//     Point p3 = points[(i + 2) % numPoints];

//     for (float t = 0; t <= 1; t += step) {
//       result[resultCount++] = catmullRom2(p0, p1, p2, p3, t);
//     }
//   }
// }

// // Funkce pro vyplnění oblasti mezi body křivky
// void RobotCYDCore::fillPolygon(Point* points, int numPoints, uint16_t fillColor) {
//   // Najdeme minimální a maximální y-ové souřadnice
//   int minY = points[0].y, maxY = points[0].y;
//   for (int i = 1; i < numPoints; i++) {
//     if (points[i].y < minY) minY = points[i].y;
//     if (points[i].y > maxY) maxY = points[i].y;
//   }

//   // Scanline algoritmus
//   for (int y = minY; y <= maxY; y++) {
//     int intersections[20];
//     int count = 0;

//     // Najdeme průsečíky s aktuální scanline
//     for (int i = 0; i < numPoints; i++) {
//       Point p1 = points[i];
//       Point p2 = points[(i + 1) % numPoints];
//       if ((p1.y <= y && p2.y > y) || (p2.y <= y && p1.y > y)) {
//         float t = float(y - p1.y) / float(p2.y - p1.y);
//         intersections[count++] = p1.x + t * (p2.x - p1.x);
//       }
//     }

//     // Seřadíme průsečíky podle x
//     for (int i = 0; i < count - 1; i++) {
//       for (int j = i + 1; j < count; j++) {
//         if (intersections[i] > intersections[j]) {
//           int temp = intersections[i];
//           intersections[i] = intersections[j];
//           intersections[j] = temp;
//         }
//       }
//     }

//     // Vykreslíme čáry mezi dvojicemi průsečíků
//     for (int i = 0; i < count; i += 2) {
//       sprite.drawFastHLine(intersections[i], y, intersections[i + 1] - intersections[i], fillColor);
//     }
//   }

// }
//88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888


// Funkce pro výpočet Catmull-Rom interpolace
RobotCYDCore::Point RobotCYDCore::catmullRom2(Point p0, Point p1, Point p2, Point p3, float t) {
  float t2 = t * t;
  float t3 = t2 * t;

  float x = 0.5 * ((2 * p1.x) + (-p0.x + p2.x) * t + (2 * p0.x - 5 * p1.x + 4 * p2.x - p3.x) * t2 + (-p0.x + 3 * p1.x - 3 * p2.x + p3.x) * t3);
  float y = 0.5 * ((2 * p1.y) + (-p0.y + p2.y) * t + (2 * p0.y - 5 * p1.y + 4 * p2.y - p3.y) * t2 + (-p0.y + 3 * p1.y - 3 * p2.y + p3.y) * t3);

  return { int(x), int(y) };
}

// Funkce pro získání bodů uzavřené Catmull-Rom křivky s adaptivním vzorkováním
void RobotCYDCore::getSplinePoints(Point* points, int numPoints, Point* result, int& resultCount, float step) {
  resultCount = 0;
  for (int i = 0; i < numPoints; i++) {
    Point p0 = points[(i - 1 + numPoints) % numPoints];
    Point p1 = points[i];
    Point p2 = points[(i + 1) % numPoints];
    Point p3 = points[(i + 2) % numPoints];

    Point lastPoint = p1;
    result[resultCount++] = p1;

    for (float t = step; t <= 1; t += step) {
      Point currentPoint = catmullRom2(p0, p1, p2, p3, t);

      // Adaptivní vzorkování podle vzdálenosti bodů
      if (abs(currentPoint.x - lastPoint.x) > 2 || abs(currentPoint.y - lastPoint.y) > 2) {
        result[resultCount++] = currentPoint;
        lastPoint = currentPoint;
      }
    }
  }
}

// Optimalizovaný Scanline algoritmus pro vyplnění oblasti
void RobotCYDCore::fillPolygon(Point* points, int numPoints, uint16_t fillColor) {
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
      sprite.drawFastHLine(intersections[i], y, intersections[i + 1] - intersections[i], fillColor);
      //      sprite.drawFastHLine(intersections[i], y, intersections[i + 1] - intersections[i], fillColor);
    }
  }
}


// BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
// Funkce pro výpočet bodu Bézierovy křivky
RobotCYDCore::Point RobotCYDCore::B_bezierPoint(Point p0, Point p1, Point p2, Point p3, float t) {
  float u = 1 - t;
  float tt = t * t;
  float uu = u * u;
  float uuu = uu * u;
  float ttt = tt * t;

  float x = uuu * p0.x + 3 * uu * t * p1.x + 3 * u * tt * p2.x + ttt * p3.x;
  float y = uuu * p0.y + 3 * uu * t * p1.y + 3 * u * tt * p2.y + ttt * p3.y;

  return { int(x), int(y) };
}

// Funkce pro vytvoření bodů uzavřeného Bézierova polygonu
void RobotCYDCore::B_getBezierPoints(Point* points, int numPoints, Point* result, int& resultCount, float step) {
  resultCount = 0;

  for (int i = 0; i < numPoints; i++) {
    Point p0 = points[i];
    Point p1 = points[(i + 1) % numPoints];
    Point p2 = points[(i + 2) % numPoints];
    Point p3 = points[(i + 3) % numPoints];

    result[resultCount++] = p0;

    for (float t = step; t < 1.0; t += step) {
      result[resultCount++] = B_bezierPoint(p0, p1, p2, p3, t);
    }
  }
}

// Funkce pro vyplnění polygonu pomocí Bézierových bodů (scanline algoritmus)
void RobotCYDCore::B_fillPolygon(Point* points, int numPoints, uint16_t fillColor) {
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
      sprite.drawFastHLine(intersections[i], y, intersections[i + 1] - intersections[i], fillColor);
    }
  }
}
