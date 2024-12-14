

#ifndef ROBOT_CYD_EYESPOLY_FILES_H
#define ROBOT_CYD_EYESPOLY_FILES_H

#include <string>

namespace RobotCYDEyesPoly {
namespace Files {

inline static std::string getDefaultTest()
{
  
  std::string jsonString = "{'eyes':["; // zacatek definic shapes
  jsonString=jsonString  + "{'Heart_XXL':[{'x':-30,'y':-30},{'x':0,'y':0},{'x':0,'y':0},{'x':30,'y':-30},{'x':60,'y':-10},{'x':40,'y':40},{'x':10,'y':70},{'x':0,'y':80},{'x':0,'y':80},{'x':-10,'y':70},{'x':-40,'y':40},{'x':-60,'y':-10}]},";
  jsonString=jsonString  + "{'Heart_XL':[{'x':-27,'y':-27},{'x':0,'y':0},{'x':0,'y':0},{'x':27,'y':-27},{'x':54,'y':-9},{'x':36,'y':36},{'x':9,'y':63},{'x':0,'y':72},{'x':0,'y':72},{'x':-9,'y':63},{'x':-36,'y':36},{'x':-54,'y':-9}]},";
  jsonString=jsonString  + "{'Heart_L':[{'x':-24,'y':-24},{'x':0,'y':0},{'x':0,'y':0},{'x':24,'y':-24},{'x':48,'y':-8},{'x':32,'y':32},{'x':8,'y':56},{'x':0,'y':64},{'x':0,'y':64},{'x':-8,'y':56},{'x':-32,'y':32},{'x':-48,'y':-8}]},";
  jsonString=jsonString  + "{'Heart_N':[{'x':-21,'y':-21},{'x':0,'y':0},{'x':0,'y':0},{'x':21,'y':-21},{'x':42,'y':-7},{'x':28,'y':28},{'x':7,'y':49},{'x':0,'y':56},{'x':0,'y':56},{'x':-7,'y':49},{'x':-28,'y':28},{'x':-42,'y':-7}]},";
  jsonString=jsonString  + "{'Heart_S':[{'x':-18,'y':-18},{'x':0,'y':0},{'x':0,'y':0},{'x':18,'y':-18},{'x':36,'y':-6},{'x':24,'y':24},{'x':6,'y':42},{'x':0,'y':48},{'x':0,'y':48},{'x':-6,'y':42},{'x':-24,'y':24},{'x':-36,'y':-6}]},";
  jsonString=jsonString  + "{'Heart_XS':[{'x':-15,'y':-15},{'x':0,'y':0},{'x':0,'y':0},{'x':15,'y':-15},{'x':30,'y':-5},{'x':20,'y':20},{'x':5,'y':35},{'x':0,'y':40},{'x':0,'y':40},{'x':-5,'y':35},{'x':-20,'y':20},{'x':-30,'y':-5}]},";  
  jsonString=jsonString  + "{'Normal_Square':[{'x':-40,'y':-40},{'x':-20,'y':-45},{'x':20,'y':-45},{'x':40,'y':-40},{'x':45,'y':-20},{'x':45,'y':20},{'x':40,'y':40},{'x':20,'y':45},{'x':-20,'y':45},{'x':-40,'y':40},{'x':-45,'y':20},{'x':-45,'y':-20}]},";
  jsonString=jsonString  + "{'Angry_Normal_Left': [{'x':-60,'y':-40},{'x':-30,'y':-25},{'x':10,'y':-5},{'x':20,'y':0},{'x':40,'y':0},{'x':40,'y':10},{'x':40,'y':40},{'x':20,'y':45},{'x':-20,'y':45},{'x':-40,'y':40},{'x':-60,'y':20},{'x':-65,'y':-20}]},";
  jsonString=jsonString  + "{'Angry_Normal_Right': [{'x':-20,'y':0},{'x':-10,'y':-5},{'x':30,'y':-25},{'x':60,'y':-40},{'x':65,'y':-20},{'x':60,'y':20},{'x':40,'y':40},{'x':20,'y':45},{'x':-20,'y':45},{'x':-40,'y':40},{'x':-40,'y':10},{'x':-40,'y':0}]},";
  jsonString=jsonString  + "{'Angry_Normal2_Left': [{'x':-60,'y':-40},{'x':-30,'y':-25},{'x':10,'y':-5},{'x':20,'y':0},{'x':40,'y':20},{'x':40,'y':25},{'x':40,'y':25},{'x':20,'y':25},{'x':-20,'y':25},{'x':-40,'y':20},{'x':-60,'y':10},{'x':-65,'y':-20}]},";
  jsonString=jsonString  + "{'Angry_Normal2_Right': [{'x':-20,'y':0},{'x':-10,'y':-5},{'x':30,'y':-25},{'x':60,'y':-40},{'x':65,'y':-20},{'x':60,'y':10},{'x':40,'y':20},{'x':20,'y':25},{'x':-20,'y':25},{'x':-40,'y':25},{'x':-40,'y':25},{'x':-40,'y':20}]},";
  jsonString=jsonString  + "{'Angry_Normal3_Left': [{'x':-60,'y':-40},{'x':-30,'y':-25},{'x':10,'y':-5},{'x':20,'y':0},{'x':40,'y':10},{'x':40,'y':15},{'x':40,'y':15},{'x':20,'y':15},{'x':-20,'y':15},{'x':-40,'y':10},{'x':-60,'y':0},{'x':-65,'y':-20}]},";
  jsonString=jsonString  + "{'Angry_Normal3_Right': [{'x':-20,'y':0},{'x':-10,'y':-5},{'x':30,'y':-25},{'x':60,'y':-40},{'x':65,'y':-20},{'x':60,'y':0},{'x':40,'y':10},{'x':20,'y':15},{'x':-20,'y':15},{'x':-40,'y':15},{'x':-40,'y':15},{'x':-40,'y':10}]},";
  jsonString=jsonString  + "{'Angry_Normal4_Left': [{'x':-60,'y':-40},{'x':-30,'y':-25},{'x':10,'y':-5},{'x':20,'y':0},{'x':40,'y':10},{'x':40,'y':15},{'x':30,'y':10},{'x':20,'y':10},{'x':-20,'y':0},{'x':-40,'y':-10},{'x':-60,'y':-20},{'x':-65,'y':-30}]},";
  jsonString=jsonString  + "{'Angry_Normal4_Right': [{'x':-20,'y':0},{'x':-10,'y':-5},{'x':30,'y':-25},{'x':60,'y':-40},{'x':65,'y':-30},{'x':60,'y':-20},{'x':40,'y':-10},{'x':20,'y':0},{'x':-20,'y':10},{'x':-30,'y':10},{'x':-40,'y':15},{'x':-40,'y':10}]},";
  jsonString=jsonString  + "{'Angry_Blink_Left': [{'x':-65,'y':-30},{'x':-30,'y':-25},{'x':10,'y':-5},{'x':20,'y':0},{'x':45,'y':10},{'x':45,'y':15},{'x':30,'y':10},{'x':20,'y':10},{'x':-20,'y':0},{'x':-40,'y':-10},{'x':-65,'y':-15},{'x':-70,'y':-25}]},";
  jsonString=jsonString  + "{'Angry_Blink_Right': [{'x':-20,'y':0},{'x':-10,'y':-5},{'x':30,'y':-30},{'x':65,'y':-30},{'x':70,'y':-25},{'x':65,'y':-15},{'x':40,'y':-10},{'x':20,'y':0},{'x':-20,'y':10},{'x':-30,'y':10},{'x':-45,'y':15},{'x':-45,'y':10}]},";
  jsonString=jsonString  + "{'Flight_Plane':[{'x':-80,'y':10},{'x':-40,'y':-10},{'x':50,'y':-10},{'x':90,'y':-40},{'x':70,'y':10},{'x':30,'y':10},{'x':30,'y':10},{'x':50,'y':30},{'x':50,'y':30},{'x':-20,'y':10},{'x':-20,'y':10},{'x':-80,'y':10}]}"; //last
  jsonString=jsonString  + "]"; // konec vsech shapes
  jsonString=jsonString  + ",'animations':["; // zacatek sekce animace
  jsonString=jsonString  + "{'testAnim1':[";
  jsonString=jsonString  + "{'transitionSpeed':-4.0,'steps':50,'L_eye':'Custom::Normal_Square','R_eye':'Custom::Normal_Square','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':-4.0,'steps':50,'L_eye':'Custom::Angry_Normal_Left','R_eye':'Custom::Angry_Normal_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':-4.0,'steps':3,'L_eye':'Custom::Angry_Blink_Left','R_eye':'Custom::Angry_Blink_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':-4.0,'steps':20,'L_eye':'Custom::Angry_Normal_Left','R_eye':'Custom::Angry_Normal_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':-4.0,'steps':3,'L_eye':'Custom::Angry_Blink_Left','R_eye':'Custom::Angry_Blink_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':-4.0,'steps':20,'L_eye':'Custom::Angry_Normal_Left','R_eye':'Custom::Angry_Normal_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':1.0,'steps':50,'L_eye':'Custom::Angry_Normal2_Left','R_eye':'Custom::Angry_Normal2_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':1.0,'steps':50,'L_eye':'Custom::Angry_Normal3_Left','R_eye':'Custom::Angry_Normal3_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':1.0,'steps':50,'L_eye':'Custom::Angry_Normal4_Left','R_eye':'Custom::Angry_Normal4_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':4.0,'steps':50,'L_eye':'Custom::Angry_Normal4_Left','R_eye':'Custom::Angry_Normal4_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':1.0,'steps':50,'L_eye':'Custom::Angry_Normal3_Left','R_eye':'Custom::Angry_Normal3_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':1.0,'steps':50,'L_eye':'Custom::Angry_Normal4_Left','R_eye':'Custom::Angry_Normal4_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':4.0,'steps':50,'L_eye':'Custom::Angry_Normal4_Left','R_eye':'Custom::Angry_Normal4_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':-4.0,'steps':3,'L_eye':'Custom::Angry_Blink_Left','R_eye':'Custom::Angry_Blink_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':-4.0,'steps':3,'L_eye':'Custom::Angry_Normal_Left','R_eye':'Custom::Angry_Normal_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':-4.0,'steps':50,'L_eye':'Custom::Angry_Normal_Left','R_eye':'Custom::Angry_Normal_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':-4.0,'steps':3,'L_eye':'Custom::Angry_Blink_Left','R_eye':'Custom::Angry_Blink_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':1.0,'steps':20,'L_eye':'Custom::Angry_Normal_Left','R_eye':'Custom::Angry_Normal_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':1.0,'steps':50,'L_eye':'Custom::Angry_Normal4_Left','R_eye':'Custom::Angry_Normal4_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},";
  jsonString=jsonString  + "{'transitionSpeed':-4.0,'steps':50,'L_eye':'Custom::Angry_Normal3_Left','R_eye':'Custom::Angry_Normal3_Right','L_flip':0,'R_flip':1,'L_color':10,'R_color':10}"; //last
  jsonString=jsonString  + "]},"; // konec 1 animace
  jsonString=jsonString  + "{'HeartBeat':[";
  jsonString=jsonString  + "{'transitionSpeed':-1.0,'steps':70,'L_eye':'Custom::Heart_S','R_eye':'Custom::Heart_S','L_flip':0,'R_flip':1,'L_color':7,'R_color':7},";
  jsonString=jsonString  + "{'transitionSpeed':5.0,'steps':6,'L_eye':'Custom::Heart_L','R_eye':'Custom::Heart_L','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},"; //last
  jsonString=jsonString  + "{'transitionSpeed':1.0,'steps':2,'L_eye':'Custom::Heart_L','R_eye':'Custom::Heart_L','L_flip':0,'R_flip':1,'L_color':7,'R_color':7},"; //last
  jsonString=jsonString  + "{'transitionSpeed':-2.0,'steps':4,'L_eye':'Custom::Heart_N','R_eye':'Custom::Heart_N','L_flip':0,'R_flip':1,'L_color':7,'R_color':7},"; //last
  jsonString=jsonString  + "{'transitionSpeed':5.0,'steps':6,'L_eye':'Custom::Heart_XL','R_eye':'Custom::Heart_XL','L_flip':0,'R_flip':1,'L_color':10,'R_color':10},"; //last
  jsonString=jsonString  + "{'transitionSpeed':1.0,'steps':2,'L_eye':'Custom::Heart_XL','R_eye':'Custom::Heart_XL','L_flip':0,'R_flip':1,'L_color':7,'R_color':7},"; //last
  jsonString=jsonString  + "{'transitionSpeed':-4.0,'steps':10,'L_eye':'Custom::Heart_S','R_eye':'Custom::Heart_S','L_flip':0,'R_flip':1,'L_color':7,'R_color':7}";
  jsonString=jsonString  + "]}"; // konec 1 animace
  jsonString=jsonString  + "]"; // konec sekce animace
  jsonString=jsonString  + "}"; // konec vseho
  return jsonString;
}

}
}
#endif