#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QPushButton>
#include <QListView>
#include <QSlider>

#include "ui_mainwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  /** master playlist */
  /** for loading,saving and editing */
  QStringList playlist;

  /** player button status */
  //  0 stopped
  //  1 play
  //  2 paused
  int bt_status;

private:
  Ui::MainWindow *ui;


  QGroupBox *horizontalGroupBox;

  QMenuBar *appMenuBar;
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

  void printData(QStringList);

public slots:

signals:
  void sendEditData(QStringList);

};
#endif // MAINWINDOW_H
