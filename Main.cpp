#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include <raymath.h>

#include "Functions.hpp"
#include "Main.hpp"
#include "Menus.hpp"

Functions programFunctions;
Menus programMenus;
Grid editorGrid = Grid();

int main() {
	InitWindow(GetScreenWidth(), GetScreenWidth(), "Sparkles Level Editor - v0.1 - Build 230914");
	//ToggleFullscreen();
	SetTargetFPS(30);

	Texture2D textures[10]{
	};

	for (int i = 0; i < 10; ++i) {
		textures[i] = LoadTexture((std::string("./textures/") + std::to_string(i) + ".png").c_str());
	}

	int textureSelected = 0;
	
	Camera2D camera = { 0 };
	camera.target = Vector2{ float(GetScreenWidth()) / 2, float(GetScreenHeight()) / 2 };
	camera.offset = Vector2{ float(GetScreenWidth()) / 2, float(GetScreenHeight()) / 2 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	programMenus.mainMenu();
	programMenus.startMenu();

	std::vector <gridCell> gridCells;
	gridCells = programFunctions.createGrid(editorGrid.Size, editorGrid.Width, editorGrid.Height);

	while (!WindowShouldClose()) {
		ClearBackground(BLACK);
		BeginDrawing();
		textureSelected = programFunctions.keyboardToCurrentTexture(textureSelected);
		DrawTexture(textures[textureSelected], 0, 0, RAYWHITE);
		BeginMode2D(camera);
		camera = programFunctions.updateCamera(camera);

		for (int i = 0; i < editorGrid.Width * editorGrid.Height; ++i) {
			if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), gridCells[i].rect))
				gridCells[i] = programFunctions.onCellCollision(textures[textureSelected], gridCells[i]);
		}

		programFunctions.drawGrid(editorGrid.Width, editorGrid.Height, gridCells);

		EndMode2D();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}