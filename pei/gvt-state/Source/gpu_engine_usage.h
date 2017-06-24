/*
  ==============================================================================

    gpu_engine_usage.h
    Created: 24 Jun 2017 3:15:13am
    Author:  zhang

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class gpu_engine_usage    : public Component, public Timer
{
public:
    gpu_engine_usage()
    {
		idle_time = 0;
    }

    ~gpu_engine_usage()
    {
    }

    void paint (Graphics& g) override
    {
		unsigned text_height = 20;
		unsigned w = getWidth();
		unsigned h = getHeight() - text_height;
		unsigned y = (h * 100 - h * idle_time) / 100;

        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

        /* draw an outline around the component 
         */
        g.setColour (Colours::grey);
        g.drawRect (Rectangle<int>(0, y, w, h - y));

        g.setColour (Colours::white);
        g.setFont (14.0f);
        g.drawText (String::formatted("%d%%", idle_time), Rectangle<int>(0, h, w, text_height),
                    Justification::centred, true);
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

	void timerCallback() override
	{
		/* app will get the engine idle time in a fixed interval (1s for example). The new got
		* value decrease the original value, divide the interval, will get the busy percent
		* in time badse.
		*
		* busy percent = (idle_time[1] - idle_time[0]) / interval
		*/
		static unsigned _idle_time[2];

		idle_time += 10;
		idle_time %= 100;

		repaint();
	}
    
private:
	unsigned idle_time;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (gpu_engine_usage)
};
