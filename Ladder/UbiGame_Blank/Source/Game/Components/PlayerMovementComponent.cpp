#include "PlayerMovementComponent.h"
#include "GameEngine\GameEngineMain.h"
#include <math.h>
#include <iostream>

#include <SFML/Window/Keyboard.hpp>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
{

}

PlayerMovementComponent::~PlayerMovementComponent()
{

}

void PlayerMovementComponent::OnAddToWorld() 
{
	__super::OnAddToWorld();
}

void PlayerMovementComponent::Update()
{
	__super::Update();

	float dt = GameEngine::GameEngineMain::GetTimeDelta();

	sf::Vector2f wantedVel = sf::Vector2f(0.f, 0.f);

	float jumpDistance = 100;

	float jumpTime = 1;

	float jumpHeight = 150;

	float playerVel = jumpDistance / jumpTime;


	if (startPosition - endPosition >= 0) {
		playerVel *= -1;
	}

	if (jumpDuration == 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			switch ((int)(round((GetEntity()->GetPos()).x) + 0.03)) {
			case 100: 
				jumpDuration = jumpTime;
				startPosition = (int)(round((GetEntity()->GetPos()).x) + 0.03);
				endPosition = (int)(round((GetEntity()->GetPos()).x) + 0.03) - jumpDistance;
			case 200:
				jumpDuration = jumpTime;
				startPosition = (int)(round((GetEntity()->GetPos()).x) + 0.03);
				endPosition = (int)(round((GetEntity()->GetPos()).x) + 0.03) - jumpDistance;
			default:
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			switch ((int)(round((GetEntity()->GetPos()).x) + 0.03)) {
			case 0:
				jumpDuration = jumpTime;
				startPosition = (int)(round((GetEntity()->GetPos()).x) + 0.03);
				endPosition = (int)(round((GetEntity()->GetPos()).x) + 0.03) + jumpDistance;
			case 100:
				jumpDuration = jumpTime;
				startPosition = (int)(round((GetEntity()->GetPos()).x) + 0.03);
				endPosition = (int)(round((GetEntity()->GetPos()).x) + 0.03) + jumpDistance;
			default:
				break;
			}
		}
	}
	else if (jumpDuration - dt <= 0) {
		wantedVel.y = -1 * GetEntity()->GetPos().y;
		wantedVel.x = -1 * GetEntity()->GetPos().x + endPosition;
	}
	else {
		wantedVel.x = playerVel * dt;
		wantedVel.y = jumpHeight * (1 - pow(((GetEntity()->GetPos().x + wantedVel.x)-(startPosition+endPosition)/2),2)/pow(jumpDistance/2,2)) -GetEntity()->GetPos().y;
	
	}



	jumpDuration -= dt;
	if (jumpDuration <= 0) jumpDuration = 0;

	

	GetEntity()->SetPos(GetEntity()->GetPos() + wantedVel);

}

