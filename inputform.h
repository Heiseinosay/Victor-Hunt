#ifndef INPUTFORM_H
#define INPUTFORM_H

#include <QDialog>
#include "outputpresentation.h"

namespace Ui {
class InputForm;
}

class InputForm : public QDialog
{
    Q_OBJECT

public:
    explicit InputForm(QWidget *parent = nullptr);
    ~InputForm();

public slots:

private slots:

    void on_btnEditName_clicked();

    void on_btnAddName_clicked();

    void on_btnAddPrize_clicked();

    void on_btnEditPrize_clicked();

    void on_themeSelection_currentIndexChanged(int index);

    void on_btnRoll_clicked();

    void on_btnCheck_clicked();

    void on_btnCancel_clicked();

    void on_tbStart_clicked();

    void on_tbAbout_clicked();

    void on_tbResult_clicked();

    void on_tbErase_clicked();

    void on_tbQuit_clicked();

    void on_cbFullScreen_clicked(bool checked);

    void on_pushButton_clicked();

    void RemoveLines(int whichTextEdit);

    void changeBG(int width, int height);

    void on_tbResume_clicked();

    void saveAll();

    void on_tbResultBack_clicked();

    void on_tbResultSave_clicked();

    void on_tbOpen_clicked();

    void on_tbSave_clicked();

    void closeEvent(QCloseEvent *bar);

private:
    Ui::InputForm *ui;

};

#endif // INPUTFORM_H
