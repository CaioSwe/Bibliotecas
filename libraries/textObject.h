#ifndef _TextObject_h_
#define _TextObject_h_

#include <stdbool.h>
#include <raylib.h>

#include <delimiters.h>

typedef void* TextObject;

TextObject Text_Init(const char* text);

TextObject Text_Copy(TextObject txtObj);

void Text_Set(TextObject txtObj, const char* text);

void Text_SetFontSize(TextObject txtObj, int fontSize);

void Text_SetRecPadding(TextObject txtObj, float padding);

void Text_Scale(TextObject txtObj, float scaling);

void Text_SetPosition(TextObject txtObj, Vector2 position);

bool Text_IsPointOverText(TextObject txtObj, Vector2 point);

void Text_MoveDelta(TextObject txtObj, Vector2 delta);

void Text_Draw(TextObject txtObj);

int Text_getId(TextObject txtObj);

Rectangle Text_getRectangle(TextObject txtObj);

float Text_getPadding(TextObject txtObj);

#endif