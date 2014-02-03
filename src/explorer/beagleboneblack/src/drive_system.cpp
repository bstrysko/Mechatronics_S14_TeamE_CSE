#include <drive_system.h>

DriveSystem::DriveSystem(I2CBus* bus, uint8_t address) : I2CDevice(bus, address)
{
}

DriveSystem::~DriveSystem()
{

}
