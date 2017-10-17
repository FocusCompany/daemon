//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <gtest/gtest.h>
#include <TestWindows.hpp>


TEST(DummyTestModule, Dummy) {
    TestWindows toto;

    std::string tmp = "Hello world";

    toto.DisplayText(tmp);

    ASSERT_EQ(1, 1) << "Error";
}