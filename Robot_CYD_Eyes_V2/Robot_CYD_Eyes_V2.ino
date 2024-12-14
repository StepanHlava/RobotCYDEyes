#include <gpio_viewer.h>
#include <Robot_CYD_Core.h>

GPIOViewer gpio_viewer;

RobotCYDCore RoboDisplay=RobotCYDCore();
int delayWait=1;

void setup(void) {
//setCpuFrequencyMhz(240);  // Nastavte CPU na 240 MHz
// esp_timer_deinit();  // Deaktivuje watchdog pro aktuální task
    Serial.println("Memory diagnostics:");
    Serial.printf("Free heap: %d bytes\n", ESP.getFreeHeap());
    Serial.printf("Minimum free heap: %d bytes\n", ESP.getMinFreeHeap());
    Serial.printf("Free PSRAM: %d bytes\n", ESP.getFreePsram());

  gpio_viewer.connectToWifi("ASUS","rams2012");

  RoboDisplay.initialize();
  RoboDisplay.setFramerate(60);
  Serial.begin(115200);
  gpio_viewer.begin();
}

void loop() {

   if (Serial.available() > 0) {
        delayWait=1;
        String input = Serial.readStringUntil('\n'); // Načtení vstupu až do konce řádku
        Serial.println("(action):");
        // Výběr fáze na základě příkazu
        if (input=="deinit")
        { 
          // Zbytek setupu
        }
        else
        if (input.startsWith("set")) {
            input.replace("set", "");  // Odstraní "set" z příkazu
            input.trim();              // Odstraní bílé znaky na začátku a konci
            input.replace("[", "");    // Odstraní závorky
            input.replace("]", "");    // Odstraní závorky

            // Rozdělení hodnot podle čárky
            String values[4];
            int index = 0;
            while (input.length() > 0 && index <4) {
                int commaIndex = input.indexOf(',');
                String value;
                if (commaIndex == -1) {
                    value = input; // Poslední hodnota
                    input = "";
                } else {
                    value = input.substring(0, commaIndex); // Hodnota před čárkou
                    input = input.substring(commaIndex + 1); // Zbytek řetězce
                }
                value.trim(); // Odstranění mezer

                // Vyhodnocení výrazu (např. "90+90")
                values[index++] =value;// evaluateExpression(value);
            }

            

            Serial.print(values[0]);
            Serial.print(",");
            Serial.print(values[1]);
            RoboDisplay.set(values[0],values[1],values[2],values[3]); 
            // std::vector<std::vector<int>> set = {
            //                                    {0, 100, angles[0],angles[1],angles[2],angles[3]},  // Fáze 1
            //                                 };
            //servoController.loadPhases(set);
            //RoboDisplay.set("","");
        } else if (input == "stop") {
            //servoController.loadPhases(stop);
        }
        else {
            Serial.println("Neznámý příkaz: " + input);
        }
    }

  RoboDisplay.update();
  delay(delayWait);
}



