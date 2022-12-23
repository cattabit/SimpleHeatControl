################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
D:\Sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\3.0.2\libraries\Hash\src\Hash.cpp 

LINK_OBJ += \
.\libraries\Hash\src\Hash.cpp.o 

CPP_DEPS += \
.\libraries\Hash\src\Hash.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries\Hash\src\Hash.cpp.o: D:\Sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\3.0.2\libraries\Hash\src\Hash.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:\Sloeber\arduinoPlugin\packages\esp8266\tools\xtensa-lx106-elf-gcc\3.0.4-gcc10.3-1757bed/bin/xtensa-lx106-elf-g++" -D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ -D_GNU_SOURCE "-ID:\Sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\3.0.2/tools/sdk/include" "-ID:\Sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\3.0.2/tools/sdk/lwip2/include" "-ID:\Sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\3.0.2/tools/sdk/libc/xtensa-lx106-elf/include" "-ID:\20_YandexDisk\05_PROJECTS\05_MyOwn\sloeber-workspace\HeatControl\Release/core" -c -w -Werror=return-type  -Os -g -free -fipa-pta -mlongcalls -mtext-section-literals -fno-rtti -falign-functions=4 -std=gnu++17 -MMD -ffunction-sections -fdata-sections -fno-exceptions  -DMMU_IRAM_SIZE=0x8000 -DMMU_ICACHE_SIZE=0x8000  -DNONOSDK22x_190703=1 -DF_CPU=80000000L -DLWIP_OPEN_SRC -DTCP_MSS=536 -DLWIP_FEATURES=1 -DLWIP_IPV6=0   -DARDUINO=10812 -DARDUINO_ESP8266_NODEMCU_ESP12E -DARDUINO_ARCH_ESP8266 "-DARDUINO_BOARD=\"ESP8266_NODEMCU_ESP12E\"" -DLED_BUILTIN=2 -DFLASHMODE_DIO  -DESP8266   -I"D:\Sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\3.0.2\variants\d1_mini" -I"D:\Sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\3.0.2\cores\esp8266" -I"D:\arduino\arduino-1.8.18\libraries\ESPAsyncWebServer-master\src" -I"D:\arduino\arduino-1.8.18\libraries\ESPAsyncTCP-master\src" -I"D:\Sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\3.0.2\libraries\ESP8266WiFi\src" -I"D:\Sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\3.0.2\libraries\LittleFS\src" -I"D:\Sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\3.0.2\libraries\Hash\src" -I"D:\Sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\3.0.2\libraries\SoftwareSerial\src" -I"D:\arduino\arduino-1.8.18\libraries\Bounce2" -I"D:\Sloeber\arduinoPlugin\libraries\ArduinoJson\6.19.4\src" -I"D:\Sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\3.0.2\libraries\DNSServer\src" -I"D:\00_Vector\Documents\Arduino\libraries\TinyGPSPlus-master\src" -I"D:\Sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\3.0.2\libraries\Wire" -I"D:\Sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\3.0.2\cores\esp8266" -I"D:\Sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\3.0.2\variants\nodemcu" -I"D:\Sloeber\arduinoPlugin\libraries\OneWire\2.3.7" -I"D:\Sloeber\arduinoPlugin\libraries\DallasTemperature\3.9.0" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '


