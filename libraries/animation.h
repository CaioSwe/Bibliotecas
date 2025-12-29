#ifndef _Animation_h_
#define _Animation_h_

#include "utils.h"
#include <delimiters.h>

typedef void* Animation;

Animation Animation_Init();

void Animation_AddPositionAnimation(Animation animation, Vector2 position, interpolationFunction interFunc);

void Animation_AddScaleAnimation(Animation animation, Rectangle rectangle, interpolationFunction interFunc);

void Animation_AddFramesAnimation(Animation animation, int amountOfFrames, int framesSpeed);

void Animation_MoveTo(Animation animation, Vector2 finalPoint, float duration);

void Animation_UpdatePosition(Animation animation, float deltaTime);

void Animation_Resize(Animation animation, float scaleTo, float duration);

void Animation_UpdateScale(Animation animation, float deltaTime);

void Animation_UpdateAll(Animation animation, float deltaTime);

void Animation_SetPosition(Animation animation, Vector2 position);

Vector2 Animation_GetPosition(Animation animation);

void Animation_SetRectangle(Animation animation, Rectangle rectangle);

Rectangle Animation_GetScale(Animation animation);

void Animation_SetPositionFunction(Animation animation, interpolationFunction interFunc);

void Animation_SetScaleFunction(Animation animation, interpolationFunction interFunc);

#endif