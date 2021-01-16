#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "Game/GameBoard.h"

namespace Game {
	class BackgroundMovementComponent : public GameEngine::Component {
	public:
		static float speed;
		void SetSingleHeight(float height) { this->singleHeight = height; }
		virtual void Update() override;
		virtual void OnAddToWorld() override;
	private:
		float singleHeight;
	};
}