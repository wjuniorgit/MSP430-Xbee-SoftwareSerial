################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := F:/Program Files/ti/ccsv6/tools/compiler/msp430_4.3.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./xbee_s1.obj" \
"./timer.obj" \
"./software_serial.obj" \
"./main.obj" \
"../lnk_msp430g2553.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
MSP430-Xbee-SoftwareSerial.out \

EXE_OUTPUTS__QUOTED += \
"MSP430-Xbee-SoftwareSerial.out" \

BIN_OUTPUTS += \
MSP430-Xbee-SoftwareSerial.hex \

BIN_OUTPUTS__QUOTED += \
"MSP430-Xbee-SoftwareSerial.hex" \


# All Target
all: MSP430-Xbee-SoftwareSerial.out

# Tool invocations
MSP430-Xbee-SoftwareSerial.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"F:/Program Files/ti/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" -vmsp --abi=eabi -O3 --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal -z -m"MSP430-Xbee-SoftwareSerial.map" --heap_size=80 --stack_size=80 -i"F:/Program Files/ti/ccsv6/ccs_base/msp430/include" -i"F:/Program Files/ti/ccsv6/tools/compiler/msp430_4.3.1/lib" -i"F:/Program Files/ti/ccsv6/tools/compiler/msp430_4.3.1/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="MSP430-Xbee-SoftwareSerial_linkInfo.xml" --rom_model -o "MSP430-Xbee-SoftwareSerial.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

MSP430-Xbee-SoftwareSerial.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP430 Hex Utility'
	"F:/Program Files/ti/ccsv6/tools/compiler/msp430_4.3.1/bin/hex430"  -o "MSP430-Xbee-SoftwareSerial.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main.pp" "software_serial.pp" "timer.pp" "xbee_s1.pp" 
	-$(RM) "main.obj" "software_serial.obj" "timer.obj" "xbee_s1.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

