#pragma once
#include "Application.h"
#include <vector>
#include "Entity/Player.h"
#include "Entity/Enemy.h"
#include "Projectiles/Projectile.h"
#include "Algorithms/StarField.h"
#include "Algorithms/CameraFollowScroll.h"
#include "Algorithms/Utilities.h"
#include "SceneManager/Scene.h"
//Class Implemented by Daniel 02.27 10:00 AM
class ShooterGame :public Application {
	//Implemented by Daniel 02.27 10:01 AM
private:
	SceneManagement::Scene* m_currentScene;
	SceneManagement::SceneMenu* m_menu;
public:
	//Constructors and Destructors
	ShooterGame(const sf::Vector2i& screen_dimensions, const char* app_name);
	~ShooterGame();
	//Added by Daniel 02.27 11:00 AM
	void update()override;
	void render()override;
private:
	const sf::RenderWindow* GetWindow()const  { 
		return m_window; }
};
