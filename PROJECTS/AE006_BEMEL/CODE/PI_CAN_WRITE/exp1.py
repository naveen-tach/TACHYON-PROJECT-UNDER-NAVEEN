import spidev
import RPi.GPIO as GPIO
import time
import CAN

from copy import deepcopy
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(37,GPIO.OUT)
def current_milli_time():
    return round(time.time() * 1000)

# def spi_open(SPI):
#     SPI.open("/dev/spidev0.0", 0, 1000000, bit_order="msb", bits_per_word=8, extra_flags=0)

# def spi_close(SPI):
#     SPI.close()


RXBnCTRL_RXM_STD        = 0x20
RXBnCTRL_RXM_EXT        = 0x40
RXBnCTRL_RXM_STDEXT     = 0x00
RXBnCTRL_RXM_MASK       = 0x60
RXBnCTRL_RTR            = 0x08
RXB0CTRL_BUKT           = 0x04
RXB0CTRL_FILHIT_MASK    = 0x03
RXB1CTRL_FILHIT_MASK    = 0x07
RXB0CTRL_FILHIT         = 0x00
RXB1CTRL_FILHIT         = 0x01

CANSTAT_OPMOD           = 0xE0  #variable


class RXF(enumerate):
    RXF0 = 0,
    RXF1 = 1,
    RXF2 = 2,
    RXF3 = 3,
    RXF4 = 4,
    RXF5 = 5

class CAN_SPEED(enumerate):
    CAN_5KBPS       =0
    CAN_10KBPS      =1
    CAN_20KBPS      =2
    CAN_31K25BPS    =3
    CAN_33KBPS      =4
    CAN_40KBPS      =5
    CAN_50KBPS      =6
    CAN_80KBPS      =7
    CAN_83K3BPS     =8
    CAN_95KBPS      =9
    CAN_100KBPS     =10
    CAN_125KBPS     =11
    CAN_200KBPS     =12
    CAN_250KBPS     =13
    CAN_500KBPS     =14
    CAN_1000KBPS    =15

class CAN_CLOCK(enumerate):
    MCP_20MHZ       =0
    MCP_16MHZ       =1
    MCP_8MHZ        =2


CAN_SFF_ID_BITS   = 11
CAN_EFF_ID_BITS   = 29

# /* CAN payload length and DLC definitions according to ISO 11898-1 */
CAN_MAX_DLC = 8
CAN_MAX_DLEN = 8

class CAN_FRAME:
    def __init__(self,id,dlc,data):
        self.can_id     =   id
        self.can_dlc    =   dlc
        self.can_data   =  data



class ERROR(enumerate):
    ERROR_OK        = 0
    ERROR_FAIL      = 1
    ERROR_ALLTXBUSY = 2
    ERROR_FAILINIT  = 3
    ERROR_FAILTX    = 4
    ERROR_NOMSG     = 5

class CANINTF(enumerate):
    CANINTF_RX0IF = 0x01
    CANINTF_RX1IF = 0x02
    CANINTF_TX0IF = 0x04
    CANINTF_TX1IF = 0x08
    CANINTF_TX2IF = 0x10
    CANINTF_ERRIF = 0x20
    CANINTF_WAKIF = 0x40
    CANINTF_MERRF = 0x80


class CANCTRL_REQOP_MODE(enumerate):
    CANCTRL_REQOP_NORMAL     = 0x00
    CANCTRL_REQOP_SLEEP      = 0x20
    CANCTRL_REQOP_LOOPBACK   = 0x40
    CANCTRL_REQOP_LISTENONLY = 0x60
    CANCTRL_REQOP_CONFIG     = 0x80
    CANCTRL_REQOP_POWERUP    = 0xE0

class INSTRUCTION(enumerate):
    INSTRUCTION_WRITE       = 0x02
    INSTRUCTION_READ        = 0x03
    INSTRUCTION_BITMOD      = 0x05
    INSTRUCTION_LOAD_TX0    = 0x40
    INSTRUCTION_LOAD_TX1    = 0x42
    INSTRUCTION_LOAD_TX2    = 0x44
    INSTRUCTION_RTS_TX0     = 0x81
    INSTRUCTION_RTS_TX1     = 0x82
    INSTRUCTION_RTS_TX2     = 0x84
    INSTRUCTION_RTS_ALL     = 0x87
    INSTRUCTION_READ_RX0    = 0x90
    INSTRUCTION_READ_RX1    = 0x94
    INSTRUCTION_READ_STATUS = 0xA0
    INSTRUCTION_RX_STATUS   = 0xB0
    INSTRUCTION_RESET       = 0xC0

