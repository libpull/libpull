#include <stdlib.h>
#include <stdio.h>

#define SERVER_ADDR "fd11:22::74e9:2c62:9046:8129"

#include "network.h" // Test header

int main() {
    printf("starting test\n");
    STEST_INIT();
    //STEST_RUN(test_txp);
    STEST_RUN(test_receiver);
    STEST_END();
    return 0;
}
