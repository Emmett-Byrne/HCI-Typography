#include "LevelLoader.h"

/// The various operator >> overloads below are non-member functions used to extract
///  the game data from the YAML data structure.

/// <summary>
/// @brief Extracts the obstacle type, position and rotation values.
/// 
/// </summary>
/// <param name="obstacleNode">A YAML node</param>
/// <param name="obstacle">A simple struct to store the obstacle data</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& obstacleNode, ObstacleData& obstacle)
{
	obstacle.m_type = obstacleNode["type"].as<std::string>();
	obstacle.m_position.x = obstacleNode["position"]["x"].as<float>();
	obstacle.m_position.y = obstacleNode["position"]["y"].as<float>();
	obstacle.m_rotation = obstacleNode["rotation"].as<double>();
}

/// <summary>
/// @brief Extracts the filename for the game background texture.
/// 
/// </summary>
/// <param name="backgroundNode">A YAML node</param>
/// <param name="background">A simple struct to store background related data</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& backgroundNode, BackgroundData& background)
{
	background.m_fileName = backgroundNode["file"].as<std::string>();
}

/// <summary>
/// @brief Extracts the initial screen position for the player tank.
/// 
/// </summary>
/// <param name="tankNode">A YAML node</param>
/// <param name="tank">A simple struct to store data related to the player tank</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& tankNode, TankData& tank)
{
	tank.m_position.x = tankNode["position"]["x"].as<float>();
	tank.m_position.y = tankNode["position"]["y"].as<float>();
}



void operator >> (const YAML::Node& invadersNode, InvaderData& invader)
{
	invader.m_position.x = invadersNode["position"]["x"].as<float>();
	invader.m_position.y = invadersNode["position"]["y"].as<float>();
}

void operator >> (const YAML::Node& bricksNode, BrickData& brick)
{
	brick.m_position.x = bricksNode["position"]["x"].as<float>();
	brick.m_position.y = bricksNode["position"]["y"].as<float>();
}

void operator >> (const YAML::Node& playerNode, PlayerData& player)
{
	player.m_position.x = playerNode["position"]["x"].as<float>();
	player.m_position.y = playerNode["position"]["y"].as<float>();
}

void operator >> (const YAML::Node& boltNode, BoltData& bolt)
{
	bolt.m_position.x = boltNode["position"]["x"].as<float>();
	bolt.m_position.y = boltNode["position"]["y"].as<float>();
}


/// <summary>
/// @brief Top level function that extracts various game data from the YAML data stucture.
/// 
/// Invokes other functions to extract the background, tank and obstacle data.
//   Because there are multiple obstacles, obstacle data are stored in a vector.
/// </summary>
/// <param name="tankNode">A YAML node</param>
/// <param name="tank">A simple struct to store data related to the player tank</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& levelNode, LevelData& level)
{
	const YAML::Node& invadersNode = levelNode["invaders"].as<YAML::Node>();
	for (unsigned i = 0; i < invadersNode.size(); ++i)
	{
		InvaderData invader;
		invadersNode[i] >> invader;
		level.m_invaders.push_back(invader);
	}

	const YAML::Node& bricksNode = levelNode["bricks"].as<YAML::Node>();
	for (unsigned i = 0; i < bricksNode.size(); ++i)
	{
		BrickData brick;
		bricksNode[i] >> brick;
		level.m_bricks.push_back(brick);
	}


	//keeping for reference

	/*levelNode["background"] >> level.m_background;

	levelNode["tank"] >> level.m_tank;

	const YAML::Node& obstaclesNode = levelNode["obstacles"].as<YAML::Node>();
	for (unsigned i = 0; i < obstaclesNode.size(); ++i)
	{
		ObstacleData obstacle;
		obstaclesNode[i] >> obstacle;
		level.m_obstacles.push_back(obstacle);
	}*/
}

////////////////////////////////////////////////////////////
bool LevelLoader::load(int nr, LevelData& level)
{
	std::stringstream ss;
	ss << "./level/credits.yaml";
	/*ss << nr;
	ss << ".yaml";*/

	try
	{
		YAML::Node baseNode = YAML::LoadFile(ss.str());
		if (baseNode.IsNull())
		{
			std::string message("file: " + ss.str() + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> level;
	}
	catch (YAML::ParserException& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	return true;
}

