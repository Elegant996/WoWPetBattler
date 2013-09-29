////////////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------------- //
//                                                                            //
//                        (C) 2010-2013  David Krutsko                        //
//                        See LICENSE.md for copyright                        //
//                                                                            //
// -------------------------------------------------------------------------- //
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------//
// Prefaces                                                                   //
//----------------------------------------------------------------------------//

#ifndef ROBOT_KEYBOARD_H
#define ROBOT_KEYBOARD_H

#include "Global.h"
namespace Robot {



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

enum Keycode
{
#ifdef ROBOT_OS_LINUX32

	KeySpace			= 65,
	KeyEscape			= 9,

	KeyTab				= 23,
	KeyAlt				= 64,
	KeyControl			= 37,
	KeyShift			= 50,
	KeySystem			= 133,
	KeyMenu				= 135,

	KeyF1				= 67,
	KeyF2				= 68,
	KeyF3				= 69,
	KeyF4				= 70,
	KeyF5				= 71,
	KeyF6				= 72,
	KeyF7				= 73,
	KeyF8				= 74,
	KeyF9				= 75,
	KeyF10				= 76,
	KeyF11				= 95,
	KeyF12				= 96,

	Key0				= 19,
	Key1				= 10,
	Key2				= 11,
	Key3				= 12,
	Key4				= 13,
	Key5				= 14,
	Key6				= 15,
	Key7				= 16,
	Key8				= 17,
	Key9				= 18,

	KeyA				= 38,
	KeyB				= 56,
	KeyC				= 54,
	KeyD				= 40,
	KeyE				= 26,
	KeyF				= 41,
	KeyG				= 42,
	KeyH				= 43,
	KeyI				= 31,
	KeyJ				= 44,
	KeyK				= 45,
	KeyL				= 46,
	KeyM				= 58,
	KeyN				= 57,
	KeyO				= 32,
	KeyP				= 33,
	KeyQ				= 24,
	KeyR				= 27,
	KeyS				= 39,
	KeyT				= 28,
	KeyU				= 30,
	KeyV				= 55,
	KeyW				= 25,
	KeyX				= 53,
	KeyY				= 29,
	KeyZ				= 52,

	KeyGrave			= 49,
	KeyMinus			= 20,
	KeyEqual			= 21,
	KeyBackspace		= 22,
	KeyLBracket			= 34,
	KeyRBracket			= 35,
	KeyBackslash		= 51,
	KeySemicolon		= 47,
	KeyQuote			= 48,
	KeyReturn			= 36,
	KeyComma			= 59,
	KeyPeriod			= 60,
	KeySlash			= 61,

	KeyLeft				= 113,
	KeyUp				= 111,
	KeyRight			= 114,
	KeyDown				= 116,

	KeyPrint			= 107,
	KeyPause			= 127,
	KeyInsert			= 118,
	KeyDelete			= 119,
	KeyHome				= 110,
	KeyEnd				= 115,
	KeyPageUp			= 112,
	KeyPageDown			= 117,

	KeyAdd				= 86,
	KeySubtract			= 82,
	KeyMultiply			= 63,
	KeyDivide			= 106,
	KeyDecimal			= 91,

	KeyNumpad0			= 90,
	KeyNumpad1			= 87,
	KeyNumpad2			= 88,
	KeyNumpad3			= 89,
	KeyNumpad4			= 83,
	KeyNumpad5			= 84,
	KeyNumpad6			= 85,
	KeyNumpad7			= 79,
	KeyNumpad8			= 80,
	KeyNumpad9			= 81,

	KeyCapsLock			= 66,
	KeyScrollLock		= 78,
	KeyNumLock			= 77,

#endif // ROBOT_OS_LINUX32
#ifdef ROBOT_OS_MAC32

	KeySpace			= 0x31,			// kVK_Space
	KeyEscape			= 0x35,			// kVK_Escape

	KeyTab				= 0x30,			// kVK_Tab
	KeyAlt				= 0x3A,			// kVK_Option
	KeyControl			= 0x3B,			// kVK_Control
	KeyShift			= 0x38,			// kVK_Shift
	KeySystem			= 0x37,			// kVK_Command
	KeyMenu				= 0x6E,

