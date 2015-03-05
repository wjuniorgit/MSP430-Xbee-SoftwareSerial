################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" -vmsp --abi=eabi -O3 --include_path="F:/Program Files/ti/ccsv6/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv6/tools/compiler/msp430_4.3.1/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

software_serial.obj: ../software_serial.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" -vmsp --abi=eabi -O3 --include_path="F:/Program Files/ti/ccsv6/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv6/tools/compiler/msp430_4.3.1/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="software_serial.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

timer.obj: ../timer.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" -vmsp --abi=eabi -O3 --include_path="F:/Program Files/ti/ccsv6/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv6/tools/compiler/msp430_4.3.1/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="timer.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

xbee_s1.obj: ../xbee_s1.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" -vmsp --abi=eabi -O3 --include_path="F:/Program Files/ti/ccsv6/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv6/tools/compiler/msp430_4.3.1/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="xbee_s1.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