class REGISTER(enumerate):
    MCP_RXF0SIDH = 0x00
    MCP_RXF0SIDL = 0x01
    MCP_RXF0EID8 = 0x02
    MCP_RXF0EID0 = 0x03
    MCP_RXF1SIDH = 0x04
    MCP_RXF1SIDL = 0x05
    MCP_RXF1EID8 = 0x06
    MCP_RXF1EID0 = 0x07
    MCP_RXF2SIDH = 0x08
    MCP_RXF2SIDL = 0x09
    MCP_RXF2EID8 = 0x0A
    MCP_RXF2EID0 = 0x0B
    MCP_CANSTAT  = 0x0E
    MCP_CANCTRL  = 0x0F
    MCP_RXF3SIDH = 0x10
    MCP_RXF3SIDL = 0x11
    MCP_RXF3EID8 = 0x12
    MCP_RXF3EID0 = 0x13
    MCP_RXF4SIDH = 0x14
    MCP_RXF4SIDL = 0x15
    MCP_RXF4EID8 = 0x16
    MCP_RXF4EID0 = 0x17
    MCP_RXF5SIDH = 0x18
    MCP_RXF5SIDL = 0x19
    MCP_RXF5EID8 = 0x1A
    MCP_RXF5EID0 = 0x1B
    MCP_TEC      = 0x1C
    MCP_REC      = 0x1D
    MCP_RXM0SIDH = 0x20
    MCP_RXM0SIDL = 0x21
    MCP_RXM0EID8 = 0x22
    MCP_RXM0EID0 = 0x23
    MCP_RXM1SIDH = 0x24
    MCP_RXM1SIDL = 0x25
    MCP_RXM1EID8 = 0x26
    MCP_RXM1EID0 = 0x27
    MCP_CNF3     = 0x28
    MCP_CNF2     = 0x29
    MCP_CNF1     = 0x2A
    MCP_CANINTE  = 0x2B
    MCP_CANINTF  = 0x2C
    MCP_EFLG     = 0x2D
    MCP_TXB0CTRL = 0x30
    MCP_TXB0SIDH = 0x31
    MCP_TXB0SIDL = 0x32
    MCP_TXB0EID8 = 0x33
    MCP_TXB0EID0 = 0x34
    MCP_TXB0DLC  = 0x35
    MCP_TXB0DATA = 0x36
    MCP_TXB1CTRL = 0x40
    MCP_TXB1SIDH = 0x41
    MCP_TXB1SIDL = 0x42
    MCP_TXB1EID8 = 0x43
    MCP_TXB1EID0 = 0x44
    MCP_TXB1DLC  = 0x45
    MCP_TXB1DATA = 0x46
    MCP_TXB2CTRL = 0x50
    MCP_TXB2SIDH = 0x51
    MCP_TXB2SIDL = 0x52
    MCP_TXB2EID8 = 0x53
    MCP_TXB2EID0 = 0x54
    MCP_TXB2DLC  = 0x55
    MCP_TXB2DATA = 0x56
    MCP_RXB0CTRL = 0x60
    MCP_RXB0SIDH = 0x61
    MCP_RXB0SIDL = 0x62
    MCP_RXB0EID8 = 0x63
    MCP_RXB0EID0 = 0x64
    MCP_RXB0DLC  = 0x65
    MCP_RXB0DATA = 0x66
    MCP_RXB1CTRL = 0x70
    MCP_RXB1SIDH = 0x71
    MCP_RXB1SIDL = 0x72
    MCP_RXB1EID8 = 0x73
    MCP_RXB1EID0 = 0x74
    MCP_RXB1DLC  = 0x75
    MCP_RXB1DATA = 0x76


#send message buffer class
N_TXBUFFERS = 3
N_RXBUFFERS = 2

class TXBn_REGS():
    def __init__(self,CTRL:REGISTER,SIDH:REGISTER,DATA:REGISTER):
        self.CTRL:REGISTER   =   CTRL
        self.SIDH:REGISTER   =   SIDH
        self.DATA:REGISTER  =    DATA

