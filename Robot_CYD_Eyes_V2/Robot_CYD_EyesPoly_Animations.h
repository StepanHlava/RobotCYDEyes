
#ifndef ROBOT_CYD_EYESPOLY_ANIMATIONS_H
#define ROBOT_CYD_EYESPOLY_ANIMATIONS_H
// ANIMATION list of face Definitions
#include "Robot_CYD_EyesPoly_Faces.h"
#include "Robot_CYD_EyesPoly_Modifiers.h"
#include "Robot_CYD_EyesPoly_Effects.h"
#include "Robot_CYD_EyesPoly_Colors.h"
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <any>
#include <string>
#include <array>
#include <vector>
#include <map>
// #include <iostream>
#include <optional>
#include <unordered_map>
#include <fstream>
#include <memory>


namespace RobotCYDEyesPoly {
namespace Anim {

inline static Eye::Point REOffset = { 100, 0 };  // RIGHT EYE OFFSET - default offset to right Eye compared to left eye - (center point)
inline static Eye::Point NOffset = { 0, 0 };     // No Offset

//--------------------------------------------------------------------------------------------------------------------------------------
//(NOT USED) Custom modification definition for eyes
//.... Mods({{"L_offset", {0,0}}}, {"repeatLastStages", 10}, {"waitTimeMS", 3000}})
// class Mods {
//     std::vector<Effect::EffectStage> effect = Effect::Nothing;  // both Eye : Mdifier definition of Left Eye for this stage
//     std::array<Mod::Point, 12> L_modifier = Mod::Nothing;       //<TBD> Left Eye : Mdifier definition of Left Eye for this stage
//     std::array<Mod::Point, 12> R_modifier = Mod::Nothing;       //<TBD>  Right Eye : Mdifier definition of Right Eye for this stage
//     Eye::Point L_offset = NOffset;                             // Left Eye offset for this stage, if next stage has offset 0,0 it means it will return to default position automatically
//     Eye::Point R_offset = NOffset;                             // Right Eye offset for this stage, if next stage has offset 0,0 it means it will return to default position automatically
//     int waitTimeMS = 0;                                        // number of ms waiting before next stage
//     int repeatLastStages = 0;                                  // number of stages to repeat animation again (do it only on the end of whole animation)
//     float rotate = 0;                                            // rotation angle

// //    Mods() = default;

//     Mods(const std::map<std::string, std::any>& params) {
//         for (const auto& [key, value] : params) {
//                  if (key == "effect") effect = std::any_cast<std::vector<Effect::EffectStage>>(value);

//             else if (key == "L_modifier") L_modifier = std::any_cast<std::array<Mod::Point, 12>>(value);
//             else if (key == "R_modifier") L_modifier = std::any_cast<std::array<Mod::Point, 12>>(value);

//             else if (key == "L_offset") L_offset = std::any_cast<Eye::Point>(value);
//             else if (key == "R_offset") R_offset = std::any_cast<Eye::Point>(value);

//             else if (key == "waitTimeMS") waitTimeMS = std::any_cast<int>(value);
//             else if (key == "repeatLastStages") repeatLastStages = std::any_cast<int>(value);

//             else if (key == "rotate") rotate = std::any_cast<float>(value);

//         }
//     }
// };

// ------------------------------------------------------------------------------------------------------------------
// Standard animation definitions
// Default (Mandatory) fields to define animation
struct AnimationStage {
  float transitionSpeed = 0;         // -1 = slower end, (+)1 = faster end, 0= constant speed
  int steps = 10;                    // number of steps to change next Stage
  std::array<Eye::Point, 12> L_eye;  // Left Eye : Face definition for this stage
  std::array<Eye::Point, 12> R_eye;  // Right Eye : Face definition for this stage
                                     // optional fields
  int L_flip = 0;                    // horizontal flip for Left Eye - 1= true
  int R_flip = 1;                    // horizontal flip for Right Eye - 1= true
                                     // std::optional<Mods*> Modifications;          // [optional] special named modifications
                                     //Mods* Modifications = nullptr;         // [optional] special named modifications

