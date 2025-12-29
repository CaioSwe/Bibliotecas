#include "textObject.h"

#include <raymath.h>

#include <stdlib.h>
#include <string.h>

typedef struct TextObjectStr{
    int id;
    char text[MAX_STRSIZE];
    Color color;
    int fontsize;
    float x, y;
    bool collision;
    Rectangle rectangle;

    float padding;
} TextObjectStr;

TextObject Text_Init(const char* text){
    TextObjectStr* txt = (TextObjectStr*)malloc(sizeof(TextObjectStr));
    
    static int id = 0;

    txt->id = id;
    id += 1;

    strncpy(txt->text, text, MAX_STRSIZE - 1);
    txt->text[MAX_STRSIZE - 1] = '\0';

    txt->color = WHITE;
    txt->fontsize = 10;
    txt->x = txt->y = 0;
    txt->collision = false;
    txt->rectangle = (Rectangle){txt->x, txt->y, MeasureText(txt->text, txt->fontsize), txt->fontsize};
    txt->padding = 0.0f;

    return (TextObject)txt;
}

TextObject Text_Copy(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    TextObjectStr* newTxt = (TextObjectStr*)Text_Init(txt->text);

    newTxt->collision = txt->collision;
    newTxt->fontsize = txt->fontsize;
    newTxt->color = txt->color;
    newTxt->rectangle = txt->rectangle;
    newTxt->x = txt->x;
    newTxt->y = txt->y;
    newTxt->padding = txt->padding;

    return (TextObject)newTxt;
}

static void Text_UpdateRec(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    txt->rectangle = (Rectangle){txt->x - txt->padding, txt->y - txt->padding, MeasureText(txt->text, txt->fontsize) + txt->padding * 2, txt->fontsize + txt->padding * 2};
}

void Text_Set(TextObject txtObj, const char* text){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    strncpy(txt->text, text, MAX_STRSIZE - 1);
    txt->text[MAX_STRSIZE - 1] = '\0';

    Text_UpdateRec(txt);
}

void Text_SetFontSize(TextObject txtObj, int fontSize){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    txt->fontsize = fontSize;
    Text_UpdateRec(txt);
}

void Text_SetRecPadding(TextObject txtObj, float padding){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    txt->padding = padding;
    Text_UpdateRec(txt);
}

void Text_Scale(TextObject txtObj, float scaling){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    int basefontsize = 20;
    float scale_font = (float)(GetScreenWidth() * scaling) / MeasureText(txt->text, basefontsize);
    txt->fontsize = basefontsize * scale_font;
}

void Text_SetPosition(TextObject txtObj, Vector2 position){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    txt->rectangle.x = position.x;
    txt->rectangle.y = position.y;
    
    txt->x = txt->rectangle.x + txt->padding;
    txt->y = txt->rectangle.y + txt->padding;
}

bool Text_IsPointOverText(TextObject txtObj, Vector2 point){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    return CheckCollisionPointRec(point, txt->rectangle);
}

void Text_MoveDelta(TextObject txtObj, Vector2 delta){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    txt->rectangle.x += delta.x;
    txt->rectangle.y += delta.y;
    
    txt->x = txt->rectangle.x + txt->padding;
    txt->y = txt->rectangle.y + txt->padding;
}

void Text_Draw(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    DrawText(txt->text, txt->x, txt->y, txt->fontsize, txt->color);
}

int Text_getId(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    return txt->id;
}

Rectangle Text_getRectangle(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    return txt->rectangle;
}

float Text_getPadding(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    return txt->padding;
}