# def TXB(n):
#     if(n == 0):
#         return REGISTER.MCP_TXB0CTRL,REGISTER.MCP_TXB0SIDH,REGISTER.MCP_TXB0DATA
#     elif( n == 1):
#         return REGISTER.MCP_TXB1CTRL,REGISTER.MCP_TXB1SIDH, REGISTER.MCP_TXB1DATA
#     elif(n == 2):
#         return REGISTER.MCP_TXB2CTRL, REGISTER.MCP_TXB2SIDH, REGISTER.MCP_TXB2DATA
TXB = [
    (REGISTER.MCP_TXB0CTRL, REGISTER.MCP_TXB0SIDH, REGISTER.MCP_TXB0DATA),
    (REGISTER.MCP_TXB1CTRL, REGISTER.MCP_TXB1SIDH, REGISTER.MCP_TXB1DATA),
    (REGISTER.MCP_TXB2CTRL, REGISTER.MCP_TXB2SIDH, REGISTER.MCP_TXB2DATA)
]

def get_TXB_values(n):
    return TXB[n]



#read register function
def ReadRegister(reg:REGISTER,SPI):
    reg_byte = [reg]
    instruction_reg =[INSTRUCTION.INSTRUCTION_READ]
    # instruction_reg = [INSTRUCTION.INSTRUCTION_READ | (reg & 0x3F)]
    read_byte =[0x00]
    GPIO.output(37,GPIO.LOW)
    SPI.xfer2(instruction_reg)
    SPI.xfer2(reg_byte)
    val =  SPI.xfer2(read_byte)
    GPIO.output(37,GPIO.HIGH)

    return val

def modifyRegister(REGISTER, mask,mode,SPI):

    instruction_bitmod = [INSTRUCTION.INSTRUCTION_BITMOD]  # Use square brackets to create a list
    register_byte = [REGISTER]
    mask_byte = [mask]
    data_byte = [mode]
    GPIO.output(37,GPIO.LOW)
    SPI.xfer2(instruction_bitmod)
    SPI.xfer2(register_byte)
    SPI.xfer2(mask_byte)
    SPI.xfer2(data_byte)
    GPIO.output(37,GPIO.HIGH)




#set mode function
def SetMode(mode:CANCTRL_REQOP_MODE,SPI):

    modifyRegister(REGISTER.MCP_CANCTRL, MCP2515._CANCTRL_REQOP, mode,SPI)
    modeMatch = False
    endtime = current_milli_time()+10
    newmode = ReadRegister(REGISTER.MCP_CANSTAT,SPI)
    #return newmode

    while current_milli_time()<endtime:
        newmode = ReadRegister(REGISTER.MCP_CANSTAT,SPI)

        newmode[0] &= CANSTAT_OPMOD
        
        modeMatch = newmode[0] == mode

        if (modeMatch):
            print("set mode to :",mode)
            return ERROR.ERROR_OK

    return ERROR.ERROR_FAIL
    
# def setConfigMode():
    # return SetMode(CANCTRL_REQOP_MODE.CANCTRL_REQOP_CONFIG)

#set Registers method
def MCP2515_set_registers(reg:REGISTER,values, n:int,SPI):
    reg_byte = [reg]
    GPIO.output(37,GPIO.LOW)
    SPI.xfer2([INSTRUCTION.INSTRUCTION_WRITE])
    SPI.xfer2(reg_byte)
    i=0
    for i in range(n):
        SPI.xfer2([values[i]])
        #print(values[i])
    GPIO.output(37,GPIO.HIGH)

# #set Register 
def MCP2515_set_register(reg:REGISTER,val:int,SPI):
    GPIO.output(37,GPIO.LOW)
    SPI.xfer2([INSTRUCTION.INSTRUCTION_WRITE])
    SPI.xfer2([reg])
    SPI.xfer2([val])
    GPIO.output(37,GPIO.HIGH)

