#include <gtest/gtest.h>
#include "group/g1_affine.h"
#include "group/g1_projective.h"
#include "field/constant.h"

TEST(TestG1, Beta) {
    auto a = Fp::from_bytes({
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x5f, 0x19, 0x67, 0x2f, 0xdf, 0x76, 0xce, 0x51,
                                    0xba, 0x69, 0xc6, 0x07, 0x6a, 0x0f, 0x77, 0xea,
                                    0xdd, 0xb3, 0xa9, 0x3b, 0xe6, 0xf8, 0x96, 0x88,
                                    0xde, 0x17, 0xd8, 0x13, 0x62, 0x0a, 0x00, 0x02,
                                    0x2e, 0x01, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xfe
                            }).value();
    EXPECT_EQ(a, BETA);
    EXPECT_NE(BETA, Fp::one());
    EXPECT_NE(BETA * BETA, Fp::one());
    EXPECT_EQ(BETA * BETA * BETA, Fp::one());
}

TEST(TestG1, OnCurve) {
    EXPECT_TRUE(G1Affine::identity().is_on_curve());
    EXPECT_TRUE(G1Affine::generator().is_on_curve());
    EXPECT_TRUE(G1Projective::identity().is_on_curve());
    EXPECT_TRUE(G1Projective::generator().is_on_curve());

    Fp z({
                 0xba7afa1f9a6fe250, 0xfa0f5b595eafe731, 0x3bdc477694c306e7,
                 0x2149be4b3949fa24, 0x64aa6e0649b2078c, 0x12b108ac33643c3e,
         });
    G1Affine gen = G1Affine::generator();
    G1Projective test1{gen.getX() * z, gen.getY() * z, z};
    G1Projective test2{z, gen.getY() * z, z};

    EXPECT_TRUE(test1.is_on_curve());
    EXPECT_FALSE(test2.is_on_curve());
}

TEST(TestG1, AffineEquality) {
    G1Affine a = G1Affine::generator();
    G1Affine b = G1Affine::identity();

    EXPECT_TRUE(a == a);
    EXPECT_TRUE(b == b);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(b != a);
}

TEST(TestG1, ProjectiveEquality) {
    G1Projective a = G1Projective::generator();
    G1Projective b = G1Projective::identity();

    EXPECT_TRUE(a == a);
    EXPECT_TRUE(b == b);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(b != a);

    Fp z({
                 0xba7afa1f9a6fe250, 0xfa0f5b595eafe731, 0x3bdc477694c306e7,
                 0x2149be4b3949fa24, 0x64aa6e0649b2078c, 0x12b108ac33643c3e,
         });
    G1Projective p1{a.getX() * z, a.getY() * z, z};
    G1Projective p2{a.getX() * z, -a.getY() * z, z};
    G1Projective p3{z, a.getY() * z, z};

    EXPECT_TRUE(p1.is_on_curve());
    EXPECT_TRUE(p2.is_on_curve());
    EXPECT_FALSE(p3.is_on_curve());

    EXPECT_TRUE(a == p1);
    EXPECT_TRUE(p1 == a);
    EXPECT_TRUE(b != p1);
    EXPECT_TRUE(p1 != b);

    EXPECT_TRUE(a != p2);
    EXPECT_TRUE(p2 != a);
    EXPECT_TRUE(b != p2);
    EXPECT_TRUE(p2 != b);

    EXPECT_TRUE(a != p3);
    EXPECT_TRUE(p3 != a);
    EXPECT_TRUE(b != p3);
    EXPECT_TRUE(p3 != b);
}

TEST(TestG1, ProjectiveToAffine) {
    G1Projective a = G1Projective::generator();
    G1Projective b = G1Projective::identity();

    EXPECT_TRUE(G1Affine(a).is_on_curve());
    EXPECT_FALSE(G1Affine(a).is_identity());
    EXPECT_TRUE(G1Affine(b).is_on_curve());
    EXPECT_TRUE(G1Affine(b).is_identity());
}

