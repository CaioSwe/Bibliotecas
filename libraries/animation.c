#include "Animation.h"

#include <stdlib.h>

typedef struct AnimResources{
    float elapsed;
    bool animating;
    float duration;
} AnimResources;

typedef struct PositionAnimation{
    AnimResources resources;

    interpolationFunction interFunc;

    Vector2 start;
    Vector2 current; // (current position)
    Vector2 end;
} PositionAnimation;

typedef struct ScaleAnimation{
    AnimResources resources;

    interpolationFunction interFunc;

    bool maximized;
    bool resizing;
    bool minimized;

    Rectangle rectangle; // (current size)

    float start;
    float current;
    float end;
} ScaleAnimation;

typedef struct FramesAnimation{
    bool animating;

    float framesPadding;
    float padding;

    int animationDirection;
    int currentFrame;
    int amountOfFrames;
    int framesCounter;

    int framesSpeed;
    int baseSpeed;
} FramesAnimation;

typedef struct AnimationStr{
    PositionAnimation* position;
    ScaleAnimation* scale;
    FramesAnimation* frames;
} AnimationStr;

static AnimResources Animation_ResourcesInit(){
    return (AnimResources){0, false, 0.0f};
}

Animation Animation_Init(){
    AnimationStr* anim = (AnimationStr*)malloc(sizeof(AnimationStr));
    
    anim->position = NULL;
    anim->scale = NULL;
    anim->frames = NULL;

    return (Animation)anim;
}

static PositionAnimation* Animation_PositionInit(Vector2 position, interpolationFunction interFunc){
    PositionAnimation* posAnim = (PositionAnimation*)malloc(sizeof(PositionAnimation));
    
    posAnim->resources = Animation_ResourcesInit(0.0f);
    posAnim->start = posAnim->current = posAnim->end = position;
    posAnim->interFunc = interFunc;

    return posAnim;
}

static ScaleAnimation* Animation_ScaleInit(Rectangle rectangle, interpolationFunction interFunc){
    ScaleAnimation* scaleAnim = (ScaleAnimation*)malloc(sizeof(ScaleAnimation));

    scaleAnim->resources = Animation_ResourcesInit();
    scaleAnim->start = 1.0f;
    scaleAnim->current = 1.0f;
    scaleAnim->end = 1.0f;

    scaleAnim->maximized = false;
    scaleAnim->resizing = false;
    scaleAnim->minimized = false;

    scaleAnim->rectangle = rectangle;

    scaleAnim->interFunc = interFunc;

    return scaleAnim;
}

static FramesAnimation* Animation_FramesInit(int amountOfFrames, int framesSpeed){
    FramesAnimation* framesAnim = (FramesAnimation*)malloc(sizeof(FramesAnimation));

    framesAnim->animating = false;
    framesAnim->framesPadding = 0.0f;
    framesAnim->padding = 0.0f;
    framesAnim->animationDirection = 1;
    framesAnim->currentFrame = 0;
    framesAnim->amountOfFrames = amountOfFrames;
    framesAnim->framesCounter = 0;
    framesAnim->framesSpeed = framesSpeed;
    framesAnim->baseSpeed = framesSpeed;

    return framesAnim;
}

void Animation_AddPositionAnimation(Animation animation, Vector2 position, interpolationFunction interFunc){
    AnimationStr* anim = (AnimationStr*)animation;

    anim->position = Animation_PositionInit(position, interFunc);
}

void Animation_AddScaleAnimation(Animation animation, Rectangle rectangle, interpolationFunction interFunc){
    AnimationStr* anim = (AnimationStr*)animation;

    anim->scale = Animation_ScaleInit(rectangle, interFunc);
}

void Animation_AddFramesAnimation(Animation animation, int amountOfFrames, int framesSpeed){
    AnimationStr* anim = (AnimationStr*)animation;

    anim->frames = Animation_FramesInit(amountOfFrames, framesSpeed);
}

void Animation_MoveTo(Animation animation, Vector2 finalPoint, float duration){
    AnimationStr* anim = (AnimationStr*)animation;
    PositionAnimation* animPos = anim->position;

    if(animPos == NULL) return;

    animPos->end = finalPoint;

    animPos->resources.duration = duration;
    animPos->resources.elapsed = 0;
    animPos->resources.animating = true;
}

void Animation_UpdatePosition(Animation animation, float deltaTime){
    AnimationStr* anim = (AnimationStr*)animation;
    PositionAnimation* animPos = anim->position;

    if(animPos == NULL) return;

    Vector2 current = animPos->end;

    if(animPos->resources.animating == false) return;

    animPos->resources.elapsed += deltaTime;

    float progress = animPos->resources.elapsed / animPos->resources.duration;

    if(progress >= 1.0f){
        progress = 1.0f;
        animPos->resources.animating = false;
    }
    
    float eased = animPos->interFunc(progress);

    current.x = lerp(animPos->start.x, animPos->end.x, eased);
    current.y = lerp(animPos->start.y, animPos->end.y, eased);

    animPos->current = current;
}

