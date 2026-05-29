#pragma once

#include "SDL3/SDL.h"

namespace Firebox {
    enum KeyCode
    {
        FBK_KEY_UNKNOWN = 0,
        FBK_KEY_A = SDL_SCANCODE_A,
        FBK_KEY_B = SDL_SCANCODE_B,
        FBK_KEY_C = SDL_SCANCODE_C,
        FBK_KEY_D = SDL_SCANCODE_D,
        FBK_KEY_E = SDL_SCANCODE_E,
        FBK_KEY_F = SDL_SCANCODE_F,
        FBK_KEY_G = SDL_SCANCODE_G,
        FBK_KEY_H = SDL_SCANCODE_H,
        FBK_KEY_I = SDL_SCANCODE_I,
        FBK_KEY_J = SDL_SCANCODE_J,
        FBK_KEY_K = SDL_SCANCODE_K,
        FBK_KEY_L = SDL_SCANCODE_L,
        FBK_KEY_M = SDL_SCANCODE_M,
        FBK_KEY_N = SDL_SCANCODE_N,
        FBK_KEY_O = SDL_SCANCODE_O,
        FBK_KEY_P = SDL_SCANCODE_P,
        FBK_KEY_Q = SDL_SCANCODE_Q,
        FBK_KEY_R = SDL_SCANCODE_R,
        FBK_KEY_S = SDL_SCANCODE_S,
        FBK_KEY_T = SDL_SCANCODE_T,
        FBK_KEY_U = SDL_SCANCODE_U,
        FBK_KEY_V = SDL_SCANCODE_V,
        FBK_KEY_W = SDL_SCANCODE_W,
        FBK_KEY_X = SDL_SCANCODE_X,
        FBK_KEY_Y = SDL_SCANCODE_Y,
        FBK_KEY_Z = SDL_SCANCODE_Z,

        // Numbers
        FBK_KEY_1 = SDL_SCANCODE_1,
        FBK_KEY_2 = SDL_SCANCODE_2,
        FBK_KEY_3 = SDL_SCANCODE_3,
        FBK_KEY_4 = SDL_SCANCODE_4,
        FBK_KEY_5 = SDL_SCANCODE_5,
        FBK_KEY_6 = SDL_SCANCODE_6,
        FBK_KEY_7 = SDL_SCANCODE_7,
        FBK_KEY_8 = SDL_SCANCODE_8,
        FBK_KEY_9 = SDL_SCANCODE_9,
        FBK_KEY_0 = SDL_SCANCODE_0,

        // Function keys
        FBK_KEY_F1 = SDL_SCANCODE_F1,
        FBK_KEY_F2 = SDL_SCANCODE_F2,
        FBK_KEY_F3 = SDL_SCANCODE_F3,
        FBK_KEY_F4 = SDL_SCANCODE_F4,
        FBK_KEY_F5 = SDL_SCANCODE_F5,
        FBK_KEY_F6 = SDL_SCANCODE_F6,
        FBK_KEY_F7 = SDL_SCANCODE_F7,
        FBK_KEY_F8 = SDL_SCANCODE_F8,
        FBK_KEY_F9 = SDL_SCANCODE_F9,
        FBK_KEY_F10 = SDL_SCANCODE_F10,
        FBK_KEY_F11 = SDL_SCANCODE_F11,
        FBK_KEY_F12 = SDL_SCANCODE_F12,

        FBK_KEY_ESCAPE = SDL_SCANCODE_ESCAPE,
        FBK_KEY_RETURN = SDL_SCANCODE_RETURN,
        FBK_KEY_BACKSPACE = SDL_SCANCODE_BACKSPACE,
        FBK_KEY_TAB = SDL_SCANCODE_TAB,
        FBK_KEY_SPACE = SDL_SCANCODE_SPACE,
        FBK_KEY_MINUS = SDL_SCANCODE_MINUS,
        FBK_KEY_EQUALS = SDL_SCANCODE_EQUALS,
        FBK_KEY_LEFTBRACKET = SDL_SCANCODE_LEFTBRACKET,
        FBK_KEY_RIGHTBRACKET = SDL_SCANCODE_RIGHTBRACKET,
        FBK_KEY_BACKSLASH = SDL_SCANCODE_BACKSLASH,
        FBK_KEY_SEMICOLON = SDL_SCANCODE_SEMICOLON,
        FBK_KEY_APOSTROPHE = SDL_SCANCODE_APOSTROPHE,
        FBK_KEY_COMMA = SDL_SCANCODE_COMMA,
        FBK_KEY_PERIOD = SDL_SCANCODE_PERIOD,
        FBK_KEY_SLASH = SDL_SCANCODE_SLASH,
        FBK_KEY_CAPSLOCK = SDL_SCANCODE_CAPSLOCK,
        FBK_KEY_LSHIFT = SDL_SCANCODE_LSHIFT,
        FBK_KEY_LCTRL = SDL_SCANCODE_LCTRL,
        FBK_KEY_LALT = SDL_SCANCODE_LALT,
        FBK_KEY_RSHIFT = SDL_SCANCODE_RSHIFT,
        FBK_KEY_RCTRL = SDL_SCANCODE_RCTRL,
        FBK_KEY_RALT = SDL_SCANCODE_RALT,
        FBK_KEY_ENTER = SDL_SCANCODE_KP_ENTER,

		//Arrow keys
		FBK_KEY_ARROW_UP = SDL_SCANCODE_UP,
		FBK_KEY_ARROW_DOWN = SDL_SCANCODE_DOWN,
		FBK_KEY_ARROW_LEFT = SDL_SCANCODE_LEFT,
		FBK_KEY_ARROW_RIGHT = SDL_SCANCODE_RIGHT
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