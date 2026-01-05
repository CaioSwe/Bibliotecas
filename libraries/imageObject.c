#include "imageObject.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct ImageObjectStr {
    char* filename;
    Texture2D image;
    
    Rectangle source;           // Controla a fonte de imagem na textura original (qual parte da imagem original vai ser mostrada)
    Rectangle destination;      // Controla o output de imagem (onde aparece na tela)
    
    float rotation;
    Vector2 origin;

    Color color;
} ImageObjectStr;

static void Image_ReplaceTexture(ImageObjectStr* imgobj, const char* filename, bool replaceSource, bool replaceDestination){
    if(filename != NULL){
        if (imgobj->filename == NULL) {
            imgobj->filename = (char*)malloc(MAX_STRSIZE);
        }
        
        strncpy(imgobj->filename, filename, MAX_STRSIZE - 1);
        imgobj->filename[MAX_STRSIZE - 1] = '\0';
        
        imgobj->image = LoadTexture(filename);
        
        if(replaceSource == true){
            imgobj->source = (Rectangle){0, 0, (float)imgobj->image.width, (float)imgobj->image.height};
        }
    }
    else{
        imgobj->source = (Rectangle){0, 0, 0, 0};
    }

    if(replaceDestination == true){
        imgobj->destination = imgobj->source;
    }
}

ImageObject Image_Init(const char* filename){
    ImageObjectStr* imgobj = (ImageObjectStr*)malloc(sizeof(ImageObjectStr));

    imgobj->filename = NULL;
    Image_ReplaceTexture(imgobj, filename, true, true);

    imgobj->color = WHITE;
    imgobj->rotation = 0;
    imgobj->origin = (Vector2){0, 0};

    return (ImageObject)imgobj;
}

void Image_SetPosition(ImageObject img, Vector2 position){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;
    imgobj->destination.x = position.x;
    imgobj->destination.y = position.y;
}

void Image_SetColor(ImageObject img, Color color){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;
    imgobj->color = color;
}

void Image_ApplyScale(ImageObject img, float scale){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;
    imgobj->destination.width *= scale;
    imgobj->destination.height *= scale;
}

void Image_SetRotation(ImageObject img, float rotation){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;
    imgobj->rotation = rotation;
}

void Image_SetDestination(ImageObject img, Rectangle destination){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;
    imgobj->destination = destination;
}

void Image_SetSource(ImageObject img, Rectangle source){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;
    imgobj->source = source;
}

void Image_SetTexture(ImageObject img, const char* filename, bool replaceSource, bool replaceDestination){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;
    
    UnloadTexture(imgobj->image);
    
    Image_ReplaceTexture(imgobj, filename, replaceSource, replaceDestination);
}

void Image_SetOrigin(ImageObject img, Vector2 origin){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;
    imgobj->origin = origin;
}

void Image_FitToSize(ImageObject img, Vector2 size){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;

    float xscale = size.x / imgobj->image.width;
    float yscale = size.y / (imgobj->image.height / 2);
    float finalScale = fmin(yscale, xscale);

    Image_ApplyScale(img, finalScale);
}

void Image_FitToScreenSize(ImageObject img){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;

    float xscale = (float)(GetScreenWidth()) / imgobj->image.width;
    float yscale = (float)(GetScreenHeight()) / (imgobj->image.height);
    float finalScale = fmax(yscale, xscale);

    Image_ApplyScale(img, finalScale);
}

Vector2 Image_GetPosition(ImageObject img){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;
    return (Vector2){imgobj->destination.x, imgobj->destination.y};
}

Rectangle Image_GetDestination(ImageObject img){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;
    return imgobj->destination;
}

Color Image_GetColor(ImageObject img){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;
    return imgobj->color;
}

float Image_GetRotation(ImageObject img){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;
    return imgobj->rotation;
}

const char* Image_GetTextureName(ImageObject img){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;
    return TextFormat("%s", imgobj->filename);
}

Vector2 Image_GetOrigin(ImageObject img){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;
    return imgobj->origin;
}

ImageObject Image_Copy(ImageObject img){
    ImageObjectStr* imgobj1 = (ImageObjectStr*)img;

    ImageObjectStr* imgobj2 = (ImageObjectStr*)Image_Init(imgobj1->filename);
    
    imgobj2->source = imgobj1->source;
    imgobj2->destination = imgobj1->destination;

    imgobj2->rotation = imgobj1->rotation;
    imgobj2->color = imgobj1->color;

    return (ImageObject)imgobj2;
}

void Image_Draw(ImageObject img){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;

    DrawTexturePro(imgobj->image, imgobj->source, imgobj->destination, imgobj->origin, imgobj->rotation, imgobj->color);
}

void Image_Free(ImageObject img){
    ImageObjectStr* imgobj = (ImageObjectStr*)img;

    free(imgobj->filename);
    UnloadTexture(imgobj->image);
    free(imgobj);
}