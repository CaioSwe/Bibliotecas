#ifndef _Utils_h_
#define _Utils_h_

#include <raylib.h>
#include <stddef.h>
#include <stdbool.h>

// Minimal WinAPI cursor declarations (Windows only)
typedef void* HCURSOR;
typedef void* HINSTANCE;
typedef const wchar_t* LPCWSTR;   // wide string (Windows uses UTF-16)

__declspec(dllimport) HCURSOR __stdcall LoadCursorW(HINSTANCE hInstance, LPCWSTR lpCursorName);
__declspec(dllimport) HCURSOR __stdcall SetCursor(HCURSOR hCursor);

// Predefined system cursor IDs
#define IDC_ARROW   ((LPCWSTR)32512)
#define IDC_HAND    ((LPCWSTR)32649)
#define IDC_SIZEALL ((LPCWSTR)32646)

#define TO_STRING(variable) #variable

bool wait(double intervalo);

int normalize(float value);

float lerp(float a, float b, float t);

void DrawArrow(Vector2 start, Vector2 end, float headLength, float headWidth, float backOffset, Color color);

Vector2 getRectCenter(Rectangle rectangle);

// ANIMATION FUNCTIONS (0 <= t <= 1)
///////////////////////////////////

typedef float (*interpolationFunction)(float t);

float linearFunction(float t);

float easeInFunction(float t);

float easeOutFunction(float t);

float quadraticFunction(float t);

float rootFunction(float t);

float easeInOutFunction(float t);

float easeInOutCubic(float t);

float easeInOutQuint(float t);

float easeInOutCirc(float t);

float easeOutBounce(float t);

#endif