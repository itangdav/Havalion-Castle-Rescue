#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "Game/GameBoard.h"

namespace Game {
	class PauseMenuComponent : public GameEngine::Component {
	public:
		static float pauseDuration;
		virtual void Update() override;
		virtual void OnAddToWorld() override;
	};
}