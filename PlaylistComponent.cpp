/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 2 Sep 2022 2:22:00am
    Author:  Antony

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include "DeckGUI.h"

//==============================================================================
PlaylistComponent::PlaylistComponent( DeckGUI* _player, DeckGUI* _player1) : player(_player), player1(_player1)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    tableComponent.getHeader().addColumn("Track Title", 1, 400);
    tableComponent.getHeader().addColumn("select", 2, 100);
    tableComponent.setModel(this);

    //Making visible table components
    addAndMakeVisible(tableComponent);
    //addAndMakeVisible(importButton);

    //Making visible the select song button
    addAndMakeVisible(songButton);
    //Adding a listener, so that the button responds correctly when the user clicks
    songButton.addListener(this);

    //By default.
    changer = false;

    //Making visible the change deck
    addAndMakeVisible(change_deck);
    //And adding a listener
    change_deck.addListener(this);
    
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::coral);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    tableComponent.setBounds(0, 0, getWidth(), (getHeight()/10)*8);

    //Sizing and position the songButton so that the user can select a song.
    songButton.setBounds(0, (getHeight() / 10) * 8, getWidth()/2, (getHeight() / 10) * 2);

    //Sizing and positioning of the change deck button.
    change_deck.setBounds(getWidth() / 2, (getHeight() / 10) * 8, getWidth()/2, (getHeight() / 10) * 2);

}

int PlaylistComponent::getNumRows()
{
    return (int) trackTitles.size();
}

void PlaylistComponent::paintRowBackground ( Graphics & g,
                             int rowNumber,
                             int width,
                             int height,
                             bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else {
        //changed colour to grey
        g.fillAll(Colours::grey);
    }

}

void PlaylistComponent::paintCell(Graphics & g,
                    int rowNumber,
                    int columnId,
                    int width,
                    int height,
                    bool rowIsSelected)
{
    
    //Adding the selected song to their respective rows.

    if (rowNumber < getNumRows())
    {
        if (columnId == 1)
        {
            g.drawText(trackTitles[rowNumber].name,
                2, 0,
                width - 4, height,
                Justification::centredLeft,
                true);
        }
    }
}

Component* PlaylistComponent::refreshComponentForCell (int rowNumber,
                                  int columnId,
                                  bool isRowSelected,
                                  Component* existingComponentToUpdate)
{
    if (columnId == 2)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton{ "load" };
            btn->addListener(this);
            String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);
            existingComponentToUpdate = btn;

        }
    }

    return existingComponentToUpdate;
}

//Button clicked function

void PlaylistComponent::buttonClicked(Button* button)
{
    //If button is clicked then the load_songs() is activated.
    if (button == &songButton)
    {
        load_songs();       
    }
    //Whenever this button is clicked the deck is changed.
    else if (button == &change_deck) {
        changer = !changer;
    }
    else {
        int id = std::stoi(button->getComponentID().toStdString());
        
        //The deck is changed based on the boolean value of changer.
        if (changer == false) {
            player1->loadSong(File{ trackTitles[id].path });
        }
        else {
            player->loadSong(File{ trackTitles[id].path });
        }
        
    }
    
}

//The function load_songs to load the song

void PlaylistComponent::load_songs()
{
    auto fileChooserFlags = FileBrowserComponent::canSelectFiles;

    fChooser.launchAsync(fileChooserFlags, [&](const FileChooser& chooser)
        {
            auto f = chooser.getResult();
            //If the song exists then..
            if (f.existsAsFile())
            {
                // Contructor object is being initialised
                Title track;
                //Getting track name and path
                track.name = chooser.getResult().getFileNameWithoutExtension().toStdString();
                track.path = chooser.getResult().getFullPathName().toStdString();

                //song being pushed into trackTiles vector
                trackTitles.push_back(std::move(track));

                //updating the list of tracks
                tableComponent.updateContent();
            }
            
        });

}
