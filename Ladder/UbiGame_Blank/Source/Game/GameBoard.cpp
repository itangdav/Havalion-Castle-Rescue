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
}


GameBoard::~GameBoard()
{

}

void GameBoard::CreatePlayer()
{
	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

	m_player->SetPos(sf::Vector2f(300.f, 300.f));
	m_player->SetSize(sf::Vector2f(30.f, 30.f));

	GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>(m_player->AddComponent<GameEngine::SpriteRenderComponent>());
    
	spriteRender->SetFillColor(sf::Color::Transparent);
	spriteRender->SetZLevel(2);
	spriteRender->SetTexture(GameEngine::eTexture::Player);
	spriteRender->SetTileIndex(1, 0);
	m_player->AddComponent<PlayerMovementComponent>();
}


void GameBoard::Update()
{
	if (m_player->GetComponent<PlayerMovementComponent>()->jumpDuration == 0) {
		if (m_player->GetComponent<GameEngine::SpriteRenderComponent>()->direction != 1) {
			m_player->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(1, 0);
			m_player->GetComponent<GameEngine::SpriteRenderComponent>()->direction = 1;
			m_player->GetComponent<GameEngine::SpriteRenderComponent>()->Update();
		}
	}
	else if (m_player->GetComponent<PlayerMovementComponent>()->startPosition - m_player->GetComponent<PlayerMovementComponent>()->endPosition >= 0) {
		if (m_player->GetComponent<GameEngine::SpriteRenderComponent>()->direction != 0) {
			m_player->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(0, 0);
			m_player->GetComponent<GameEngine::SpriteRenderComponent>()->direction = 0;
			m_player->GetComponent<GameEngine::SpriteRenderComponent>()->Update();
		}
	}
	else {
		if (m_player->GetComponent<GameEngine::SpriteRenderComponent>()->direction != 2) {
			m_player->GetComponent<GameEngine::SpriteRenderComponent>()->SetTileIndex(2, 0);
			m_player->GetComponent<GameEngine::SpriteRenderComponent>()->direction = 2;
			m_player->GetComponent<GameEngine::SpriteRenderComponent>()->Update();
		}
	}
}
