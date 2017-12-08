//
// Created by L Nguyen Huu on 28/09/2017 ap. J.-C..
//

#pragma once

// TODO: define this macro only in test_engine build
#ifdef TEST_ENGINE

#define FRIEND_TEST(test_case_name, test_name)\
friend class test_case_name##_##test_name##_Test
// ? In Catch, it's very hard to see what class is produced

#endif
