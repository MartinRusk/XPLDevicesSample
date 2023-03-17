#include <Arduino.h>
#include <XPLDevices.h>

Button btnStart(2);
Encoder encHeading(3, 4, 5, enc4Pulse);
Switch swStrobe(6);
long strobe;

// setup function
void setup() { 
  // setup interface
  XP.begin("Sample");

  // register Commands
  btnStart.setCommand(
      XP.registerCommand(F("sim/starters/engage_starter_1")));

  encHeading.setCommand(
    XP.registerCommand(F("sim/autopilot/heading_up")),
    XP.registerCommand(F("sim/autopilot/heading_down")),
    XP.registerCommand(F("sim/autopilot/heading_sync")));
  
  swStrobe.setCommand(      
      XP.registerCommand(F("sim/lights/strobe_lights_on")),
      XP.registerCommand(F("sim/lights/strobe_lights_off")));
  
  // register DataRefs
  XP.registerDataRef(F("sim/cockpit/electrical/strobe_lights_on"), XPL_READ, 100, 0, &strobe);
}

// loop function
void loop() {
  // handle interface
  XP.xloop();

  // handle all devices and process commands
  btnStart.handleXP();
  encHeading.handleXP();
  swStrobe.handleXP();

  digitalWrite(LED_BUILTIN, (strobe > 0));
}