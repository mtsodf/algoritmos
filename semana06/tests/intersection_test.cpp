
#include <gtest/gtest.h>

#include "point.h"
#include "segment_detection.h"

// Demonstrate some basic assertions.
TEST(SegmentTests, SegmentIntersection) {
    Point a(0, 0), b(1, 1);
    Point c(1, 0), d(0, 1);
    EXPECT_TRUE(intersect(&a, &b, &c, &d));
}

TEST(SegmentTests, SegmentNotIntersection) {
    Point a(0, 0), b(1, 0);
    Point c(0, 1), d(1, 1);
    EXPECT_FALSE(intersect(&a, &b, &c, &d));
}
