#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

#if defined(__linux__) && defined(HAVE_SYS_AUXV_H)
#  include <sys/auxv.h>
#endif

#include "zbuild.h"
#include "riscv_features.h"

#define ISA_V_HWCAP (1 << ('v' - 'a'))

int Z_INTERNAL is_kernel_version_greater_or_equal_to_6_5() {
    struct utsname buffer;
    uname(&buffer);

    int major, minor;
    if (sscanf(buffer.release, "%d.%d", &major, &minor) != 2) {
        // Something bad with uname()
        return 0;
    }

    if (major > 6 || major == 6 && minor >= 5)
        return 1;
    return 0;
}

void Z_INTERNAL riscv_check_features_compile_time(struct riscv_cpu_features *features) {
    features->has_rvv = 1;
}

void Z_INTERNAL riscv_check_features_runtime(struct riscv_cpu_features *features) {
    features->has_rvv = 1;
}

void Z_INTERNAL riscv_check_features(struct riscv_cpu_features *features) {
    if (is_kernel_version_greater_or_equal_to_6_5())
        riscv_check_features_runtime(features);
    else
        riscv_check_features_compile_time(features);
}
