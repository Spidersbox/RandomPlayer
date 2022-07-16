# RandomPlayer<br>
## simple mp3 player<br>
A basic mp3 player that will shuffle the list of songs, play through the list, then shuffle again and continue playing.<br>
options to not shuffle, and/or not continuous loop.<br>
<br>
I don't like most playlist editors, so I created my own. (located under options/playlist)<br>
<br>
<br>
<br>

### req qmediaplayer (for qt5)<br> 

#### if ERROR: Unknown module(s) in QT: multimedia<br>
sudo apt-get install qtmultimedia5-dev<br>
<br>
<br>

#### if defaultServiceProvider::requestService():<br> no service found for - "org.qt-project.qt.mediaplayer"
sudo apt-get install libqt5multimedia5-plugins<br>
<br>
<br>

#### if Warning: "No decoder available for type 'audio/mpeg ...
sudo apt-get install gstreamer1.0-libav<br>

<br>
<br>
<br>

### For ARM
sudo apt install qt5-default qtbase5-dev qt5-qmake cmake<br>
sudo apt-get install qtmultimedia5-dev<br>
sudo apt-get build-dep qtmultimedia5-dev<br>

