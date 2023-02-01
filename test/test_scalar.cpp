#include <gtest/gtest.h>
#include "scalar/constant.h"
#include "scalar/scalar.h"

TEST(TestScalar, Inv) {
    uint64_t inv = 1;
    for (int i = 0; i < 63; ++i) {
        inv = inv * inv;
        inv = inv * 0xffffffff00000001;
    }
    inv = -inv;
    EXPECT_EQ(inv, bls12_381::scalar::constant::INV);
}

TEST(TestScalar, Zero) {
    EXPECT_EQ(bls12_381::scalar::Scalar::zero(), -bls12_381::scalar::Scalar::zero());
    EXPECT_EQ(bls12_381::scalar::Scalar::zero(), bls12_381::scalar::Scalar::zero() + bls12_381::scalar::Scalar::zero());
    EXPECT_EQ(bls12_381::scalar::Scalar::zero(), bls12_381::scalar::Scalar::zero() - bls12_381::scalar::Scalar::zero());
    EXPECT_EQ(bls12_381::scalar::Scalar::zero(), bls12_381::scalar::Scalar::zero() * bls12_381::scalar::Scalar::zero());
}

TEST(TestScalar, HexStr) {
    EXPECT_TRUE(bls12_381::scalar::Scalar::zero().getHex() ==
                "0x0000000000000000000000000000000000000000000000000000000000000000");
    EXPECT_TRUE(bls12_381::scalar::Scalar::one().getHex() ==
                "0x0000000000000000000000000000000000000000000000000000000000000001");
    EXPECT_TRUE(bls12_381::scalar::constant::R2.getHex() ==
                "0x1824b159acc5056f998c4fefecbc4ff55884b7fa0003480200000001fffffffe");
}

TEST(TestScalar, Equality) {
    EXPECT_EQ(bls12_381::scalar::Scalar::zero(), bls12_381::scalar::Scalar::zero());
    EXPECT_EQ(bls12_381::scalar::Scalar::one(), bls12_381::scalar::Scalar::one());
    EXPECT_EQ(bls12_381::scalar::constant::R2, bls12_381::scalar::constant::R2);

    EXPECT_NE(bls12_381::scalar::Scalar::zero(), bls12_381::scalar::Scalar::one());
    EXPECT_NE(bls12_381::scalar::Scalar::one(), bls12_381::scalar::constant::R2);
}

TEST(TestScalar, ToBytes) {
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t)> expected_0 = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t)> expected_1 = {
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t)> expected_r2 = {
            254, 255, 255, 255, 1, 0, 0, 0, 2, 72, 3, 0, 250, 183, 132, 88,
            245, 79, 188, 236, 239, 79, 140, 153, 111, 5, 197, 172, 89, 177, 36, 24
    };
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t)> expected_neg_1 = {
            0, 0, 0, 0, 255, 255, 255, 255, 254, 91, 254, 255, 2, 164, 189, 83,
            5, 216, 161, 9, 8, 216, 57, 51, 72, 125, 157, 41, 83, 167, 237, 115
    };

    std::array<uint8_t,
            bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t)> bytes_0 = bls12_381::scalar::Scalar::zero().to_bytes();
    std::array<uint8_t,
            bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t)> bytes_1 = bls12_381::scalar::Scalar::one().to_bytes();
    std::array<uint8_t,
            bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t)> bytes_r2 = bls12_381::scalar::constant::R2.to_bytes();
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH *
                        sizeof(uint64_t)> bytes_neg_1 = (-bls12_381::scalar::Scalar::one()).to_bytes();

    EXPECT_TRUE(bytes_0 == expected_0);
    EXPECT_TRUE(bytes_1 == expected_1);
    EXPECT_TRUE(bytes_r2 == expected_r2);
    EXPECT_TRUE(bytes_neg_1 == expected_neg_1);
}

