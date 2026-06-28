#include "Jugador.h"
#include "box2d.h"
#include "raylib.h"
#include <vector>
#include "Cuerpos.h"


Jugador::Jugador(b2World& mundo, b2Vec2 pos, b2Vec2 tam,Texture2D base,Texture2D arma) {
	
	textura_1 = base;
	textura_2 = arma;

	posicion = pos;
	tamano = tam;

	tipo = Personaje;

	b2BodyDef cuerpoDef;
	cuerpoDef.type = b2_dynamicBody;
	cuerpoDef.position.Set(posicion.x / Escala, posicion.y / Escala);
	cuerpo = mundo.CreateBody(&cuerpoDef);

	b2PolygonShape cuerpoShape;
	cuerpoShape.SetAsBox((tamano.x / 2.0f) / Escala, (tamano.y / 2.0f) / Escala);
	
	b2FixtureDef cuerpoFixture;
	cuerpoFixture.shape = &cuerpoShape;
	cuerpoFixture.density = 1.8f;
	cuerpoFixture.friction = 0.5f;
	cuerpoFixture.restitution = 0.0f;
	cuerpo->CreateFixture(&cuerpoFixture);
	
	cuerpo->GetUserData().pointer = (uintptr_t)this;

}

void Jugador::actualizacion() {

	b2Vec2 velocidad = cuerpo->GetLinearVelocity();

	if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && velocidad.x<= 5.0f ) {


		cuerpo->ApplyForceToCenter(b2Vec2(1.0f, 0.0f), true);

	}
	else if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && velocidad.x >= -5.0f) {



		cuerpo->ApplyForceToCenter(b2Vec2(-1.0f, 0.0f), true);


	}
	
	
}

void Jugador::dibujar() {

	b2Vec2 pos = cuerpo->GetPosition();
	
	Rectangle source = {0, 0,(float)textura_1.width+5.0f,(float)textura_1.height+5.0f};

	Rectangle dest = {pos.x * Escala,pos.y  * Escala,tamano.x+10.0f,tamano.y+10.0f};

	Vector2 origin = {tamano.x/ 2.0f,tamano.y / 2.0f};

	DrawTexturePro(textura_1, source, dest, origin, 0.0f, WHITE);

	for (auto* Proyectil : proyectil) {
		Proyectil->dibujar();
	}

	DrawText(TextFormat("Vidas : %.0f", (float)vidas), 750.0f, 10.0f, 7.5f, BLACK);
}

void Jugador::reinicio() {

	cuerpo->SetTransform(b2Vec2(posicion.x/Escala,posicion.y/Escala), 0.0f);
	cuerpo->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	vidas = 3;

}
bool Jugador::vivo() {

	return vidas > 0;
}
Proyectiles* Jugador::disparo(b2World& mundo) {

	b2Vec2 posDisparo = cuerpo->GetPosition();
	posDisparo.x += 0.1f;
	posDisparo.y-=0.15f;

	Proyectiles* proyectil = new Proyectiles(mundo, posDisparo, tamano, Pj,-1.0f,textura_2);

	return proyectil;
}

void Jugador::colision(Cuerpos* otro) {

	if (otro->tipo == Proyectil) {

		Proyectiles* guia = (Proyectiles*)otro;
	
		if (guia->mando == Em) {
			vidas--;
		}
	}
	
}