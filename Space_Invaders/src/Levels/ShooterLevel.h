#pragma once
#include "LevelTemplate.h"
#include <json.hpp>
using json = nlohmann::json;

class ShooterLevel :public Level {

public: 
	void update(float delta_time)override;
	void render()override;
	ShooterLevel(json cfg);
	~ShooterLevel();
private:
	void prepareContainers()override;
	void loadTextures()override;

	int upgrade_points[2] = {40, 50};

};