TEST(TestScalar, FromBytes) {
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t)> bytes_0 = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t)> bytes_1 = {
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t)> bytes_r2 = {
            254, 255, 255, 255, 1, 0, 0, 0, 2, 72, 3, 0, 250, 183, 132, 88,
            245, 79, 188, 236, 239, 79, 140, 153, 111, 5, 197, 172, 89, 177, 36, 24
    };
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t)> bytes_neg_1 = {
            0, 0, 0, 0, 255, 255, 255, 255, 254, 91, 254, 255, 2, 164, 189, 83,
            5, 216, 161, 9, 8, 216, 57, 51, 72, 125, 157, 41, 83, 167, 237, 115
    };
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t)> modulus = {
            1, 0, 0, 0, 255, 255, 255, 255, 254, 91, 254, 255, 2, 164, 189, 83,
            5, 216, 161, 9, 8, 216, 57, 51, 72, 125, 157, 41, 83, 167, 237, 115
    };
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t)> larger_than_modulus_0 = {
            2, 0, 0, 0, 255, 255, 255, 255, 254, 91, 254, 255, 2, 164, 189, 83,
            5, 216, 161, 9, 8, 216, 57, 51, 72, 125, 157, 41, 83, 167, 237, 115
    };
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t)> larger_than_modulus_1 = {
            1, 0, 0, 0, 255, 255, 255, 255, 254, 91, 254, 255, 2, 164, 189, 83,
            5, 216, 161, 9, 8, 216, 58, 51, 72, 125, 157, 41, 83, 167, 237, 115
    };
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t)> larger_than_modulus_2 = {
            1, 0, 0, 0, 255, 255, 255, 255, 254, 91, 254, 255, 2, 164, 189, 83,
            5, 216, 161, 9, 8, 216, 57, 51, 72, 125, 157, 41, 83, 167, 237, 116
    };

    bls12_381::scalar::Scalar expected_0 = bls12_381::scalar::Scalar::from_bytes(bytes_0).value();
    bls12_381::scalar::Scalar expected_1 = bls12_381::scalar::Scalar::from_bytes(bytes_1).value();
    bls12_381::scalar::Scalar expected_r2 = bls12_381::scalar::Scalar::from_bytes(bytes_r2).value();
    bls12_381::scalar::Scalar expected_neg_1 = bls12_381::scalar::Scalar::from_bytes(bytes_neg_1).value();

    EXPECT_TRUE(expected_0 == bls12_381::scalar::Scalar::zero());
    EXPECT_TRUE(expected_1 == bls12_381::scalar::Scalar::one());
    EXPECT_TRUE(expected_r2 == bls12_381::scalar::constant::R2);
    EXPECT_TRUE(expected_neg_1 == -bls12_381::scalar::Scalar::one());

    EXPECT_FALSE(bls12_381::scalar::Scalar::from_bytes(modulus).has_value());
    EXPECT_FALSE(bls12_381::scalar::Scalar::from_bytes(larger_than_modulus_0).has_value());
    EXPECT_FALSE(bls12_381::scalar::Scalar::from_bytes(larger_than_modulus_1).has_value());
    EXPECT_FALSE(bls12_381::scalar::Scalar::from_bytes(larger_than_modulus_2).has_value());
}

TEST(TestScalar, FromWide) {
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t) * 2> bytes_r2 = {
            254, 255, 255, 255, 1, 0, 0, 0, 2, 72, 3, 0, 250, 183, 132, 88,
            245, 79, 188, 236, 239, 79, 140, 153, 111, 5, 197, 172, 89, 177, 36, 24,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t) * 2> bytes_n1 = {
            0, 0, 0, 0, 255, 255, 255, 255, 254, 91, 254, 255, 2, 164, 189, 83,
            5, 216, 161, 9, 8, 216, 57, 51, 72, 125, 157, 41, 83, 167, 237, 115,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    std::array<uint8_t, bls12_381::scalar::Scalar::WIDTH * sizeof(uint64_t) * 2> bytes_max = {
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };

    bls12_381::scalar::Scalar max_exp({0xc62c1805439b73b1, 0xc2b9551e8ced218e, 0xda44ec81daf9a422, 0x5605aa601c162e79});

    bls12_381::scalar::Scalar from_r2 = bls12_381::scalar::Scalar::from_bytes_wide(bytes_r2);
    bls12_381::scalar::Scalar from_n1 = bls12_381::scalar::Scalar::from_bytes_wide(bytes_n1);
    bls12_381::scalar::Scalar from_max = bls12_381::scalar::Scalar::from_bytes_wide(bytes_max);

    EXPECT_EQ(from_r2, bls12_381::scalar::constant::R2);
    EXPECT_EQ(from_n1, -bls12_381::scalar::Scalar::one());
    EXPECT_EQ(from_max, max_exp);
}

