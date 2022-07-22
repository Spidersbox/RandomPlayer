#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QPushButton>
#include <QListView>
#include <QSlider>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QtGlobal>
#include "ui_mainwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent =0);
  ~MainWindow();

  /** master playlist */
  /** for loading,saving and editing */
  QStringList playlist;


private:
  Ui::MainWindow *ui;
  QMediaPlayer *player;
  QAudioOutput *audioOutput;

  QGroupBox *horizontalGroupBox;
  QGroupBox *progressGroupBox;

  QMenuBar *appMenuBar;
  QLabel *label_length;
  QAction *openAction;
  QAction *quitAction;

  /** playlist submenu options */
  QAction *editAction;
  QAction *saveAction;

  QAction *randomAction;
  QAction *randomizerAction;
  QAction *loopAction;

  /** Toolbar actions */
  QAction *playAction;
  QAction *pauseAction;
  QAction *stopAction;
  QAction *nextAction;
  QAction *previousAction;

  QPushButton *playButton;
  QPushButton *pauseButton;
  QPushButton *stopButton;
  QPushButton *nextButton;
  QPushButton *previousButton;

  QSlider *progressBar;

  QString second_to_minutes(int seconds);
  void setStatusInfo(const QString &info);


  /** Create the main UI actions. */
  void createActions();
  /** Create the menu bar and sub-menus. */
  void createMenuBar();
  /** Create the toolbars */
  void createToolBars();



private slots:
  /** Show open file dialog */
  void openClicked();
  /** exit this app */
  void quitClicked();

  /** show playlist editor */
  void editClicked();
  /** save playlist */
  void saveClicked();
  /** randomize now trigger */
  void randomClicked();
  /** toggle randomizer switch */
  void randomizerClicked();
  /** toggle play loop switch */
  void loopClicked();

  /** player slots */
  void playClicked();
  void pauseClicked();
  void stopClicked();
  void nextClicked();
  void previousClicked();

  void loadPlayer();
  void printData(QStringList);

  void on_positionChanged(qint64 position);
  void on_durationChanged(qint64 position);
  void mediaStatuChngd(QMediaPlayer::MediaStatus state);
  void displayErrorMessage();

public slots:

signals:
  void sendEditData(QStringList);

};
#endif // MAINWINDOW_H
