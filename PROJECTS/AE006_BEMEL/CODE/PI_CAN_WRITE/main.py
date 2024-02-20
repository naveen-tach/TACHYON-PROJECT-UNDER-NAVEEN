#from periphery import SPI
import exp1
import spidev
import time

# MCP2515 SPI Configuration
spi_bus = 0  # SPI bus number (check using 'ls /dev/spi*')
spi_device = 1  # SPI device (chip-select) number
spi_speed = 1000000  # SPI speed in Hz

# Initialize SPI
spi1_1 = spidev.SpiDev()
spi1_1.open(spi_bus, spi_device)
spi1_1.max_speed_hz = spi_speed
#create mcp2515 instance
mcp2515_instance = exp1.MCP2515()

#create CAN frame object
CAN_frame_instance =exp1.CAN_FRAME( 0x0F6 , 7 ,[ 0x8E , 0x87 , 0x32 , 0xFA , 0x26 , 0x8E , 0xBE , 0x86,0x99 ] )
val= mcp2515_instance.setBitrate(exp1.CAN_SPEED.CAN_125KBPS,spi1_1)
print("set BITRATE :" , val)
val = mcp2515_instance.setNormalMode(spi1_1)
print("set MODE :" , val)

val = mcp2515_instance.sendmessage(CAN_frame_instance,spi1_1)
print("send message return :" , val)
# try:
#   while True:
#     val = mcp2515_instance.sendmessage(CAN_frame_instance,spi1_1)
#     print("set function :" , val)
# finally:
#     print("set function :" , val)  
