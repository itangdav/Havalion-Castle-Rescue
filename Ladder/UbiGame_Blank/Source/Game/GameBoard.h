#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio.hpp>

#include <SFML/System/Vector2.hpp>
#include <vector>
namespace GameEngine
{
    class ObstacleShower;
}
namespace Game
{
	//Used for storing and controlling all game related entities, as well as providing an entry point for the "game" side of application	
	class PlayerEntity;	

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();
		void Update();
		bool IsGameOver() { return false; }

	private:
        void CreateShower();
		GameEngine::Entity* m_player;
		GameEngine::Entity* m_score;
		void CreatePlayer();

		GameEngine::Entity* ladderHiddenCenter;
		GameEngine::Entity** ladders[5];
		void CreateLadders();

		GameEngine::Entity* wallHiddenCenter;
		GameEngine::Entity*** walls;
		void CreateWall();
        GameEngine::ObstacleShower* m_shower;

		GameEngine::Entity* fog;
		void CreateFog();
	};
}

