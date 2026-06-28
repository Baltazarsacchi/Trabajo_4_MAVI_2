#include "raylib.h"
#include "box2d.h"
#include "Objetos.h"
#include "Jugador.h"
#include "Enemigo.h"
#include "Contacto.h"
#include "Pantallas.h"


int main() {

	float ancho = 800, alto = 600;
	int indice = -1;
	float tiempo_1 = 0.5f,tiempo_2 = 0.0f;
	bool pantalla_1 = true, pantalla_2 = false, pantalla_3 = false;
	bool gano,sonido;

	InitWindow(ancho, alto, "Actividad 4 de MAVI 2");
	InitAudioDevice();

	Texture2D pj = LoadTexture("textura/personaje.png");
	Texture2D en = LoadTexture("textura/enemigo.png");
	Texture2D disparo_1 = LoadTexture("textura/disparo_1.png");
	Texture2D disparo_2 = LoadTexture("textura/disparo_2.png");
	Texture2D fondo = LoadTexture("textura/fondo.png");

	Sound golpe = LoadSound("sonidos/golpe.mp3");
	Sound gana = LoadSound("sonidos/gana.mp3");
	Sound pierde = LoadSound("sonidos/pierde.mp3");

	b2World mundo(b2Vec2(0.0f, 9.81f));

	Contacto contacto;
	mundo.SetContactListener(& contacto);

	Objetos piso, pared_1, pared_2, techo, ancla;
	Jugador jugador(mundo, b2Vec2(300.0f, 525.0f), b2Vec2(25.0f, 25.0f),pj,disparo_1);
	Enemigo enemigo(mundo, b2Vec2(300.0f, 50.0f), b2Vec2(50.0f, 50.0f),en,disparo_2);

	Pantallas pantalla(fondo);

	vector<Proyectiles*> proyectil_jugador;
	vector<Proyectiles*> proyectil_enemigo;

	piso.crear_objetos(mundo, b2Vec2(400.0f, 575.0f), b2Vec2(775.0f, 25.0f), true, GRAY);
	techo.crear_objetos(mundo, b2Vec2(400.0f, 0.0f), b2Vec2(775.0f, 25.0f), true, GRAY);
	pared_1.crear_objetos(mundo, b2Vec2(775.0f, 275.0f), b2Vec2(25.0f, 575.0f), true, GRAY);
	pared_2.crear_objetos(mundo, b2Vec2(25.0f, 275.0f), b2Vec2(25.0f, 575.0f), true, GRAY);

	ancla.crear_objetos(mundo, b2Vec2(400.0f, 50.0f), b2Vec2(10.0f, 10.0f), true, GRAY);

	enemigo.conexion(mundo, ancla.obtenerCuerpo());

	SetTargetFPS(60);
	while (!WindowShouldClose()) {

		mundo.Step(1.0f / 60.0f, 6, 2);

		if (pantalla_1) {
			
			BeginDrawing();
			ClearBackground(BLACK);
			
			pantalla.Inicio();
			
			EndDrawing();
			
			if (IsKeyPressed(KEY_ENTER)) {

				pantalla_1 = false;
				pantalla_2 = true;
			}

		}

		if(pantalla_2){
		
			sonido = true;
			tiempo_1 += GetFrameTime();
			tiempo_2 += GetFrameTime();

			if (IsKeyPressed(KEY_SPACE) && tiempo_1>=0.5f) {
			
				proyectil_jugador.push_back(jugador.disparo(mundo));
				tiempo_1 = 0.0f;
		
			}
		
			for (auto* p : proyectil_jugador) {
			
				p->actualizacion();
		    }

			if (tiempo_2 >= 3.5f) {
				proyectil_enemigo.push_back(enemigo.disparo(mundo));

				tiempo_2 = 0.0f;
			}
			
			if (!proyectil_enemigo.empty()) {
			
				for (auto* p : proyectil_enemigo) {

					p->actualizacion();
				}

			}

		    jugador.actualizacion();

		    for (int i = 0; i < proyectil_jugador.size(); i++) {

			    if (proyectil_jugador[i]->destruccion) {
					PlaySound(golpe);
				
					mundo.DestroyBody(proyectil_jugador[i]->obtenerCuerpo());
				    delete proyectil_jugador[i];

				    proyectil_jugador.erase(proyectil_jugador.begin() + i);
				    i--;
			    }
		    }
			for (int i = 0; i < proyectil_enemigo.size(); i++) {

				if (proyectil_enemigo[i]->destruccion) {


					mundo.DestroyBody(proyectil_enemigo[i]->obtenerCuerpo());
					delete proyectil_enemigo[i];

					proyectil_enemigo.erase(proyectil_enemigo.begin() + i);
					i--;
				}
			}

		    enemigo.actualizacion();


			if (!jugador.vivo()) {
				pantalla_2 = false;
				pantalla_3 = true;
				gano = false;
			}
			
			if (!enemigo.vivo()) {
				
				pantalla_2 = false;
				pantalla_3 = true;
				gano = true;

			}
 
		    BeginDrawing();
		    ClearBackground(BLACK);
			pantalla.Juego();
		    piso.dibujar();
		    techo.dibujar();
		    pared_1.dibujar();
		    pared_2.dibujar();

	    	enemigo.dibujar();
		    
			for (auto* p : proyectil_jugador) {
			
				p->dibujar();
		    }
			for (auto* p : proyectil_enemigo) {

				p->dibujar();
			}

		    jugador.dibujar();

		    EndDrawing();
	    }

		if (pantalla_3) {
			
			BeginDrawing();
			ClearBackground(WHITE);
			
			pantalla.Final(gano);
			
			EndDrawing();
			
			if (sonido && gano) {

				PlaySound(gana);
				sonido = false;
			}
			if (sonido && !gano) {

				PlaySound(pierde);
				sonido = false;
			}

			if (IsKeyPressed(KEY_R)) {


				proyectil_enemigo.clear();
				proyectil_jugador.clear();
				jugador.reinicio();
				enemigo.reinicio();
				pantalla_2 = true;
				pantalla_3 = false;
			}

		}

	}

	UnloadTexture(pj);
	UnloadTexture(en);
	UnloadTexture(disparo_1);
	UnloadTexture(disparo_2);
	UnloadTexture(fondo);
	return 0;
}