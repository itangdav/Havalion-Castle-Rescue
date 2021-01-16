#include "GameBoard.h"
#include "iostream"
#include "GameEngine/GameEngineMain.h"
#include "Game/Components/PlayerMovementComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"

using namespace Game;

GameBoard::GameBoard()
	:m_player(nullptr)
{
	CreatePlayer();
	CreateLadders();
}


GameBoard::~GameBoard()
{
}

void GameBoard::CreatePlayer()
{
	sf::RenderWindow* mainWindow = GameEngine::GameEngineMain::GetInstance()->GetRenderWindow();
	unsigned int winWidth = mainWindow->getSize().x;
	unsigned int winHeight = mainWindow->getSize().y;

	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

	m_player->SetPos(sf::Vector2f(winWidth/2, winHeight/2));
	m_player->SetSize(sf::Vector2f(30.f, 30.f));

	GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>(m_player->AddComponent<GameEngine::SpriteRenderComponent>());
    
	spriteRender->SetFillColor(sf::Color::Transparent);
	spriteRender->SetZLevel(2);
	spriteRender->SetTexture(GameEngine::eTexture::Player);
	spriteRender->SetTileIndex(2, 0);
	spriteRender->image = 2;
	m_player->AddComponent<PlayerMovementComponent>();
}

void GameBoard::CreateLadders()
{
	unsigned int ladderWidth = 76;
	unsigned int ladderHeight = 148;

	sf::RenderWindow* mainWindow = GameEngine::GameEngineMain::GetInstance()->GetRenderWindow();
	unsigned int winWidth = mainWindow->getSize().x;
	unsigned int winHeight = mainWindow->getSize().y;
	int copiesStacked = (winHeight / ladderHeight + 1) * 2;

	float laddersX[5] = { 0.14, 0.31, 0.5, 0.61, 0.84 };

	for (int i = 0; i < 5; i++) {
		ladders[i] = new GameEngine::Entity*[copiesStacked];
		for (int j = 0; j < copiesStacked; j++) {
			ladders[i][j] = new GameEngine::Entity();
			GameEngine::GameEngineMain::GetInstance()->AddEntity(ladders[i][j]);
			ladders[i][j]->SetSize(sf::Vector2f(ladderWidth, ladderHeight));
			ladders[i][j]->SetPos(sf::Vector2f(winWidth *laddersX[i], winHeight - ladderHeight / 2.0 - ladderHeight * j));
			GameEngine::SpriteRenderComponent* render = ladders[i][j]->AddComponent<GameEngine::SpriteRenderComponent>();
			render->SetFillColor(sf::Color::Transparent);
			render->SetZLevel(1);
			render->SetTexture(GameEngine::eTexture::Ladder);
		}
	}
}


void GameBoard::Update()
{
	if (m_player->GetComponent<PlayerMovementComponent>()->jumpDuration == 0) {
		if (m_player->GetComponent<GameEngine::SpriteRenderComponent>()->image == 2) {
			m_player->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(2, 0);
		}
	}
	else if (m_player->GetComponent<PlayerMovementComponent>()->startPosition - m_player->GetComponent<PlayerMovementComponent>()->endPosition >= 0) {
		if (m_player->GetComponent<GameEngine::SpriteRenderComponent>()->image == 0) {
			m_player->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(0, 0);
		}
	}
	else {
		if (m_player->GetComponent<GameEngine::SpriteRenderComponent>()->image == 4) {
			m_player->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(4, 0);
		}
	}
}
