#include "Bus.h"
#include "CPU.cpp"
#include "APU.cpp"

Bus::Bus() {
    cpu = new CPU();
    cpu->connectBus(this);  // Connect CPU to Bus
    APU apu;
}

Bus::~Bus() = default;

void Bus::write(uint16_t address, uint8_t data) {

    if (address >= 0x0000 && address <= 0x1FFF) {
        cpuRam[address & 0x07FF] = data;
    } else if (address >= 0x2000 && address <= 0x3FFF) {
        ppuRegister[(address - 0x2000) % 0x8] = data;
    } else if ((address >= 0x4000 && address <= 0x4013) || address == 0x4015 || address == 0x4017) {
        // TODO: write to APU address
        apu.apuRegister[(address - 0x4000)] = data;
    } else if (address == 0x4014) {
        // TODO: write to address for DMA transfer
    } else if (address >= 0x4016 && address <= 0x4017) {
        // TODO: write to address and save controller state
    } else if (address >= 0x4020 && address <= 0xFFFF) {
        // TODO: write to cartridge memory
    }
}

uint8_t Bus::read(uint16_t address) {
    if (address >= 0x0000 && address <= 0x1FFF) {
        return cpuRam[address & 0x07FF];
    } else if (address >= 0x2000 && address <= 0x3FFF) {
        // TODO: read from PPU registers and mirror
        return ppuRegister[(address - 0x2000) % 0x8];
    } //else if ((address >= 0x4000 && address <= 0x4013) || address == 0x4015 || address == 0x4017) {
      else if (address == 0x4015) {
        // TODO: read from APU address
        // APU registers are write-only, save for 0x4015 (status register)
        return apu.apuRegister[address];
    } else if (address == 0x4014) {
        // TODO: read from address for DMA transfer
    } else if (address >= 0x4016 && address <= 0x4017) {
        // TODO: read from address and save controller state
    } else if (address >= 0x4020 && address <= 0xFFFF) {
        // TODO: read from cartridge memory
    }
    return -1;
}

void Bus::reset() const {
    cpu->reset();
    // TODO: add resets for other components
}

void Bus::clock() const {
    // TODO: cycle the PPU and the APU

    if (clockCounter % 3 == 0) {
        // TODO: cycle the CPU
    }
}
