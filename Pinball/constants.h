#pragma once
#include "Library.h"
using namespace sf;
const int height = 1080, width = 1920;
bool GameOver = false;
bool FirstTime = true;
bool win_you = 0;
bool ball_stan = 0;
bool ball_stan_was = 0;
bool time_stan = 0;
bool time_acceleration = 0;
int frame_ball_stan = 0;
int number_platform_ball_stan = 0;
int count_stan_time = 3;
int count_accelerate_time = 3;
bool touch_was = false;
Clock cloc;