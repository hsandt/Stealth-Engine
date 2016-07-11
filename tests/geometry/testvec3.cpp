//
// Created by acro_ on 2016/06/24.
//

#include "catch.hpp"

#include "geometry/Vec3.h"

TEST_CASE( "Test Vec3f comparison", "[geometry]" )
{
	Vec3f a(1, 2, 3);
	Vec3f b(1, 2, 3);
	Vec3f c(2, 3, 4);

	SECTION("Equality")
	{
		CHECK( a == b );
	}
	SECTION("Inequality")
	{
		CHECK( a != c );
	}
}