TEST(TestG1, Doubleing) {
    G1Projective temp1 = G1Projective::identity().doubles();
    G1Projective temp2 = G1Projective::generator().doubles();

    EXPECT_TRUE(temp1.is_identity());
    EXPECT_TRUE(temp1.is_on_curve());
    EXPECT_FALSE(temp2.is_identity());
    EXPECT_TRUE(temp2.is_on_curve());

    G1Affine temp3{
            Fp({
                       0x53e978ce58a9ba3c, 0x3ea0583c4f3d65f9, 0x4d20bb47f0012960,
                       0xa54c664ae5b2b5d9, 0x26b552a39d7eb21f, 0x0008895d26e68785,
               }),
            Fp({
                       0x70110b3298293940, 0xda33c5393f1f6afc, 0xb86edfd16a5aa785,
                       0xaec6d1c9e7b1c895, 0x25cfc2b522d11720, 0x06361c83f8d09b15,
               }),
            false,
    };

    EXPECT_EQ(G1Affine(temp2), temp3);
}

TEST(TestG1, Add1) {
    G1Projective a = G1Projective::identity();
    G1Projective b = G1Projective::identity();
    G1Projective c = a + b;

    EXPECT_TRUE(c.is_identity());
    EXPECT_TRUE(c.is_on_curve());
}

TEST(TestG1, Add2) {
    G1Projective a = G1Projective::identity();
    G1Projective b = G1Projective::generator();

    Fp z = Fp({
                      0xba7afa1f9a6fe250, 0xfa0f5b595eafe731, 0x3bdc477694c306e7,
                      0x2149be4b3949fa24, 0x64aa6e0649b2078c, 0x12b108ac33643c3e,
              });
    b = G1Projective{b.getX() * z, b.getY() * z, z};
    G1Projective c = a + b;

    EXPECT_FALSE(c.is_identity());
    EXPECT_TRUE(c.is_on_curve());
    EXPECT_TRUE(c == G1Projective::generator());
}

TEST(TestG1, Add3) {
    G1Projective a = G1Projective::identity();
    G1Projective b = G1Projective::generator();

    Fp z = Fp({
                      0xba7afa1f9a6fe250, 0xfa0f5b595eafe731, 0x3bdc477694c306e7,
                      0x2149be4b3949fa24, 0x64aa6e0649b2078c, 0x12b108ac33643c3e,
              });
    b = G1Projective{b.getX() * z, b.getY() * z, z};
    G1Projective c = b + a;

    EXPECT_FALSE(c.is_identity());
    EXPECT_TRUE(c.is_on_curve());
    EXPECT_TRUE(c == G1Projective::generator());
}

TEST(TestG1, Add4) {
    G1Projective a = G1Projective::generator().doubles().doubles();
    G1Projective b = G1Projective::generator().doubles();
    G1Projective c = a + b;
    G1Projective d = G1Projective::generator();
    for (int i = 0; i < 5; ++i) d += G1Projective::generator();

    EXPECT_FALSE(c.is_identity());
    EXPECT_TRUE(c.is_on_curve());
    EXPECT_FALSE(d.is_identity());
    EXPECT_TRUE(d.is_on_curve());
    EXPECT_EQ(c, d);
}

TEST(TestG1, Add5) {
    Fp beta({
                    0xcd03c9e48671f071, 0x5dab22461fcda5d2, 0x587042afd3851b95,
                    0x8eb60ebe01bacb9e, 0x03f97d6e83d050d2, 0x18f0206554638741,
            });
    beta = beta.square();

    G1Projective a = G1Projective::generator().doubles().doubles();
    G1Projective b{a.getX() * beta, -a.getY(), a.getZ()};

    EXPECT_TRUE(a.is_on_curve());
    EXPECT_TRUE(b.is_on_curve());

    G1Projective c = a + b;
    G1Projective d{
            Fp({
                       0x29e1e987ef68f2d0, 0xc5f3ec531db03233, 0xacd6c4b6ca19730f,
                       0x18ad9e827bc2bab7, 0x46e3b2c5785cc7a9, 0x07e571d42d22ddd6,
               }),
            Fp({
                       0x94d117a7e5a539e7, 0x8e17ef673d4b5d22, 0x9d746aaf508a33ea,
                       0x8c6d883d2516c9a2, 0x0bc3b8d5fb0447f7, 0x07bfa4c7210f4f44,
               }),
            Fp::one(),
    };

    EXPECT_EQ(G1Affine(c), G1Affine(d));
    EXPECT_FALSE(c.is_identity());
    EXPECT_TRUE(c.is_on_curve());
}

