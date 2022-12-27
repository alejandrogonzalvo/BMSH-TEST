################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := BMSH_TEST
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
BMSH_TEST.elf \

MAP_FILES += \
BMSH_TEST.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
BMSH_TEST.list \


# All Target
all: main-build

# Main-build Target
main-build: BMSH_TEST.elf secondary-outputs

dependents:
	-cd C:/Users/aleja/Proyectos/Hyper-H8/BMS/BMS-LIB/Debug && $(MAKE) all
	-cd C:/Users/aleja/Proyectos/Hyper-H8/ST-LIB/Debug && $(MAKE) all

# Tool invocations
BMSH_TEST.elf BMSH_TEST.map: $(OBJS) $(USER_OBJS) C:/Users/aleja/Proyectos/Hyper-H8/BMS/BMS-LIB/Debug/libBMS-LIB.a C:/Users/aleja/Proyectos/Hyper-H8/ST-LIB/Debug/libST-LIB.a C:\Users\aleja\Proyectos\Hyper-H8\Tests\BMSH_TEST\STM32H723ZGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-g++ -o "BMSH_TEST.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\aleja\Proyectos\Hyper-H8\Tests\BMSH_TEST\STM32H723ZGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="BMSH_TEST.map" -Wl,--gc-sections -static -L"C:\Users\aleja\Proyectos\Hyper-H8\ST-LIB\Debug" -L"C:\Users\aleja\Proyectos\Hyper-H8\BMS\BMS-LIB\Debug" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

BMSH_TEST.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "BMSH_TEST.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) BMSH_TEST.elf BMSH_TEST.list BMSH_TEST.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified
C:/Users/aleja/Proyectos/Hyper-H8/BMS/BMS-LIB/Debug/libBMS-LIB.a:
C:/Users/aleja/Proyectos/Hyper-H8/ST-LIB/Debug/libST-LIB.a:

-include ../makefile.targets
