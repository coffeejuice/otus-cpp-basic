#include <gtest/gtest.h>
#include "fake_int_class.h"

TEST(StdVector, DestructorCount) {
    // Setup
    const int elementCount = 10;
    FakeInt::resetDestructorCalls();

    {
        std::vector<FakeInt> container;
        container.reserve(elementCount);

        for (int i = 0; i < elementCount; i++) {
            container.push_back(FakeInt(i));
        }
        // Destructor is called here
    }

    EXPECT_EQ(elementCount, FakeInt::destructorCalls());
}

