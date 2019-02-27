CC=arm-none-eabi-gcc
INC="libopencm3/include"

build:
	$(CC) -O0 -g3 -Wextra -Wshadow -Wimplicit-function-declaration -Wredundant-decls -fno-common -ffunction-sections -fdata-sections -MD -Wall -Wundef -I$(INC) -DSTM32F0 -mthumb -mcpu=cortex-m0 -mfloat-abi=soft -o firmware.o -c main.c