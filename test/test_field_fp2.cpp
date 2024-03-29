#include <gtest/gtest.h>
#include "field/fp2.h"

using bls12_381::field::Fp;
using bls12_381::field::Fp2;

TEST(TestFp2, Equality) {
    Fp2 const a{
            Fp({1, 2, 3, 4, 5, 6}),
            Fp({7, 8, 9, 10, 11, 12})
    };
    Fp2 const b{
            Fp({1, 2, 3, 4, 5, 6}),
            Fp({7, 8, 9, 10, 11, 12})
    };
    EXPECT_TRUE(a == b);
}

TEST(TestFp2, Add) {
    Fp2 const a{
            Fp({
                       0xc9a2183163ee70d4, 0xbc3770a7196b5c91, 0xa247f8c1304c5f44,
                       0xb01fc2a3726c80b5, 0xe1d293e5bbd919c9, 0x04b78e80020ef2ca,
               }),
            Fp({
                       0x952ea4460462618f, 0x238d5eddf025c62f, 0xf6c94b012ea92e72,
                       0x03ce24eac1c93808, 0x055950f945da483c, 0x010a768d0df4eabc,
               })
    };
    Fp2 const b{
            Fp({
                       0xa1e09175a4d2c1fe, 0x8b33acfc204eff12, 0xe24415a11b456e42,
                       0x61d996b1b6ee1936, 0x1164dbe8667c853c, 0x0788557acc7d9c79,
               }),
            Fp({
                       0xda6a87cc6f48fa36, 0x0fc7b488277c1903, 0x9445ac4adc448187,
                       0x02616d5bc9099209, 0xdbed46772db58d48, 0x11b94d5076c7b7b1,
               })
    };
    Fp2 const c{
            Fp({
                       0x6b82a9a708c132d2, 0x476b1da339ba5ba4, 0x848c0e624b91cd87,
                       0x11f95955295a99ec, 0xf3376fce22559f06, 0x0c3fe3face8c8f43,
               }),
            Fp({
                       0x6f992c1273ab5bc5, 0x3355136617a1df33, 0x8b0ef74c0aedaff9,
                       0x062f92468ad2ca12, 0xe1469770738fd584, 0x12c3c3dd84bca26d,
               })
    };
    EXPECT_EQ(a + b, c);
}

TEST(TestFp2, Sub) {
    Fp2 const a{
            Fp({
                       0xc9a2183163ee70d4, 0xbc3770a7196b5c91, 0xa247f8c1304c5f44,
                       0xb01fc2a3726c80b5, 0xe1d293e5bbd919c9, 0x04b78e80020ef2ca,
               }),
            Fp({
                       0x952ea4460462618f, 0x238d5eddf025c62f, 0xf6c94b012ea92e72,
                       0x03ce24eac1c93808, 0x055950f945da483c, 0x010a768d0df4eabc,
               })
    };
    Fp2 const b{
            Fp({
                       0xa1e09175a4d2c1fe, 0x8b33acfc204eff12, 0xe24415a11b456e42,
                       0x61d996b1b6ee1936, 0x1164dbe8667c853c, 0x0788557acc7d9c79,
               }),
            Fp({
                       0xda6a87cc6f48fa36, 0x0fc7b488277c1903, 0x9445ac4adc448187,
                       0x02616d5bc9099209, 0xdbed46772db58d48, 0x11b94d5076c7b7b1,
               })
    };
    Fp2 const c{
            Fp({
                       0xe1c086bbbf1b5981, 0x4fafc3a9aa705d7e, 0x2734b5c10bb7e726,
                       0xb2bd7776af037a3e, 0x1b895fb398a84164, 0x17304aef6f113cec,
               }),
            Fp({
                       0x74c31c7995191204, 0x3271aa5479fdad2b, 0xc9b471574915a30f,
                       0x65e40313ec44b8be, 0x7487b2385b7067cb, 0x09523b26d0ad19a4,
               })
    };
    EXPECT_EQ(a - b, c);
}

