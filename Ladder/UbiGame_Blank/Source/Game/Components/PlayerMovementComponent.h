#pragma once
#include "GameEngine/EntitySystem/Component.h"

namespace Game
{
	class PlayerMovementComponent : public GameEngine::Component
	{
	public:
		PlayerMovementComponent();
		~PlayerMovementComponent();

		virtual void Update() override;
		virtual void OnAddToWorld() override;

		float jumpDuration;
		float maxJumpDuration;
		float startPosition;
		float endPosition;
		float jumpHeight;
		float jumpDistance;
		float jumpTime;
		float cooldown;
	
	private:

	};

}
