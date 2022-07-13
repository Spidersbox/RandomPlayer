#ifndef EDITFORM_H
#define EDITFORM_H

#include <QWidget>
#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QListWidgetItem>

namespace Ui
{
  class EditForm;
}

class EditForm : public QWidget
{
    Q_OBJECT

public:
    explicit EditForm(QWidget *parent = nullptr);
    ~EditForm();

    QStringList playlist;
    void receivePlaylist(QStringList list);
private:
    Ui::EditForm *ui;


    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;


    void updateFilters();

    //    QStringList  playlist;

    /** setup button signals */
    void SetSignals();

private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void on_listView_doubleClicked(const QModelIndex &index);

    void on_driveChanged(QString choice);
    void bt_right_clicked();
    void bt_rightAll_clicked();
    void bt_left_clicked();

    void bt_cancel_clicked();
    void bt_ok_clicked();
    void bt_save_clicked();

    void cb_mp3_clicked();
    void cb_midi_clicked();
    void cb_wave_clicked();

    void recieveEditData(QStringList);

signals:
    void sendData(QStringList);
};

#endif // EDITFORM_H
