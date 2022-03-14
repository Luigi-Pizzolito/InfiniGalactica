#pragma once
#include "LevelTemplate.h"

class Level1 :public Level {

public: 
	void update(float delta_time)override;
	void render()override;
	Level1();
	~Level1();
private:
	void prepareContainers()override;
	void loadTextures()override;
	void setUpTimers()override;


};