  std::vector<Effect::EffectStage> effect = Effect::Nothing;  // both Eye : Mdifier definition of Left Eye for this stage
                                                              //    std::array<Mod::Point, 12> L_modifier = Mod::Nothing;       //<TBD> Left Eye : Mdifier definition of Left Eye for this stage
                                                              //    std::array<Mod::Point, 12> R_modifier = Mod::Nothing;       //<TBD>  Right Eye : Mdifier definition of Right Eye for this stage
  Mod::Point* L_modifier = new Mod::Point[12];                // Dynamicky alokovaná paměť
  Mod::Point* R_modifier = new Mod::Point[12];

  Eye::Point L_offset = NOffset;  // Left Eye offset for this stage, if next stage has offset 0,0 it means it will return to default position automatically
  Eye::Point R_offset = NOffset;  // Right Eye offset for this stage, if next stage has offset 0,0 it means it will return to default position automatically
  int L_color = 10;  // Left Eye offset for this stage, if next stage has offset 0,0 it means it will return to default position automatically
  int R_color = 10;  // Left Eye offset for this stage, if next stage has offset 0,0 it means it will return to default position automatically
  int waitTimeMS = 0;             // number of ms waiting before next stage
  int repeatLastStages = 0;       // number of stages to repeat animation again (do it only on the end of whole animation)
  float rotate = 0;               // rotation angle
  Colors::Palette* paletteObject;          // used palette 
};


// Slovník animací
inline std::unordered_map<std::string, std::vector<AnimationStage>> customAnimations;  // named Animations definition from json file
//inline std::unordered_map<std::string, std::array<Eye::Point, 12>> customEyes; //named Eye definition shapes from json file
inline std::unique_ptr<std::unordered_map<std::string, std::array<Eye::Point, 12>>> customEyes;  // Dynamická alokace pomocí ukazatele

// Funkce pro načtení JSON ze souboru
// inline void loadAnimationsFromFile(const std::string& filename) {
//     std::ifstream file(filename);
//     if (!file.is_open()) {
//         throw std::runtime_error("Failed to open file");
//     }

//     JsonDocument json;
//     //deserializeJson(doc, File);
//     //file >> json;

//     for (const auto& [name, stages] : json["animations"].items()) {
//         std::vector<AnimationStage> animationStages;
//         for (const auto& stage : stages) {
//             animationStages.emplace_back(stage);
//         }
//         animations[name] = animationStages;
//     }
// }

// **********************************************************************************************************
// *** Example (basic animation without Mods):
//
// inline static std::vector<AnimationStage> MyCustomName = {
//  { -4.0f, 10, Eye::Normal_Square,Eye::Normal_Square},
//  { -4.0f, 10, Eye::Cross_Normal,Eye::Cross_Normal},
// };
// ---------------------------------------------------------------
// *** Example (advanced animation with some Modification):
//
// inline static std::vector<AnimationStage> MyCustomName = {
//  { -4.0f, 10, Eye::Normal_Square,Eye::Normal_Square,Mods{{"waitTimeMS":3000}}},
//  { -4.0f, 10, Eye::Cross_Normal,Eye::Cross_Normal,Mods{"Repeat":1} },
// };

// **********************************************************************************************************

// inline static std::vector<AnimationStage> Square_to_Cross_and_Back = {
//   { -4.0f, 10, Eye::Normal_Square,Eye::Normal_Square},
//   { -4.0f, 10, Eye::Normal_Square,Eye::Cross_Normal},
//   { -4.0f, 10, Eye::Normal_Square,Eye::Normal_Square,0,1,Mods({{"waitTimeMS",3000}})},
//   { -4.0f, 10, Eye::Cross_Normal,Eye::Cross_Normal,0,1,Mods({{"repeatLastStages",1},{"waitTimeMS",1000}})},
// };

inline static std::vector<AnimationStage> Wake_UP = {
  { -1.0f, 50, Eye::Sleep_Down, Eye::Sleep_Down },
  { -1.0f, 50, Eye::Sleep_Down2, Eye::Sleep_Down2 },
  { -1.0f, 50, Eye::Sleep_Down, Eye::Sleep_Down },
  { -1.0f, 100, Eye::Sleep_Half, Eye::Sleep_Half },
  { -1.0f, 100, Eye::Sleep_Normal, Eye::Sleep_Normal },
  { -1.0f, 10, Eye::Normal_Square, Eye::Sleep_Half },
  { -1.0f, 100, Eye::Normal_Square, Eye::Sleep_Half },
  { -1.0f, 100, Eye::Sleep_Normal, Eye::Sleep_Normal },
  { -1.0f, 100, Eye::Sleep_Little, Eye::Sleep_Little },
  { -4.0f, 10, Eye::Normal_Square, Eye::Normal_Square },
  { 0.1f, 30, Eye::Normal_Square, Eye::Normal_Square },
  { 0.1f, 3, Eye::Sleep_Normal, Eye::Sleep_Normal },
  { 0.1f, 3, Eye::Normal_Square, Eye::Normal_Square },
  { 0.1f, 3, Eye::Sleep_Normal, Eye::Sleep_Normal },
  { 0.1f, 50, Eye::Normal_Square, Eye::Normal_Square },
  { -4.0f, 100, Eye::Sleep_Little, Eye::Sleep_Little },
  { 2.0f, 50, Eye::Left_Side, Eye::Right_Side },
  { 0.1f, 100, Eye::Left_Side, Eye::Right_Side },
  { -4.0f, 100, Eye::Sleep_Little, Eye::Sleep_Little },
  { 2.0f, 50, Eye::Right_Side, Eye::Left_Side },
  { 0.1f, 100, Eye::Right_Side, Eye::Left_Side },
  { -2.0f, 50, Eye::Normal_Square, Eye::Normal_Square },
  { 0.1f, 100, Eye::Normal_Square, Eye::Normal_Square },
  { 0.1f, 3, Eye::Sleep_Normal, Eye::Sleep_Normal },
  { 0.1f, 30, Eye::Normal_Square, Eye::Normal_Square },
  { -4.0f, 100, Eye::Sleep_Little, Eye::Sleep_Little },
  { -4.0f, 60, Eye::Sleep_Normal, Eye::Sleep_Normal },
};

inline static std::vector<AnimationStage> tst = {
  { -4.0f, 20, Eye::Normal_Square, Eye::Normal_Square },
  { 0.01f, 20, Eye::Normal_Square, Eye::Normal_Square },

  { -4.0f, 100, Eye::Number_Four, Eye::Number_Four },
  { 0.01f, 20, Eye::Number_Four, Eye::Number_Four },

  { -4.0f, 20, Eye::Number_Three, Eye::Number_Three },
  { 0.01f, 20, Eye::Number_Three, Eye::Number_Three },

  { -4.0f, 20, Eye::Number_Two, Eye::Number_Two },
  { 0.01f, 20, Eye::Number_Two, Eye::Number_Two },

  { -4.0f, 20, Eye::Number_One, Eye::Number_One },
  { 0.01f, 20, Eye::Number_One, Eye::Number_One },

  { -4.0f, 20, Eye::Normal_Square, Eye::Normal_Square },
  { 0.01f, 20, Eye::Normal_Square, Eye::Normal_Square },

  { -4.0f, 20, Eye::Normal_Square, Eye::Cross_Normal },
  { 0.01f, 20, Eye::Normal_Square, Eye::Cross_Normal },

  { -4.0f, 20, Eye::Cross_Normal, Eye::Normal_Square },
  { 0.01f, 20, Eye::Cross_Normal, Eye::Normal_Square },

  { -4.0f, 20, Eye::Normal_Square, Eye::Heart_Normal },
  { 0.01f, 20, Eye::Normal_Square, Eye::Heart_Normal },

  { -4.0f, 20, Eye::Heart_Normal, Eye::Normal_Square },
  { 0.01f, 20, Eye::Heart_Normal, Eye::Normal_Square },

  { -4.0f, 20, Eye::Cross_Normal, Eye::Heart_Normal },
  { 0.01f, 20, Eye::Cross_Normal, Eye::Heart_Normal },

  { -4.0f, 20, Eye::Cross_Normal, Eye::Cross_Normal },
  { 0.01f, 20, Eye::Cross_Normal, Eye::Cross_Normal },

  { -4.0f, 20, Eye::Heart_Normal, Eye::Heart_Normal },
  { 0.01f, 20, Eye::Heart_Normal, Eye::Heart_Normal },

  { -4.0f, 20, Eye::Left_Side, Eye::Right_Side },
  { 0.01f, 20, Eye::Left_Side, Eye::Right_Side },

  { -4.0f, 20, Eye::Right_Side, Eye::Left_Side },
  { 0.01f, 20, Eye::Right_Side, Eye::Left_Side },

  { -4.0f, 20, Eye::Sleep_Normal, Eye::Sleep_Normal },
  { 0.01f, 20, Eye::Sleep_Normal, Eye::Sleep_Normal },

  { -4.0f, 20, Eye::Sleep_Little, Eye::Sleep_Little },
  { 0.01f, 20, Eye::Sleep_Little, Eye::Sleep_Little },

};
inline static std::vector<AnimationStage> Normal_Square = {
  { 0, 10, Eye::Normal_Square, Eye::Normal_Square },
  {
    0,
    10,
    Eye::Normal_Square,
    Eye::Normal_Square,
  }
};
// inline static std::vector<AnimationStage> Normal_Square = std::vector<AnimationStage>{
//     AnimationStage{ 0,10, RobotCYDEyesPoly::EYE_Normal_Square, RobotCYDEyesPoly::Modifier_Null, 0, RobotCYDEyesPoly::EYE_Normal_Square, RobotCYDEyesPoly::Modifier_Null, 1 },
//     AnimationStage{ 0,10, RobotCYDEyesPoly::EYE_Normal_Square, RobotCYDEyesPoly::Modifier_Null, 0, RobotCYDEyesPoly::EYE_Normal_Square, RobotCYDEyesPoly::Modifier_Null, 1 }
// };
// inline static std::vector<AnimationStage> Normal_Square = {
//   { 10, Faces::EYE_Normal_Square, RobotCYDEyesPoly::Faces::Modifier_Null, 0,
//     RobotCYDEyesPoly::Faces::EYE_Normal_Square, RobotCYDEyesPoly::Faces::Modifier_Null, 1 },
//   { 10, RobotCYDEyesPoly::Faces::EYE_Normal_Square, RobotCYDEyesPoly::Faces::Modifier_Null, 0,
//     RobotCYDEyesPoly::Faces::EYE_Normal_Square, RobotCYDEyesPoly::Faces::Modifier_Null, 1 }
// };



// Funkce pro načtení JSONu a vytvoření animací
inline void loadAnimations(std::string jsonString) {
  //StaticJsonDocument<2048> doc;
    Serial.println("(loadAnimations) start...");
  JsonDocument doc;
    Serial.println("(loadAnimations) Deserializing...");
  DeserializationError error = deserializeJson(doc, jsonString);
    Serial.println("(loadAnimations) Deserialized...");

  if (error) {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.c_str());
    return;
  }


