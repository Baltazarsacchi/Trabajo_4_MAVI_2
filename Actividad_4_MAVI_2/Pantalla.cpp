#include "Pantallas.h"
#include "raylib.h"

Pantallas::Pantallas(Texture2D tex) {

	textura = tex;
}
void Pantallas::Inicio() {

	DrawTexture(textura, 0.0f, 0.0f, WHITE);
	DrawText("Actividad 4 de Mavi 2", 250, 250, 25.0f, GREEN);
	DrawText("Pulsa Enter para iniciar ", 250.0f, 275.0f, 10.0f, WHITE);
	DrawText("Controles : ",  210.0f, 310.0f, 10.0f, WHITE);
	DrawText("Movimiento : 'A' y 'D'", 225.0f,  335.0f, 2.0f, WHITE);
	DrawText("Disparo : 'Espacio'", 225.0f, 360.0f, 2.0f, WHITE);
	DrawText("Objetivo : ", 410.0f, 300.0f, 10.0f, WHITE);
	DrawText("Derrotar a tu enemigo ", 410.0f, 315.0f, 10.0f, WHITE);

}

void Pantallas::Juego() {

	DrawTexture(textura, 0.0f, 0.0f, WHITE);
} 
void Pantallas::Final(bool condicion){

	if (!condicion) {
		DrawTexture(textura, 0.0f, 0.0f, WHITE);
		DrawText("Perdiste", 275, 250, 25.0f, RED);
		DrawText("Pulsa R para reiniciar", 300.0f, 275.0f, 10.0f, WHITE);
	}
	else {
		DrawTexture(textura, 0.0f, 0.0f, WHITE);
		DrawText("Ganaste", 275, 250, 25.0f, GREEN);
		DrawText("Pulsa R para reiniciar", 300.0f, 275.0f, 10.0f, WHITE);

	}

}
