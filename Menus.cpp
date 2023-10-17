#include <raylib.h>
#include <string>

#include "Main.hpp"
#include "Menus.hpp"
#include "Functions.hpp"

Program programdata;

int Menus::mainMenu() {
	Camera2D camera = programFunctions.createCamera();

	while (!WindowShouldClose()) {
		ClearBackground(BLACK);
		BeginDrawing();

		programFunctions.drawTextCenter(programdata.ver, 0, 150);

		Rectangle startButtonRect{ GetScreenWidth() / 2 - 200, 400, 400, 100 };
		DrawRectangleRec(startButtonRect, RAYWHITE);
		programFunctions.drawStringCenterRect("Start", 100, startButtonRect);
		if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), startButtonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			return 0;
		}


		EndDrawing();
	}
	return 1;
}

int Menus::startMenu() {
	Camera2D camera = programFunctions.createCamera();

	std::string texutreSizeText = "Texture Size";
	std::string inputSize = " ";
	int keyboardInput = 0;
	while (!WindowShouldClose()) {
		ClearBackground(BLACK);
		BeginDrawing();

		programFunctions.drawTextCenter(programdata.ver, 0, 150);

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
		programFunctions.drawStringCenterRect(texutreSizeText, 25, textureSizeRect);

		Rectangle createButtonRect{ GetScreenWidth() / 2 - 200, 800, 400, 100 };
		DrawRectangleRec(createButtonRect, RAYWHITE);
		  
		if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), createButtonRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			editorGrid.Size = stoi(inputSize);
			return 0;
		}
		EndDrawing();
	}
	return 1;
}