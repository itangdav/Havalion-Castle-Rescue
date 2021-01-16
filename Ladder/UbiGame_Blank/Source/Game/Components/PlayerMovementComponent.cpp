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

	float jumpDistance = 100;

	float jumpTime = 1;

	float jumpHeight = 50;

	float defaultHeight = 300;

	float playerVel = jumpDistance / jumpTime;


	if (startPosition - endPosition >= 0) {
		playerVel *= -1;
	}

	if (jumpDuration == 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			switch ((int)(round((GetEntity()->GetPos()).x) + 0.03)) {
			case 300: 
				jumpDuration = jumpTime;
				startPosition = (int)(round((GetEntity()->GetPos()).x) + 0.03);
				endPosition = (int)(round((GetEntity()->GetPos()).x) + 0.03) - jumpDistance;
			case 400:
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
			case 200:
				jumpDuration = jumpTime;
				startPosition = (int)(round((GetEntity()->GetPos()).x) + 0.03);
				endPosition = (int)(round((GetEntity()->GetPos()).x) + 0.03) + jumpDistance;
			case 300:
				jumpDuration = jumpTime;
				startPosition = (int)(round((GetEntity()->GetPos()).x) + 0.03);
				endPosition = (int)(round((GetEntity()->GetPos()).x) + 0.03) + jumpDistance;
			default:
				break;
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