#mcp2515 reset method
def mcp2515_reset(reg:INSTRUCTION,SPI):
    cs.write(False)
    SPI.transfer([reg])
    cs.write(True)

    time.sleep(10 / 1000)  # Delay in seconds (10 milliseconds converted to seconds)
    # Using bytearray
    zeros = bytearray(14)
    print("These are the registers")
    print(zeros)
    MCP2515_set_registers( REGISTER.MCP_TXB0CTRL, zeros, 14 ,SPI )
    MCP2515_set_registers( REGISTER.MCP_TXB1CTRL, zeros, 14 ,SPI )
    MCP2515_set_registers( REGISTER.MCP_TXB2CTRL, zeros, 14 ,SPI )

    MCP2515_set_register(REGISTER.MCP_RXB0CTRL, 0,SPI)
    MCP2515_set_register(REGISTER.MCP_RXB1CTRL, 0,SPI)
    MCP2515_set_register(REGISTER.MCP_CANINTE, CANINTF.CANINTF_RX0IF | CANINTF.CANINTF_RX1IF | CANINTF.CANINTF_ERRIF | CANINTF.CANINTF_MERRF)
    
    modifyRegister(REGISTER.MCP_RXB0CTRL,
                   RXBnCTRL_RXM_MASK | RXB0CTRL_BUKT | RXB0CTRL_FILHIT_MASK,
                   RXBnCTRL_RXM_STDEXT | RXB0CTRL_BUKT | RXB0CTRL_FILHIT)
    modifyRegister(REGISTER.MCP_RXB1CTRL,
                   RXBnCTRL_RXM_MASK | RXB1CTRL_FILHIT_MASK,
                   RXBnCTRL_RXM_STDEXT | RXB1CTRL_FILHIT)
    
    filters = {RXF.RXF0, RXF.RXF1, RXF.RXF2, RXF.RXF3, RXF.RXF4, RXF.RXF5}

#switch case function
def switch_case(setvalue, cfg1, cfg2,cfg3,canspeed:CAN_SPEED,clock:CAN_CLOCK):
    setvalue=1
    if(clock == CAN_CLOCK.MCP_8MHZ) :
        if(canspeed == CAN_SPEED.CAN_5KBPS):#5KBPS
            cfg1 = CAN.MCP_8MHz_5kBPS_CFG1
            cfg2 = CAN.MCP_8MHz_5kBPS_CFG2
            cfg3 = CAN.MCP_8MHz_5kBPS_CFG3
            return setvalue,cfg1,cfg2,cfg3
        
    if(clock == CAN_CLOCK.MCP_16MHZ):
        if(canspeed == CAN_SPEED.CAN_125KBPS):
            cfg1=CAN.MCP_16MHz_125kBPS_CFG1
            cfg2=CAN.MCP_16MHz_125kBPS_CFG2
            cfg3=CAN.MCP_16MHz_125kBPS_CFG3
            return setvalue,cfg1,cfg2,cfg3
        







def MCP2515_set_bitrate(canspeed:CAN_SPEED,clock:CAN_CLOCK,SPI):
    set_value = 1
    cfg1 = cfg2 = cfg3 = 0
    set_value,cfg1,cfg2,cfg3 = switch_case(set_value, cfg1, cfg2,cfg3,canspeed,clock)
    if(set_value):
        MCP2515_set_register(REGISTER.MCP_CNF1,cfg1,SPI)
        MCP2515_set_register(REGISTER.MCP_CNF2,cfg2,SPI)
        MCP2515_set_register(REGISTER.MCP_CNF3,cfg3,SPI)
        return ERROR.ERROR_OK
    else:
        return ERROR.ERROR_FAIL
    
