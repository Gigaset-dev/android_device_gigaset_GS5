/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/properties.h>
#include <libinit_set_props.h>
#include <libinit_utils.h>
#include <string>
#include <sys/sysinfo.h>

#define GIGASET "Gigaset"
#define VOLLA "Volla"

void check_manufacturer_and_set_props() {
    struct sysinfo sys;
    sysinfo(&sys);
    bool is6GB = sys.totalram > GB(5);
    std::string manufacturer = android::base::GetProperty("ro.product.system.manufacturer", VOLLA);

    if (strcmp(manufacturer.c_str(), GIGASET) == 0) {
        if (is6GB) {
            set_ro_build_prop("device", "GS5_PRO", true);
            set_ro_build_prop("model", "E940-2796-05", true);
        }
    } else if (strcmp(manufacturer.c_str(), VOLLA) == 0) {
        if (is6GB)
            set_ro_build_prop("model", "Volla Phone 22 Plus", true);
    }
}
