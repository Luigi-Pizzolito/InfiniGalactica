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

	void updateEntityCollisions()override;
	void updateEntities()override;

	json cfg;

	int* upgrade_points = NULL;
	int upgrade_points_n;

	bool debug_xa = false;

};
