/*
  ------------------------- PLEASE READ ME -----------------------
  1. Start up set up
    - Click on the name of the project on the top middle of the window
    - Click on "Enable Expert Autocomplete" 
      - prevent you from making any typos
      - cuts time to actually write the code
    - Start writing code below "using namespace vex;"
      - See Figure 1.1 for more info
  2. Motor / Sensor set up
    - What is Configuration?
      - Configuration is the arrangement of parts or elements in a particular form
        - In this case arranging motors and sensors using port numbers
    - Motors 
      - Motor Setup
        - See figure 2.1 to see how to set up the motor in VEXCODE PRO V5
      - Motor Spin
        - Spins the motor clockwise or counterclockwise at certain speed
        - See Figure 2.2 to see how to spin the motor in VEXCODE PRO V5
      - Motor Stop
        - Stops the motor that is currently spinning
        - See Figure 2.3 to see how to spin the motor in VEXCODE PRO V5
*/

// this always ALWAYS comes first!!! - Allows you to use vex related code
#include "vex.h"

// ----------------- Figure 1.1 -----------------
// It automatically finds everything within the vex library - without it, you need to know what code came from vex and not. 
using namespace vex;

/* Example 1: Without Figure 1.1 */

void Example1() {
  vex::motor example (vex::PORT1);
  example.spin(vex::directionType::fwd, 80, vex::velocityUnits::pct);
}

/*Example 2: With Figure 1.1 */

void Example2() {
  motor example (PORT1);
  example.spin(directionType::fwd, 80, velocityUnits::pct);
}

//-------------------------------------------------------



// ----------------- Figure 2.1 -----------------

// motor motor_name (PORT#, reversed?);

  /* Example 1 */ 
    motor rotation_not_reversed (PORT1);
    /* Same as motor chassis_right (PORT1, false); */

  /* Example 2*/
    motor rotation_reversed (PORT5, true); // reversed rotation by default

// -------------------------------------------------------------------

// ----------------- Figure 2.2 -----------------

// motor_name.spin(directionType::fwd, power, velocityUnits::pct);
  /*
    - directionType: determines the spining direction of the motor
      - fwd: motor spins clockwise when the power is positive (highly recommended to use this)
      - rev: motor spins counter-clockwise when the power is positive

    - power: determines the speed of the motor
      - When the power is positive, the motor spins at a normal direction of the directionType
      - When the power is negative, the motor spins at an opposite direction of the directionType
      - When the power is 0, the motor stops spinning

      - static: The power is fixed and never changes (see Example 1 & 2)
      - dynamic: the power changes based on other factors such as controller axis or a rotation of the motor (I'll come back to this later)

    - velocityUnits: determines the units of the power
      - pct: abbreviation for percent. (the power is capped at -100 to 100)
      - just use pct: dps and rpm max limit depends on what motor insert you are using: cause inconsistency 
  */

  /* Example 1 */
    void Spin_Motor1() {
      motor test (PORT1);
      test.spin(directionType::fwd, 100, velocityUnits::pct); // Spins the motor called "test" clockwise with 100% speed
    }

  /* Example 2 */
    void Spin_Motor2() {
      motor test (PORT1);
      test.spin(directionType::fwd, -50, velocityUnits::pct); // Spins the motor called "test" counter-clockwise with 50% speed
    }

// -------------------------------------------------------------------------------------------------------------------------------------------


// ----------------- Figure 2.3 -----------------

  // motor_name.stop()

  /* Example 1 */
  void Stop_Motor() {
    motor test (PORT1);
    test.spin(directionType::fwd, -50, velocityUnits::pct); 
    task::sleep(1000); /* Waits 1000 miliseconds before it executes the code below */
    test.stop(); /* Stops the motor called "test* from spinning */
  }

  // * It is way more simpler to write "test.stop();" than "test.spin(directionType::fwd, 0, velocityUnits::pct);" * //

// ---------------------------------------------------------------------------------------

int main() {
  vexcodeInit();
  
}
