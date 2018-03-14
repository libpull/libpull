#include "common/error.h"
#include "memory/memory.h"
#include "memory_mock.h"

pull_error memory_open_impl(mem_object* ctx, obj_id obj);
uint16_t memory_read_impl(mem_object* ctx, void* memory_buffer, uint16_t size, uint32_t offset);
uint16_t memory_write_impl(mem_object* ctx, const void* memory_buffer, uint16_t size, uint32_t offset);
pull_error memory_flush_impl(mem_object* ctx);
pull_error memory_close_impl(mem_object* ctx);

memory_mock_t memory_mock = {
    .memory_open_impl = memory_open_impl,
    .memory_read_impl = memory_read_impl,
    .memory_write_impl = memory_write_impl,
    .memory_flush_impl = memory_flush_impl,
    .memory_close_impl = memory_close_impl
};

void memory_mock_restore() {
    memory_mock.memory_open_impl = memory_open_impl;
    memory_mock.memory_read_impl = memory_read_impl;
    memory_mock.memory_write_impl = memory_write_impl;
    memory_mock.memory_flush_impl = memory_flush_impl;
    memory_mock.memory_close_impl = memory_close_impl;
}

inline pull_error memory_open(mem_object* ctx, obj_id obj) {
    return memory_mock.memory_open_impl(ctx, obj);
}

inline int memory_read(mem_object* ctx, void* memory_buffer, uint16_t size, uint32_t offset) {
    return memory_mock.memory_read_impl(ctx, memory_buffer, size, offset);
}

inline int memory_write(mem_object* ctx, const void* memory_buffer, uint16_t size, uint32_t offset) {
    return memory_mock.memory_write_impl(ctx, memory_buffer, size, offset);
}

inline pull_error memory_flush(mem_object* ctx) {
    return memory_mock.memory_flush_impl(ctx);
}

inline pull_error memory_close(mem_object* ctx) {
    return memory_mock.memory_close_impl(ctx);
}

pull_error memory_open_invalid(mem_object* ctx, obj_id obj) {
    return GENERIC_ERROR;
}
uint16_t memory_read_invalid(mem_object* ctx, void* memory_buffer, uint16_t size, uint32_t offset) {
    return 0;
}
uint16_t memory_write_invalid(mem_object* ctx, const void* memory_buffer, uint16_t size, uint32_t offset) {
    return 0;
}
pull_error memory_flush_invalid(mem_object* ctx) {
    return GENERIC_ERROR;
}
pull_error memory_close_invalid(mem_object* ctx) {
    return GENERIC_ERROR;
}