#include "BackgroundMovementComponent.h"
#include "GameEngine/GameEngineMain.h"
#include "Game/GameBoard.h"

using namespace Game;

float BackgroundMovementComponent::speed = 100;

void BackgroundMovementComponent::Update() {
	Component::Update();

	sf::RenderWindow* mainWindow = GameEngine::GameEngineMain::GetInstance()->GetRenderWindow();
	int winWidth = (int) mainWindow->getSize().x;
	int winHeight = (int) mainWindow->getSize().y;
	int halfCopies = winHeight / singleHeight + 1;

	float dt = GameEngine::GameEngineMain::GetTimeDelta();
	sf::Vector2f displacement = { 0, BackgroundMovementComponent::speed * dt };
	GetEntity()->SetPos(GetEntity()->GetPos() + displacement);
	if (GetEntity()->GetPos().y >= halfCopies * singleHeight) {
		sf::Vector2f goToTop = { 0, (float) (-halfCopies * singleHeight)};
		GetEntity()->SetPos(GetEntity()->GetPos() + goToTop);
	}
}

void BackgroundMovementComponent::OnAddToWorld() {
	Component::OnAddToWorld();
}