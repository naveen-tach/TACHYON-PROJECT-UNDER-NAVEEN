################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := BI-DIRECTIONAL-PORT-COMM-W-ACK
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
BI-DIRECTIONAL-PORT-COMM-W-ACK.elf \

MAP_FILES += \
BI-DIRECTIONAL-PORT-COMM-W-ACK.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
BI-DIRECTIONAL-PORT-COMM-W-ACK.list \


# All Target
all: main-build

# Main-build Target
main-build: BI-DIRECTIONAL-PORT-COMM-W-ACK.elf secondary-outputs

# Tool invocations
BI-DIRECTIONAL-PORT-COMM-W-ACK.elf BI-DIRECTIONAL-PORT-COMM-W-ACK.map: $(OBJS) $(USER_OBJS) D:\personalwork\stm_cube_ide\STM32_EXPLORE_WORK_SPACE\BI-DIRECTIONAL-PORT-COMM-W-ACK\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "BI-DIRECTIONAL-PORT-COMM-W-ACK.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\personalwork\stm_cube_ide\STM32_EXPLORE_WORK_SPACE\BI-DIRECTIONAL-PORT-COMM-W-ACK\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="BI-DIRECTIONAL-PORT-COMM-W-ACK.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

BI-DIRECTIONAL-PORT-COMM-W-ACK.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "BI-DIRECTIONAL-PORT-COMM-W-ACK.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) BI-DIRECTIONAL-PORT-COMM-W-ACK.elf BI-DIRECTIONAL-PORT-COMM-W-ACK.list BI-DIRECTIONAL-PORT-COMM-W-ACK.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
