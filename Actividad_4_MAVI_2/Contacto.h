#ifndef CONTACTO_H
#define CONTACTO_H
#include "box2d.h"

class Contacto : public b2ContactListener {//clase que sirve para la deteccion de contactos.
public:
    void BeginContact(b2Contact* contacto) override;
};



#endif // !CONTACTO_H

