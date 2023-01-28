#ifndef BLS12_381_BIT_H
#define BLS12_381_BIT_H

#include <cstdint>
#include <array>

namespace bls12_381::util::bit_operation {

/// Converts a byte array to a 64-bit unsigned integer.
uint64_t be_bytes_to_uint64(std::array<uint8_t, sizeof(uint64_t)> bytes);
uint64_t le_bytes_to_uint64(std::array<uint8_t, sizeof(uint64_t)> bytes);

/// Converts a 64-bit unsigned integer to a byte array.
std::array<uint8_t, sizeof(uint64_t)> uint64_to_be_bytes(uint64_t value);
std::array<uint8_t, sizeof(uint64_t)> uint64_to_le_bytes(uint64_t value);

} // namespace bls12_381::util::bit_operation

#endif //BLS12_381_BIT_H