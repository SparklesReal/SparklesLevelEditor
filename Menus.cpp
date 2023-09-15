#include <raylib.h>
#include <string>

#include "Main.hpp"
#include "Menus.hpp"

Program programdata;

void Menus::mainMenu() {
	Camera2D camera{ 0 };
	camera.target = Vector2{ float(GetScreenWidth()) / 2, float(GetScreenHeight()) / 2 };
	camera.offset = Vector2{ float(GetScreenWidth()) / 2, float(GetScreenHeight()) / 2 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	while (!WindowShouldClose()) {
		ClearBackground(BLACK);
		BeginDrawing();

		DrawText(programdata.ver, GetScreenWidth() / 2 - MeasureText(programdata.ver, 150) / 2, 0, 150, RAYWHITE);

		Rectangle startButtonRect{ GetScreenWidth() / 2 - 200, 400, 400, 100 };
		DrawRectangleRec(startButtonRect, RAYWHITE);
		DrawText("Start", startButtonRect.x + startButtonRect.width / 2 - MeasureText("Start", 100) / 2, startButtonRect.y + startButtonRect.height / 2 - 100 / 2, 100, DARKGRAY);
		if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), startButtonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			return;
		}


		EndDrawing();
	}
	return;
}

void Menus::startMenu() {
	Camera2D camera{ 0 };
	camera.target = Vector2{ float(GetScreenWidth()) / 2, float(GetScreenHeight()) / 2 };
	camera.offset = Vector2{ float(GetScreenWidth()) / 2, float(GetScreenHeight()) / 2 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	std::string texutreSizeText = "Texture Size";
	std::string inputSize = " ";
	int keyboardInput = 0;
	while (!WindowShouldClose()) {
		ClearBackground(BLACK);
		BeginDrawing();

		DrawText(programdata.ver, GetScreenWidth() / 2 - MeasureText(programdata.ver, 150) / 2, 0, 150, RAYWHITE);

		if (inputSize != " ")
			texutreSizeText = inputSize;
		else
			texutreSizeText = "Texture Size";

		Rectangle textureSizeRect{ GetScreenWidth() / 2 - 200, 400, 400, 100 };
		keyboardInput = GetCharPressed();
		if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), textureSizeRect) &&
			MeasureText(inputSize.c_str(), 25) < textureSizeRect.width &&
			keyboardInput != 0)
			inputSize += (char(keyboardInput));

		DrawRectangleRec(textureSizeRect, RAYWHITE);
		DrawText(texutreSizeText.c_str(), textureSizeRect.x + textureSizeRect.width / 2 - MeasureText(texutreSizeText.c_str(), 25) / 2, textureSizeRect.y + textureSizeRect.height / 2 - 25 / 2, 25, DARKGRAY);

		Rectangle createButtonRect{ GetScreenWidth() / 2 - 200, 800, 400, 100 };
		DrawRectangleRec(createButtonRect, RAYWHITE);
		DrawText("Create", createButtonRect.x + createButtonRect.width / 2 - MeasureText("Create", 25) / 2, createButtonRect.y + createButtonRect.height / 2 - 25 / 2, 25, DARKGRAY);
		if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), createButtonRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			editorGrid.Size = stoi(inputSize);
			return;
		}
		EndDrawing();
	}
	return;
}