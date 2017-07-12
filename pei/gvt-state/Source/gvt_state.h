/*
  ==============================================================================

    gvt_state.h
    Created: 26 Jun 2017 8:35:52pm
    Author:  pei

  ==============================================================================
*/

#pragma once


#define GVT_STATE_ENGINES 5
#define GVT_STATE_GPUS	15
typedef  unsigned long long cycles_t;

struct engine_idle_state {
	cycles_t idle_time;
	unsigned int submit_count;
	unsigned int idle_count;
};

struct gpu_idle_state {
	bool valid;
    struct engine_idle_state engines[INTEL_ENGINE_COUNT];

	unsigned int read_trap_count;
	cycles_t read_trap_time;
	unsigned int write_trap_count;
	cycles_t write_trap_time;
};

class gvt_state
{
public:
    cycles_t cur_time;
	struct gpu_idle_state host;
	struct gpu_idle_state vgpu[16]; /* support maximum 16 vGPU instances */
	bool is_current_state;

public:
    gvt_state()
    {
        cur_time = 0;
    }

    bool reset()
    {
        /* echo any content to sysfs interface gvt_state to reset kernel data */
        File f("/sys/class/drm/card0/gvt_state");
        if (f.existsAsFile()) {
            f.appendData("0", 1);
            update(f);
            return true;
        }

        return false;
    }

    void update(File &f)
    {        
        int i, vgpu_num;
        int global_head_lines = 2;
        int gpu_head_lines = 1;
        int gpu_info_lines = 6;
        int host_head_line = global_head_lines + gpu_head_lines;
        int vm_head_line = host_head_line + gpu_info_lines;
        StringArray lines;

        f.readLines(lines);
        cur_time = lines[0].substring(10).getHexValue64();
        for (i = 0; i < GVT_STATE_ENGINES; i++) {
            host.engines[i].submit_count = lines[host_head_line + i].substring(3, 11).getHexValue32();
            host.engines[i].idle_count = lines[host_head_line + i].substring(12, 21).getHexValue32();
            host.engines[i].idle_time = lines[host_head_line + i].substring(21).getHexValue64();
        }

        vgpu_num = (lines.size() - global_head_lines - gpu_info_lines) / gpu_info_lines;
        for (i = 0; i < GVT_STATE_GPUS; i++)
            vgpu[i].valid = false;
        for (i = 0; i < vgpu_num; i++) {
            int line_idx = global_head_lines + (i + 1) * gpu_info_lines;
            String info = lines[line_idx];
            int idx = info.indexOfIgnoreCase("vgpu");

            if (idx > 0) {
                int vgpu_idx = info.substring(idx + 5, idx + 7).getIntValue();

                line_idx++;
                vgpu[vgpu_idx].valid = true;
                for (int j = 0; j < GVT_STATE_ENGINES; j++) {
                    //printf("%s\n", lines[line_idx + j].toRawUTF8());
                    vgpu[vgpu_idx].engines[j].submit_count = 
                        lines[line_idx + j].substring(3, 11).getHexValue32();
                    vgpu[vgpu_idx].engines[j].idle_count = 
                        lines[line_idx + j].substring(12, 21).getHexValue32();
                    vgpu[vgpu_idx].engines[j].idle_time =
                        lines[line_idx + j].substring(21).getHexValue64();
                }
            }
        }
    }

    bool update()
    {
        File f("/sys/class/drm/card0/gvt_state");
        if (f.existsAsFile()) {
            update(f);
            return true;
        }
        else {
            printf("err: failed to open gvt_state. errno is %d\n", errno);
            return false;
        }
    }
};

extern gvt_state gvt_start;
extern gvt_state gvt_state[2];
