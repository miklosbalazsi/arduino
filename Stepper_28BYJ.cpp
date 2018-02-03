#include "Arduino.h"
#include "Stepper_28BYJ.h"  // include header

Stepper_28BYJ::Stepper_28BYJ(int p1, int p2, int p3, int p4){

  this->motor_pin_1 = p1;
  this->motor_pin_2 = p2;
  this->motor_pin_3 = p3;
  this->motor_pin_4 = p4;
 
  pinMode(this->motor_pin_1, OUTPUT);
  pinMode(this->motor_pin_2, OUTPUT);
  pinMode(this->motor_pin_3, OUTPUT);
  pinMode(this->motor_pin_4, OUTPUT);
  this->max_number_of_steps = 4096;
  this->step_number = 0;
  this->step_delay = 900;

 }

void Stepper_28BYJ::step(int number_of_steps)
{
  
  int direction;	
  int steps_left = abs(number_of_steps);  // how many steps to take

  // determine direction based on whether steps_to_mode is + or -:
  if (number_of_steps > 0) { direction = 1; }
  if (number_of_steps < 0) { direction = 0; }


  // decrement the number of steps, moving one step each time:
  while (steps_left > 0)
  {
    unsigned long now = micros();
    // move only if the appropriate delay has passed:
    if (now - this->last_step_time >= this->step_delay)
    {

      // get the timeStamp of when you stepped:
      this->last_step_time = now;
      // increment or decrement the step number,
      // depending on direction:
      if (direction == 1)
      {
        this->step_number++;
        if (this->step_number == this->max_number_of_steps) {
          this->step_number = 0;
        }
      }
      else
      {
        if (this->step_number == 0) {
          this->step_number = this->max_number_of_steps;
        }
        this->step_number--;
      }
      // decrement the steps left:
      steps_left--;
      // step the motor to step number 0, 1, ..., {3 or 10}
      this->stepMotor(this->step_number % 8);
    }
  }
}

void Stepper_28BYJ::stepMotor(int thisStep){
  switch (thisStep) {
    case 0:  // 1000
      digitalWrite(motor_pin_1, HIGH);
      digitalWrite(motor_pin_2, LOW);
      digitalWrite(motor_pin_3, LOW);
      digitalWrite(motor_pin_4, LOW);
    break;
    case 1:  // 1100
      digitalWrite(motor_pin_1, HIGH);
      digitalWrite(motor_pin_2, HIGH);
      digitalWrite(motor_pin_3, LOW);
      digitalWrite(motor_pin_4, LOW);
    break;
    case 2:  //0100
      digitalWrite(motor_pin_1, LOW);
      digitalWrite(motor_pin_2, HIGH);
      digitalWrite(motor_pin_3, LOW);
      digitalWrite(motor_pin_4, LOW);
    break;
    case 3:  //0110
      digitalWrite(motor_pin_1, LOW);
      digitalWrite(motor_pin_2, HIGH);
      digitalWrite(motor_pin_3, HIGH);
      digitalWrite(motor_pin_4, LOW);
    break;
    case 4:  //0010
      digitalWrite(motor_pin_1, LOW);
      digitalWrite(motor_pin_2, LOW);
      digitalWrite(motor_pin_3, HIGH);
      digitalWrite(motor_pin_4, LOW);
    break;
    case 5:  //0011
      digitalWrite(motor_pin_1, LOW);
      digitalWrite(motor_pin_2, LOW);
      digitalWrite(motor_pin_3, HIGH);
      digitalWrite(motor_pin_4, HIGH);
    break;
    case 6:  //0001
      digitalWrite(motor_pin_1, LOW);
      digitalWrite(motor_pin_2, LOW);
      digitalWrite(motor_pin_3, LOW);
      digitalWrite(motor_pin_4, HIGH);
    break;
    case 7:  //1001
      digitalWrite(motor_pin_1, HIGH);
      digitalWrite(motor_pin_2, LOW);
      digitalWrite(motor_pin_3, LOW);
      digitalWrite(motor_pin_4, HIGH);
    break;
  }
}


/*
 * Sets the speed in revs per minute
 */
void Stepper_28BYJ::setSpeed(long whatSpeed) { this->step_delay = 60L * 1000L * 1000L / this->max_number_of_steps / whatSpeed; }

int Stepper_28BYJ::version(void) { return 1; }
