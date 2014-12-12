
#include <limits.h>
#include "../src/mathExpression.h"
#include "gtest/gtest.h"

TEST(MathExpressionTest, Normal) {
	std::string x = "25*88/11";
	mathExpression mathExp(x);
	EXPECT_EQ(200, mathExp.evaluate(x));
}