	KeyF1				= 0x7A,			// kVK_F1
	KeyF2				= 0x78,			// kVK_F2
	KeyF3				= 0x63,			// kVK_F3
	KeyF4				= 0x76,			// kVK_F4
	KeyF5				= 0x60,			// kVK_F5
	KeyF6				= 0x61,			// kVK_F6
	KeyF7				= 0x62,			// kVK_F7
	KeyF8				= 0x64,			// kVK_F8
	KeyF9				= 0x65,			// kVK_F9
	KeyF10				= 0x6D,			// kVK_F10
	KeyF11				= 0x67,			// kVK_F11
	KeyF12				= 0x6F,			// kVK_F12

	Key0				= 0x1D,			// kVK_ANSI_0
	Key1				= 0x12,			// kVK_ANSI_1
	Key2				= 0x13,			// kVK_ANSI_2
	Key3				= 0x14,			// kVK_ANSI_3
	Key4				= 0x15,			// kVK_ANSI_4
	Key5				= 0x17,			// kVK_ANSI_5
	Key6				= 0x16,			// kVK_ANSI_6
	Key7				= 0x1A,			// kVK_ANSI_7
	Key8				= 0x1C,			// kVK_ANSI_8
	Key9				= 0x19,			// kVK_ANSI_9

	KeyA				= 0x00,			// kVK_ANSI_A
	KeyB				= 0x0B,			// kVK_ANSI_B
	KeyC				= 0x08,			// kVK_ANSI_C
	KeyD				= 0x02,			// kVK_ANSI_D
	KeyE				= 0x0E,			// kVK_ANSI_E
	KeyF				= 0x03,			// kVK_ANSI_F
	KeyG				= 0x05,			// kVK_ANSI_G
	KeyH				= 0x04,			// kVK_ANSI_H
	KeyI				= 0x22,			// kVK_ANSI_I
	KeyJ				= 0x26,			// kVK_ANSI_J
	KeyK				= 0x28,			// kVK_ANSI_K
	KeyL				= 0x25,			// kVK_ANSI_L
	KeyM				= 0x2E,			// kVK_ANSI_M
	KeyN				= 0x2D,			// kVK_ANSI_N
	KeyO				= 0x1F,			// kVK_ANSI_O
	KeyP				= 0x23,			// kVK_ANSI_P
	KeyQ				= 0x0C,			// kVK_ANSI_Q
	KeyR				= 0x0F,			// kVK_ANSI_R
	KeyS				= 0x01,			// kVK_ANSI_S
	KeyT				= 0x11,			// kVK_ANSI_T
	KeyU				= 0x20,			// kVK_ANSI_U
	KeyV				= 0x09,			// kVK_ANSI_V
	KeyW				= 0x0D,			// kVK_ANSI_W
	KeyX				= 0x07,			// kVK_ANSI_X
	KeyY				= 0x10,			// kVK_ANSI_Y
	KeyZ				= 0x06,			// kVK_ANSI_Z

	KeyGrave			= 0x32,			// kVK_ANSI_Grave
	KeyMinus			= 0x1B,			// kVK_ANSI_Minus
	KeyEqual			= 0x18,			// kVK_ANSI_Equal
	KeyBackspace		= 0x33,			// kVK_Delete
	KeyLBracket			= 0x21,			// kVK_ANSI_LeftBracket
	KeyRBracket			= 0x1E,			// kVK_ANSI_RightBracket
	KeyBackslash		= 0x2A,			// kVK_ANSI_Backslash
	KeySemicolon		= 0x29,			// kVK_ANSI_Semicolon
	KeyQuote			= 0x27,			// kVK_ANSI_Quote
	KeyReturn			= 0x24,			// kVK_Return
	KeyComma			= 0x2B,			// kVK_ANSI_Comma
	KeyPeriod			= 0x2F,			// kVK_ANSI_Period
	KeySlash			= 0x2C,			// kVK_ANSI_Slash

