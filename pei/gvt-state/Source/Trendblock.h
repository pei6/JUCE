/*
  ==============================================================================

    Trendblock.h
    Created: 24 Jun 2017 3:15:13am
    Author:  zhang

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Trendblock    : public Component
{
public:
    Trendblock()
    {
        percent = 0;
        percent1 = 0;
        direction = true;
        usePercent1 = true;
    }

    ~Trendblock()
    {
    }

    void paint (Graphics& g) override
    {
		unsigned w = getWidth();
		unsigned h = getHeight();
        g.setFont(20.0);

		// clear the background
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

		if (direction == 0) { /* vertical direction */
            unsigned text_height = 20;
            unsigned y = (h * 100 - h * percent) / 100;

            h -= text_height;

            /* draw an outline around the component */
            g.setColour (Colours::grey);
            g.drawRect (Rectangle<int>(0, y, w, h - y));

            g.setColour (Colours::white);
            g.setFont (14.0f);
            g.drawText (String::formatted("%3d\n", percent) + tag, Rectangle<int>(0, h, w, text_height),
                        Justification::centred, true);
        } else {    /* horizontal direction */
            unsigned tag_width = 50;
            unsigned info_width = 180;
            unsigned blk_width_total = w;
            unsigned blk_width, blk_width1;
            unsigned blk_x = tag_width + 8;
            unsigned blk_x1;
            unsigned info_x;

            blk_width_total -= tag_width + info_width;
            info_x = tag_width + blk_width_total + 10;
            blk_width = (blk_width_total * percent) / 100;
            blk_width1 = (blk_width_total * percent1) / 100;
            blk_x1 = blk_x + blk_width;

            /* write tag */
            g.setColour (Colours::white);
            g.setFont (14.0f);
            g.drawText(tag, Rectangle<int>(0, 0, tag_width - 6, h), Justification::right, true);

            /* fill the block for percent value */
            g.setColour (Colours::red);
            g.fillRect (blk_x, 0, blk_width, h/2);
            if (usePercent1) {
                /* use another color to draw percent1 */
                g.setColour (Colours::grey);
                g.fillRect (blk_x, (int)h/2, blk_width1, (int)h/2);
            }

            g.setColour (Colours::red);
            g.drawText (String::formatted("%3d%%", percent), Rectangle<int>(info_x, 0, 40, h/2),
                        Justification::left, true);
            g.drawText (info[0] + " CMD", Rectangle<int>(info_x + 40, 0, info_width - 80, h/2), 
                        Justification::right, true);
            if (usePercent1) {
                g.setColour (Colours::grey);
                g.drawText (String::formatted("%3d%%", percent1), Rectangle<int>(info_x, h/2, 40, h/2),
                        Justification::left, true);
                g.drawText (info[1] + " Total", Rectangle<int>(info_x + 40, h/2, info_width - 80, h/2), 
                    Justification::right, true);
            }
            g.setColour (Colours::white);
        }
    }

    void resized() override
    {
    }

    void setTag(String _tag)
    {
        tag = _tag;
    }

    void setDirection(bool horizontal)
    {
        direction = horizontal;
    }

    void setInfo(String info0, String info1)
    {
        info[0] = info0;
        info[1] = info1;
    }

	virtual void refresh()
	{
		/* app will get the engine idle time in a fixed interval (1s for example). The new got
		* value decrease the original value, divide the interval, will get the busy percent
		* in time badse.
		*
		* busy percent = (idle_time[1] - idle_time[0]) / interval
		*/
		static unsigned _idle_time[2];

		percent += 10;
		percent %= 100;

		repaint();
	}

protected:
    bool direction;
    bool usePercent1;
	unsigned percent;
	unsigned percent1;

    String tag;
    String info[2];

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Trendblock)
};
