#pragma once
#include "LevelTemplate.h"
#include "Entity/Bosses.h"
#include "SceneManager/SceneUtils/Composit.h"
#include "Algorithms/StarField.h"

#include <json.hpp>
using json = nlohmann::json;

class BossLevel1 :public Level {

public:
	void update(float delta_time)override;
	void render()override;
	BossLevel1(json cfg);
	~BossLevel1();
	
private:
	Commander* boss;
	sf::Texture boss_texture;
	sf::Texture boss_projectile_texture;
	sf::Vector2f boss_health;
	void prepareContainers()override;
	void loadTextures()override;
	void updateEntityCollisions()override;
	void updateEntities()override;

	//Transition
	Composit::Fade* f_in;
	RadialStarField* r_starfield;
};