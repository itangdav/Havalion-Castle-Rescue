#include <math.h>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include "PlayerMovementComponent.h"
#include "GameEngine/GameEngineMain.h"


using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
{

}

PlayerMovementComponent::~PlayerMovementComponent()
{

}

void PlayerMovementComponent::OnAddToWorld() 
{
	Component::OnAddToWorld();
}

void PlayerMovementComponent::Update()
{
	Component::Update();

	float dt = GameEngine::GameEngineMain::GetTimeDelta();

	sf::Vector2f wantedVel = sf::Vector2f(0.f, 0.f);

	float ladders[5] = { 50, 131, 190, 250, 400};

	float jumpTimes[4] = { 1, 1, 1, 1.4 };
	

	float jumpHeights[4] = { 50, 50, 50, 80};

	float defaultHeight = 250;

	float playerVel = 1;

	if (jumpTime != 0) {
		playerVel = jumpDistance / jumpTime;
	}


	if (startPosition - endPosition >= 0) {
		playerVel *= -1;
	}

	if (jumpDuration == 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			int currX = (int)(round((GetEntity()->GetPos()).x) + 0.03);
			
			for (int i = 0; i < 4; i++) {
				if (currX == ladders[i + 1]) {
					jumpDuration = jumpTimes[i];
					startPosition = currX;
					endPosition = ladders[i];
					jumpHeight = jumpHeights[i];
					jumpDistance = ladders[i + 1] - ladders[i];
					jumpTime = jumpTimes[i];
				}
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			int currX = (int)(round((GetEntity()->GetPos()).x) + 0.03);

			for (int i = 0; i < 4; i++) {
				if (currX == ladders[i]) {
					jumpDuration = jumpTimes[i];
					startPosition = currX;
					endPosition = ladders[i+1];
					jumpHeight = jumpHeights[i];
					jumpDistance = ladders[i+1] - ladders[i];
					jumpTime = jumpTimes[i];
				}
			}
		}
	}
	else if (jumpDuration - dt <= 0) {
		wantedVel.y = -1 * GetEntity()->GetPos().y + defaultHeight;
		wantedVel.x = -1 * GetEntity()->GetPos().x + endPosition;
	}
	else {
		wantedVel.x = playerVel * dt;
		wantedVel.y = -1 * jumpHeight * (1 - pow(((GetEntity()->GetPos().x + wantedVel.x)-(startPosition+endPosition)/2),2)/pow(jumpDistance/2,2)) -GetEntity()->GetPos().y + defaultHeight;
	
	}



	jumpDuration -= dt;
	if (jumpDuration <= 0) jumpDuration = 0;

	

	GetEntity()->SetPos(GetEntity()->GetPos() + wantedVel);

}

