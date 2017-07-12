/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#define ARRAY_SIZE(Array) (sizeof(Array) / sizeof((Array)[0]))

#include "../JuceLibraryCode/JuceHeader.h"
#include "GpuStateComponent.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component, public Timer, 
							public ButtonListener,
							public ComboBoxListener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;
	void timerCallback() override;

	void buttonClicked(Button* b)
	{
		if (b == &start) {
			paused = false;
			if (b->getButtonText().equalsIgnoreCase("start")) {
				timeout = 0;
				gvt_start.reset();
				b->setButtonText(String("Stop"));
				pause.setEnabled(true);
				pause.setButtonText("Pause");
				startTimer(1000);
			}
			else {
				b->setButtonText(String("Start"));
				pause.setButtonText("---");
				pause.setEnabled(false);
				stopTimer();
			}
		} else if (b == &pause) {
			/* button only enabled when start button clicked*/
			if (start.getButtonText().equalsIgnoreCase("stop")) {
				if (b->getButtonText().equalsIgnoreCase("Pause")) {
					paused = true; //stopTimer();
					b->setButtonText("Resume");
				} else {
					paused = false; //startTimer(1000);
					b->setButtonText("Pause");
				}
			} else
				b->setEnabled(false);
		}
	}

	virtual void comboBoxChanged (ComboBox* comboBoxThatHasChanged)
	{
		
	}
private:
    //==============================================================================
	TextButton start;
	TextButton pause;
	Label timeoutLabel;
	ComboBox vgpu_list;
	int timeout;
	bool paused;
	int vm_id;

	GpuStateComponent host;
	GpuStateComponent guest;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
