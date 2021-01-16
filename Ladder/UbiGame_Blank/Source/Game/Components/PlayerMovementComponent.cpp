#include <math.h>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include "PlayerMovementComponent.h"
#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"


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
	sf::RenderWindow* mainWindow = GameEngine::GameEngineMain::GetInstance()->GetRenderWindow();
	unsigned int winWidth = mainWindow->getSize().x;
	unsigned int winHeight = mainWindow->getSize().y;
	Component::Update();

	float dt = GameEngine::GameEngineMain::GetTimeDelta();

	sf::Vector2f wantedVel = sf::Vector2f(0.f, 0.f);

	float laddersX[5] = { 0.14, 0.31, 0.5, 0.61, 0.84 };

	float laddersArr[5] = { winWidth, winWidth, winWidth, winWidth, winWidth};

	for (int i = 0; i < 5; i++) {
		laddersArr[i] *= laddersX[i];
	}

	float jumpTimes[4] = { 0.9, 1, 0.7, 1.3 };
	
	float maxCooldown = 0.1;

	float jumpHeights[4] = { 50, 50, 30, 80};

	float defaultHeight = winHeight/2;

	float playerVel = 1;

	if (jumpTime != 0) {
		playerVel = jumpDistance / jumpTime;
	}


	if (startPosition - endPosition >= 0) {
		playerVel *= -1;
	}

	if (jumpDuration == 0) {

		cooldown -= dt;
		if (cooldown <= 0) cooldown = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			int currX = (int)(round((GetEntity()->GetPos()).x) + 0.03);
			
			for (int i = 0; i < 4; i++) {
				if (currX == laddersArr[i + 1]) {
					jumpDuration = jumpTimes[i];
					maxJumpDuration = jumpDuration;
					startPosition = currX;
					endPosition = laddersArr[i];
					jumpHeight = jumpHeights[i];
					jumpDistance = laddersArr[i + 1] - laddersArr[i];
					jumpTime = jumpTimes[i];
				}
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			int currX = (int)(round((GetEntity()->GetPos()).x) + 0.03);

			for (int i = 0; i < 4; i++) {
				if (currX == laddersArr[i]) {
					jumpDuration = jumpTimes[i];
					maxJumpDuration = jumpDuration;
					startPosition = currX;
					endPosition = laddersArr[i+1];
					jumpHeight = jumpHeights[i];
					jumpDistance = laddersArr[i+1] - laddersArr[i];
					jumpTime = jumpTimes[i];
				}
			}
		}
	}
	else if (jumpDuration - dt <= 0) {
		cooldown = maxCooldown;
		wantedVel.y = -1 * GetEntity()->GetPos().y + defaultHeight;
		wantedVel.x = -1 * GetEntity()->GetPos().x + endPosition;
	}
	else {
		wantedVel.x = playerVel * dt;
		wantedVel.y = -1 * jumpHeight * (1 - pow(((GetEntity()->GetPos().x + wantedVel.x)-(startPosition+endPosition)/2),2)/pow(jumpDistance/2,2)) -GetEntity()->GetPos().y + defaultHeight;
	
	}

	if (jumpDuration > 0) {
		if (jumpDuration <= maxJumpDuration / 8 && playerVel < 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(1, 0);
		}
		else if (jumpDuration >= 7 * maxJumpDuration / 8 && playerVel < 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(1, 0);
		}
		else if (playerVel < 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(0, 0);
		}
		else if (jumpDuration <= maxJumpDuration / 8 && playerVel > 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(3, 0);
		}
		else if (jumpDuration >= 7 * maxJumpDuration / 8 && playerVel > 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(3, 0);
		}
		else if (playerVel > 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(4, 0);
		}
	}
	else {
		if (cooldown == 0)
		{
			cooldown = maxCooldown;
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->image++;
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->image %= 6;
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->image, 0);
			
			
		}
	}
	



	jumpDuration -= dt;
	if (jumpDuration <= 0) jumpDuration = 0;

	

	GetEntity()->SetPos(GetEntity()->GetPos() + wantedVel);

}

