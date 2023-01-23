/*
  ==============================================================================

    DeckGUI.h
    Created: 1 Sep 2022 8:22:42pm
    Author:  Antony

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, 
                AudioFormatManager & 	formatManagerToUse,
                AudioThumbnailCache & 	cacheToUse
           ) : player(_player), 
               waveformDisplay(formatManagerToUse, cacheToUse)
{

    //Play/stop/load buttons
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);

    //Making visible the waveform display
    addAndMakeVisible(waveformDisplay);

    //slider to control the speed of the track being played
    addAndMakeVisible(speedSlider);
    //setting the colour of LookAndfeel class and then overriding it to change the colour of the 
    //speed slider to blue.
    speedSlider.setSliderStyle(juce::Slider::Rotary);
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::red);
    speedSlider.setLookAndFeel(&otherLookAndFeel);
    speedSlider.addListener(this);
    speedSlider.setRange(0.5, 1.5);

    //slider to control the volume of the tracks
    volSlider.setSliderStyle(juce::Slider::Rotary);
    addAndMakeVisible(volSlider);
    volSlider.addListener(this);
    volSlider.setRange(0.0, 1.0);

    //slider to control the position of the song being played
    posSlider.setSliderStyle(juce::Slider::LinearBar);
    addAndMakeVisible(posSlider);
    posSlider.addListener(this);
    posSlider.setRange(0.0, 1.0);

    //listeners for the play/stop/load buttons
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    startTimer(500);



}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 8;
    //play button
    playButton.setBounds(0, rowH * 7, getWidth() / 3, rowH * 1.1);
    //stop button
    stopButton.setBounds(getWidth() / 3, rowH * 7, getWidth() / 3, rowH * 1.1);
    //volume slider
    volSlider.setBounds(0, 0, getWidth() / 2, rowH * 4);
    //speed slider
    speedSlider.setBounds(getWidth() / 2, 0, getWidth() / 2, rowH * 4);
    //position slider
    posSlider.setBounds(0, rowH * 4, getWidth(), rowH);
    //waveform slider
    waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);
    //load button slider
    loadButton.setBounds(getWidth() * 2 / 3, rowH * 7, getWidth() / 3, rowH * 1.1);

}

void DeckGUI::loadSong(File& file)
{
    //Load song to the player using JUCE URL
    player->loadURL(URL{ file });
    // Load song to the waveformDisplay as well using JUCE URL
    waveformDisplay.loadURL(URL{ file });
}


void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
     if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();

    }
       if (button == &loadButton)
    {
        auto fileChooserFlags = 
        FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
                loadSong(chooser.getResult());
        });
    }
    
}

void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
    
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
  return true; 
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
    player->loadURL(URL{File{files[0]}});
  }
}

void DeckGUI::timerCallback()
{
    
    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
}


    

