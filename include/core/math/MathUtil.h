//
// Created by wing on 17/02/13.
//

#pragma once

namespace math
{
	constexpr const float& clamp( const float& v, const float& lo, const float& hi)
	{
		return v < lo ? lo : hi < v ? hi : v;
	}
}