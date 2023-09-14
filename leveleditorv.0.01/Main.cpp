#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include <raymath.h>

Camera2D updateCamera(Camera2D camera) {
	if (IsKeyDown(KEY_A))			camera.target = Vector2Add(camera.target, Vector2{ -50 / camera.zoom, 0});
	if (IsKeyDown(KEY_D))			camera.target = Vector2Add(camera.target, Vector2{ 50  / camera.zoom, 0 });
	if (IsKeyDown(KEY_W))			camera.target = Vector2Add(camera.target, Vector2{ 0, -50 / camera.zoom });
	if (IsKeyDown(KEY_S))			camera.target = Vector2Add(camera.target, Vector2{ 0, 50  / camera.zoom });
	if (GetMouseWheelMove() > 0)	camera.zoom += 0.5f;
	if (GetMouseWheelMove() < 0)	camera.zoom -= 0.5f;
	return camera;
}

int keyboardToCurrentTexture(int textureSelected) {
	if (IsKeyPressed(KEY_ONE))		return 0;
	if (IsKeyPressed(KEY_TWO))		return 1;
	if (IsKeyPressed(KEY_THREE))	return 2;
	if (IsKeyPressed(KEY_FOUR))		return 3;
	if (IsKeyPressed(KEY_FIVE))		return 4;
	if (IsKeyPressed(KEY_SIX))		return 5;
	if (IsKeyPressed(KEY_SEVEN))	return 6;
	if (IsKeyPressed(KEY_EIGHT))	return 7;
	if (IsKeyPressed(KEY_NINE))		return 8;
	if (IsKeyPressed(KEY_ZERO))		return 9;
	return textureSelected;
}

struct gridCell {
	Rectangle rect;
	Texture2D texture;
};

gridCell onCellCollision(Texture2D texture, gridCell gridCell) {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		gridCell.texture = texture;
	return gridCell;
}

std::vector<gridCell> createGrid(int gridSize, int gridWidth, int gridHeight) {
	std::vector<gridCell> gridCells;
	gridCells.resize(gridWidth * gridHeight);

	int nextRectX = 0;
	int nextRectY = 0;

	for (int i = 0; i < gridWidth; ++i) {
		for (int j = 0; j < gridHeight; ++j) {
			gridCells[i * gridHeight + j].rect = { float(nextRectX), float(nextRectY), float(gridSize), float(gridSize) };
			nextRectY += gridSize;
		}
		nextRectX += gridSize;
		nextRectY = 0;
	}

	return gridCells;
}

void drawGrid(int gridWidth, int gridHeight, std::vector<gridCell> gridCells) {
	for (int i = 0; i < gridWidth * gridHeight; i++) {
		DrawRectangleLinesEx(gridCells[i].rect, 1, RAYWHITE);
		DrawTexture(gridCells[i].texture, gridCells[i].rect.x, gridCells[i].rect.y, RAYWHITE);
	}
}

int main() {
	int gridSize;
	int gridWidth;
	int gridHeight;
	std::cout << "Enter grid size (only 1:1) (example: 32)";
	std::cin >> gridSize;
	std::cout << "Enter amount of textures in width";
	std::cin >> gridWidth;
	std::cout << "Enter amount of textures in height";
	std::cin >> gridHeight;

	InitWindow(GetScreenWidth(), GetScreenWidth(), "Sparkles Level Editor - v0.01");
	ToggleFullscreen();
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

	std::vector <gridCell> gridCells;
	gridCells = createGrid(gridSize, gridWidth, gridHeight);

	while (!WindowShouldClose()) {
		ClearBackground(BLACK);
		BeginDrawing();
		textureSelected = keyboardToCurrentTexture(textureSelected);
		DrawTexture(textures[textureSelected], 0, 0, RAYWHITE);

		BeginMode2D(camera);
		camera = updateCamera(camera);

		for (int i = 0; i < gridWidth * gridHeight; ++i) {
			if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), gridCells[i].rect))
				gridCells[i] = onCellCollision(textures[textureSelected], gridCells[i]);
		}

		drawGrid(gridWidth, gridHeight, gridCells);

		EndMode2D();
		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}