/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    int vgpu_list_idx = 1;
    vm_id = 1;

	addAndMakeVisible(start);
	start.setBounds(90, 10, 60, 25);
	start.setButtonText(String("Start"));
	start.addListener(this);

    addAndMakeVisible(pause);
    pause.setEnabled(false);
    pause.setBounds(160, 10, 60, 25);
    pause.setButtonText(String("---"));
    pause.addListener(this);

    timeout = 0;
    addAndMakeVisible(timeoutLabel);
    timeoutLabel.setBounds(230, 10, 60, 25);
    timeoutLabel.setFont(Font("Ubuntu", 16.0, 0));

    addAndMakeVisible(vgpu_list);
    vgpu_list.addListener(this);
    gvt_start.update();
    for (int i = 0; i < 16; i++) {
        if (gvt_start.vgpu[i].valid) {
            vgpu_list.addItem(String("vgpu ") + String(i), vgpu_list_idx++);
        }
    }
    vgpu_list.setSelectedId(1);
    vgpu_list.setBounds(90, 232, 110, 25);

    addAndMakeVisible(host);
    host.setBounds(90, 45, 500, 180);

    addAndMakeVisible(guest);
    guest.setBounds(90, 265, 500, 180);

    setSize (600, 460);
    //setResizable(true);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    //g.drawLine (80.0, 45, 80.0, getHeight() - 5);

    //g.drawText("Host", Rectangle<int>(90, 5, 60, 25), Justification::left, true);

    Font f = g.getCurrentFont();
    f.setStyleFlags(Font::bold);
    f.setHeight(18);
    g.setFont(f);
    g.drawText("Host", Rectangle<int>(15, 120, 60, 25), Justification::right, true);
    g.drawText("Guest", Rectangle<int>(15, 330, 60, 25), Justification::right, true);
}

void MainContentComponent::timerCallback()
{
    int i;
    int cur_idx;
    int pre_idx;

    timeout++;
    timeoutLabel.setText(String::formatted("%dS", timeout), NotificationType::sendNotification);
    for (i = 0; i < 2; i++)
        if (gvt_state[i].is_current_state || i == 1) {
            pre_idx = i;
            cur_idx = (i + 1) % 2;

            gvt_state[i].is_current_state = false;
            gvt_state[(i + 1) % 2].update();
            gvt_state[(i + 1) % 2].is_current_state = true;

            if (gvt_state[i].cur_time == 0)
                gvt_state[i] = gvt_state[(i + 1) % 2];
            break;
        }

    if (!paused) {
        unsigned long long interval = gvt_state[cur_idx].cur_time - gvt_state[pre_idx].cur_time;
        unsigned long long total_time = gvt_state[cur_idx].cur_time - gvt_start.cur_time;
        host.refresh(gvt_state[pre_idx].host, gvt_state[cur_idx].host, interval, total_time);
        guest.refresh(gvt_state[pre_idx].vgpu[vm_id], gvt_state[cur_idx].vgpu[vm_id], interval, total_time);
    }
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
