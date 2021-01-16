#include "BackgroundMovementComponent.h"
#include "GameEngine/GameEngineMain.h"
#include "Game/GameBoard.h"

using namespace Game;

float BackgroundMovementComponent::speed = 100;

void BackgroundMovementComponent::Update() {
	Component::Update();

	int ladderHeight = 148;
	sf::RenderWindow* mainWindow = GameEngine::GameEngineMain::GetInstance()->GetRenderWindow();
	int winWidth = (int) mainWindow->getSize().x;
	int winHeight = (int) mainWindow->getSize().y;
	int halfCopies = winHeight / ladderHeight + 1;

	float dt = GameEngine::GameEngineMain::GetTimeDelta();
	sf::Vector2f displacement = { 0, BackgroundMovementComponent::speed * dt };
	GetEntity()->SetPos(GetEntity()->GetPos() + displacement);
	if (GetEntity()->GetPos().y >= halfCopies * ladderHeight) {
		sf::Vector2f goToTop = { 0, (float) (-halfCopies * ladderHeight)};
		GetEntity()->SetPos(GetEntity()->GetPos() + goToTop);
	}
}

void BackgroundMovementComponent::OnAddToWorld() {
	Component::OnAddToWorld();
}