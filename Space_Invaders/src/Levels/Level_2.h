#pragma once

#include "LevelTemplate.h"

class Level2 :public Level {

public:
	void update(float delta_time)override;
	void render()override;
	Level2();
	~Level2();
private:
	void prepareContainers()override;
	void loadTextures()override;
	


};
