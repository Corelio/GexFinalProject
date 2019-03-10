#pragma once

namespace Category
{
	enum Type
	{
		None				= 0 << 0,
		Scene				= 1 << 0,
		PlayerAircraft		= 1 << 1,
		AlliedAircraft		= 1 << 2,
		EnemyAircraft		= 1 << 3,
		EnemyProjectile		= 1 << 4,
		AlliedProjectile	= 1 << 5,
		AirSceneLayer		= 1 << 6,
		Pickup				= 1 << 7,
		ParticleSystem		= 1 << 8,
		SoundEffect			= 1 << 9,
		Mushroom			= 1 << 10,
		Hero				= 1 << 11,
		Zombie				= 1 << 12,
		Pacman				= 1 << 13,
		Ghost				= 1 << 14,
		Cherry				= 1 << 15,
		Power				= 1 << 16,
		Car					= 1 << 17,

		Aircraft			= PlayerAircraft | EnemyAircraft | AlliedAircraft,
		Projectile			= EnemyProjectile | AlliedProjectile
	};
}