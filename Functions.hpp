#pragma once
#include <raylib.h>
#include <vector>
#include <string>

struct gridCell {
	Rectangle rect;
	Texture2D texture;
};

class Functions {
public:
	Camera2D createCamera();
	Camera2D updateCamera(Camera2D camera);
	int keyboardToCurrentTexture(int textureSelected);
	gridCell onCellCollision(Texture2D texture, gridCell gridCell);
	std::vector<gridCell> createGrid(int gridSize, int gridWidth, int gridHeight);
	void drawGrid(int gridWidth, int gridHeight, std::vector<gridCell> gridCells);
	void drawTextCenter(const char *text, int posY, int fontSize);
	void drawStringCenterRect(std::string string, int fontSize, Rectangle rect);
};

extern Functions programFunctions;