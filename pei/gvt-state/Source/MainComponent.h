/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "gpu_engine_usage.h"
#include "trendgraph.h"

#define ARRAY_SIZE(Array) (sizeof(Array) / sizeof((Array)[0]))

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;
	void startTimer(bool start);
private:
    //==============================================================================
	TextButton start;
	class startButtonListener : public ButtonListener {
		void buttonClicked(Button* b)
		{
			if (b->getButtonText().equalsIgnoreCase("start")) {
				b->setButtonText(String("Stop"));
				((MainContentComponent *)(b->getParentComponent()))->startTimer(true);
			}
			else {
				b->setButtonText(String("Start"));
				((MainContentComponent *)(b->getParentComponent()))->startTimer(false);
			}
		}
	};
	gpu_engine_usage gpu_engine[2];
	
	Trendgraph gpu_trap;
	Trendgraph vcpu_trap;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
