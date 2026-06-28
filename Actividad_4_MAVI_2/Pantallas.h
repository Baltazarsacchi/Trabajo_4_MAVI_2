#ifndef PANTALLAS_H
#define PANTALLAS_H

#include "raylib.h"

class Pantallas {

private:

	Texture2D textura;

public:
	
	Pantallas(Texture2D tex);
	void Inicio();
	void Juego();
	void Final(bool final);

};

#endif