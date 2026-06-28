#include "Objetos.h"
#include "raylib.h"
#include "box2d.h"
#include "Cuerpos.h"

void Objetos::crear_objetos(b2World& world, b2Vec2 pos, b2Vec2 tam, bool esEstatico, Color col) {//Definición de la función para crear objetos en el mundo Box2D

	posicion = pos;
	color = col;
	tamano = tam;

	estado = esEstatico;

	tipo = Estructura;
	
	b2BodyDef cuerpoDef;
	cuerpoDef.type = estado ? b2_staticBody : b2_dynamicBody;//Dependiendo de si el objeto es estático o dinámico, se define el tipo de cuerpo
	cuerpoDef.position.Set(posicion.x/ESCALE, posicion.y/ESCALE);
	cuerpo = world.CreateBody(&cuerpoDef);

	b2PolygonShape cuerpoShape;
	cuerpoShape.SetAsBox((tamano.x/2.0f)/ESCALE, (tamano.y/2.0f)/ESCALE);

	b2FixtureDef cuerpoFixture;
	cuerpoFixture.shape = &cuerpoShape;
	cuerpoFixture.density = 0.8f;
	cuerpoFixture.friction = 0.5f;
	cuerpoFixture.restitution = 0.0f;
	cuerpo->CreateFixture(&cuerpoFixture);
	cuerpo->GetUserData().pointer = (uintptr_t)this;
    
}

void Objetos::dibujar() {//Función para dibujar los objetos en la pantalla utilizando Raylib

	b2Vec2 posJugador = cuerpo->GetPosition();
	float angle = cuerpo->GetAngle();
	float ancho = tamano.x ;
	float alto = tamano.y;

	DrawRectanglePro(Rectangle{ posJugador.x * ESCALE, posJugador.y* ESCALE, ancho, alto}, Vector2{ ancho/2.0f, alto /2.0f}, angle * RAD2DEG, color);

}

b2Vec2 Objetos::obtenerPosicionX() {//Función para obtener la posición del objeto en el eje X
	return cuerpo->GetPosition();
}
float Objetos::angulo() {//Función para obtener el ángulo del objeto

	return cuerpo->GetAngle() * RAD2DEG;
}

void Objetos::reiniciarPosicion() {//Funcion para reiniciar la posición del objeto a su posición inicial
	cuerpo->SetTransform(posicion, 0.0f);
	cuerpo->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	cuerpo->SetAngularVelocity(0.0f);
}

b2Body* Objetos::Obtener_cuerpo() {

	return cuerpo;
}