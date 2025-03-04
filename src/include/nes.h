#pragma once

#include "types.h"

/* NES Memory Layout */
// $0000 - $00FF(256 bytes)   - Zero Page
// $0100 - $01FF(256 bytes)   - Stack memory
// $0200 - $07FF(1536 bytes)  - RAM
// $0800 - $0FFF(2048 bytes)  - Mirror of $000 - $07FF
// $1000 - $17FF(2048 bytes)  - Mirror of $000 - $07FF
// $1800 - $1FFF(2048 bytes)  - Mirror of $000 - $07FF
// $2000 - $2007(8 bytes)     - I/O registers
// $2008 - $3FFF(8184 bytes)  - Mirror of $2000 - $2007 (repeated)
// $4000 - $401F(32 bytes)    - I/O registers
// $4020 - $5FFF(8160 bytes)  - Expansion ROM
// $6000 - $7FFF(8192 bytes)  - SRAM
// $8000 - $FFFF(32768 bytes) - PRG-ROM
// $FFFA - $FFFB(2 bytes)     - NMI handler routine
// $FFFC - $FFFD(2 bytes)     - Power on reset handler routine
// $FFFE - $FFFF(2 bytes)     - IRQ/BRK handler routine

#define NES_STACK_OFFSET 0x100
#define NES_PRG_RAM_OFFSET 0x6000
#define NES_PRG_DATA_OFFSET 0x8000
#define NES_NMI_HANDLE_OFFSET 0xFFFA
#define NES_RESET_HANDLE_OFFSET 0xFFFC
#define NES_IRQ_BRK_HANDLE_OFFSET 0xFFFE

#define NES_RAM_SIZE 0x800
#define NES_HEADER_SIZE 0x10
#define NES_PRG_DATA_UNIT_SIZE 0x4000
#define NES_PRG_RAM_UNIT_SIZE 0x2000
#define NES_PRG_SLOT_SIZE 0x2000
#define NES_CHR_SLOT_SIZE 0x400

#define NES_DISPLAY_WIDTH 256
#define NES_DISPLAY_HEIGHT 240

typedef struct {
    struct {
        u16 pc;
        u8 s;
        u8 a;
        u8 x;
        u8 y;
        u8 p;
        bool nmi;
        bool irq;
        u64 cycle;
    } cpu;

    struct {
        u8 ram[NES_RAM_SIZE];
    } memory;

    struct {
        struct {
            u8 mapper;   // Mapper ID
            u8 prg_size; // PRG size in 16kB units
            u8 chr_size; // CHR size in 8kB units
            // ppu_mirror_t mirroring; TODO // Mirroring mode if no VRAM
            bool has_vram;    // Cart contains additional VRAM, ignore mirroring mode
            bool has_chr_ram; // Cart contains additional CHR RAM, set if chr_size = 0
            bool has_prg_ram; // Cart contains additional PRG RAM
            u8 prg_ram_size;  // Size of PRG RAM in 8kB units if available
        } config;
        u8* rom;
        u8* prg;
        u8* prg_ram;
        u8* chr;
        u32 prg_map[4];
        u32 chr_map[8];
        // u8 prg_bank;
        // u8 chr_bank;
    } cartridge;
} nes_t;

bool nes_init(nes_t* nes, char const* file);
void nes_step(nes_t* nes);
