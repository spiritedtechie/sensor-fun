import binascii
import struct
import time
from bluepy.bluepy.btle import UUID, Peripheral

temp_uuid = UUID(0x2A6E)

p = Peripheral("98:4F:EE:0D:05:6A", "public")

try:
    ch = p.getCharacteristics(uuid=temp_uuid)[0]
    if (ch.supportsRead()):
        while 1:
            print ch.read()
            val = binascii.b2a_hex(ch.read())
            print val
            val = binascii.unhexlify(val)
            print val
            #val = struct.unpack('f', val)[0]
            #print str(val) + " deg C"
            time.sleep(1)

finally:
    p.disconnect()
