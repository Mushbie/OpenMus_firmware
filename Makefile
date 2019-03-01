CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

TARGET=firmware

INC=libopencm3/include
LIB_DIR=libopencm3/lib
LIB_FILE=$(LIB_DIR)/libopencm3_stm32f0.a
LD_SCRIPT=$(LIB_DIR)/stm32/f0/stm32f04xz6.ld

ARCH_FLAGS=-mthumb -mcpu=cortex-m0 -ffunction-sections -fdata-sections -mfloat-abi=soft
CFLAGS=-O0 -g3 -Wextra -Wshadow -Wimplicit-function-declaration -Wredundant-decls -fno-common $(ARCH_FLAGS) -MD -Wall -Wundef -I$(INC) -DSTM32F0  
LDFLAGS=--static -nostartfiles -L$(LIB_DIR) -T$(LD_SCRIPT) $(ARCH_FLAGS) -Wl,--gc-sections -lopencm3_stm32f0 -lc -lgcc -lnosys
DEPS = 
OBJS = main.o

$(TARGET).ihex: $(TARGET).elf
	$(OBJCOPY) -O ihex $(TARGET).elf $(TARGET).hex

$(TARGET).elf: $(OBJS) $(LIB_FILE)
	$(LD) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

$(LIB_FILE):
	make -C libopencm3

clean:
	rm -f *.o *.d $(TARGET).elf $(TARGET).hex