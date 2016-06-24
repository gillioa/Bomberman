#include "myInput.hh"


char myInput::getKey(gdl::Input &input) {
	char codeStart = SDLK_a - 1;
	char codeEnd = SDLK_z;

	while (codeStart != codeEnd) {
		codeStart++;
		if (input.getKey(codeStart, true))
			return codeStart;
	}
	return -1;
}