	KeyLeft				= 0x7B,			// kVK_LeftArrow
	KeyUp				= 0x7E,			// kVK_UpArrow
	KeyRight			= 0x7C,			// kVK_RightArrow
	KeyDown				= 0x7D,			// kVK_DownArrow

	KeyPrint			= 0x69,			// kVK_F13
	KeyPause			= 0x6A,			// kVK_F16
	KeyInsert			= 0x72,			// kVK_Help
	KeyDelete			= 0x75,			// kVK_ForwardDelete
	KeyHome				= 0x73,			// kVK_Home
	KeyEnd				= 0x77,			// kVK_End
	KeyPageUp			= 0x74,			// kVK_PageUp
	KeyPageDown			= 0x79,			// kVK_PageDown

	KeyAdd				= 0x45,			// kVK_ANSI_KeypadPlus
	KeySubtract			= 0x4E,			// kVK_ANSI_KeypadMinus
	KeyMultiply			= 0x43,			// kVK_ANSI_KeypadMultiply
	KeyDivide			= 0x4B,			// kVK_ANSI_KeypadDivide
	KeyDecimal			= 0x41,			// kVK_ANSI_KeypadDecimal

	KeyNumpad0			= 0x52,			// kVK_ANSI_Keypad0
	KeyNumpad1			= 0x53,			// kVK_ANSI_Keypad1
	KeyNumpad2			= 0x54,			// kVK_ANSI_Keypad2
	KeyNumpad3			= 0x55,			// kVK_ANSI_Keypad3
	KeyNumpad4			= 0x56,			// kVK_ANSI_Keypad4
	KeyNumpad5			= 0x57,			// kVK_ANSI_Keypad5
	KeyNumpad6			= 0x58,			// kVK_ANSI_Keypad6
	KeyNumpad7			= 0x59,			// kVK_ANSI_Keypad7
	KeyNumpad8			= 0x5B,			// kVK_ANSI_Keypad8
	KeyNumpad9			= 0x5C,			// kVK_ANSI_Keypad9

	KeyCapsLock			= 0x39,			// kVK_CapsLock
	KeyScrollLock		= 0x71,			// kVK_F15
	KeyNumLock			= 0x47,			// kVK_ANSI_KeypadClear

#endif // ROBOT_OS_MAC32
#ifdef ROBOT_OS_WIN32

	KeySpace			= 0x20,			// VK_SPACE
	KeyEscape			= 0x1B,			// VK_ESCAPE

	KeyTab				= 0x09,			// VK_TAB
	KeyAlt				= 0x12,			// VK_MENU
	KeyControl			= 0x11,			// VK_CONTROL
	KeyShift			= 0x10,			// VK_SHIFT
	KeySystem			= 0x5B,			// VK_LWIN
	KeyMenu				= 0x5D,			// VK_APPS

	KeyF1				= 0x70,			// VK_F1
	KeyF2				= 0x71,			// VK_F2
	KeyF3				= 0x72,			// VK_F3
	KeyF4				= 0x73,			// VK_F4
	KeyF5				= 0x74,			// VK_F5
	KeyF6				= 0x75,			// VK_F6
	KeyF7				= 0x76,			// VK_F7
	KeyF8				= 0x77,			// VK_F8
	KeyF9				= 0x78,			// VK_F9
	KeyF10				= 0x79,			// VK_F10
	KeyF11				= 0x7A,			// VK_F11
	KeyF12				= 0x7B,			// VK_F12

	Key0				= 0x30,
	Key1				= 0x31,
	Key2				= 0x32,
	Key3				= 0x33,
	Key4				= 0x34,
	Key5				= 0x35,
	Key6				= 0x36,
	Key7				= 0x37,
	Key8				= 0x38,
	Key9				= 0x39,