void Animation_Resize(Animation animation, float scaleTo, float duration){
    AnimationStr* anim = (AnimationStr*)animation;
    ScaleAnimation* animScale = anim->scale;

    if(animScale == NULL) return;
    // if(animScale->resources.animating) return;

    animScale->start = 1.0f;
    animScale->end = 1.0f * scaleTo;
    animScale->current = 1.0f;

    animScale->resources.duration = duration;
    animScale->resources.elapsed = 0.0f;
    animScale->resources.animating = true;
}

void Animation_UpdateScale(Animation animation, float deltaTime){
    AnimationStr* anim = (AnimationStr*)animation;
    ScaleAnimation* animScale = anim->scale;

    if(animScale == NULL) return;

    Rectangle recItem = animScale->rectangle;

    if(animScale->resources.animating == false) return;

    animScale->resources.elapsed += deltaTime;

    float progress = animScale->resources.elapsed / animScale->resources.duration;

    if(progress >= 1.0f){
        progress = 1.0f;
        animScale->resources.animating = false;
    }

    float eased = animScale->interFunc(progress);

    float prevScale = animScale->current;
    float newScale = lerp(animScale->start, animScale->end, eased);
    
    animScale->current = newScale;

    Vector2 center = getRectCenter(recItem);

    float baseWidth = recItem.width / prevScale;
    float baseHeight = recItem.height / prevScale;

    recItem.width = baseWidth * newScale;
    recItem.height = baseHeight * newScale;

    recItem.x = center.x - recItem.width / 2.0f;
    recItem.y = center.y - recItem.height / 2.0f;

    animScale->rectangle = recItem;
}

void Animation_UpdateAll(Animation animation, float deltaTime){
    Animation_UpdatePosition(animation, deltaTime);
    Animation_UpdateScale(animation, deltaTime);
}

void Animation_SetPosition(Animation animation, Vector2 position){
    AnimationStr* anim = (AnimationStr*)animation;
    PositionAnimation* animPos = anim->position;

    if(animPos == NULL) return;

    animPos->start = position;
    animPos->current = position;
}

Vector2 Animation_GetPosition(Animation animation){
    AnimationStr* anim = (AnimationStr*)animation;
    PositionAnimation* animPos = anim->position;

    return (animPos == NULL ? (Vector2){0, 0} : animPos->current);
}

void Animation_SetRectangle(Animation animation, Rectangle rectangle){
    AnimationStr* anim = (AnimationStr*)animation;
    ScaleAnimation* animScale = anim->scale;

    if(animScale == NULL) return;

    animScale->rectangle = rectangle;
}

Rectangle Animation_GetScale(Animation animation){
    AnimationStr* anim = (AnimationStr*)animation;
    ScaleAnimation* animScale = anim->scale;

    return (animScale == NULL ? (Rectangle){0, 0, 0, 0} : animScale->rectangle);
}

void Animation_SetPositionFunction(Animation animation, interpolationFunction interFunc){
    AnimationStr* anim = (AnimationStr*)animation;
    PositionAnimation* animPos = anim->position;

    if(animPos == NULL) return;

    animPos->interFunc = interFunc;
}

void Animation_SetScaleFunction(Animation animation, interpolationFunction interFunc){
    AnimationStr* anim = (AnimationStr*)animation;
    ScaleAnimation* animScale = anim->scale;

    if(animScale == NULL) return;

    animScale->interFunc = interFunc;
}

// PositionAnimation* AnimationPosition_Copy(PositionAnimation* posFrom){
//     PositionAnimation* 

//     posTo->elapsed = posFrom->elapsed;
//     posTo->animating = posFrom->animating;
//     posTo->duration = posFrom->duration;

//     posTo->function = posFrom->function;

//     posTo->current = posFrom->current;
//     posTo->start = posFrom->start;
//     posTo->end = posFrom->end;
// }

// void Animation_ScaleCopy(ScaleAnimation* scaleFrom, ScaleAnimation* scaleTo){
//     scaleTo->elapsed = scaleFrom->elapsed;
//     scaleTo->animating = scaleFrom->animating;
//     scaleTo->duration = scaleFrom->duration;

//     scaleTo->maximized = scaleFrom->maximized;
//     scaleTo->minimized = scaleFrom->minimized;

//     scaleTo->current = scaleFrom->current;
//     scaleTo->start = scaleFrom->start;
//     scaleTo->end = scaleFrom->end;
// }

// void Animation_FramesCopy(FramesAnimation* framesFrom, FramesAnimation* framesTo){
//     framesTo->animating = framesFrom->animating;

//     framesTo->framesPadding = framesFrom->framesPadding;
//     framesTo->padding = framesFrom->padding;

//     framesTo->animationDirection = framesFrom->animationDirection;
//     framesTo->currentFrame = framesFrom->currentFrame;
//     framesTo->amountOfFrames = framesFrom->amountOfFrames;
//     framesTo->framesCounter = framesFrom->framesCounter;

//     framesTo->framesSpeed = framesFrom->framesSpeed;
//     framesTo->baseSpeed = framesFrom->baseSpeed;
// }