TEST(TestG1, MixAdd1) {
    G1Affine a = G1Affine::identity();
    G1Projective b = G1Projective::identity();
    G1Projective c = a + b;

    EXPECT_TRUE(c.is_identity());
    EXPECT_TRUE(c.is_on_curve());
}

TEST(TestG1, MixAdd2) {
    G1Affine a = G1Affine::identity();
    G1Projective b = G1Projective::generator();

    Fp z = Fp({
                      0xba7afa1f9a6fe250, 0xfa0f5b595eafe731, 0x3bdc477694c306e7,
                      0x2149be4b3949fa24, 0x64aa6e0649b2078c, 0x12b108ac33643c3e,
              });
    b = G1Projective{b.getX() * z, b.getY() * z, z};
    G1Projective c = a + b;

    EXPECT_FALSE(c.is_identity());
    EXPECT_TRUE(c.is_on_curve());
    EXPECT_TRUE(c == G1Projective::generator());
}

TEST(TestG1, MixAdd3) {
    G1Affine a = G1Affine::identity();
    G1Projective b = G1Projective::generator();

    Fp z = Fp({
                      0xba7afa1f9a6fe250, 0xfa0f5b595eafe731, 0x3bdc477694c306e7,
                      0x2149be4b3949fa24, 0x64aa6e0649b2078c, 0x12b108ac33643c3e,
              });
    b = G1Projective{b.getX() * z, b.getY() * z, z};
    G1Projective c = b + a;

    EXPECT_FALSE(c.is_identity());
    EXPECT_TRUE(c.is_on_curve());
    EXPECT_TRUE(c == G1Projective::generator());
}

TEST(TestG1, MixAdd4) {
    G1Projective a = G1Projective::generator().doubles().doubles();
    G1Projective b = G1Projective::generator().doubles();
    G1Projective c = a + b;
    G1Projective d = G1Projective::generator();
    for (int i = 0; i < 5; ++i) d += G1Affine::generator();

    EXPECT_FALSE(c.is_identity());
    EXPECT_TRUE(c.is_on_curve());
    EXPECT_FALSE(d.is_identity());
    EXPECT_TRUE(d.is_on_curve());
    EXPECT_EQ(c, d);
}

TEST(TestG1, MixAdd5) {
    Fp beta({
                    0xcd03c9e48671f071, 0x5dab22461fcda5d2, 0x587042afd3851b95,
                    0x8eb60ebe01bacb9e, 0x03f97d6e83d050d2, 0x18f0206554638741,
            });
    beta = beta.square();

    G1Projective a = G1Projective::generator().doubles().doubles();
    G1Projective b{a.getX() * beta, -a.getY(), a.getZ()};

    G1Affine aa(a);

    EXPECT_TRUE(aa.is_on_curve());
    EXPECT_TRUE(b.is_on_curve());

    G1Projective c = aa + b;
    G1Projective d{
            Fp({
                       0x29e1e987ef68f2d0, 0xc5f3ec531db03233, 0xacd6c4b6ca19730f,
                       0x18ad9e827bc2bab7, 0x46e3b2c5785cc7a9, 0x07e571d42d22ddd6,
               }),
            Fp({
                       0x94d117a7e5a539e7, 0x8e17ef673d4b5d22, 0x9d746aaf508a33ea,
                       0x8c6d883d2516c9a2, 0x0bc3b8d5fb0447f7, 0x07bfa4c7210f4f44,
               }),
            Fp::one(),
    };

    EXPECT_EQ(G1Affine(c), G1Affine(d));
    EXPECT_FALSE(c.is_identity());
    EXPECT_TRUE(c.is_on_curve());
}

