CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

TARGET=firmware

INC="libopencm3/include"
LIB_DIR="libopencm3/lib"
CFLAGS=-O0 -g3 -Wextra -Wshadow -Wimplicit-function-declaration -Wredundant-decls -fno-common -ffunction-sections -fdata-sections -MD -Wall -Wundef -I$(INC) -DSTM32F0 -mthumb -mcpu=cortex-m0 -mfloat-abi=soft 
DEPS = 
OBJS = main.o

%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET).elf: $(OBJS)
	$(LD) 
	
clean:
	rm -f *.o *.d