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
const double DIVIDER_SMALL_GEAR_DIAMETER = 18.97;//18.95;//23;//22;//25;.83;//32.8;//33.1; //32.981; //34.81; 
const double DIVIDER_GEARS_PROPORTION = DIVIDER_BIG_GEAR_DIAMETER / DIVIDER_SMALL_GEAR_DIAMETER;

/***************************** TABLE MOTOR ****************************************/
const double TABLE_BIG_GEAR_DIAMETER = 87;
const double TABLE_SMALL_GEAR_DIAMETER = 16.42;
const double TABLE_GEARS_PROPORTION = TABLE_BIG_GEAR_DIAMETER / TABLE_SMALL_GEAR_DIAMETER;
 
