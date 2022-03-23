#pragma once
#include "LevelTemplate.h"
#include "Entity/Bosses.h"
#include "SceneManager/SceneUtils/Composit.h"
#include "Algorithms/StarField.h"
#include <random>
#include <json.hpp>
using json = nlohmann::json;

class BossLevel3 :public Level {

public:
	void update(float delta_time)override;
	void render()override;
	BossLevel3(json cfg);
	~BossLevel3();

private:
	CommanderStarminator* boss;
	sf::Texture boss_texture;
	sf::Texture boss_projectile_texture;
	sf::Texture mines_texture;
	sf::Vector2f boss_health;
	Control::GameTimer mines_timer;
	bool can_spawn = true;
	void prepareContainers()override;
	void loadTextures()override;
	void updateEntityCollisions()override;
	void updateEntities()override;
	void spawnMines();
	//Transition
	json cfg;
	Composit::Fade* f_in;
	RadialStarField* r_starfield;
};