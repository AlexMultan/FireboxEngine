#pragma once

#include "Engine/Core/Core.h"
#include "SDL3/SDL.h"

namespace Firebox {
	enum KeyCode
	{
		FBK_KEY_UNKNOWN = 0,
		FBK_KEY_A = 4,
		FBK_KEY_B = 5,
		FBK_KEY_C = 6,
		FBK_KEY_D = 7,
		FBK_KEY_E = 8,
		FBK_KEY_F = 9,
		FBK_KEY_G = 10,
		FBK_KEY_H = 11,
		FBK_KEY_I = 12,
		FBK_KEY_J = 13,
		FBK_KEY_K = 14,
		FBK_KEY_L = 15,
		FBK_KEY_M = 16,
		FBK_KEY_N = 17,
		FBK_KEY_O = 18,
		FBK_KEY_P = 19,
		FBK_KEY_Q = 20,
		FBK_KEY_R = 21,
		FBK_KEY_S = 22,
		FBK_KEY_T = 23,
		FBK_KEY_U = 24,
		FBK_KEY_V = 25,
		FBK_KEY_W = 26,
		FBK_KEY_X = 27,
		FBK_KEY_Y = 28,
		FBK_KEY_Z = 29,

        // Numbers
		FBK_KEY_1 = 30,
		FBK_KEY_2 = 31,
		FBK_KEY_3 = 32,
		FBK_KEY_4 = 33,
		FBK_KEY_5 = 34,
		FBK_KEY_6 = 35,
		FBK_KEY_7 = 36,
		FBK_KEY_8 = 37,
		FBK_KEY_9 = 38,
		FBK_KEY_0 = 39,

        // Function keys
		FBK_KEY_F1 = 40,
		FBK_KEY_F2 = 41,
		FBK_KEY_F3 = 42,
		FBK_KEY_F4 = 43,
		FBK_KEY_F5 = 44,
		FBK_KEY_F6 = 45,
		FBK_KEY_F7 = 46,
		FBK_KEY_F8 = 47,
		FBK_KEY_F9 = 48,
		FBK_KEY_F10 = 49,
		FBK_KEY_F11 = 50,
		FBK_KEY_F12 = 51,

		FBK_KEY_ESCAPE = 52,
		FBK_KEY_RETURN = 53,
		FBK_KEY_BACKSPACE = 54,
		FBK_KEY_TAB = 55,
		FBK_KEY_SPACE = 56,
		FBK_KEY_MINUS = 57,
		FBK_KEY_EQUALS = 58,
		FBK_KEY_LEFTBRACKET = 59,
		FBK_KEY_RIGHTBRACKET = 60,
		FBK_KEY_BACKSLASH = 61,
		FBK_KEY_NONUSHASH = 62,
		FBK_KEY_SEMICOLON = 63,
		FBK_KEY_APOSTROPHE = 64,
		FBK_KEY_GRAVE = 65,
		FBK_KEY_COMMA = 66,
		FBK_KEY_PERIOD = 67,
		FBK_KEY_SLASH = 68,
		FBK_KEY_CAPSLOCK = 69,
		FBK_KEY_LEFT_SHIFT = 70,
		FBK_KEY_LEFT_CTRL = 71,
		FBK_KEY_LEFT_ALT = 72,
		FBK_KEY_RIGHT_SHIFT = 73,
		FBK_KEY_RIGHT_CTRL = 74,
		FBK_KEY_RIGHT_ALT = 75,

		//Arrow keys
		FBK_KEY_ARROW_UP = 76,
		FBK_KEY_ARROW_DOWN = 77,
		FBK_KEY_ARROW_LEFT = 78,
		FBK_KEY_ARROW_RIGHT = 79,
        FBK_KEY_ENTER = 80
	};