def sendM(txb:CAN.TXBn,frame:CAN_FRAME,SPI):
    print("sendm")
    print("can id :",frame.can_id)
    print("can dlc:",frame.can_dlc)
    if(frame.can_dlc > CAN_MAX_DLEN):
        return ERROR.ERROR_FAILTX
    
    data = [0] * 13

    TXbuff = TXBn_REGS(*get_TXB_values(txb))

    ext = (frame.can_id & CAN.CAN_EFF_FLAG)
    rtr = (frame.can_id & CAN.CAN_RTR_FLAG)
    id = frame.can_id & (CAN.CAN_EFF_MASK if ext else CAN.CAN_SFF_MASK) #uint32_t id = (frame->can_id & (ext ? CAN_EFF_MASK : CAN_SFF_MASK));

    prepare_id(data, ext, id)

    data[CAN.MCP_DLC] = (frame.can_dlc | CAN.RTR_MASK) if rtr else frame.can_dlc
 

    data[CAN.MCP_DATA:CAN.MCP_DATA + frame.can_dlc] = deepcopy(frame.can_data) 
    print("buff reg :",TXbuff.SIDH)
 
    MCP2515_set_registers(TXbuff.SIDH, data, 5 + frame.can_dlc,SPI)

    modifyRegister(TXbuff.CTRL, CAN.TXBnCTRL.TXB_TXREQ, CAN.TXBnCTRL.TXB_TXREQ,SPI)

    ctrl = ReadRegister(TXbuff.CTRL,SPI)
    if((ctrl[0] & (CAN.TXBnCTRL.TXB_ABTF | CAN.TXBnCTRL.TXB_MLOA | CAN.TXBnCTRL.TXB_TXERR)) != 0):
        return ERROR.ERROR_FAILTX
    return ERROR.ERROR_OK
    
    

def prepare_id(buffer, ext, can_id):
    canid = can_id & 0x0FFFF

    if ext:
        buffer[CAN.MCP_EID0] = canid & 0xFF
        buffer[CAN.MCP_EID8] = canid >> 8
        canid = can_id >> 16
        buffer[CAN.MCP_SIDL] = (canid & 0x03)
        buffer[CAN.MCP_SIDL] += (canid & 0x1C) << 3
        buffer[CAN.MCP_SIDL] |= CAN.TXB_EXIDE_MASK
        buffer[CAN.MCP_SIDH] = canid >> 5
    else:
        buffer[CAN.MCP_SIDH] = canid >> 3
        buffer[CAN.MCP_SIDL] = (canid & 0x07) << 5
        buffer[CAN.MCP_EID0] = 0
        buffer[CAN.MCP_EID8] = 0



def sendmsg(obj:CAN_FRAME,SPI):

    if(obj.can_dlc > CAN_MAX_DLEN):
        print("its in sendmsg, dlc error")
        return ERROR.ERROR_FAILTX
        #    return 1
    
    txbuffers = {CAN.TXBn.TXB0, CAN.TXBn.TXB1, CAN.TXBn.TXB2}
    for buffer in range(3):
        print("sendmsg-> buffer :",buffer)
        TXbuff = TXBn_REGS(*get_TXB_values(buffer))
        print("txbuff ->ctrl  :",TXbuff.CTRL)
        ctrlval = ReadRegister(TXbuff.CTRL,SPI)
        print(ctrlval)
        if(ctrlval[0] &  CAN.TXBnCTRL.TXB_TXREQ    == 0):
            return sendM(buffer,obj,SPI)
        # return 1
    
    return ERROR.ERROR_ALLTXBUSY

    



class MCP2515:
    def __init__ (self):
        GPIO.output(37,GPIO.HIGH)

    CANSTAT_OPMOD = 0xE0
    _CANCTRL_REQOP = 0xE0

    def setSleepMode(self,SPI):
        return SetMode(CANCTRL_REQOP_MODE.CANCTRL_REQOP_SLEEP,SPI)
    
    def setLoopbackMode(self,SPI):
        return SetMode(CANCTRL_REQOP_MODE.CANCTRL_REQOP_LOOPBACK,SPI)

    def setNormalMode(self,SPI):
        return SetMode(CANCTRL_REQOP_MODE.CANCTRL_REQOP_NORMAL,SPI)
    def reset(self,SPI):
        mcp2515_reset(INSTRUCTION.INSTRUCTION_RESET,SPI)
    
    def setBitrate(self,canspeed:CAN_SPEED,SPI):
        error =MCP2515.setConfigMode(SPI)
        if(error !=ERROR.ERROR_OK):
            print("Its error...")
            return error
        return MCP2515_set_bitrate(canspeed,CAN_CLOCK.MCP_16MHZ,SPI)
    
    def sendmessage(self,obj:CAN_FRAME,SPI):
        return sendmsg(obj,SPI)

    def setConfigMode(SPI):

        return SetMode(CANCTRL_REQOP_MODE.CANCTRL_REQOP_CONFIG,SPI)
    
    # def SetBitrate(CAN_SPEED):
    #     return SetBitrate(CAN_SPEED, CAN_CLOCK.MCP_16MHZ)
    

    
