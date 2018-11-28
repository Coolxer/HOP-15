#pragma once

enum Keys { KEY_NONE, KEY_ENTER, KEY_RETURN, KEY_UP, KEY_DOWN, KEY_DISRUPT, KEY_RESET,
			KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9};

const int STEPS_PER_REVOLUTION = 200;
const int MICROPSTEPPING = 8;

const int MAX_SPEED = 10000;
const int DEFAULT_SPEED = 800;
const int DEFAULT_STEP_INTERVAL = 1250;

const double STEPS_PER_MM = 14.63116457257362;

const double STEPS_PER_DEGREE = STEPS_PER_REVOLUTION * MICROPSTEPPING / 360.0;

/***************************** DIVIDER MOTOR **************************************/
const double DIVIDER_BIG_GEAR_DIAMETER = 130.1;
//													           ->       <-
const double DIVIDER_SMALL_GEAR_DIAMETER = 19.046;//19.047;//19.2;//19.0462;//19.0463;//19.0465;//19.046;//19.047;//19.048;//19.045;//19.04;//19.055;//19.048;//19.05;//19.1;//18.949;//18.947;//18.945;//18.95;//18.96;//18.97;//18.95;//23;//22;//25;.83;//32.8;//33.1; //32.981; //34.81; 
const double DIVIDER_GEARS_PROPORTION = DIVIDER_BIG_GEAR_DIAMETER / DIVIDER_SMALL_GEAR_DIAMETER;

/***************************** TABLE MOTOR ****************************************/
const double TABLE_BIG_GEAR_DIAMETER = 87;
const double TABLE_SMALL_GEAR_DIAMETER = 14.15;//14.18;//14.2;//14;//14.5;//15;//16;//16.2;//16.42;
const double TABLE_GEARS_PROPORTION = TABLE_BIG_GEAR_DIAMETER / TABLE_SMALL_GEAR_DIAMETER;
 
