#include "stdafx.h"

TestArenaTile::TestArenaTile() 
{
	for (auto i : walls_)
	{
		walls_[i] = false;
	}
}


TestArenaTile::TestArenaTile(const boolean walls[4])
{
	for (auto i = 0; i < 4; i++)
	{
		walls_[i] = walls[i];
	}
}