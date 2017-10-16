//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <gtest/gtest.h>
#include <TestShared.hpp>


TEST(DummyTestModule, Dummy) {
    TestShared toto;

    std::string tmp = "Hello world";

    toto.DisplayText(tmp);

    ASSERT_EQ("Hello world", "Hello world") << "Error";
}