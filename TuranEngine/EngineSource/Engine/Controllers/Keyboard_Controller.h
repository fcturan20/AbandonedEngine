#pragma once
#include "Engine_Includes.h"

enum ENGINE KEYBOARD_KEYs : unsigned char {
	KEYBOARD_W = 0,
	KEYBOARD_S = 1,
	KEYBOARD_A = 2,
	KEYBOARD_D = 3,
	KEYBOARD_NP_2 = 4,
	KEYBOARD_NP_4 = 5,
	KEYBOARD_NP_6 = 6,
	KEYBOARD_NP_8 = 7,
	KEYBOARD_C = 8
};

/*To define a Keyboard Key to TuranEngine, you should do these:
1) Add an enum piece to KEYBOARD_KEYs, this means you specified an ID for your new key!
2) You should add the new ID to Keyboard_Controller class in default constructor, like below:
	 ALL_KEYs.push_back([KEYBOARD_KEYs id specified at first step!]); IS_KEY_PRESSSED.push_back(false);
3) You should do GFX_API specific Key_Input handling API operations in responding GFX_API's ENUMs header
For example: Go to OGL3_ENUMs, inspect the 2 Convert_Key functions! And add a key type to GLFW by GLFW's specifications!
//Note: Most complex part is third step, because you should deal with third party Input API (For example: GLFW) and add a new key input to its environment!
//Note: You shouldn't forget to specify a Take_Inputs() in GFX_API specific class! See an example implementation in OGL3_Core->Take_Inputs();

	 KEY is added to all TuranEngine! 
*/
class ENGINE Keyboard_Controller {
	static vector<KEYBOARD_KEYs> ALL_KEYs;
	static vector<bool> IS_KEY_PRESSED;

	static unsigned int Get_KEY_vectorindex(KEYBOARD_KEYs KEY);

public:
	//Don't forget to push back a IS_KEY_PRESSED, after ALL_KEYs.push_back()!
	Keyboard_Controller();

	static void Set_Key_is_Pressed(KEYBOARD_KEYs KEY, bool is_Key_Pressed);

	static vector<KEYBOARD_KEYs> Return_ALL_Keys();

	static bool Is_Key_Pressed(KEYBOARD_KEYs KEY);
};