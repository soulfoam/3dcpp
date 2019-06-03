#pragma once

#include <cstdint>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using f32 = float;
using f64 = double;

#define delete_copy_and_move(C) \
	C(const C &) = delete; \
C(C &&) = delete; \
C &operator=(const C &) = delete; \
C &operator=(C &&) = delete

#define delete_copy(C) \
C(const C &) = delete; \
C &operator=(const C &) = delete
