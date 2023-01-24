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
          - port numbers are written on the brain
    - Motors 
      - Motor Setup
        - See Figure 2.1 to see how to set up the motor in VEXCODE PRO V5
      - Motor Spin
        - Spins the motor clockwise or counterclockwise at certain speed
        - See Figure 2.2 to see how to spin the motor in VEXCODE PRO V5
      - Motor Stop
        - Stops the motor that is currently spinning
        - See Figure 2.3 to see how to spin the motor in VEXCODE PRO V5

  3. Controller inputs 
    - Define controller 
      - Single controller: See Figure 3.1
      - Two controllers: See Figure 3.2
    - Axis 
        - See Figure 3.3
    - Buttons
      - hold: something happens only when you are pressing and nothing happens when you are not pressing
        - See Figure 3.4
      - toggle: something happens when you press the button once and something stops when pressed again
      - macro: small chunk of auton built into the user control
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
      - rev: motor spins counter-clockwise when the power is positive (you have no reason to use this)

    - power: determines the speed of the motor
      - When the power is positive, the motor spins at a normal direction of the directionType
      - When the power is negative, the motor spins at an opposite direction of the directionType
      - When the power is 0, the motor stops spinning

      - static: The power is fixed and never changes (see Example 1 & 2)
      - dynamic: the power changes based on other factors such as controller axis or a rotation of the motor (I'll come back to this later)

    - velocityUnits: determines the units of the power
      - pct: abbreviation for percent. (the power is capped at -100 to 100)
      - just use pct: dps and rpm max limit depends on what motor insert you are using: may cause inconsistency / motor burn out
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

  // * It is way more simpler to write and read "test.stop();" than "test.spin(directionType::fwd, 0, velocityUnits::pct);" * //

// ---------------------------------------------------------------------------------------

// ----------------- Figure 3.1 -----------------

  // When there is only one controller, you can write
  controller only_controller_name;

// ---------------------------------------------------------------------------------------

// ----------------- Figure 3.2 -----------------

  // when there are two controllers, you can write

  controller controller_name1 (primary); // when you have one controller
  controller controller_name2 (partner); // when you have a second controller

  // controllers will be defined by the order of being linked to the brain.
    // - in this case the controller that was linked first will be called "controller_name1" and second controller will be called "controller_name2"

// ---------------------------------------------------------------------------------------


// ----------------- Figure 3.3 -----------------

  /* All the Axis values are considered an Integer (no decimals) between 127 to -127 */   

      /* Although there are only two joysticks, there are 4 axis
        - right joystick horizontal: Axis1
        - right joystick vertical:   Axis2
        - left  joystick horizontal: Axis3
        - left  joystick vertical:   Axis4
      */ 

    // * The Axis are written on the controller so you don't have to remember it. * //

    // When the right joystick moves all the way to the left, the value of Axis1 will be -127 while the value of Axis 2 is 0
    // When the right joystick moves all the way to up, the value of Axis 1 will be 0 while the value of Axis 2 is 127
    // When the right joystick moves towards right top, both the value of Axis 1 and the value of Axis 2 will be positive number
    // When the right joystick moves towards left top, both the value of Axis 1 will be negative number while the value of Axis 2 will be positive number

  void Axis() {
    controller Ctrl; // Defined primary controller as "Ctrl"
    motor example (PORT1); // Defined motor that is connected to the port 1 of the brain as "example"
    
    // Because Axis values are just numbers, you can store them in integer variable
    // Axis follows "controller_name.Axis#.value();" when writing code 
    int Axis1_value = Ctrl.Axis1.value(); // obtains current Axis1 value of the "Ctrl" controller and store into the "Axis1_value" variable.

    // Axis values are generally used to adjust motor power of the chassis (The power of the motor is dynamic since the value defers based on the position of the joystick)
    example.spin(directionType::fwd, Axis1_value, velocityUnits::pct);

    // !!!! They DO NOT CHANGE CONTINUOUSLY !!!! 
      // - This means that Ctrl.Axis1.value() will not change when the code is running 

    // To solve this problem, you can use loops to constantly update the Axis value

    while (true) {
      example.spin(directionType::fwd, Ctrl.Axis3.value(), velocityUnits::pct);
    }

    // By doing so, Axis1 value will be constantly changing based on the controller since it is called infinite time when the code is running
  }
// ---------------------------------------------------------------------------------------

// ----------------- Figure 3.4 -----------------

  /* Button Hold */

  void Button_Hold() {
    controller Ctrl;
    motor motor1 (PORT6);
    // Button pressing is basically determined as boolean (true / false)
    // In order to give button a function, you need to check the condition using if statement
    // you can use "controller_name.Button$.pressing()""
      /* Buttons you can use (replace $ with...)
        Letters: A, X, B, Y
        Arrow: Up, Down, Left, Right
        Extra: L1, L2, R1, R2
      */

    /* Example 1 */
    if (Ctrl.ButtonB.pressing()) {
      motor1.spin(directionType::fwd, 100, velocityUnits::pct); // spin "motor1" motor at 100% power when Button "B" is pressing
    }
    else if (Ctrl.ButtonUp.pressing()) {
      motor1.spin(directionType::fwd, 50, velocityUnits::pct); // spin "motor1" motor at 50% power when Button "Up" is pressing and Button "B" is not pressing
    }
    else if (Ctrl.ButtonL2.pressing()) {
      motor1.spin(directionType::fwd, -80, velocityUnits::pct); // spin "motor1" motor at -80% power when Button "L2" is pressing and Button "B" and Button "Up" is not pressing
    }
    else {
      motor1.stop(); // stop "motor1" motor when Button "B", Button "up", and Button "L2" is not pressing
    }
  }

// ---------------------------------------------------------------------------------------

int main() {
  vexcodeInit();
  
}