TEST(TestFp2, Neg) {
    Fp2 const a{
            Fp({
                       0xc9a2183163ee70d4, 0xbc3770a7196b5c91, 0xa247f8c1304c5f44,
                       0xb01fc2a3726c80b5, 0xe1d293e5bbd919c9, 0x04b78e80020ef2ca,
               }),
            Fp({
                       0x952ea4460462618f, 0x238d5eddf025c62f, 0xf6c94b012ea92e72,
                       0x03ce24eac1c93808, 0x055950f945da483c, 0x010a768d0df4eabc,
               })
    };
    Fp2 const b{
            Fp({
                       0xf05ce7ce9c1139d7, 0x62748f5797e8a36d, 0xc4e8d9dfc66496df,
                       0xb45788e181189209, 0x694913d08772930d, 0x1549836a3770f3cf,
               }),
            Fp({
                       0x24d05bb9fb9d491c, 0xfb1ea120c12e39d0, 0x7067879fc807c7b1,
                       0x60a9269a31bbdab6, 0x45c256bcfd71649b, 0x18f69b5d2b8afbde,
               })
    };
    EXPECT_EQ(-a, b);
}

TEST(TestFp2, Mul) {
    Fp2 const a{
            Fp({
                       0xc9a2183163ee70d4, 0xbc3770a7196b5c91, 0xa247f8c1304c5f44,
                       0xb01fc2a3726c80b5, 0xe1d293e5bbd919c9, 0x04b78e80020ef2ca,
               }),
            Fp({
                       0x952ea4460462618f, 0x238d5eddf025c62f, 0xf6c94b012ea92e72,
                       0x03ce24eac1c93808, 0x055950f945da483c, 0x010a768d0df4eabc,
               })
    };
    Fp2 const b{
            Fp({
                       0xa1e09175a4d2c1fe, 0x8b33acfc204eff12, 0xe24415a11b456e42,
                       0x61d996b1b6ee1936, 0x1164dbe8667c853c, 0x0788557acc7d9c79,
               }),
            Fp({
                       0xda6a87cc6f48fa36, 0x0fc7b488277c1903, 0x9445ac4adc448187,
                       0x02616d5bc9099209, 0xdbed46772db58d48, 0x11b94d5076c7b7b1,
               })
    };
    Fp2 const c{
            Fp({
                       0xf597483e27b4e0f7, 0x610fbadf811dae5f, 0x8432af917714327a,
                       0x6a9a9603cf88f09e, 0xf05a7bf8bad0eb01, 0x09549131c003ffae,
               }),
            Fp({
                       0x963b02d0f93d37cd, 0xc95ce1cdb30a73d4, 0x308725fa3126f9b8,
                       0x56da3c167fab0d50, 0x6b5086b5f4b6d6af, 0x09c39f062f18e9f2,
               })
    };
    EXPECT_EQ(a * b, c);
}

TEST(TestFp2, Square) {
    Fp2 const a{
            Fp({
                       0xc9a2183163ee70d4, 0xbc3770a7196b5c91, 0xa247f8c1304c5f44,
                       0xb01fc2a3726c80b5, 0xe1d293e5bbd919c9, 0x04b78e80020ef2ca,
               }),
            Fp({
                       0x952ea4460462618f, 0x238d5eddf025c62f, 0xf6c94b012ea92e72,
                       0x03ce24eac1c93808, 0x055950f945da483c, 0x010a768d0df4eabc,
               })
    };
    Fp2 const b{
            Fp({
                       0xa1e09175a4d2c1fe, 0x8b33acfc204eff12, 0xe24415a11b456e42,
                       0x61d996b1b6ee1936, 0x1164dbe8667c853c, 0x0788557acc7d9c79,
               }),
            Fp({
                       0xda6a87cc6f48fa36, 0x0fc7b488277c1903, 0x9445ac4adc448187,
                       0x02616d5bc9099209, 0xdbed46772db58d48, 0x11b94d5076c7b7b1,
               })
    };
    EXPECT_EQ(a.square(), b);
}

TEST(TestFp2, Sqrt) {
    Fp2 const a{
            Fp({
                       0x2beed14627d7f9e9, 0xb6614e06660e5dce, 0x06c4cc7c2f91d42c,
                       0x996d78474b7a63cc, 0xebaebc4c820d574e, 0x18865e12d93fd845,
               }),
            Fp({
                       0x7d828664baf4f566, 0xd17e663996ec7339, 0x679ead55cb4078d0,
                       0xfe3b2260e001ec28, 0x305993d043d91b68, 0x0626f03c0489b72d,
               })
    };
    EXPECT_EQ(a.sqrt().value().square(), a); // NOLINT(bugprone-unchecked-optional-access)

    Fp2 const b{
            Fp({
                       0x6631000000105545, 0x211400400eec000d, 0x3fa7af30c820e316,
                       0xc52a8b8d6387695d, 0x9fb4e61d1e83eac5, 0x005cb922afe84dc7,
               }),
            Fp::zero()
    };
    EXPECT_EQ(b.sqrt().value().square(), b); // NOLINT(bugprone-unchecked-optional-access)

    Fp2 const c{
            Fp({
                       0x44f600000051ffae, 0x86b8014199480043, 0xd7159952f1f3794a,
                       0x755d6e3dfe1ffc12, 0xd36cd6db5547e905, 0x02f8c8ecbf1867bb,
               }),
            Fp::zero()
    };
    EXPECT_EQ(c.sqrt().value().square(), c); // NOLINT(bugprone-unchecked-optional-access)

    Fp2 const d{
            Fp({
                       0xc5fa1bc8fd00d7f6, 0x3830ca454606003b, 0x2b287f1104b102da,
                       0xa7fb30f28230f23e, 0x339cdb9ee953dbf0, 0x0d78ec51d989fc57,
               }),
            Fp({
                       0x27ec4898cf87f613, 0x9de1394e1abb05a5, 0x0947f85dc170fc14,
                       0x586fbc696b6114b7, 0x2b3475a4077d7169, 0x13e1c895cc4b6c22,
               })
    };
    EXPECT_FALSE(d.sqrt().has_value());
}

