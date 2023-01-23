/*
  ==============================================================================

    DeckGUI.h
    Created: 1 Sep 2022 8:22:42pm
    Author:  Antony

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener, 
                   public FileDragAndDropTarget, 
                   public Timer
{
public:
    DeckGUI(DJAudioPlayer* player, 
           AudioFormatManager & 	formatManagerToUse,
           AudioThumbnailCache & 	cacheToUse );
    ~DeckGUI();

    void paint (Graphics&) override;
    void resized() override;

     /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

    bool isInterestedInFileDrag (const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override; 

    void timerCallback() override;

    void loadSong(File& file);

private:



    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
  
    //Code adapted from docs.juce.com - customise the look and feel - customise yur app
    juce::LookAndFeel_V4 otherLookAndFeel;
    Slider volSlider; 
    Slider speedSlider;
    Slider posSlider;
    juce::Label posLabel;


    FileChooser fChooser{"Select a file..."};


    WaveformDisplay waveformDisplay;

    DJAudioPlayer* player; 



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
