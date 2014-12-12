
#include <limits.h>
#include "../src/mathExpression.h"
#include "gtest/gtest.h"

TEST(MathExpressionTest, Normal) {
	
	mathExpression mathExp("25*88/11");
	EXPECT_EQ(200, mathExp.evaluate());
}
