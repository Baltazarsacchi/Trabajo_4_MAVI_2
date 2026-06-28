#include "Contacto.h"
#include "box2d.h"
#include "Cuerpos.h"

void Contacto::BeginContact(b2Contact* contacto) {

	Cuerpos* a = (Cuerpos*)contacto->GetFixtureA()->GetBody()->GetUserData().pointer;
	Cuerpos* b = (Cuerpos*)contacto->GetFixtureB()->GetBody()->GetUserData().pointer;

	if (!a || !b) { return; }

	Cuerpos* cuerpo_1 = reinterpret_cast<Cuerpos*>(a);
	Cuerpos* cuerpo_2 = reinterpret_cast<Cuerpos*>(b);

	if (!cuerpo_1 || !cuerpo_2) return;

	cuerpo_1->colision(cuerpo_2);
	cuerpo_2->colision(cuerpo_1);
}