  Serial.printf("Free heap before: %d bytes\n", ESP.getFreeHeap());

  // Před alokací customEyes
  customEyes.reset();  //= std::make_unique<std::unordered_map<std::string, std::array<Eye::Point, 12>>>();
  Serial.printf("Free heap after Eyes allocation: %d bytes\n", ESP.getFreeHeap());

  // Před alokací customAnimations
  customAnimations.clear();
  Serial.printf("Free heap after Animations cleared: %d bytes\n", ESP.getFreeHeap());



  // 1. Nejdříve zpracujeme "eyes", pokud existuje
  if (doc.containsKey("eyes")) {
    JsonArray eyes = doc["eyes"].as<JsonArray>();
    Serial.println("Processing 'eyes'");

    // Alokace mapy na haldě
    customEyes = std::make_unique<std::unordered_map<std::string, std::array<Eye::Point, 12>>>();
    //Serial.printf("Free heap: %d bytes\n", ESP.getFreeHeap());
    //Serial.printf("Largest free block: %d bytes\n", ESP.getMaxAllocHeap());

    // Pro každý prvek v poli "eyes"
    for (JsonVariant oneEye : eyes) {
      // Předpokládáme, že "oneEye" je JsonObject, a získáme název
      JsonObject eyeObject = oneEye.as<JsonObject>();

      // Procházejte všechny klíče v tomto objektu
      for (JsonPair pair : eyeObject) {
        std::string name = pair.key().c_str();            // Získání názvu klíče
        JsonArray stages = pair.value().as<JsonArray>();  // Získání hodnoty, což je pole bodů

        Serial.println("Processing Eye: ");
        Serial.println(name.c_str());

        // Uložení souřadnic do mapy (pokud existují)
        std::array<Eye::Point, 12> eyePoints;
        int index = 0;

        for (JsonVariant stage : stages) {
          JsonObject coordinates = stage.as<JsonObject>();
          if (coordinates.containsKey("x") && coordinates.containsKey("y") && index < 12) {
            eyePoints[index].x = coordinates["x"];
            eyePoints[index].y = coordinates["y"];
            index++;
          }
        }

        // Uložíme souřadnice do mapy podle názvu
        (*customEyes)[name] = eyePoints;

        name.clear();
        name.shrink_to_fit();
      }
    }
  }


