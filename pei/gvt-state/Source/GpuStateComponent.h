/*
  ==============================================================================

    GpuStateComponent.h
    Created: 29 Jun 2017 11:25:59pm
    Author:  pei

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "gvt_state.h"
#include "gvt_state_component.h"

//==============================================================================
/*
*/
class GpuStateComponent    : public Component
{
public:
    GpuStateComponent();
    ~GpuStateComponent();

    void paint (Graphics&) override;
    void resized() override;
    void refresh (struct gpu_idle_state &pre, struct gpu_idle_state &cur, 
        unsigned long long interval, unsigned long long total_time);

private:

    engine_idle_state_wnd gpu_engines[INTEL_ENGINE_COUNT];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GpuStateComponent)
};
