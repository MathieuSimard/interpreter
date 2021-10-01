ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
BUILD_DIR := $(ROOT_DIR)/build

configure:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..

build: configure
	make -C $(BUILD_DIR) all -j12

test:
	$(BUILD_DIR)/test/utest

clean:
	$(RM) -r $(BUILD_DIR)

.PHONY: configure build test clean
