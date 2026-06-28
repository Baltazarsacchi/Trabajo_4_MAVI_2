#include "Contacto.h"
#include "box2d.h"
#include "Cuerpos.h"

void Contacto::BeginContact(b2Contact* contacto) {//Deteccion de cuando comienza el contacto

	Cuerpos* a = (Cuerpos*)contacto->GetFixtureA()->GetBody()->GetUserData().pointer;//Almacena en un puntero de cuerpo a ambos objetos
	Cuerpos* b = (Cuerpos*)contacto->GetFixtureB()->GetBody()->GetUserData().pointer;

	if (!a || !b) { return; }//Verifico que si existan

	Cuerpos* cuerpo_1 = reinterpret_cast<Cuerpos*>(a);//Hago que lo reinterprete a ambos valores para corroborar que no haya una falla
	Cuerpos* cuerpo_2 = reinterpret_cast<Cuerpos*>(b);

	if (!cuerpo_1 || !cuerpo_2) return;

	cuerpo_1->colision(cuerpo_2);//Detecta si uno de los dos objetos colision con el otro
	cuerpo_2->colision(cuerpo_1);
}
