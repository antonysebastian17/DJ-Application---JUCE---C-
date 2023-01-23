/*
  ==============================================================================

    PlaylistComponent.h
    Created: 2 Sep 2022 2:22:00am
    Author:  Antony

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include<vector>
#include<string>
#include <fstream>

class DeckGUI;
//==============================================================================
/*
*/
class PlaylistComponent    : public Component,
                            public TableListBoxModel,
                            public Button::Listener
{
public:
    PlaylistComponent( DeckGUI *_player, DeckGUI* _player1);
    ~PlaylistComponent();

    void paint (Graphics &) override;
    void resized() override;

    int getNumRows () override;

    void paintRowBackground (Graphics &,
                         int rowNumber,
                         int width,
                         int height,
                         bool rowIsSelected) override;

    void paintCell (Graphics &,
                int rowNumber,
                int columnId,
                int width,
                int height,
                bool rowIsSelected) override;

    Component* refreshComponentForCell (int rowNumber,
                                       int columnId, 
                                       bool isRowSelected, 
                                       Component *existingComponentToUpdate) override;

    void buttonClicked (Button* button) override;

private:
    
    //Creating class Title to contain the path and the name
    class Title
    {
    public:
        //construtor
        Title() {}
        String path;
        String name;
    };

    //track title
    TableListBox tableComponent;
    std::vector<Title> trackTitles;

    //juce::TextButton importButton{ "IMPORT TRACKS" };
    
    //button change deck
    juce::TextButton change_deck{ "CHANGE DECK" };


    //Juce library objects FileChooser and TextButton to 
    // choose files and select a song respectively.
    FileChooser fChooser{ "Select a file..." };
    TextButton songButton{ "SELECT SONG" };

    //funtion to load the songs has been created.
    void load_songs();

    //boolen used to change deck.
    bool changer;

    //Deck player 1 and Player 2
    DeckGUI* player;
    DeckGUI* player1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
