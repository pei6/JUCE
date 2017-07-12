/*
  ==============================================================================

    GpuStateComponent.cpp
    Created: 29 Jun 2017 11:25:59pm
    Author:  pei

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "GpuStateComponent.h"

class gvt_state gvt_start;
class gvt_state gvt_state[2];

const char *intel_engine_name[] = {"RCS", "BCS", "VCS", "VCS2", "VECS"};

//==============================================================================
GpuStateComponent::GpuStateComponent()
{  
    for (int i = 0; i < INTEL_ENGINE_COUNT; i++) {
        addAndMakeVisible(gpu_engines[i]);
        gpu_engines[i].setDirection(true); /* draw horizontal block*/
        gpu_engines[i].setEngineId(i);
        gpu_engines[i].setTag(intel_engine_name[i]);
        gpu_engines[i].setBounds(10, 10 + i * 32, 420, 30);
    }
}

GpuStateComponent::~GpuStateComponent()
{
}

void GpuStateComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::black);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void GpuStateComponent::resized()
{
}

void GpuStateComponent::refresh (struct gpu_idle_state &pre, struct gpu_idle_state &cur,
        unsigned long long interval, unsigned long long total_time)
{  
    unsigned int submit_count, submit_count_total;
    unsigned int percent_jit, percent_average;

    for (int engine_id = 0; engine_id < INTEL_ENGINE_COUNT; engine_id++) {
        percent_average = 0;
        percent_jit = 0;
        submit_count_total = cur.engines[engine_id].submit_count;
        submit_count = submit_count_total - pre.engines[engine_id].submit_count;

        if (interval == 0 || total_time == 0)
            printf("err: time is %llx-%llx\n", interval, total_time);
        else {
            unsigned long long idle_total = cur.engines[engine_id].idle_time - 
                gvt_start.host.engines[engine_id].idle_time;

            percent_jit = 100;
            if (cur.engines[engine_id].submit_count > pre.engines[engine_id].submit_count) {              
                unsigned long long idle_interval = cur.engines[engine_id].idle_time - 
                    pre.engines[engine_id].idle_time;

                percent_jit = (100 * idle_interval) / interval;                
                if (percent_jit > 100) {
                    printf("err: percent_jit is abnormal %d\n", percent_jit);
                    percent_jit = 100;
                }
            }
  
            percent_average = (100 * idle_total) / total_time;
            if (percent_average > 100) {
                printf("err: percent_average is abnormal %d\n", percent_average);
                percent_average = 100;
            }
            percent_average = 100 - percent_average;
            percent_jit = 100 - percent_jit;
        }

        gpu_engines[engine_id].setInfo(String(submit_count), String(submit_count_total));
        gpu_engines[engine_id].refresh(percent_jit, percent_average);
    }
}
