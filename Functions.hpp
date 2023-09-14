#pragma once
#include <raylib.h>
#include <vector>

struct gridCell {
	Rectangle rect;
	Texture2D texture;
};

class Functions {
public:
	Camera2D updateCamera(Camera2D camera);
	int keyboardToCurrentTexture(int textureSelected);
	gridCell onCellCollision(Texture2D texture, gridCell gridCell);
	std::vector<gridCell> createGrid(int gridSize, int gridWidth, int gridHeight);
	void drawGrid(int gridWidth, int gridHeight, std::vector<gridCell> gridCells);
};