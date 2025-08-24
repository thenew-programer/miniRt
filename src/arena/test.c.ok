#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>
#include "arena.h"

// Test framework macros
#define TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s - %s\n", __func__, message); \
            return 0; \
        } \
    } while(0)

#define TEST_PASS() \
    do { \
        printf("PASS: %s\n", __func__); \
        return 1; \
    } while(0)

#define RUN_TEST(test) \
    do { \
        printf("Running %s...\n", #test); \
        if (test()) { \
            tests_passed++; \
        } else { \
            tests_failed++; \
        } \
        total_tests++; \
    } while(0)

// Test statistics
static int total_tests = 0;
static int tests_passed = 0;
static int tests_failed = 0;

// Helper functions
static int is_aligned(void *ptr, size_t alignment)
{
    uintptr_t addr = (uintptr_t)ptr;
    return (addr % alignment) == 0;
}

static int is_error_ptr(void *ptr)
{
    return (intptr_t)ptr < 0;
}

static void fill_pattern(void *ptr, size_t size, unsigned char pattern)
{
    memset(ptr, pattern, size);
}

static int check_pattern(void *ptr, size_t size, unsigned char pattern)
{
    unsigned char *bytes = (unsigned char *)ptr;
    for (size_t i = 0; i < size; i++) {
        if (bytes[i] != pattern) {
            return 0;
        }
    }
    return 1;
}

// ============================================================================
// BASIC FUNCTIONALITY TESTS
// ============================================================================

static int test_arena_init_valid()
{
    t_arena arena;
    char buffer[1024];
    
    t_arena_error result = arena_init(&arena, buffer, sizeof(buffer), 8);
    
    TEST_ASSERT(result == ARENA_OK, "arena_init should succeed with valid params");
    TEST_ASSERT(arena.buffer == buffer, "buffer should be set correctly");
    TEST_ASSERT(arena.size == sizeof(buffer), "size should be set correctly");
    TEST_ASSERT(arena.offset == 0, "offset should be initialized to 0");
    TEST_ASSERT(arena.alignment == 8, "alignment should be set correctly");
    TEST_ASSERT(!arena.own_buffer, "should not own external buffer");
    TEST_ASSERT(arena.magic == ARENA_MAGIC_NUMBER, "magic number should be set");
    
    TEST_PASS();
}

static int test_arena_init_null_params()
{
    t_arena arena;
    char buffer[1024];
    
    // Test NULL arena
    t_arena_error result = arena_init(NULL, buffer, sizeof(buffer), 8);
    TEST_ASSERT(result == ARENA_ERROR_NULL_PARAM, "should fail with NULL arena");
    
    // Test NULL buffer
    result = arena_init(&arena, NULL, sizeof(buffer), 8);
    TEST_ASSERT(result == ARENA_ERROR_NULL_PARAM, "should fail with NULL buffer");
    
    TEST_PASS();
}

static int test_arena_create_valid()
{
    t_arena arena;
    
    t_arena_error result = arena_create(&arena, 1024, 8);
    
    TEST_ASSERT(result == ARENA_OK, "arena_create should succeed");
    TEST_ASSERT(arena.buffer != NULL, "buffer should be allocated");
    TEST_ASSERT(arena.size == 1024, "size should be set correctly");
    TEST_ASSERT(arena.offset == 0, "offset should be initialized to 0");
    TEST_ASSERT(arena.alignment == 8, "alignment should be set correctly");
    TEST_ASSERT(arena.own_buffer, "should own allocated buffer");
    TEST_ASSERT(arena.magic == ARENA_MAGIC_NUMBER, "magic number should be set");
    
    arena_destroy(&arena);
    TEST_PASS();
}

static int test_basic_allocation()
{
    t_arena arena;
    char buffer[1024];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    // Test single allocation
    void *ptr1 = arena_alloc(&arena, 64);
    TEST_ASSERT(ptr1 != NULL, "allocation should succeed");
    TEST_ASSERT(!is_error_ptr(ptr1), "should not return error code");
    TEST_ASSERT(is_aligned(ptr1, 8), "pointer should be aligned");
    TEST_ASSERT(arena.offset == 64, "offset should be updated");
    
    // Test second allocation
    void *ptr2 = arena_alloc(&arena, 32);
    TEST_ASSERT(ptr2 != NULL, "second allocation should succeed");
    TEST_ASSERT(ptr2 > ptr1, "second pointer should be after first");
    TEST_ASSERT((char*)ptr2 - (char*)ptr1 >= 64, "allocations should not overlap");
    
    TEST_PASS();
}

// ============================================================================
// ALIGNMENT TESTS
// ============================================================================

static int test_alignment_basic()
{
    t_arena arena;
    char buffer[1024];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    // Test various alignments
    size_t alignments[] = {1, 2, 4, 8, 16, 32};
    size_t num_alignments = sizeof(alignments) / sizeof(alignments[0]);
    
    for (size_t i = 0; i < num_alignments; i++) {
        arena_reset(&arena);
        
        void *ptr = arena_alloc_aligned(&arena, 16, alignments[i]);
        TEST_ASSERT(ptr != NULL, "aligned allocation should succeed");
        TEST_ASSERT(is_aligned(ptr, alignments[i]), "pointer should be properly aligned");
    }
    
    TEST_PASS();
}

static int test_alignment_with_offset()
{
    t_arena arena;
    char buffer[1024];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    // Create unaligned offset
    void *ptr1 = arena_alloc_aligned(&arena, 5, 1);
    TEST_ASSERT(ptr1 != NULL, "first allocation should succeed");
    TEST_ASSERT(arena.offset == 5, "offset should be 5");
    
    // Request 8-byte aligned allocation
    void *ptr2 = arena_alloc_aligned(&arena, 16, 8);
    TEST_ASSERT(ptr2 != NULL, "aligned allocation should succeed");
    TEST_ASSERT(is_aligned(ptr2, 8), "pointer should be 8-byte aligned");
    
    // Check that padding was added
    uintptr_t expected_addr = (uintptr_t)buffer;
    expected_addr = (expected_addr + 5 + 8 - 1) & ~(8 - 1);
    TEST_ASSERT((uintptr_t)ptr2 == expected_addr, "alignment padding should be correct");
    
    TEST_PASS();
}

static int test_alignment_edge_cases()
{
    t_arena arena;
    char buffer[1024];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    // Test zero alignment (should fail)
    void *ptr = arena_alloc_aligned(&arena, 16, 0);
    TEST_ASSERT(is_error_ptr(ptr), "zero alignment should fail");
    
    // Test non-power-of-2 alignment (should fail)
    ptr = arena_alloc_aligned(&arena, 16, 3);
    TEST_ASSERT(is_error_ptr(ptr), "non-power-of-2 alignment should fail");
    
    ptr = arena_alloc_aligned(&arena, 16, 12);
    TEST_ASSERT(is_error_ptr(ptr), "non-power-of-2 alignment should fail");
    
    TEST_PASS();
}

// ============================================================================
// BOUNDARY AND ERROR TESTS
// ============================================================================

static int test_out_of_memory()
{
    t_arena arena;
    char buffer[100];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    // Fill most of arena
    void *ptr1 = arena_alloc(&arena, 80);
    TEST_ASSERT(ptr1 != NULL, "first allocation should succeed");
    
    // Try to allocate more than remaining space
    void *ptr2 = arena_alloc(&arena, 50);
    TEST_ASSERT(is_error_ptr(ptr2), "oversized allocation should fail");
    
    // Arena state should be unchanged after failed allocation
    TEST_ASSERT(arena.offset == 80, "offset should be unchanged after failed allocation");
    
    TEST_PASS();
}

static int test_zero_size_allocation()
{
    t_arena arena;
    char buffer[1024];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    void *ptr = arena_alloc(&arena, 0);
    TEST_ASSERT(is_error_ptr(ptr), "zero-size allocation should fail");
    TEST_ASSERT(arena.offset == 0, "offset should be unchanged");
    
    TEST_PASS();
}

static int test_massive_allocation()
{
    t_arena arena;
    char buffer[1024];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    // Try to allocate huge amount
    void *ptr = arena_alloc(&arena, SIZE_MAX);
    TEST_ASSERT(is_error_ptr(ptr), "massive allocation should fail");
    
    ptr = arena_alloc(&arena, LONG_MAX);
    TEST_ASSERT(is_error_ptr(ptr), "LONG_MAX allocation should fail");
    
    TEST_PASS();
}

static int test_null_arena_parameter()
{
    void *ptr = arena_alloc(NULL, 64);
    TEST_ASSERT(is_error_ptr(ptr), "NULL arena should fail");
    
    ptr = arena_alloc_aligned(NULL, 64, 8);
    TEST_ASSERT(is_error_ptr(ptr), "NULL arena should fail");
    
    char *str = arena_strdup(NULL, "test");
    TEST_ASSERT(is_error_ptr(str), "NULL arena should fail");
    
    TEST_PASS();
}

// ============================================================================
// MEMORY PATTERN TESTS
// ============================================================================

static int test_memory_isolation()
{
    t_arena arena;
    char buffer[1024];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    // Allocate and fill first block
    void *ptr1 = arena_alloc(&arena, 64);
    TEST_ASSERT(ptr1 != NULL, "first allocation should succeed");
    fill_pattern(ptr1, 64, 0xAA);
    
    // Allocate and fill second block
    void *ptr2 = arena_alloc(&arena, 64);
    TEST_ASSERT(ptr2 != NULL, "second allocation should succeed");
    fill_pattern(ptr2, 64, 0xBB);
    
    // Verify first block wasn't corrupted
    TEST_ASSERT(check_pattern(ptr1, 64, 0xAA), "first block should be intact");
    TEST_ASSERT(check_pattern(ptr2, 64, 0xBB), "second block should be intact");
    
    TEST_PASS();
}

static int test_arena_reset()
{
    t_arena arena;
    char buffer[1024];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    // Allocate some memory
    void *ptr1 = arena_alloc(&arena, 100);
    TEST_ASSERT(ptr1 != NULL, "allocation should succeed");
    TEST_ASSERT(arena.offset == 100, "offset should be updated");
    
    // Reset arena
    arena_reset(&arena);
    TEST_ASSERT(arena.offset == 0, "offset should be reset to 0");
    
    // Should be able to allocate from beginning again
    void *ptr2 = arena_alloc(&arena, 100);
    TEST_ASSERT(ptr2 == ptr1, "should get same pointer after reset");
    
    TEST_PASS();
}

// ============================================================================
// STRING DUPLICATION TESTS
// ============================================================================

static int test_arena_strdup()
{
    t_arena arena;
    char buffer[1024];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    const char *original = "Hello, World!";
    char *copy = arena_strdup(&arena, original);
    
    TEST_ASSERT(copy != NULL, "strdup should succeed");
    TEST_ASSERT(!is_error_ptr(copy), "should not return error code");
    TEST_ASSERT(strcmp(copy, original) == 0, "strings should be identical");
    TEST_ASSERT(copy != original, "should be different memory locations");
    
    // Check null termination
    size_t len = strlen(original);
    TEST_ASSERT(copy[len] == '\0', "string should be null terminated");
    
    TEST_PASS();
}

static int test_arena_strdup_null()
{
    t_arena arena;
    char buffer[1024];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    char *copy = arena_strdup(&arena, NULL);
    TEST_ASSERT(is_error_ptr(copy), "strdup with NULL should fail");
    
    TEST_PASS();
}

static int test_arena_strdup_empty()
{
    t_arena arena;
    char buffer[1024];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    char *copy = arena_strdup(&arena, "");
    TEST_ASSERT(copy != NULL, "empty string strdup should succeed");
    TEST_ASSERT(strlen(copy) == 0, "copied string should be empty");
    TEST_ASSERT(copy[0] == '\0', "should be null terminated");
    
    TEST_PASS();
}

// ============================================================================
// CALLOC TESTS
// ============================================================================

static int test_arena_calloc()
{
    t_arena arena;
    char buffer[1024];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    void *ptr = arena_calloc(&arena, 64);
    TEST_ASSERT(ptr != NULL, "calloc should succeed");
    TEST_ASSERT(!is_error_ptr(ptr), "should not return error code");
    
    // Check that memory is zeroed
    TEST_ASSERT(check_pattern(ptr, 64, 0x00), "memory should be zero-initialized");
    
    TEST_PASS();
}

// ============================================================================
// STRESS TESTS
// ============================================================================

static int test_many_small_allocations()
{
    t_arena arena;
    char buffer[8192];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    const int num_allocs = 1000;
    void *ptrs[num_allocs];
    
    // Allocate many small blocks
    for (int i = 0; i < num_allocs; i++) {
        ptrs[i] = arena_alloc(&arena, 4);
        if (is_error_ptr(ptrs[i])) {
            // Out of memory is expected
            break;
        }
        
        // Fill with pattern
        fill_pattern(ptrs[i], 4, (unsigned char)i);
    }
    
    // Verify no corruption occurred
    for (int i = 0; i < num_allocs && !is_error_ptr(ptrs[i]); i++) {
        TEST_ASSERT(check_pattern(ptrs[i], 4, (unsigned char)i), 
                   "allocation should not be corrupted");
    }
    
    TEST_PASS();
}

static int test_mixed_size_allocations()
{
    t_arena arena;
    char buffer[4096];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    size_t sizes[] = {1, 3, 7, 15, 31, 63, 127, 255};
    size_t num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    void *ptrs[100];
    int alloc_count = 0;
    
    // Allocate with varying sizes
    for (int round = 0; round < 10 && alloc_count < 100; round++) {
        for (size_t i = 0; i < num_sizes && alloc_count < 100; i++) {
            ptrs[alloc_count] = arena_alloc(&arena, sizes[i]);
            if (is_error_ptr(ptrs[alloc_count])) {
                goto verify_phase;
            }
            
            fill_pattern(ptrs[alloc_count], sizes[i], (unsigned char)(alloc_count + 1));
            alloc_count++;
        }
    }
    
verify_phase:
    // Verify integrity
    for (int i = 0; i < alloc_count; i++) {
        size_t size = sizes[i % num_sizes];
        TEST_ASSERT(check_pattern(ptrs[i], size, (unsigned char)(i + 1)),
                   "mixed allocation should not be corrupted");
    }
    
    TEST_PASS();
}

static int test_alignment_stress()
{
    t_arena arena;
    char buffer[4096];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    size_t alignments[] = {1, 2, 4, 8, 16, 32};
    size_t num_alignments = sizeof(alignments) / sizeof(alignments[0]);
    
    // Allocate with various alignments
    for (int i = 0; i < 50; i++) {
        size_t alignment = alignments[i % num_alignments];
        size_t size = 8 + (i % 64);
        
        void *ptr = arena_alloc_aligned(&arena, size, alignment);
        if (is_error_ptr(ptr)) {
            // Out of memory is expected
            break;
        }
        
        TEST_ASSERT(is_aligned(ptr, alignment), "allocation should be properly aligned");
        fill_pattern(ptr, size, (unsigned char)i);
    }
    
    TEST_PASS();
}

// ============================================================================
// PERFORMANCE TESTS
// ============================================================================

static int test_allocation_performance()
{
    t_arena arena;
    size_t arena_size = 1024 * 1024; // 1MB
    char *buffer = malloc(arena_size);
    TEST_ASSERT(buffer != NULL, "test buffer allocation should succeed");
    
    arena_init(&arena, buffer, arena_size, 8);
    
    clock_t start = clock();
    
    // Perform many allocations
    const int num_allocs = 10000;
    for (int i = 0; i < num_allocs; i++) {
        void *ptr = arena_alloc(&arena, 64);
        if (is_error_ptr(ptr)) {
            break;
        }
    }
    
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("Allocated %d blocks in %f seconds\n", num_allocs, time_taken);
    printf("Average time per allocation: %f microseconds\n", 
           (time_taken * 1000000) / num_allocs);
    
    free(buffer);
    TEST_PASS();
}

// ============================================================================
// COMPREHENSIVE INTEGRATION TESTS
// ============================================================================

static int test_realistic_usage_scenario()
{
    t_arena arena;
    char buffer[8192];
    arena_init(&arena, buffer, sizeof(buffer), 8);
    
    // Simulate parsing a configuration file
    char *config_name = arena_strdup(&arena, "my_config.txt");
    TEST_ASSERT(config_name != NULL, "config name allocation should succeed");
    
    // Allocate array of settings
    typedef struct {
        char *key;
        char *value;
        int enabled;
    } setting_t;
    
    setting_t *settings = arena_alloc(&arena, sizeof(setting_t) * 10);
    TEST_ASSERT(settings != NULL, "settings array allocation should succeed");
    
    // Fill settings
    for (int i = 0; i < 10; i++) {
        char key_buf[32], value_buf[32];
        sprintf(key_buf, "key_%d", i);
        sprintf(value_buf, "value_%d", i);
        
        settings[i].key = arena_strdup(&arena, key_buf);
        settings[i].value = arena_strdup(&arena, value_buf);
        settings[i].enabled = i % 2;
        
        TEST_ASSERT(settings[i].key != NULL, "key allocation should succeed");
        TEST_ASSERT(settings[i].value != NULL, "value allocation should succeed");
    }
    
    // Verify data integrity
    for (int i = 0; i < 10; i++) {
        char expected_key[32], expected_value[32];
        sprintf(expected_key, "key_%d", i);
        sprintf(expected_value, "value_%d", i);
        
        TEST_ASSERT(strcmp(settings[i].key, expected_key) == 0, "key should match");
        TEST_ASSERT(strcmp(settings[i].value, expected_value) == 0, "value should match");
        TEST_ASSERT(settings[i].enabled == (i % 2), "enabled flag should match");
    }
    
    TEST_PASS();
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

int main()
{
    printf("Starting Arena Allocator Test Suite\n");
    printf("====================================\n\n");
    
    // Basic functionality tests
    RUN_TEST(test_arena_init_valid);
    RUN_TEST(test_arena_init_null_params);
    RUN_TEST(test_arena_create_valid);
    RUN_TEST(test_basic_allocation);
    
    // Alignment tests
    RUN_TEST(test_alignment_basic);
    RUN_TEST(test_alignment_with_offset);
    RUN_TEST(test_alignment_edge_cases);
    
    // Boundary and error tests
    RUN_TEST(test_out_of_memory);
    RUN_TEST(test_zero_size_allocation);
    RUN_TEST(test_massive_allocation);
    RUN_TEST(test_null_arena_parameter);
    
    // Memory pattern tests
    RUN_TEST(test_memory_isolation);
    RUN_TEST(test_arena_reset);
    
    // String duplication tests
    RUN_TEST(test_arena_strdup);
    RUN_TEST(test_arena_strdup_null);
    RUN_TEST(test_arena_strdup_empty);
    
    // Calloc tests
    RUN_TEST(test_arena_calloc);
    
    // Stress tests
    RUN_TEST(test_many_small_allocations);
    RUN_TEST(test_mixed_size_allocations);
    RUN_TEST(test_alignment_stress);
    
    // Performance tests
    RUN_TEST(test_allocation_performance);
    
    // Integration tests
    RUN_TEST(test_realistic_usage_scenario);
    
    // Print results
    printf("\n====================================\n");
    printf("Test Results:\n");
    printf("Total tests: %d\n", total_tests);
    printf("Passed: %d\n", tests_passed);
    printf("Failed: %d\n", tests_failed);
    printf("Success rate: %.1f%%\n", (double)tests_passed / total_tests * 100);
    
    if (tests_failed == 0) {
        printf("\n✅ ALL TESTS PASSED! Arena is production ready.\n");
    } else {
        printf("\n❌ Some tests failed. Fix issues before production use.\n");
    }
    
    return tests_failed == 0 ? 0 : 1;
}