TEST(TestScalar, FromRaw) {
    std::array<uint64_t, bls12_381::scalar::Scalar::WIDTH> raw_1 = {
            0x00000001fffffffd, 0x5884b7fa00034802,
            0x998c4fefecbc4ff5, 0x1824b159acc5056f,
    };
    std::array<uint64_t, bls12_381::scalar::Scalar::WIDTH> raw_2 = {
            0xffffffffffffffff, 0xffffffffffffffff,
            0xffffffffffffffff, 0xffffffffffffffff,
    };
    std::array<uint64_t, bls12_381::scalar::Scalar::WIDTH> modulus = {
            0xffffffff00000001, 0x53bda402fffe5bfe,
            0x3339d80809a1d805, 0x73eda753299d7d48,
    };

    EXPECT_EQ(bls12_381::scalar::Scalar::from_raw(raw_1), bls12_381::scalar::Scalar::from_raw(raw_2));
    EXPECT_EQ(bls12_381::scalar::Scalar::from_raw(modulus), bls12_381::scalar::Scalar::zero());
    EXPECT_EQ(bls12_381::scalar::Scalar::from_raw({1, 0, 0, 0}), bls12_381::scalar::constant::R1);
}

TEST(TestScalar, Neg) {
    bls12_381::scalar::Scalar largest({0xffffffff00000000, 0x53bda402fffe5bfe, 0x3339d80809a1d805, 0x73eda753299d7d48});
    bls12_381::scalar::Scalar exp_neg_largest = -largest;
    bls12_381::scalar::Scalar neg_largest({1, 0, 0, 0});

    EXPECT_EQ(exp_neg_largest, neg_largest);

    bls12_381::scalar::Scalar neg_zero = -bls12_381::scalar::Scalar::zero();
    EXPECT_EQ(neg_zero, bls12_381::scalar::Scalar::zero());

    bls12_381::scalar::Scalar neg_neg_largest = -neg_largest;
    EXPECT_EQ(neg_neg_largest, largest);
}

TEST(TestScalar, Add) {
    bls12_381::scalar::Scalar largest({0xffffffff00000000, 0x53bda402fffe5bfe, 0x3339d80809a1d805, 0x73eda753299d7d48});
    bls12_381::scalar::Scalar largest2(
            {0xffffffff00000000, 0x53bda402fffe5bfe, 0x3339d80809a1d805, 0x73eda753299d7d48});
    bls12_381::scalar::Scalar expected(
            {0xfffffffeffffffff, 0x53bda402fffe5bfe, 0x3339d80809a1d805, 0x73eda753299d7d48});
    largest += largest;
    largest2 += bls12_381::scalar::Scalar({1, 0, 0, 0});

    EXPECT_EQ(largest, expected);
    EXPECT_EQ(largest2, bls12_381::scalar::Scalar::zero());
}

TEST(TestScalar, Sub) {
    const bls12_381::scalar::Scalar largest(
            {0xffffffff00000000, 0x53bda402fffe5bfe, 0x3339d80809a1d805, 0x73eda753299d7d48});
    bls12_381::scalar::Scalar temp = largest;
    temp -= largest;
    EXPECT_EQ(temp, bls12_381::scalar::Scalar::zero());

    temp = bls12_381::scalar::Scalar::zero();
    temp -= largest;

    bls12_381::scalar::Scalar temp2 = bls12_381::scalar::constant::MODULUS;
    temp2 -= largest;
    EXPECT_EQ(temp, temp2);
}

TEST(TestScalar, Mul) {
    const bls12_381::scalar::Scalar largest(
            {0xffffffff00000000, 0x53bda402fffe5bfe, 0x3339d80809a1d805, 0x73eda753299d7d48});
    bls12_381::scalar::Scalar current = largest;

    for (int i = 0; i < 100; ++i) {
        bls12_381::scalar::Scalar temp = current;
        temp *= current;
        bls12_381::scalar::Scalar temp2 = bls12_381::scalar::Scalar::zero();

        std::array<uint8_t, 32> bytes = current.to_bytes();

        for (auto iter = bytes.rbegin(); iter != bytes.rend(); ++iter) { // NOLINT(modernize-loop-convert)
            for (int k = 7; k >= 0; --k) {
                bool b = ((*iter >> k) & static_cast<uint8_t>(1)) == static_cast<uint8_t>(1);
                bls12_381::scalar::Scalar temp3 = temp2;
                temp2 += temp3;
                if (b) temp2 += current;
            }
        }
        EXPECT_EQ(temp, temp2);
        current += largest;
    }
}

