/**
* @file
* Category.h
* @author
* Marco Corsini Baccaro 2019
* @version 1.0
*
* @section DESCRIPTION
* Game Experience Development Course
* Class of 2018-2019 
* Final Project
*
* @section LICENSE
*
* Copyright 2019
* Permission to use, copy, modify, and/or distribute this software for
* any purpose with or without fee is hereby granted, provided that the
* above copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
* @section Academic Integrity
* I certify that this work is solely my own and complies with
* NBCC Academic Integrity Policy (policy 1111)
*/
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