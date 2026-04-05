#include "EnemyFactory.h"
#include "Camera.h"

#include "Slime.h"

Actor2D* EnemyFactory::RandomEnemy(const TileContext& tile, Camera* camera)
{
	//“G‚Ìí—Ş‚Íƒ‰ƒ“ƒ_ƒ€‚ÉŒˆ‚ß‚é
	int enemyType = GetRand(0); //¡‚ÍƒXƒ‰ƒCƒ€‚µ‚©‚¢‚È‚¢‚Ì‚Å0ŒÅ’è

	switch (enemyType)
	{
	case 0:
		return new Slime(tile, camera);
		break;
	//case 1:
		//	return new Bat(tile, camera);
		// break;
	//case 2:
		//	return new Goblin(tile, camera);]
		//break;


	}
}