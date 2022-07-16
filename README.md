# RandomPlayer
## simple mp3 player<br>






### req qmediaplayer (for qt5)<br>
**  if ERROR: Unknown module(s) in QT: multimedia<br>
sudo apt-get install qtmultimedia5-dev<br>
<br>
**  if defaultServiceProvider::requestService():<br>
**  no service found for - "org.qt-project.qt.mediaplayer"<br>
sudo apt-get install libqt5multimedia5-plugins<br>
<br>
**  if Warning: "No decoder available for type 'audio/mpeg ...<br>
sudo apt-get install gstreamer1.0-libav<br>

<br>
<br>
<br>
### For ARM<br>
sudo apt install qt5-default qtbase5-dev qt5-qmake cmake<br>
sudo apt-get install qtmultimedia5-dev<br>
sudo apt-get build-dep qtmultimedia5-dev<br>