  if (doc.containsKey("animations")) {
    JsonArray animations = doc["animations"].as<JsonArray>();
    Serial.println("Processing 'animations'");

    // Pro každou animaci v poli "animations"
    for (JsonVariant oneAnimation : animations) {
      JsonObject animationObject = oneAnimation.as<JsonObject>();

      // Iterace přes všechny klíče a hodnoty v objektu animace
      for (JsonPair pair : animationObject) {
        std::string name = pair.key().c_str();            // Získání názvu animace
        JsonArray stages = pair.value().as<JsonArray>();  // Získání kroků animace (stages)

        Serial.println("Processing Animation: ");
        Serial.println(name.c_str());

        std::vector<AnimationStage> animationStages;

        // Procházejte jednotlivé kroky animace
        for (JsonVariant stageVariant : stages) {
          JsonObject stage = stageVariant.as<JsonObject>();
          AnimationStage animStage;

          // Získání hodnot pro aktuální krok animace
          animStage.transitionSpeed = stage["transitionSpeed"].as<float>();
          animStage.steps = stage["steps"] | 10;

          // Načteme pole pro L_eye a R_eye
          JsonArray L_facePoly = stage["L_eye"].as<JsonArray>();
          JsonArray R_facePoly = stage["R_eye"].as<JsonArray>();

          JsonVariant L_eyeVariant = stage["L_eye"];
          JsonVariant R_eyeVariant = stage["R_eye"];

          if (R_eyeVariant.is<JsonArray>()) {
            JsonArray R_facePoly = R_eyeVariant.as<JsonArray>();
            // Zpracujte R_eye jako JsonArray
          } else if (R_eyeVariant.is<JsonObject>()) {
            JsonObject R_facePoly = R_eyeVariant.as<JsonObject>();
            // Zpracujte R_eye jako JsonObject
            Serial.println("R_eye je JsonObject");
          } else if (R_eyeVariant.is<String>()) {
            String R_facePoly = R_eyeVariant.as<String>();
            // Zpracujte R_eye jako String
            Serial.println("R_eye je String");
            Serial.println(R_facePoly);
            if (R_facePoly.startsWith("Eye::")) {
              //je to default eye tady from memory
            } else if (R_facePoly.startsWith("Custom::")) {
              //je to custom eyes v tmto jsonu

              // Zkontrolujte, zda klíč existuje v mapě
              std::string name = R_facePoly.substring(8).c_str();
              Serial.println(R_facePoly.substring(8));
              if (customEyes && customEyes->find(name) != customEyes->end()) {
                // Získání pole podle jména
                std::array<Eye::Point, 12>& eyePoints = (*customEyes)[name];
                Serial.println("found");
                // Zde můžete přistoupit k jednotlivým bodům (Eye::Point) a např. je kopírovat do jiného pole
                std::array<Eye::Point, 12> newEyePoints;
                Serial.println();
                // Kopírování hodnot z jednoho pole do druhého
                for (size_t i = 0; i < eyePoints.size(); ++i) {
                  newEyePoints[i] = eyePoints[i];  // Kopírování jednotlivých bodů
                  Serial.print("{");
                  Serial.print(newEyePoints[i].x);
                  Serial.print(",");
                  Serial.print(newEyePoints[i].y);
                  Serial.print("}");
                  animStage.R_eye[i] = newEyePoints[i];
                }
                //delete[] newEyePoints;
                // nebo jednoduše
                // std::copy(eyePoints.begin(), eyePoints.end(), newEyePoints.begin());

                // Nyní máte v newEyePoints zkopírovaná data z customEyes

                animStage.L_color = stage["L_color"] | COLOR_DEFAULT;
                animStage.R_color = stage["R_color"] | COLOR_DEFAULT;

              } else {
                Serial.println("Klíč nebyl nalezen.");
              }

            } else if (R_facePoly.startsWith("File::")) {
              //je to load ze souboru kde jsou data
            } else {
              // asi je to primo string s hodnotama "x,y,x,y,x,y"
            }

          } else {
            Serial.println("R_eye má nepodporovaný typ");
          }

        Serial.println();


        if (L_eyeVariant.is<JsonArray>()) {
            JsonArray L_facePoly = L_eyeVariant.as<JsonArray>();
            // Zpracujte R_eye jako JsonArray
          } else if (L_eyeVariant.is<JsonObject>()) {
            JsonObject L_facePoly = L_eyeVariant.as<JsonObject>();
            // Zpracujte R_eye jako JsonObject
            Serial.println("L_eye je JsonObject");
          } else if (L_eyeVariant.is<String>()) {
            String L_facePoly = L_eyeVariant.as<String>();
            // Zpracujte R_eye jako String
            Serial.println("L_eye je String");
            Serial.println(L_facePoly);
            if (L_facePoly.startsWith("Eye::")) {
              //je to default eye tady from memory
            } else if (L_facePoly.startsWith("Custom::")) {
              //je to custom eyes v tmto jsonu

              // Zkontrolujte, zda klíč existuje v mapě
              std::string name = L_facePoly.substring(8).c_str();
              Serial.println(L_facePoly.substring(8));
              if (customEyes && customEyes->find(name) != customEyes->end()) {
                // Získání pole podle jména
                std::array<Eye::Point, 12>& eyePoints = (*customEyes)[name];
                Serial.println("found");
                // Zde můžete přistoupit k jednotlivým bodům (Eye::Point) a např. je kopírovat do jiného pole
                std::array<Eye::Point, 12> newEyePoints;
                Serial.println();
                // Kopírování hodnot z jednoho pole do druhého
                for (size_t i = 0; i < eyePoints.size(); ++i) {
                  newEyePoints[i] = eyePoints[i];  // Kopírování jednotlivých bodů
                  Serial.print("{");
                  Serial.print(newEyePoints[i].x);
                  Serial.print(",");
                  Serial.print(newEyePoints[i].y);
                  Serial.print("}");
                  animStage.L_eye[i] = newEyePoints[i];
                }
                //delete[] newEyePoints;
                // nebo jednoduše
                // std::copy(eyePoints.begin(), eyePoints.end(), newEyePoints.begin());

                // Nyní máte v newEyePoints zkopírovaná data z customEyes

              } else {
                Serial.println("Klíč nebyl nalezen.");
              }

              name.clear();
              name.shrink_to_fit();


            } else if (L_facePoly.startsWith("File::")) {
              //je to load ze souboru kde jsou data
            } else {
              // asi je to primo string s hodnotama "x,y,x,y,x,y"
            }

          } else {
            Serial.println("L_eye má nepodporovaný typ");
          }

        // // Zpracování bodů pro L_eye a R_eye
        // for (size_t i = 0; i < 12; i++) {
        //     animStage.L_eye[i] = {L_facePoly[i][0] | 0, L_facePoly[i][1] | 0};
        //     animStage.R_eye[i] = {R_facePoly[i][0] | 0, R_facePoly[i][1] | 0};
        // }

        // Získání hodnot pro L_flip a R_flip
        animStage.L_flip = stage["L_flip"] | 0;
        animStage.R_flip = stage["R_flip"] | 0;

        // Přidání animace do seznamu
        animationStages.push_back(animStage);
      }

      // Uložení animace do mapy podle názvu
      customAnimations[name] = animationStages;
    }
  }
  doc.clear();
}

// // Iterujeme přes JSON objekty
// // at first in JSON should be all eye shapes, cause in next iteration for animations definitins are linked to stored eyeShapes
// for (JsonPair nmspace : doc.as<JsonObject>()) {
//       Serial.printf("processing: %s",nmspace.key().c_str() );


//   if (nmspace.key()=="animations")
//     {

//   }
// }
}




}
}

#endif