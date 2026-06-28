#include "Enemigo.h"
#include "Proyectiles.h"
#include "box2d.h"
#include "raylib.h"

Enemigo::Enemigo(b2World& mundo, b2Vec2 pos, b2Vec2 tam, Texture2D tex,Texture2D tex_2) {

	posicion = pos;
	tamano = tam;

	direccion = 1;
	vida = 10;

	textura = tex;
	textura_2 = tex_2;

	tipo = Enemigos;

	b2BodyDef cuerpoDef;
	cuerpoDef.type =  b2_dynamicBody;
	cuerpoDef.position.Set(posicion.x / Diferencia, posicion.y / Diferencia);
	cuerpo = mundo.CreateBody(&cuerpoDef);

	b2PolygonShape cuerpoShape;
	cuerpoShape.SetAsBox((tamano.x / 2.0f) / Diferencia, (tamano.y / 2.0f) / Diferencia);

	b2FixtureDef cuerpoFixture;
	cuerpoFixture.shape = &cuerpoShape;
	cuerpoFixture.density = 0.8f;
	cuerpoFixture.friction = 0.5f;
	cuerpoFixture.restitution = 0.0f;
	cuerpo->CreateFixture(&cuerpoFixture);
	cuerpo->GetUserData().pointer = (uintptr_t)this;
	cuerpo->SetLinearVelocity(b2Vec2(5.0f,0.0f));
}

void Enemigo::actualizacion() {

	b2Vec2 vel = cuerpo->GetLinearVelocity();
	vel.y = 0; 
	cuerpo->SetLinearVelocity(vel);

	if (cuerpo->GetPosition().x >= 7.25f) {
		joint->SetMotorSpeed(-2.0f);
	}
	if (cuerpo->GetPosition().x <= 0.75f) {
		joint->SetMotorSpeed(2.0f);
	}
	

}
void Enemigo::dibujar() {

	b2Vec2 pos = cuerpo->GetPosition();
	
	Rectangle source = { 0, 0,(float)textura.width + 5.0f,(float)textura.height + 5.0f };

	Rectangle dest = { pos.x*Diferencia ,pos.y *Diferencia,tamano.x ,tamano.y};

	Vector2 origin = { tamano.x / 2.0f,tamano.y / 2.0f };

	DrawTexturePro(textura, source, dest, origin, 0.0f, WHITE);

	for (auto* Proyectil : proyectil) {
		Proyectil->dibujar();
	}

	for (int i = 1; i <= vida; i++) {
		float x = (30.0f * i)+100;
		DrawRectangle(x, 5.0f, 30.0f, 10.0f, RED);
	}

}

Proyectiles* Enemigo::disparo(b2World& mundo) {

	b2Vec2 posDisparo = cuerpo->GetPosition();
	posDisparo.x += 0.1f;
	posDisparo.y += 0.20f;

	Proyectiles* proyectil = new Proyectiles(mundo, posDisparo, tamano, Em, 0.1f,textura_2);

	return proyectil;
}

void Enemigo::conexion(b2World& mundo, b2Body* cuerpo_2) {

	b2PrismaticJointDef jointDef;

	jointDef.Initialize(cuerpo_2, cuerpo, cuerpo->GetWorldCenter(), b2Vec2(1.0f, 0.0f));

	jointDef.collideConnected = false;

	jointDef.enableLimit = true;
	jointDef.lowerTranslation = -5.0f;
	jointDef.upperTranslation = 5.0f;

	jointDef.enableMotor = true;
	jointDef.motorSpeed =  2.0f;
	jointDef.maxMotorForce = 1000.0f;


	joint = (b2PrismaticJoint*)mundo.CreateJoint(&jointDef);

}

void Enemigo::colision(Cuerpos* otro) {


	if (otro->tipo == Proyectil ) {

		Proyectiles* paso =(Proyectiles*) otro;

		if(paso->mando == Pj){

			vida -= 1;

		}

	}
	
}

bool Enemigo::vivo() {


	return vida > 0;
}

void Enemigo::reinicio() {

	vida = 10;
}