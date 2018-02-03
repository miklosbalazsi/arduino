/* CLASS definition
Rated voltage               : 5VDC 
Number of Phase             : 4 
Speed Variation Ratio       : 1/64 
Stride Angle                : 5.625° /64 
Frequency                   : 100Hz 
DC resistance               : 50 Ω ±7%(25°C ) 
Idle In-traction Frequency  > 600Hz 
Idle Out-traction Frequency > 1000Hz 
In-traction Torque          >34.3mN.m(120Hz) 
Self-positioning Torque     >34.3mN.m 
Friction torque             : 600-1200 gf.cm 
Pull in torque              : 300 gf.cm 
Insulated resistance        >10M Ω (500V) 
Insulated electricity power : 600VAC/1mA/1s 
Insulation grade            : A 
Rise in Temperature         < 40K(120Hz) 
Noise                       <35dB(120Hz,No load,10cm) 
Model                        28BYJ-48 – 5V 
http://www.instructables.com/id/BYJ48-Stepper-Motor/
http://cyaninfinite.com/tutorials/moving-the-28byj-48-stepper-motor/
*/

#ifndef Stepper_28BYJ_H
#define Stepper_28BYJ_H

class Stepper_28BYJ {
  public:
    // constructors:
    Stepper_28BYJ(int p1, int p2, int p3, int p4);

    // speed setter method:
    void setSpeed(long whatSpeed);

    // mover method:
    void step(int number_of_steps);

    // mover method:
    void go_to_position(int pos);

    int version(void);

  private:

    void stepMotor(int this_step);

    unsigned long step_delay;          // delay between steps, in ms, based on speed
    int max_number_of_steps;           // total number of steps this motor can take
    int step_number;          // which step the motor is on

    // motor pin numbers:
    int motor_pin_1;
    int motor_pin_2;
    int motor_pin_3;
    int motor_pin_4;

    unsigned long last_step_time; // time stamp in us of when the last step was taken
};
#endif
