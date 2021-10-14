# README

## For Mac Os BigSure configurations

1. Open Terminal
2. Run `cp ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/esptool.py ~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/`
3. `vim ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/platform.txt`
4. Change binary seventh line => `tools.esptool_py.cmd=esptool` to `tools.esptool_py.cmd=esptool.py`
5. Quit Arduino IDE
6. Run `~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1$ chmod +x esptool.py `

## ESP-32 microprocessors input and output GPIO's

`GPIO13` is **input** from soil humidity sensor
`GPIO15` is output for valve relay

## REST functions

1. Authorization - GET request, send username and password, in response get token

## Valve configuration

HIGH - valve is closed.
LOW - valve is opened.

Valve State is\
OPEN - `0` \
CLOSE -`1`
