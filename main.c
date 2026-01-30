#include "bh_platform.h"
#include "bh_read_file.h"
#include "wasm_export.h"
#include "wasm_runtime_common.h"

#include <stdio.h>

int run_module(char *);

int main(void) { return run_module("modules/testfile.wasm"); }

int run_module(char *path) {

  char *buffer, error_buf[128];
  wasm_module_t module;
  wasm_module_inst_t module_inst;
  wasm_function_inst_t func;
  wasm_exec_env_t exec_env;
  uint32 size, stack_size = 8092, heap_size = 8092;

  /* initialize the wasm runtime by default configurations */
  if (!wasm_runtime_init()) {
    printf("failed init\n");
    return 1;
  }

  /* read WASM file into a memory buffer */
  buffer = bh_read_file_to_buffer(path, &size);
  if (!buffer) {
    printf("failed read to buffer\n");
    return 1;
  }

  /* add line below if we want to export native functions to WASM app */
  // wasm_runtime_register_natives();

  /* parse the WASM file from buffer and create a WASM module */
  module =
      wasm_runtime_load((uint8_t *)buffer, size, error_buf, sizeof(error_buf));
  if (!module) {
    printf("failed runetime load: %s\n", error_buf);
    return 1;
  }

  /* create an instance of the WASM module (WASM linear memory is ready) */
  module_inst = wasm_runtime_instantiate(module, stack_size, heap_size,
                                         error_buf, sizeof(error_buf));
  if (!module_inst) {
    printf("failed instantiation\n");
    return 1;
  }

  const char *dir_list[] = {".", NULL};
  const char *map_dir_list[] = {NULL};
  const char *addr_pool[] = {NULL};
  const char *ns_lookup_pool[] = {NULL};
  const char *env[] = {NULL};
  char *argv[] = {"program_name"};
  os_raw_file_handle stdinfd = 0;  // usually 0
  os_raw_file_handle stdoutfd = 1; // usually 1
  os_raw_file_handle stderrfd = 2; // usually 2

  bool result =
      wasm_runtime_init_wasi(module_inst, dir_list, 0, map_dir_list, 0, env, 0,
                             addr_pool, 0, ns_lookup_pool, 0, argv, 1, stdinfd,
                             stdoutfd, stderrfd, error_buf, sizeof(error_buf));

  if (!result) {
    printf("wasi init failed: %s\n", error_buf);
    return 1;
  }

  if (module_inst->module_type == Wasm_Module_Bytecode) {
    printf("module is bytecode\n");
  } else if (module_inst->module_type == Wasm_Module_AoT) {
    printf("module is ahead of time\n");
  } else {
    printf("not sure what module is\n");
  }

  uint32 argv2[2];
  argv2[0] = 8;

  char *main_argv[2] = {"hello", "\0"};

  result = wasm_application_execute_main(module_inst, 1, main_argv);
  if (!result) {
    printf("failed to execute main: %s\n",
           wasm_runtime_get_exception(module_inst));
    return 1;
  }

  return 0;
}
