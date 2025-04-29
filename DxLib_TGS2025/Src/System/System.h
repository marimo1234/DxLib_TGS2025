#pragma once

int WakeUp(void);
void ShutDown(void);
const int FPS = 60;
const int FRAME_TIME = 1000 / FPS;

int startTime, deltaTime;
int frameCount = 0;
int fpsTimer = GetNowCount();
int currentFPS = 0;