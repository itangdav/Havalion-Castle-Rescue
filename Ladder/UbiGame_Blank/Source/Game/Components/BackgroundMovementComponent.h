#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "Game/GameBoard.h"

namespace Game {
	class BackgroundMovementComponent : public GameEngine::Component {
	public:
		static float speed;
		virtual void Update() override;
		virtual void OnAddToWorld() override;
	};
}