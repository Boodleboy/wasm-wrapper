BUILD_DIR := build
TARG := my_wamr_app
WASM_DIR := modules

WASM_SOURCE := $(wildcard $(WASM_DIR)/*.c)
WASM_FILES := $(WASM_SOURCE:.c=.wasm)

run: $(BUILD_DIR)/$(TARG) $(WASM_FILES)
	./$(BUILD_DIR)/$(TARG)

%.wasm: %.c
	./sub/wasi-sdk/build/install/bin/clang \
		--target=wasm32-wasi \
		--sysroot=./install/sysroot \
		-o $@ \
		$<

$(BUILD_DIR)/$(TARG): $(BUILD_DIR)/Makefile main.c
	cd $(BUILD_DIR) && make

$(BUILD_DIR)/Makefile: CMakeLists.txt
	cmake \
		-DCMAKE_BUILD_TYPE=Debug \
		-S . \
		-B $(BUILD_DIR)
