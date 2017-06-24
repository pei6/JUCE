/*
  ==============================================================================

    Trendgraph.h
    Created: 24 Jun 2017 1:26:44pm
    Author:  zhang

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
#define GRAPH_POINT_NUM 200

class Trendgraph    : public Component, public Timer
{
public:
    Trendgraph()
    {
        rb_wr_pnt = 0;
        rb_len = 0;
        min_val = max_val = 0;
    }

    ~Trendgraph()
    {
    }

    void paint (Graphics& g) override
    {
		unsigned y_space = 20;
		unsigned x_space = 10;
		unsigned w = getWidth() - x_space;
		unsigned h = getHeight() - y_space;
		unsigned y_elements = max_val - min_val;
		unsigned x_elements = GRAPH_POINT_NUM;
		
        g.fillAll (Colours::white);   // clear the background
        g.setColour (Colours::blue);

		{
			unsigned x, y;
			unsigned _x, _y;
			unsigned start_idx = 0;

			if (rb_len >= GRAPH_POINT_NUM)
				start_idx = rb_wr_pnt;

			for (unsigned i = 0; i < jmin(rb_len, x_elements); i++) {
				x = (x_elements - i) * w / x_elements;
				y = h - h * point_value_rb[(start_idx + i) % GRAPH_POINT_NUM] / y_elements;

				g.setColour(Colours::black);
				g.fillRect(x, y, 2, 2);
				if (i > 0) {
					g.setColour(Colours::lightblue);
					g.drawLine(_x, _y, x, y, 1);
				}
				_x = x;
				_y = y;
			}
		}
    }
    
    virtual unsigned getNewSample()
    {
        /* get new point value and store in the ::point array */        
		Random r = Random(Time::currentTimeMillis());
		return r.nextInt(100) % 100;
    }
    
    void timerCallback() override
    {   
        unsigned val = getNewSample();
        
        if (val < min_val)
            min_val = val;
        else if (val > max_val)
            max_val = val;

        point_value_rb[rb_wr_pnt++] = val;
        rb_wr_pnt %= GRAPH_POINT_NUM;
		if (rb_len < GRAPH_POINT_NUM)
			rb_len++;
		else
			rb_len = GRAPH_POINT_NUM;

        repaint();
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    unsigned point_value_rb[GRAPH_POINT_NUM];
    unsigned rb_wr_pnt;
    unsigned rb_len;
    unsigned min_val;
    unsigned max_val;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Trendgraph)
};
