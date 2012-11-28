################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
DisplayDriverTest.lss \

FLASH_IMAGE += \
DisplayDriverTest.hex \

EEPROM_IMAGE += \
DisplayDriverTest.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: DisplayDriverTest.elf secondary-outputs

# Tool invocations
DisplayDriverTest.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-gcc -Os -Wl,--gc-sections  -L"C:\dev\arduino\workspace\Arduino_Diecimila_or_Duemilanove_w__ATmega168/Release" -mmcu=atmega168  -o"DisplayDriverTest.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '

DisplayDriverTest.lss: DisplayDriverTest.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S DisplayDriverTest.elf  >"DisplayDriverTest.lss"
	@echo 'Finished building: $@'
	@echo ' '

DisplayDriverTest.hex: DisplayDriverTest.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex DisplayDriverTest.elf  "DisplayDriverTest.hex"
	@echo 'Finished building: $@'
	@echo ' '

DisplayDriverTest.eep: DisplayDriverTest.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex DisplayDriverTest.elf  "DisplayDriverTest.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: DisplayDriverTest.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega168 DisplayDriverTest.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(ELFS)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) DisplayDriverTest.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
