#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "Functions.hpp"

Camera2D Functions::updateCamera(Camera2D camera) {
	if (IsKeyDown(KEY_R)) {
		camera.target = Vector2{ 0, 0 };
		camera.zoom = 1.0f;
	}

	if (IsKeyDown(KEY_A))			camera.target = Vector2Add(camera.target, Vector2{ -50.0f / camera.zoom, 0.0f });
	if (IsKeyDown(KEY_D))			camera.target = Vector2Add(camera.target, Vector2{ 50.0f / camera.zoom, 0.0f });
	if (IsKeyDown(KEY_W))			camera.target = Vector2Add(camera.target, Vector2{ 0.0f, -50.0f / camera.zoom });
	if (IsKeyDown(KEY_S))			camera.target = Vector2Add(camera.target, Vector2{ 0.0f, 50.0f / camera.zoom });
	if (GetMouseWheelMove() > 0)	camera.zoom += 0.5f;
	if (GetMouseWheelMove() < 0)	camera.zoom -= 0.5f;
	return camera;
}

int Functions::keyboardToCurrentTexture(int textureSelected) {
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

gridCell Functions::onCellCollision(Texture2D texture, gridCell gridCell) {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		gridCell.texture = texture;
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		gridCell.texture = Texture2D();
	return gridCell;
}

std::vector<gridCell> Functions::createGrid(int gridSize, int gridWidth, int gridHeight) {
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

void Functions::drawGrid(int gridWidth, int gridHeight, std::vector<gridCell> gridCells) {
	for (int i = 0; i < gridWidth * gridHeight; i++) {
		DrawRectangleLinesEx(gridCells[i].rect, 1, RAYWHITE);
		DrawTexture(gridCells[i].texture, gridCells[i].rect.x, gridCells[i].rect.y, RAYWHITE);
	}
}