#ifndef MIPMAPSETTINGS_H_
#define MIPMAPSETTINGS_H_

struct MipmapSettings {
    double enlarge_threshold_base = 1e-7;
    int initial_mipmap_level = 3;
    int final_mipmap_level = 0;

    int current_mipmap_level = 3;
    bool is_adaptive_scaling_enabled = true;
};


#endif
