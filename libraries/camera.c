#include "camera.h"

#include <raymath.h>
#include <stdlib.h>

#include <types.h>
#include <stdio.h>

#include <hash.h>
#include "utils.h"

Hash cameraAllInstances = NULL;

typedef struct CameraStr{
    int id;
    Camera2D camera;

    float zoomBaseFactor;
    float scrolls;
} CameraStr;

MyCamera cameraInit(Vector2 position, Vector2 offset, float zoomBaseFactor){
    CameraStr* c = (CameraStr*)malloc(sizeof(CameraStr));
    
    static int id = 0;
    c->id = id;
    id += 1;

    Camera2D camera = {0};

    camera.target = position;
    camera.offset = offset;
    camera.zoom = 1.0f;

    c->camera = camera;
    c->zoomBaseFactor = zoomBaseFactor;
    c->scrolls = 0;

    createAndInsertInstance(&cameraAllInstances, c->id, c);

    return (MyCamera)c;
}

Vector2 getPointOnCamera(MyCamera camera, Vector2 point){
    CameraStr* c = (CameraStr*)camera;

    return GetScreenToWorld2D(point, c->camera);
}

void cameraMove(MyCamera camera, Vector2 delta, bool zoomProportional){
    CameraStr* c = (CameraStr*)camera;

    Vector2 rDelta = (zoomProportional ? getCameraPointDelta(camera, delta) : delta);

    c->camera.target = Vector2Subtract(c->camera.target, rDelta);

    // printf("\n [%.1f, %.1f] -> [%.1f, %.1f]", rDelta.x, rDelta.y, c->camera.target.x, c->camera.target.y);
}

void cameraSetPosition(MyCamera camera, Vector2 position){
    CameraStr* c = (CameraStr*)camera;
    c->camera.target = position;
}

Vector2 getCameraPointDelta(MyCamera camera, Vector2 delta){
    CameraStr* c = (CameraStr*)camera;

    return Vector2Multiply(delta, (Vector2){1/c->camera.zoom, 1/c->camera.zoom});
}

void cameraZoom(MyCamera camera, float factor){
    CameraStr* c = (CameraStr*)camera;

    c->scrolls = Clamp(c->scrolls + factor, logf(0.1f) / logf(c->zoomBaseFactor), logf(8.0f) / logf(c->zoomBaseFactor));
    c->camera.zoom = powf(c->zoomBaseFactor, c->scrolls);
}

Rectangle cameraGetRec(MyCamera camera){
    CameraStr* c = (CameraStr*)camera;

    Rectangle screenSize = (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()};

    float value = 1/c->camera.zoom;

    screenSize.x = c->camera.target.x - (c->camera.offset.x * value);
    screenSize.y = c->camera.target.y - (c->camera.offset.y * value);
    screenSize.width *= value;
    screenSize.height *= value;

    return screenSize;
}

Vector2 cameraGetOffset(MyCamera camera){
    CameraStr* c = (CameraStr*)camera;

    return c->camera.offset;
}

void openCamera(MyCamera camera){
    CameraStr* c = (CameraStr*)camera;

    BeginMode2D(c->camera);
}

void closeCamera(MyCamera camera){
    UNUSED(camera);
    EndMode2D();
}

static void cameraFreeInstance(MyCamera camera){
    CameraStr* c = (CameraStr*)camera;
    free(c);
}

void cameraFree(MyCamera camera){
    CameraStr* c = (CameraStr*)camera;
    removeInstance(cameraAllInstances, c->id);

    cameraFreeInstance(camera);
}

void cameraFreeAll(){
    destroiHash(cameraAllInstances, freeExtra, cameraFreeInstance);
}