TEST(TestFp2, Inv) {
    Fp2 const a{
            Fp({
                       0x1128ecad67549455, 0x9e7a1cff3a4ea1a8, 0xeb208d51e08bcf27,
                       0xe98ad40811f5fc2b, 0x736c3a59232d511d, 0x10acd42d29cfcbb6,
               }),
            Fp({
                       0xd328e37cc2f58d41, 0x948df0858a605869, 0x6032f9d56f93a573,
                       0x2be483ef3fffdc87, 0x30ef61f88f483c2a, 0x1333f55a35725be0,
               })
    };
    Fp2 const b{
            Fp({
                       0x0581a1333d4f48a6, 0x58242f6ef0748500, 0x0292c955349e6da5,
                       0xba37721ddd95fcd0, 0x70d167903aa5dfc5, 0x11895e118b58a9d5,
               }),
            Fp({
                       0x0eda09d2d7a85d17, 0x8808e137a7d1a2cf, 0x43ae2625c1ff21db,
                       0xf85ac9fdf7a74c64, 0x8fccdda5b8da9738, 0x08e84f0cb32cd17d,
               })
    };
    EXPECT_EQ(a.invert().value(), b); // NOLINT(bugprone-unchecked-optional-access)
    EXPECT_FALSE(Fp2::zero().invert().has_value());
}

TEST(TestFp2, Lexical) {
    EXPECT_FALSE(Fp2::zero().lexicographically_largest());
    EXPECT_FALSE(Fp2::one().lexicographically_largest());

    Fp2 const a{
            Fp({
                       0x1128ecad67549455, 0x9e7a1cff3a4ea1a8, 0xeb208d51e08bcf27,
                       0xe98ad40811f5fc2b, 0x736c3a59232d511d, 0x10acd42d29cfcbb6,
               }),
            Fp({
                       0xd328e37cc2f58d41, 0x948df0858a605869, 0x6032f9d56f93a573,
                       0x2be483ef3fffdc87, 0x30ef61f88f483c2a, 0x1333f55a35725be0,
               })
    };
    EXPECT_TRUE(a.lexicographically_largest());

    Fp2 const b{
            -Fp({
                        0x1128ecad67549455, 0x9e7a1cff3a4ea1a8, 0xeb208d51e08bcf27,
                        0xe98ad40811f5fc2b, 0x736c3a59232d511d, 0x10acd42d29cfcbb6,
                }),
            -Fp({
                        0xd328e37cc2f58d41, 0x948df0858a605869, 0x6032f9d56f93a573,
                        0x2be483ef3fffdc87, 0x30ef61f88f483c2a, 0x1333f55a35725be0,
                })
    };
    EXPECT_FALSE(b.lexicographically_largest());

    Fp2 const c{
            Fp({
                       0x1128ecad67549455, 0x9e7a1cff3a4ea1a8, 0xeb208d51e08bcf27,
                       0xe98ad40811f5fc2b, 0x736c3a59232d511d, 0x10acd42d29cfcbb6,
               }),
            Fp::zero()
    };
    EXPECT_FALSE(c.lexicographically_largest());

    Fp2 const d{
            -Fp({
                        0x1128ecad67549455, 0x9e7a1cff3a4ea1a8, 0xeb208d51e08bcf27,
                        0xe98ad40811f5fc2b, 0x736c3a59232d511d, 0x10acd42d29cfcbb6,
                }),
            Fp::zero()
    };
    EXPECT_TRUE(d.lexicographically_largest());
}