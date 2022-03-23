#pragma once
#include <vector>
#include "Algorithms/Utilities.h"
#include "Algorithms/MathUtils.h"
#include "SceneManager/Scene.h"
#include "GameItems/GameItem.h"
//Forward declaration
// class Enemy;
class GameItem;
namespace MemoryManagement {
	class BasicCollector {
	public:
		BasicCollector(){}
		virtual ~BasicCollector(){}
		virtual void update(){}
		

	};

	template<typename T>
	class Collector:public BasicCollector {
	protected:
		std::vector<T*>& buffer_alias;
	public:
		Collector(std::vector<T*>& buffer):buffer_alias(buffer) {

		}
		void update() override {
			
			buffer_alias.erase(std::remove_if(buffer_alias.begin(), buffer_alias.end(),
				[&](T* obj) {
					//first delete the heap mem
					bool out_of_range = leftViewport(obj);
					if (out_of_range) {
						delete obj;}
					return out_of_range; }),buffer_alias.end());

	
		}
		bool leftViewport(const T* obj) {
			sf::Vector2f top_left_pos = VectorMath::getViewPortTopLeftPos();
			sf::Vector2f lower_right_pos = VectorMath::getViewportLowerRightPos();
			//x axis
			bool far_from_right_side = obj->getTopLeftPos().x > lower_right_pos.x + obj->getSize().x;
			bool far_from_left_side = obj->getTopLeftPos().x < top_left_pos.x - obj->getSize().x;
			//y axis
			bool far_from_top = obj->getTopLeftPos().y < top_left_pos.y - obj->getSize().y;
			bool far_from_bottom = obj->getTopLeftPos().y > lower_right_pos.y + obj->getSize().y;

			return (far_from_right_side || far_from_left_side || far_from_top || far_from_bottom);
		}
	};

}

