################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
driverlib/MSP430FR2xx_4xx/%.obj: ../driverlib/MSP430FR2xx_4xx/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-msp430_20.2.2.LTS/bin/cl430" -vmspx --code_model=large --data_model=restricted --near_data=none --use_hw_mpy=none --include_path="C:/ti/ccs1011/ccs/ccs_base/msp430/include" --include_path="C:/Users/matil/Documents/workspace_v10/adc-library" --include_path="C:/Users/matil/Documents/workspace_v10/adc-library/driverlib/MSP430FR2xx_4xx" --include_path="C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-msp430_20.2.2.LTS/include" --advice:power=all --advice:hw_config=all --define=__MSP430FR4133__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="driverlib/MSP430FR2xx_4xx/$(basename $(<F)).d_raw" --obj_directory="driverlib/MSP430FR2xx_4xx" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


