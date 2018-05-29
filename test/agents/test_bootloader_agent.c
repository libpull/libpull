#include <libpull/security/sha256.h>
#include "libpull_agents/bootloader_agent.h"

#include "support/sample_data.h"
#include "support/test_runner.h"
#include "unity.h"
#include <unistd.h>

#define FOREACH_TEST(DO) \
    DO(bootloader_success, 0)

TEST_RUNNER();

#define BUFFER_SIZE 1024

static agent_msg_t agent_msg;
static bootloader_agent_config cfg;

static int8_t retries = 3;
static uint8_t success = 0;
static uint8_t buffer[BUFFER_SIZE];

// The test logic should update the OBJ_2 with the firmware with version 0xdead
// After the test is finished I invalidate the OBJ_2 to restore the status
void setUp(void) {
    override_memory_object(OBJ_1, "../assets/external_flash_simulator_updated", 0x19000, 0x32000);
    override_memory_object(OBJ_2, "../assets/external_flash_simulator_updated", 0x32000, 0x4B000);
    override_memory_object(OBJ_RUN, "../assets/internal_flash_simulator_updated", 0x7000, 0x20000);
    mem_object_t obj_t;
    TEST_ASSERT_TRUE(invalidate_object(OBJ_RUN, &obj_t) == PULL_SUCCESS);
    bzero(&cfg, sizeof(cfg));
}

void tearDown(void) { 
    retries = 3;
    success = 0;
}

void test_bootloader_success(void) {
    bootloader_agent_vendor_keys(&cfg, vendor_x_g, vendor_y_g);
    bootloader_agent_digest_func(&cfg, tinydtls_digest_sha256);
    bootloader_agent_ecc_func(&cfg, tinydtls_secp256r1_ecc);
    bootloader_agent_set_buffer(&cfg, buffer, BUFFER_SIZE);
    cfg.bootloader_ctx_id = BOOTLOADER_CTX;
    cfg.recovery_id = OBJ_GOLD;
    while(1) {
        agent_msg = bootloader_agent(&cfg);
        if (IS_FAILURE(agent_msg)) {
            printf("error is:%s\n", (err_as_str(agent_msg.event_data)));
            success = false;
            break;
        } else if (IS_CONTINUE(agent_msg)) {
            if (agent_msg.event == EVENT_BOOT) {
                TEST_ASSERT_TRUE(agent_msg.event == EVENT_BOOT);
                success = true;
                break;
            }
            continue;
        }
    }
    TEST_ASSERT_TRUE_MESSAGE(success, "Error during the booting process");
}