TEST(TestScalar, Squaring) {
    const bls12_381::scalar::Scalar largest(
            {0xffffffff00000000, 0x53bda402fffe5bfe, 0x3339d80809a1d805, 0x73eda753299d7d48});
    bls12_381::scalar::Scalar current = largest;

    for (int i = 0; i < 100; ++i) {
        bls12_381::scalar::Scalar temp = current;
        temp = temp.square();
        bls12_381::scalar::Scalar temp2 = bls12_381::scalar::Scalar::zero();

        std::array<uint8_t, 32> bytes = current.to_bytes();

        for (auto iter = bytes.rbegin(); iter != bytes.rend(); ++iter) { // NOLINT(modernize-loop-convert)
            for (int k = 7; k >= 0; --k) {
                bool b = ((*iter >> k) & static_cast<uint8_t>(1)) == static_cast<uint8_t>(1);
                bls12_381::scalar::Scalar temp3 = temp2;
                temp2 += temp3;
                if (b) temp2 += current;
            }
        }
        EXPECT_EQ(temp, temp2);
        current += largest;
    }
}

TEST(TestScalar, Inversion) {
    EXPECT_FALSE(bls12_381::scalar::Scalar::zero().invert().has_value());
    EXPECT_EQ(bls12_381::scalar::Scalar::one().invert().value(), bls12_381::scalar::Scalar::one());
    EXPECT_EQ((-bls12_381::scalar::Scalar::one()).invert().value(), -bls12_381::scalar::Scalar::one());

    bls12_381::scalar::Scalar temp = bls12_381::scalar::constant::R2;
    for (int i = 0; i < 100; ++i) {
        bls12_381::scalar::Scalar temp2 = temp.invert().value();
        temp2 *= temp;
        EXPECT_EQ(temp2, bls12_381::scalar::Scalar::one());
        temp += bls12_381::scalar::constant::R2;
    }
}

TEST(TestScalar, InvertIsPow) {
    std::array<uint64_t, bls12_381::scalar::Scalar::WIDTH> q_minus_2 = {
            0xfffffffeffffffff, 0x53bda402fffe5bfe,
            0x3339d80809a1d805, 0x73eda753299d7d48,
    };

    bls12_381::scalar::Scalar r1 = bls12_381::scalar::constant::R1;
    bls12_381::scalar::Scalar r2 = bls12_381::scalar::constant::R1;

    for (int i = 0; i < 100; ++i) {
        r1 = r1.invert().value();
        r2 = r2.pow_vartime(q_minus_2);

        EXPECT_EQ(r1, r2);

        r1 += bls12_381::scalar::constant::R1;
        r2 = r1;
    }
}

TEST(TestScalar, Sqrt) {
    EXPECT_EQ(bls12_381::scalar::Scalar::zero().sqrt().value(), bls12_381::scalar::Scalar::zero());

    bls12_381::scalar::Scalar square({0x46cd85a5f273077e, 0x1d30c47dd68fc735, 0x77f656f60beca0eb, 0x494aa01bdf32468d});
    int32_t none_count = 0;
    for (int i = 0; i < 100; ++i) {
        std::optional<bls12_381::scalar::Scalar> square_root = square.sqrt();
        if (!square_root.has_value()) {
            none_count += 1;
        } else {
            EXPECT_EQ(square_root.value() * square_root.value(), square);
        }
        square -= bls12_381::scalar::Scalar::one();
    }
    EXPECT_EQ(49, none_count);
}

TEST(TestScalar, Double) {
    bls12_381::scalar::Scalar a = bls12_381::scalar::Scalar::from_raw(
            {0x1fff3231233ffffd, 0x4884b7fa00034802, 0x998c4fefecbc4ff3, 0x1824b159acc50562});
    EXPECT_EQ(a.doubles(), a + a);
}