/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainContentComponent::MainContentComponent()
{
	addAndMakeVisible(start);
	start.setBounds(10, 10, 100, 30);
	start.setButtonText(String("Start"));
	start.addListener(new startButtonListener());

	addAndMakeVisible(gpu_engine[0]);
	gpu_engine[0].setBounds(100, 40, 20, 100);

	addAndMakeVisible(gpu_engine[1]);
	gpu_engine[1].setBounds(130, 40, 20, 100);

	addAndMakeVisible(gpu_trap);
	gpu_trap.setBounds(20, 160, 560, 100);
	addAndMakeVisible(vcpu_trap);
	vcpu_trap.setBounds(20, 280, 560, 100);
    setSize (600, 450);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::startTimer(bool _start)
{
	int i;

	if (_start) {
		gpu_trap.startTimer(1000);
		vcpu_trap.startTimer(1000);
		for (i = 0; i < ARRAY_SIZE(gpu_engine); i++)
			gpu_engine[i].startTimer(1000);
	}
	else {
		gpu_trap.stopTimer();
		vcpu_trap.stopTimer();
		for (i = 0; i < ARRAY_SIZE(gpu_engine); i++)
			gpu_engine[i].stopTimer();
	}
}

void MainContentComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
