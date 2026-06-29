#include "raylib.h"
#include "box2d.h"
#include "Objetos.h"
#include "Jugador.h"
#include "Enemigo.h"
#include "Contacto.h"
#include "Pantallas.h"


int main() {

	float ancho = 800, alto = 600;
	
	float tiempo_1 = 0.5f,tiempo_2 = 0.0f;//Variables de control para los proyectiles
	bool pantalla_1 = true, pantalla_2 = false, pantalla_3 = false;//Valores banderas para las pantallas
	bool gano,sonido;//Valores banderas 

    //Inicializacion de la pantalla y el sonido.
	
	InitWindow(ancho, alto, "Actividad 4 de MAVI 2");
	InitAudioDevice();

    //Carga de Texturas y Sonidos
	
	Texture2D pj = LoadTexture("textura/personaje.png");
	Texture2D en = LoadTexture("textura/enemigo.png");
	Texture2D disparo_1 = LoadTexture("textura/disparo_1.png");
	Texture2D disparo_2 = LoadTexture("textura/disparo_2.png");
	Texture2D fondo = LoadTexture("textura/fondo.png");

	Sound golpe = LoadSound("sonidos/golpe.mp3");
	Sound gana = LoadSound("sonidos/gana.mp3");
	Sound pierde = LoadSound("sonidos/pierde.mp3");

    //Creaccion del mundo y los objetos dentro del el
	
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

		mundo.Step(1.0f / 60.0f, 6, 2);//La actualizacion del mundo

		if (pantalla_1) {//Pantalla de inicio
			
			BeginDrawing();
			ClearBackground(BLACK);
			
			pantalla.Inicio();
			
			EndDrawing();
			
			if (IsKeyPressed(KEY_ENTER)) {//Si pulsa el usario enter el juego comienza

				pantalla_1 = false;
				pantalla_2 = true;
			}

		}

		if(pantalla_2){//Pantalla de juego

			//Sonido se vuelve true para luego utilizarla en la pantalla final, el tiempo_1 y tiempo_2 son los que le dan un tiempo de demora a los proyectiles
			sonido = true;
			tiempo_1 += GetFrameTime();
			tiempo_2 += GetFrameTime();

			if (IsKeyPressed(KEY_SPACE) && tiempo_1>=0.5f) {//El usuario crea su proyectil
			
				proyectil_jugador.push_back(jugador.disparo(mundo));//Se crea y se almacena en un vector
				tiempo_1 = 0.0f;//Comienza la demora
		
			}
		
			for (auto* p : proyectil_jugador) {//Se mueve el proyectil del usuario
			
				p->actualizacion();
		    }

			if (tiempo_2 >= 3.5f) {//Cada vez que se cumple esa condicion el Enemigo crea su proyectil
				proyectil_enemigo.push_back(enemigo.disparo(mundo));

				tiempo_2 = 0.0f;
			}
			
			if (!proyectil_enemigo.empty()) {//Verifica que el vector no este vacio 
			
				for (auto* p : proyectil_enemigo) {//Hace que el proyectil enemigo se mueva

					p->actualizacion();
				}

			}

		    jugador.actualizacion();//Permite que el jugador se mueva

		    for (int i = 0; i < proyectil_jugador.size(); i++) {//Chequea cual de todos los proyectiles del jugador colisono

			    if (proyectil_jugador[i]->destruccion) {//Si colisono suena un sonido, los destruyen del mundo y lo eliminan del vector
					PlaySound(golpe);
				
					mundo.DestroyBody(proyectil_jugador[i]->obtenerCuerpo());
				    delete proyectil_jugador[i];

				    proyectil_jugador.erase(proyectil_jugador.begin() + i);
				    i--;
			    }
		    }
			for (int i = 0; i < proyectil_enemigo.size(); i++) {//Chequea cual de todos los proyectiles del enemigo colisono

				if (proyectil_enemigo[i]->destruccion) {//Si colisono lo destruyen del mundo y lo eliminan del vector


					mundo.DestroyBody(proyectil_enemigo[i]->obtenerCuerpo());
					delete proyectil_enemigo[i];

					proyectil_enemigo.erase(proyectil_enemigo.begin() + i);
					i--;
				}
			}

		    enemigo.actualizacion();//Actualiza el movimiento del enemigo


			if (!jugador.vivo()) {//Si el jugador muere, Pierde
				pantalla_2 = false;
				pantalla_3 = true;
				gano = false;
			}
			
			if (!enemigo.vivo()) {//Si el enemigo muere, Gana
				
				pantalla_2 = false;
				pantalla_3 = true;
				gano = true;

			}
 
		    BeginDrawing();
		    ClearBackground(BLACK);
			//Dibujos de pantallas del juego, estructuras, enemigo, proyectiles y jugador
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

		if (pantalla_3) {//Pantalla de victoria o derrota
			
			BeginDrawing();
			ClearBackground(WHITE);
			
			pantalla.Final(gano);//Segun el valor de gano muestra una pantalla
			
			EndDrawing();
			
			if (sonido && gano) {//Suena un sonido si gano

				PlaySound(gana);
				sonido = false;
			}
			if (sonido && !gano) {//Suena un sonido si perdio

				PlaySound(pierde);
				sonido = false;
			}

			if (IsKeyPressed(KEY_R)) {// SI presicona R reinicia el juego


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
