#include <QApplication>
#include <QMenuBar>
#include <QIcon>
#include <QStyle>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include <QMessageBox> // for debuging
#include <QDebug>

#include "editform.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  resize(680, 540);
  setWindowTitle(tr("Random Player"));


#ifndef Q_OS_MAC
    qApp->setWindowIcon(QIcon(":icons/RandomPlayer"));
    setWindowIcon(QIcon(":icons/RandomPlayer"));
#else
    setUnifiedTitleAndToolBarOnMac(true);
    QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
#endif

  /** Create the toolbars */
  createToolBars();

  /** Create actions for the toolbar, menu bar and tray/dock icon */
  createActions();

  /** Create application menu bar */
  createMenuBar();
  /** menubar on form instead */
  menuBar()->setNativeMenuBar(false);

  player = new QMediaPlayer;
  audioOutput = new QAudioOutput;
  player->setAudioOutput(audioOutput);
  // ...

  connect(player,SIGNAL(positionChanged(qint64)) ,this,SLOT(on_positionChanged(qint64)));
  connect(player,SIGNAL(durationChanged(qint64)) ,this,SLOT(on_durationChanged(qint64)));
  connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(mediaStatuChngd(QMediaPlayer::MediaStatus)));



}

MainWindow::~MainWindow()
{
    delete ui;
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::createMenuBar()
{
#ifdef Q_OS_MAC
  /** Create a decoupled menu bar on Mac */
  /** which stays even if the window is closed */
  appMenuBar = new QMenuBar();
#else
  /** Get the main window's menu bar on other platforms */
  appMenuBar = menuBar();
#endif

  /** Configure the menus */
  QMenu *file = appMenuBar->addMenu(tr("&File"));
  file->addAction(openAction);
  file->addAction(quitAction);

  QMenu *settings = appMenuBar->addMenu(tr("&Options"));
  QMenu *submenu=settings->addMenu("&Playlist");
  submenu->addAction(editAction);
  submenu->addAction(saveAction);

  settings->addAction(randomAction);
  settings->addAction(randomizerAction);
  settings->addAction(loopAction);
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::createToolBars()
{
  playButton = new QPushButton(this);
  playButton->setStyleSheet( "*{border-image: url(:/images/bt_play); width: 16px; height: 16px;}"
                             ":hover{ border-image: url(:/images/bt_play_hover);}");
  playButton->setEnabled(true);

  pauseButton = new QPushButton(this);
  pauseButton->setStyleSheet("*{border-image: url(:/images/bt_pause); width: 16px; height: 16px;}"
                             ":hover{ border-image: url(:/images/bt_pause_hover);}");
  pauseButton->setEnabled(true);

  stopButton = new QPushButton(this);
  stopButton->setStyleSheet("*{border-image:url(:/images/bt_stop); width: 16px; height: 16px;}"
                            ":hover{ border-image: url(:/images/bt_stop_hover);}");
  stopButton->setEnabled(true);

  nextButton = new QPushButton(this);
  nextButton->setStyleSheet("*{border-image:url(:/images/bt_next); width: 16px; height: 16px;}"
                            ":hover{ border-image: url(:/images/bt_next_hover);}");
  nextButton->setEnabled(true);

  previousButton = new QPushButton(this);
  previousButton->setStyleSheet("*{border-image:url(:/images/bt_previous); width: 16px; height: 16px;}"
                                ":hover{ border-image: url(:/images/bt_previous_hover);}");
  previousButton->setEnabled(true);

  progressBar = new QSlider(Qt::Horizontal,this);

  label_length= new QLabel(this);
  label_length->setText("test message");

  horizontalGroupBox = new QGroupBox;
  progressGroupBox = new QGroupBox;
  QHBoxLayout *playerLayout = new QHBoxLayout;
  QHBoxLayout *progressLayout = new QHBoxLayout;

  playerLayout->addWidget(playButton);
  playerLayout->addWidget(pauseButton);
  playerLayout->addWidget(stopButton);
  playerLayout->addWidget(nextButton);
  playerLayout->addWidget(previousButton);
  playerLayout->setContentsMargins(0,0,0,0);

  progressLayout->addWidget(progressBar);
  progressLayout->addWidget(label_length);


  horizontalGroupBox->setLayout(playerLayout);
  horizontalGroupBox->setContentsMargins(0,0,0,0);

  progressGroupBox->setLayout(progressLayout);
  progressGroupBox->setContentsMargins(0,0,0,0);

  ui->mainLayout->addWidget(horizontalGroupBox);
  ui->mainLayout->addWidget(progressGroupBox);
//  ui->mainLayout->addWidget(progressBar);
//  ui->mainLayout->addWidget(label_length);

}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::createActions()
{
  /** main menu actions */
  openAction = new QAction(QIcon(":/images/bt_open"), tr("&Open"), this);
  openAction->setToolTip(tr("Open a playlist file"));
  quitAction = new QAction(QIcon(":/images/bt_close"), tr("E&xit"), this);
  quitAction->setToolTip(tr("Quit application"));

  editAction = new QAction(QIcon(":/images/bt_edit"), tr("&Edit Playlist"), this);
  editAction->setToolTip(tr("open the playlist editor options"));
  saveAction = new QAction(QIcon(":/images/bt_save"), tr("&Save Playlist"), this);
  saveAction->setToolTip(tr("save the playlist"));

  randomAction = new QAction(QIcon(":/images/bt_shuffle"), tr("&Shuffle (do it NOW)"), this);
  randomAction->setToolTip(tr("randomize the playlist now"));

  randomizerAction = new QAction(QIcon(":/images/bt_shuffle"), tr("Shu&ffle (switch)"), this);
  randomizerAction->setToolTip(tr("randomize the playlist each time"));
  randomizerAction->setCheckable(true);

  loopAction = new QAction(QIcon(":/images/bt_repeat"), tr("&Repeat (switch)"), this);
  loopAction->setToolTip(tr("repeat playing in a loop"));
  loopAction->setCheckable(true);

  /** player toolbar actions */
//  playAction = new QAction;
//  pauseAction = new QAction;
//  stopAction = new QAction;
//  nextAction = new QAction;
//  previousAction = new QAction;


  /** main menu signals */
  connect(openAction, SIGNAL(triggered()), this, SLOT(openClicked()));
  connect(quitAction, SIGNAL(triggered()), this, SLOT(quitClicked()));

  connect(editAction, SIGNAL(triggered()), this, SLOT(editClicked()));
  connect(saveAction, SIGNAL(triggered()), this, SLOT(saveClicked()));
  connect(randomAction, SIGNAL(triggered()), this, SLOT(randomClicked()));
  connect(randomizerAction, SIGNAL(triggered()), this, SLOT(randomizerClicked()));
  connect(loopAction, SIGNAL(triggered()), this, SLOT(loopClicked()));

  /** player toolbar signals */
//  connect(playAction, SIGNAL(triggered()), this, SLOT(playClicked()));
  connect(playButton, &QAbstractButton::clicked, this, &MainWindow::playClicked);
//  connect(pauseAction, SIGNAL(triggered()), this, SLOT(pauseClicked()));
  connect(pauseButton, &QAbstractButton::clicked, this, &MainWindow::pauseClicked);
//  connect(stopAction, SIGNAL(triggered()), this, SLOT(stopClicked()));
  connect(stopButton, &QAbstractButton::clicked, this, &MainWindow::stopClicked);
//  connect(nextAction, SIGNAL(triggered()), this, SLOT(nextClicked()));
  connect(nextButton, &QAbstractButton::clicked, this, &MainWindow::nextClicked);
//  connect(previousAction, SIGNAL(triggered()), this, SLOT(previousClicked()));
  connect(previousButton, &QAbstractButton::clicked, this, &MainWindow::previousClicked);

}


//-----------------------------------------------------------------------------------------------------------------
/** Show open file dialog */
void MainWindow::openClicked()
{
  QString filename=QFileDialog::getOpenFileName(
              this,
              "Open Playlist",
              "/",
              "playlist files (*.m3u)");

  QFile file(filename);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    playlist.clear();
    ui->listWidget->clear();
    ui->listWidget2->clear();
    QTextStream textStream(&file);
    while (!textStream.atEnd())
    {
      QString line=textStream.readLine();
      playlist<<line;
      ui->listWidget->addItem(line);
    }
    file.close();
    QApplication::restoreOverrideCursor();
    stopClicked();
    loadPlayer();
  }
  else
  {
    QString mess="Could not open file: "+filename;
    QMessageBox::warning(this,"Random Player",mess);
  }
}

//-----------------------------------------------------------------------------------------------------------------
/** exit this app */
void MainWindow::quitClicked()
{
  qApp->quit();
}

//-----------------------------------------------------------------------------------------------------------------
/** Open playlist editor dialog */
void MainWindow::editClicked()
{
  EditForm *dialog = new EditForm();
  /** for retrieving data from editform to mainform */
  connect(dialog, SIGNAL(sendData(QStringList)), this, SLOT(printData(QStringList)));

  dialog->receivePlaylist(playlist);
  dialog->show();

}

//-----------------------------------------------------------------------------------------------------------------
/** recieves playlist from editor */
void MainWindow::printData(QStringList dat)
{
  playlist=dat; // keep a copy of the playlist
  ui->listWidget->clear();
  ui->listWidget2->clear();
  ui->listWidget->addItems(dat);
}


//-----------------------------------------------------------------------------------------------------------------
/** save playlist to a file */
void MainWindow::saveClicked()
{
  QString filename = QFileDialog::getSaveFileName(this, tr("save as"), "/", tr("playlist files(*.m3u)"));
  if (filename.isEmpty())
    return;

  // check for extension
  // windows will add the extension
  // ubuntu will not
  int x=filename.indexOf("m3u");
  if(x<1)
    filename=filename+".m3u";

  QFile file(filename);
  //Open the file
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;

  QTextStream out(&file);
  for(int i=0;i<playlist.size();++i)
    out<<playlist[i]<<"\n";

  file.close();
}

//-----------------------------------------------------------------------------------------------------------------
/** randomize now trigger */
void MainWindow::randomClicked()
{
  QMessageBox::warning(this,"Random Player","the Randomize NOW was triggered");
}

//-----------------------------------------------------------------------------------------------------------------
/** toggle randomizer switch */
void MainWindow::randomizerClicked()
{
//  QMessageBox::warning(this,"Random Player","the Randomize switch was triggered");

}

//-----------------------------------------------------------------------------------------------------------------
/** toggle play loop switch */
void MainWindow::loopClicked()
{
//  QMessageBox::warning(this,"Random Player","the loop switch was triggered");

}

//-----------------------------------------------------------------------------------------------------------------
/** play button */
void MainWindow::playClicked()
{
//  QMessageBox::warning(this,"Random Player","play button pressed");
  playButton->setStyleSheet( "*{border-image: url(:/images/bt_play_hover); width: 16px; height: 16px;}"
                             ":hover{ border-image: url(:/images/bt_play_hover);}");
  bt_status=1;
//player->play();
//player->setSource(QUrl::fromLocalFile("F:/MP3/boston/Boston - Carry on My Wayward Son.mp3"));
//audioOutput->setVolume(50);
player->play();
}

//-----------------------------------------------------------------------------------------------------------------
/** pause button */
void MainWindow::pauseClicked()
{
  QMessageBox::warning(this,"Random Player","pause button pressed");

}

//-----------------------------------------------------------------------------------------------------------------
/** stop button */
void MainWindow::stopClicked()
{
player->stop();
//  QMessageBox::warning(this,"Random Player","stop button pressed");
  playButton->setStyleSheet( "*{border-image: url(:/images/bt_play); width: 16px; height: 16px;}"
                             ":hover{ border-image: url(:/images/bt_play_hover);}");
bt_status=0;
}

//-----------------------------------------------------------------------------------------------------------------
/** next button */
void MainWindow::nextClicked()
{
//  QMessageBox::warning(this,"Random Player","next button pressed");
  player->stop();

  if(ui->listWidget->count() >1)
  {
    QListWidgetItem *item = ui->listWidget->takeItem(0);
    ui->listWidget2->addItem(item->text());
    delete item;
    QString filename=ui->listWidget->item(0)->text();
    player->setSource(QUrl::fromLocalFile(filename));
    player->play();
  }
  else
  {
    player->stop();
    QListWidgetItem *item = ui->listWidget->takeItem(0);
    ui->listWidget2->addItem(item->text());
    delete item;
// trigger loop now
  }
}

//-----------------------------------------------------------------------------------------------------------------
/** previous button */
void MainWindow::previousClicked()
{
  QMessageBox::warning(this,"Random Player","previous button pressed");

}

//-----------------------------------------------------------------------------------------------------------------
/** load the player with the first song */
void MainWindow::loadPlayer()
{
  player->stop();
  if(ui->listWidget->count())
  {
    QString filename=ui->listWidget->item(0)->text();
    player->setSource(QUrl::fromLocalFile(filename));

    setWindowTitle(filename);
  }
}

//-------------------------------------------  player  ------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
void MainWindow::on_positionChanged(qint64 position)
{
    progressBar->setValue(position);
    label_length->setText( second_to_minutes(position / 1000).append("/").append( second_to_minutes( (progressBar->maximum())/1000 ) ) );
}

//-----------------------------------------------------------------------------------------------------------------
QString MainWindow::second_to_minutes(int seconds)
{
    int sec = seconds;
    QString mn = QString::number( (sec ) / 60);
    int _tmp_mn  = mn.toInt() * 60;
    QString sc= QString::number( (seconds- _tmp_mn  ) % 60 );

    return (mn.length() == 1 ? "0" + mn : mn ) + ":" + (sc.length() == 1 ? "0" + sc : sc);
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::on_durationChanged(qint64 position)
{
    progressBar->setMaximum(position);
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::mediaStatuChngd(QMediaPlayer::MediaStatus state)
{
  if(state == QMediaPlayer::EndOfMedia)
  {
    player->stop();
//    if(ui->listWidget->count() >1)
//    {
      nextClicked();
//    }
  }
}
