sudo avrdude -c avrispmkII -p t45 -P usb -Uflash:w:.pioenvs/attiny45/firmware.hex:i -B 30
sudo avrdude -c avrispmkII -p t45 -P usb -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m -B 30
