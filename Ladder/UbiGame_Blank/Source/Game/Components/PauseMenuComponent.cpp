#include "PauseMenuComponent.h"
#include "GameEngine/GameEngineMain.h"
#include "Game/GameBoard.h"

using namespace Game;

float PauseMenuComponent::pauseDuration = 0;

void PauseMenuComponent::Update() {
	Component::Update();
}

void PauseMenuComponent::OnAddToWorld() {
	Component::OnAddToWorld();
}