TEST(TestG1, ProjectiveNegSub) {
    G1Projective a = G1Projective::generator().doubles();

    EXPECT_EQ(a + (-a), G1Projective::identity());
    EXPECT_EQ(a + (-a), a - a);
}

TEST(TestG1, AffineNegSub) {
    G1Affine a = G1Affine::generator();

    EXPECT_EQ(G1Projective(a)+(-a), G1Projective::identity());
    EXPECT_EQ(G1Projective(a) +(-a), G1Projective(a) -a);
}

TEST(TestG1, TorsionFree) {
    G1Affine a{
            Fp({
                       0x0abaf895b97e43c8, 0xba4c6432eb9b61b0, 0x12506f52adfe307f,
                       0x75028c3439336b72, 0x84744f05b8e9bd71, 0x113d554fb09554f7,
               }),
            Fp({
                       0x73e90e88f5cf01c0, 0x37007b65dd3197e2, 0x5cf9a1992f0d7c78,
                       0x4f83c10b9eb3330d, 0xf6a63f6f07f60961, 0x0c53b5b97e634df3,
               }),
            false,
    };

    EXPECT_FALSE(a.is_torsion_free());
    EXPECT_TRUE(G1Affine::identity().is_torsion_free());
    EXPECT_TRUE(G1Affine::generator().is_torsion_free());
}

TEST(TestG1, CofactorClearance) {
    G1Projective gen = G1Projective::generator();
    G1Projective id = G1Projective::identity();

    EXPECT_TRUE(gen.clear_cofactor().is_on_curve());
    EXPECT_TRUE(id.clear_cofactor().is_on_curve());

    Fp z({
                 0x3d2d1c670671394e, 0x0ee3a800a2f7c1ca, 0x270f4f21da2e5050,
                 0xe02840a53f1be768, 0x55debeb597512690, 0x08bd25353dc8f791,
         });

    G1Projective point{
            Fp({
                       0x48af5ff540c817f0, 0xd73893acaf379d5a, 0xe6c43584e18e023c,
                       0x1eda39c30f188b3e, 0xf618c6d3ccc0f8d8, 0x0073542cd671e16c,
               }) * z,
            Fp({
                       0x57bf8be79461d0ba, 0xfc61459cee3547c3, 0x0d23567df1ef147b,
                       0x0ee187bcce1d9b64, 0xb0c8cfbe9dc8fdc1, 0x1328661767ef368b,
               }),
            z.square() * z,
    };

    EXPECT_TRUE(point.is_on_curve());
    EXPECT_FALSE(G1Affine(point).is_torsion_free());

    G1Projective cleared = point.clear_cofactor();

    EXPECT_TRUE(cleared.is_on_curve());
    EXPECT_TRUE(G1Affine(cleared).is_torsion_free());
}

TEST(TestG1, BatchNormalize) {
    G1Projective a = G1Projective::generator().doubles();
    G1Projective b = a.doubles();
    G1Projective c = b.doubles();

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                std::vector<G1Projective> v = {a, b, c};
                if (i == 1) v[0] = G1Projective::identity();
                if (j == 0) v[1] = G1Projective::identity();
                if (k == 0) v[2] = G1Projective::identity();

                std::vector<G1Affine> res = G1Projective::batch_normalize(v);
                G1Affine expected[3] = {G1Affine(v[0]), G1Affine(v[1]), G1Affine(v[2])};

                EXPECT_EQ(res[0], expected[0]);
                EXPECT_EQ(res[1], expected[1]);
                EXPECT_EQ(res[2], expected[2]);
            }
        }
    }
}