	KeyA				= 0x41,
	KeyB				= 0x42,
	KeyC				= 0x43,
	KeyD				= 0x44,
	KeyE				= 0x45,
	KeyF				= 0x46,
	KeyG				= 0x47,
	KeyH				= 0x48,
	KeyI				= 0x49,
	KeyJ				= 0x4A,
	KeyK				= 0x4B,
	KeyL				= 0x4C,
	KeyM				= 0x4D,
	KeyN				= 0x4E,
	KeyO				= 0x4F,
	KeyP				= 0x50,
	KeyQ				= 0x51,
	KeyR				= 0x52,
	KeyS				= 0x53,
	KeyT				= 0x54,
	KeyU				= 0x55,
	KeyV				= 0x56,
	KeyW				= 0x57,
	KeyX				= 0x58,
	KeyY				= 0x59,
	KeyZ				= 0x5A,

	KeyGrave			= 0xC0,			// VK_OEM_3
	KeyMinus			= 0xBD,			// VK_OEM_MINUS
	KeyEqual			= 0xBB,			// VK_OEM_PLUS
	KeyBackspace		= 0x08,			// VK_BACK
	KeyLBracket			= 0xDB,			// VK_OEM_4
	KeyRBracket			= 0xDD,			// VK_OEM_6
	KeyBackslash		= 0xDC,			// VK_OEM_5
	KeySemicolon		= 0xBA,			// VK_OEM_1
	KeyQuote			= 0xDE,			// VK_OEM_7
	KeyReturn			= 0x0D,			// VK_RETURN
	KeyComma			= 0xBC,			// VK_OEM_COMMA
	KeyPeriod			= 0xBE,			// VK_OEM_PERIOD
	KeySlash			= 0xBF,			// VK_OEM_2

	KeyLeft				= 0x25,			// VK_LEFT
	KeyUp				= 0x26,			// VK_UP
	KeyRight			= 0x27,			// VK_RIGHT
	KeyDown				= 0x28,			// VK_DOWN

	KeyPrint			= 0x2C,			// VK_SNAPSHOT
	KeyPause			= 0x13,			// VK_PAUSE
	KeyInsert			= 0x2D,			// VK_INSERT
	KeyDelete			= 0x2E,			// VK_DELETE
	KeyHome				= 0x24,			// VK_HOME
	KeyEnd				= 0x23,			// VK_END
	KeyPageUp			= 0x21,			// VK_PRIOR
	KeyPageDown			= 0x22,			// VK_NEXT

	KeyAdd				= 0x6B,			// VK_ADD
	KeySubtract			= 0x6D,			// VK_SUBTRACT
	KeyMultiply			= 0x6A,			// VK_MULTIPLY
	KeyDivide			= 0x6F,			// VK_DIVIDE
	KeyDecimal			= 0x6E,			// VK_DECIMAL

	KeyNumpad0			= 0x60,			// VK_NUMPAD0
	KeyNumpad1			= 0x61,			// VK_NUMPAD1
	KeyNumpad2			= 0x62,			// VK_NUMPAD2
	KeyNumpad3			= 0x63,			// VK_NUMPAD3
	KeyNumpad4			= 0x64,			// VK_NUMPAD4
	KeyNumpad5			= 0x65,			// VK_NUMPAD5
	KeyNumpad6			= 0x66,			// VK_NUMPAD6
	KeyNumpad7			= 0x67,			// VK_NUMPAD7
	KeyNumpad8			= 0x68,			// VK_NUMPAD8
	KeyNumpad9			= 0x69,			// VK_NUMPAD9

	KeyCapsLock			= 0x14,			// VK_CAPITAL
	KeyScrollLock		= 0x91,			// VK_SCROLL
	KeyNumLock			= 0x90,			// VK_NUMLOCK

#endif // ROBOT_OS_WIN32
};

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>
/// <copying> Atomic </copying>

class ROBOT_EXPORT Keyboard
{
public:
	// Constructors
	Keyboard							(void);

public:
	// Functions
	bool				Click			(const char* keys) const;
	bool				Press			(const char* keys) const;
	bool				Release			(const char* keys) const;

	void				Click			(Keycode key) const;
	void				Press			(Keycode key) const;
	void				Release			(Keycode key) const;

	// TODO: Key state

public:
	// Properties
	Range				AutoDelay;		// Auto delay range
};

} // namespace Robot
#endif // ROBOT_KEYBOARD_H