    inline static KeyCode SDLKeyCodeToFirebox(SDL_Keycode sdlKeyCode)
    {
        switch (sdlKeyCode)
        {
        case SDLK_A: return FBK_KEY_A;
        case SDLK_B: return FBK_KEY_B;
        case SDLK_C: return FBK_KEY_C;
        case SDLK_D: return FBK_KEY_D;
        case SDLK_E: return FBK_KEY_E;
        case SDLK_F: return FBK_KEY_F;
        case SDLK_G: return FBK_KEY_G;
        case SDLK_H: return FBK_KEY_H;
        case SDLK_I: return FBK_KEY_I;
        case SDLK_J: return FBK_KEY_J;
        case SDLK_K: return FBK_KEY_K;
        case SDLK_L: return FBK_KEY_L;
        case SDLK_M: return FBK_KEY_M;
        case SDLK_N: return FBK_KEY_N;
        case SDLK_O: return FBK_KEY_O;
        case SDLK_P: return FBK_KEY_P;
        case SDLK_Q: return FBK_KEY_Q;
        case SDLK_R: return FBK_KEY_R;
        case SDLK_S: return FBK_KEY_S;
        case SDLK_T: return FBK_KEY_T;
        case SDLK_U: return FBK_KEY_U;
        case SDLK_V: return FBK_KEY_V;
        case SDLK_W: return FBK_KEY_W;
        case SDLK_X: return FBK_KEY_X;
        case SDLK_Y: return FBK_KEY_Y;
        case SDLK_Z: return FBK_KEY_Z;
        case SDLK_1: return FBK_KEY_1;
        case SDLK_2: return FBK_KEY_2;
        case SDLK_3: return FBK_KEY_3;
        case SDLK_4: return FBK_KEY_4;
        case SDLK_5: return FBK_KEY_5;
        case SDLK_6: return FBK_KEY_6;
        case SDLK_7: return FBK_KEY_7;
        case SDLK_8: return FBK_KEY_8;
        case SDLK_9: return FBK_KEY_9;
        case SDLK_0: return FBK_KEY_0;
        case SDLK_F1: return FBK_KEY_F1;
        case SDLK_F2: return FBK_KEY_F2;
        case SDLK_F3: return FBK_KEY_F3;
        case SDLK_F4: return FBK_KEY_F4;
        case SDLK_F5: return FBK_KEY_F5;
        case SDLK_F6: return FBK_KEY_F6;
        case SDLK_F7: return FBK_KEY_F7;
        case SDLK_F8: return FBK_KEY_F8;
        case SDLK_F9: return FBK_KEY_F9;
        case SDLK_F10: return FBK_KEY_F10;
        case SDLK_F11: return FBK_KEY_F11;
        case SDLK_F12: return FBK_KEY_F12;
        case SDLK_ESCAPE: return FBK_KEY_ESCAPE;
        case SDLK_RETURN: return FBK_KEY_RETURN;
        case SDLK_BACKSPACE: return FBK_KEY_BACKSPACE;
        case SDLK_TAB: return FBK_KEY_TAB;
        case SDLK_SPACE: return FBK_KEY_SPACE;
        case SDLK_MINUS: return FBK_KEY_MINUS;
        case SDLK_EQUALS: return FBK_KEY_EQUALS;
        case SDLK_LEFTBRACKET: return FBK_KEY_LEFTBRACKET;
        case SDLK_RIGHTBRACKET: return FBK_KEY_RIGHTBRACKET;
        case SDLK_BACKSLASH: return FBK_KEY_BACKSLASH;
		}
	}

    inline static SDL_Keycode FireboxKeyCodeToSDL(KeyCode keyCode)
    {
        switch (keyCode)
        {
        case FBK_KEY_A: return SDLK_A;
        case FBK_KEY_B: return SDLK_B;
        case FBK_KEY_C: return SDLK_C;
        case FBK_KEY_D: return SDLK_D;
        case FBK_KEY_E: return SDLK_E;
        case FBK_KEY_F: return SDLK_F;
        case FBK_KEY_G: return SDLK_G;
        case FBK_KEY_H: return SDLK_H;
        case FBK_KEY_I: return SDLK_I;
        case FBK_KEY_J: return SDLK_J;
        case FBK_KEY_K: return SDLK_K;
        case FBK_KEY_L: return SDLK_L;
        case FBK_KEY_M: return SDLK_M;
        case FBK_KEY_N: return SDLK_N;
        case FBK_KEY_O: return SDLK_O;
        case FBK_KEY_P: return SDLK_P;
        case FBK_KEY_Q: return SDLK_Q;
        case FBK_KEY_R: return SDLK_R;
        case FBK_KEY_S: return SDLK_S;
        case FBK_KEY_T: return SDLK_T;
        case FBK_KEY_U: return SDLK_U;
        case FBK_KEY_V: return SDLK_V;
        case FBK_KEY_W: return SDLK_W;
        case FBK_KEY_X: return SDLK_X;
        case FBK_KEY_Y: return SDLK_Y;
        case FBK_KEY_Z: return SDLK_Z;
        case FBK_KEY_1: return SDLK_1;
        case FBK_KEY_2: return SDLK_2;
        case FBK_KEY_3: return SDLK_3;
        case FBK_KEY_4: return SDLK_4;
        case FBK_KEY_5: return SDLK_5;
        case FBK_KEY_6: return SDLK_6;
        case FBK_KEY_7: return SDLK_7;
        case FBK_KEY_8: return SDLK_8;
        case FBK_KEY_9: return SDLK_9;
        case FBK_KEY_0: return SDLK_0;
        case FBK_KEY_F1: return SDLK_F1;
        case FBK_KEY_F2: return SDLK_F2;
        case FBK_KEY_F3: return SDLK_F3;
        case FBK_KEY_F4: return SDLK_F4;
        case FBK_KEY_F5: return SDLK_F5;
        case FBK_KEY_F6: return SDLK_F6;
        case FBK_KEY_F7: return SDLK_F7;
        case FBK_KEY_F8: return SDLK_F8;
        case FBK_KEY_F9: return SDLK_F9;
        case FBK_KEY_F10: return SDLK_F10;
        case FBK_KEY_F11: return SDLK_F11;
        case FBK_KEY_F12: return SDLK_F12;
        case FBK_KEY_ESCAPE: return SDLK_ESCAPE;
        case FBK_KEY_RETURN: return SDLK_RETURN;
        case FBK_KEY_BACKSPACE: return SDLK_BACKSPACE;
        case FBK_KEY_TAB: return SDLK_TAB;
        case FBK_KEY_SPACE: return SDLK_SPACE;
        case FBK_KEY_MINUS: return SDLK_MINUS;
        case FBK_KEY_EQUALS: return SDLK_EQUALS;
        case FBK_KEY_LEFTBRACKET: return SDLK_LEFTBRACKET;
        case FBK_KEY_RIGHTBRACKET: return SDLK_RIGHTBRACKET;
        case FBK_KEY_BACKSLASH: return SDLK_BACKSLASH;
        }
    }
}