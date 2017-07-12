/*
  ==============================================================================

    gpu_state_component.h
    Created: 26 Jun 2017 8:32:59pm
    Author:  pei

  ==============================================================================
*/

#pragma once

#include "Trendgraph.h"
#include "Trendblock.h"
#include "gvt_state.h"


class engine_idle_state_wnd : public Trendblock
{
    int engine_id;
public:
    engine_idle_state_wnd()
    {
        engine_id = -1;
    }

    ~engine_idle_state_wnd() {}

    void setEngineId(int id)
    {
        engine_id = id;
    }

    void refresh(unsigned int percent_jit, unsigned int percent_average)
    {
        if (engine_id < 0) {
            printf("err: engine_id is not set(%d)\n", engine_id);
            return;
        }

        percent = percent_jit;
        percent1 = percent_average;
        repaint();
    }
};

class vgpu_state_wnd : public Trendgraph
{
    int vgpu_id;
public:
    vgpu_state_wnd()
    {
        vgpu_id = -1;
    }

    ~vgpu_state_wnd() {}

    void set_id(int id)
    {
        vgpu_id = id;
    }

    unsigned getNewSample()
    {
        int cur_idx = 0;
        int pre_idx = 1;

        if (vgpu_id == -1)
            return 0;

        if (gvt_state[1].is_current_state) {
            cur_idx = 1;
            pre_idx = 0;
        }

        return gvt_state[cur_idx].vgpu[vgpu_id].read_trap_count - gvt_state[pre_idx].vgpu[vgpu_id].read_trap_count;
    }
};
