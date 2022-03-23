#pragma once
#include "LevelTemplate.h"
#include "Entity/Bosses.h"
#include "SceneManager/SceneUtils/Composit.h"
#include "Algorithms/StarField.h"

#include <json.hpp>
using json = nlohmann::json;

class BossLevel2 :public Level {

public:
	void update(float delta_time)override;
	void render()override;
	BossLevel2(json cfg);
	~BossLevel2();

private:
	std::vector<CommanderAttacker> boss;
	sf::Texture boss_texture[2];
	sf::Texture boss_projectile_texture[2];
	sf::Vector2f boss_health;
	int max_enemy_count;
	int current_boss;
	void prepareContainers()override;
	void loadTextures()override;
	void updateEntityCollisions()override;
	void updateEntities()override;
	json cfg;
	//Transition
	Composit::Fade* f_in;
	RadialStarField* r_starfield;
};