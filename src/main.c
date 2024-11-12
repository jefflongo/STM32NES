#include "cartridge.h"
#include "cpu.h"
#include "log.h"

#include <stdlib.h>

int main() {
    if (cartridge_init("roms/smb.nes") != 0) {
        LOG("Failed to load ROM");
        return -1;
    }

    cpu_init();
    while (1) {
        cpu_run();
    }

    return 0;
}