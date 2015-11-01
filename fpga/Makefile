# FPGA makefile

FPGA_DIR=./fpga_hw/top_level
BSP_DIR=./bsp
SW_DIR=./fpga_sw

ELF_NAME=main.elf
GDB_TCP_PORT=2345

all: fpga_sw

# This next command just creates the Board Support Pacakge from the sopc file
# Pretty basic command, it is actually pretty cool
bsp: fpga_hw
	nios2-bsp hal $(BSP_DIR) $(FPGA_DIR)

just_sw:
	nios2-app-generate-makefile --bsp-dir $(BSP_DIR) --app-dir $(SW_DIR) --inc-rdir $(SW_DIR)/inc --src-rdir $(SW_DIR)/src --elf-name $(ELF_NAME) --set APP_CFLAGS_OPTIMIZATION '-O3'
	$(MAKE) -C $(SW_DIR)

fpga_sw: bsp
	nios2-app-generate-makefile --bsp-dir $(BSP_DIR) --app-dir $(SW_DIR) --inc-rdir $(SW_DIR)/inc --src-rdir $(SW_DIR)/src --elf-name $(ELF_NAME) --set APP_CFLAGS_OPTIMIZATION '-O3'
	$(MAKE) -C $(SW_DIR)

fpga_hw:
	$(MAKE) -C $(FPGA_DIR)

clean:
	-$(MAKE) -k -C $(SW_DIR) $@
	rm -f $(SW_DIR)/Makefile
	rm -rf $(BSP_DIR)
	$(MAKE) -C $(FPGA_DIR) $@
	$(MAKE) -C ./fpga_hw/demo_projects/pwm $@

.PHONY: all clean bsp fpga_sw fpga_hw

# Handy make targets
dl_hw:
	nios2-configure-sof --directory $(FPGA_DIR)

dl_sw:
	nios2-download -r --go --directory $(SW_DIR) $(ELF_NAME)

dl_both:
	$(MAKE) dl_hw
	$(MAKE) dl_sw

gdb_server:
	(cd $(SW_DIR) && nios2-gdb-server --tcpport $(GDB_TCP_PORT))

gdb_client:
	(cd $(SW_DIR) && nios2-elf-gdb $(ELF_NAME))

terminal:
	nios2-terminal -q

.PHONY: dl_hw dl_sw dl_both gdb_server gdb_client terminal
