# RandomPlayer
simple mp3 player

req qmediaplayer (for qt5)
**  if ERROR: Unknown module(s) in QT: multimedia
sudo apt-get install qtmultimedia5-dev

**  if defaultServiceProvider::requestService():
**  no service found for - "org.qt-project.qt.mediaplayer"
sudo apt-get install libqt5multimedia5-plugins

**  if Warning: "No decoder available for type 'audio/mpeg ...
sudo apt-get install gstreamer1.0-libav

