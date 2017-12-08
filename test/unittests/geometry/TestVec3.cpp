//
// Created by acro_ on 2016/06/24.
//

#include "catch.hpp"

#include "include/core/math/Vector3.h"

TEST_CASE( "Test Vector3 comparison", "[geometry]" )
{
	Vector3 a(1, 2, 3);
	Vector3 b(1, 2, 3);
	Vector3 c(2, 3, 4);

	SECTION("Equality")
	{
		CHECK( a == b );
	}
	SECTION("Inequality")
	{
		CHECK( a != c );
	}
}