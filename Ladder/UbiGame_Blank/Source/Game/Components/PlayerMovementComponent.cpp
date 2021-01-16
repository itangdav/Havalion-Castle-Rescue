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
	if (GameEngine::GameEngineMain::GetInstance()->isPaused) return;
	
	sf::RenderWindow* mainWindow = GameEngine::GameEngineMain::GetInstance()->GetRenderWindow();
	unsigned int winWidth = mainWindow->getSize().x;
	unsigned int winHeight = mainWindow->getSize().y;
	Component::Update();

	float dt = GameEngine::GameEngineMain::GetTimeDelta() * GameEngine::GameEngineMain::GetInstance()->GetGameSpeed();

	sf::Vector2f wantedVel = sf::Vector2f(0.f, 0.f);

	float laddersX[5] = { 0.14, 0.31, 0.5, 0.65, 0.84 };

	float laddersArr[5] = { (float)winWidth, (float)winWidth, (float)winWidth, (float)winWidth, (float)winWidth };

	for (int i = 0; i < 5; i++) {
		laddersArr[i] *= laddersX[i];
	}

	float jumpTimes[4] = { 0.9, 1, 0.8, 1.1 };

	float maxCooldown = 0.1;

	float jumpHeights[4] = { 50, 55, 40, 65 };

	float defaultHeight = 4 * winHeight / 5;

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
			int currX = GetEntity()->GetPos().x;

			for (int i = 0; i < 4; i++) {
				if (abs(currX-laddersArr[i + 1])<=5) {
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
			int currX = GetEntity()->GetPos().x;
			for (int i = 0; i < 4; i++) {
				if (abs(currX - laddersArr[i]) <= 5) {
					jumpDuration = jumpTimes[i];
					maxJumpDuration = jumpDuration;
					startPosition = currX;
					endPosition = laddersArr[i + 1];
					jumpHeight = jumpHeights[i];
					jumpDistance = laddersArr[i + 1] - laddersArr[i];
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
		wantedVel.y = -1 * jumpHeight * (1 - pow(((GetEntity()->GetPos().x + wantedVel.x) - (startPosition + endPosition) / 2), 2) / pow(jumpDistance / 2, 2)) - GetEntity()->GetPos().y + defaultHeight;

	}

	if (jumpDuration > 0) {
		if (jumpDuration <= maxJumpDuration / 8 && playerVel < 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(10, 0);
		}
		else if (jumpDuration <= maxJumpDuration / 4 && playerVel < 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(9, 0);
		}
		else if (jumpDuration >= 7 * maxJumpDuration / 8 && playerVel < 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(6, 0);
		}
		else if (jumpDuration >= 3 * maxJumpDuration / 4 && playerVel < 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(7, 0);
		}
		else if (playerVel < 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(8, 0);
		}
		else if (jumpDuration <= maxJumpDuration / 8 && playerVel > 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(15, 0);
		}
		else if (jumpDuration <= maxJumpDuration / 4 && playerVel > 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(14, 0);
		}
		else if (jumpDuration >= 7 * maxJumpDuration / 8 && playerVel > 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(11, 0);
		}
		else if (jumpDuration >= 3 * maxJumpDuration / 4 && playerVel > 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(12, 0);
		}
		else if (playerVel > 0) {
			GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(13, 0);
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

	if (GameEngine::GameEngineMain::GetInstance()->isRunning && !GameEngine::GameEngineMain::GetInstance()->isPaused) {
		GameEngine::GameEngineMain::GetInstance()->score += dt *
			GameEngine::GameEngineMain::GetInstance()->GetGameSpeed();
	}

	

	GetEntity()->SetPos(GetEntity()->GetPos() + wantedVel);

}

