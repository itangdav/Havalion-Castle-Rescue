#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "SFML/System/Vector2.hpp"

namespace Game {
	class LinkedEntityComponent : public GameEngine::Component {
	public:
		LinkedEntityComponent();
		~LinkedEntityComponent();
		void SetFollowedEntity(GameEngine::Entity* follow) { followedEntity = follow; }
		void SetFollowOffset(sf::Vector2f off) { followOffset = off; }
		virtual void Update() override;
		virtual void OnAddToWorld() override;
	private:
		GameEngine::Entity* followedEntity;
		sf::Vector2f followOffset;
	};
}