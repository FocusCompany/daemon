//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <gtest/gtest.h>
#include <TestUnix.hpp>


TEST(DummyTestModule, Dummy) {
    TestUnix toto;

    std::string tmp = "Hello world";

    toto.DisplayText(tmp);

    ASSERT_EQ(1, 1) << "Error";
}