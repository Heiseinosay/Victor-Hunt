#include "inputform.h"
#include "qlayout.h"
#include "ui_inputform.h"
#include <QMessageBox>
#include <QTextStream>
#include <QTextBlock>
#include <stdio.h>
#include <string.h>
#include <QPixmap>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <QColor>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;
using namespace std;

InputForm::InputForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputForm)

{
    ui->setupUi(this);
    //DropDown
    ui->PrizeSelectionMode->addItem("Random");
    ui->PrizeSelectionMode->addItem("Last");
    ui->PrizeSelectionMode->addItem("First");

    //TextEdit
    ui->textEditName->setDisabled(true);
    ui->textEditPrize->setDisabled(true);

    // ThemeSelection Drop down
    ui->themeSelection->addItem(QIcon(":/img/img/gold.png"), "Gold");
    ui->themeSelection->addItem(QIcon(":/img/img/red.png"), "Red");
    ui->themeSelection->addItem(QIcon(":/img/img/pink.png"), "Pink");
    ui->themeSelection->addItem(QIcon(":/img/img/green.png"), "Green");

    //Celebration title Sample Text
    ui->lineEditTitle->setText("Sample Text");

    // DISABLE ADD BUTTON
    ui->btnAddName->setEnabled(false);
    ui->btnAddPrize->setEnabled(false);

    // Disable Resize
    this->setFixedSize(QSize(1191, 695));

    // HIDE CHECK AND CANCEL BUTTON
    ui->btnCheck->setVisible(false);
    ui->btnCancel->setVisible(false);

    // SET DEFAULT TAB
    ui->tabWidget->setCurrentIndex(0);

    // HIDE TABS
    ui->tabWidget->tabBar()->hide();
    qDebug() << this->height();

    // HIDE RESUME BUTTON
    ui->tbResume->setVisible(false);


    ui->tabWidget->setContentsMargins(0, 0, 0, 0);
    this->setContentsMargins(0, 0, 0, 0);

    // SET WIDTH OF COUMN IN RESULT TABLES
    //ui->tableWidget->verticalHeader()->setDefaultSectionSize(100);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(310);
    ui->tableWidget->setColumnWidth(0, 170);

    ui->tableWidgetCancel->horizontalHeader()->setDefaultSectionSize(310);
    ui->tableWidgetCancel->setColumnWidth(0, 170);

    // ADD MINIMIZE BUTTON
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);

    // SET FONT
    int id = QFontDatabase::addApplicationFont(":/font/fonts/MarsBrandsEditTab.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont marsBrandsEditTab(family, 25);
    ui->title->setFont(marsBrandsEditTab);

    int id2 = QFontDatabase::addApplicationFont(":/font/fonts/GoodVibes.ttf");
    QString family2 = QFontDatabase::applicationFontFamilies(id2).at(0);
    QFont goodVibes(family2, 65);
    ui->CelebrationTitle->setFont(goodVibes);

    int id3 = QFontDatabase::addApplicationFont(":/font/fonts/Butler_Regular.otf");
    QString family3 = QFontDatabase::applicationFontFamilies(id3).at(0);
    QFont butler1(family3, 65);
    ui->WinnerName->setFont(butler1);

    int id4 = QFontDatabase::addApplicationFont(":/font/fonts/Butler_Regular.otf");
    QString family4 = QFontDatabase::applicationFontFamilies(id4).at(0);
    QFont butler2(family4, 65);
    ui->PrizeName->setFont(butler2);

    QFont butler5(family4, 25);
    ui->Congratulationsto->setFont(butler5);
    ui->Congratulationsto_2->setFont(butler5);
}

InputForm::~InputForm()
{
    delete ui;
}

// TIME OUT
void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(2);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

// PRESENTATION BACKGROUND
bool started = false;
bool fullScreen = false;
int bgIndex = 0;

void InputForm::on_themeSelection_currentIndexChanged(int index)
{
    bgIndex = index;
}

void InputForm::changeBG(int width, int height) {
    switch (bgIndex) {
    case 0:
    {

        QPixmap background1(":/img/img/GoldBg.jpg");
        ui->BackgroundTheme->setPixmap(background1);
        ui->BackgroundTheme->setPixmap(background1.scaled(width, height,Qt::IgnoreAspectRatio));
        ui->CelebrationTitle->setStyleSheet("color: #C49503");
        ui->WinnerName->setStyleSheet("color: #C49503");
        ui->PrizeName->setStyleSheet("color: #C49503");

        ui->BackgroundTheme->setScaledContents( true );
        ui->BackgroundTheme->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        break;
    }
    case 1:
    {
        QPixmap background2(":/img/img/RedBg.jpg");
        ui->BackgroundTheme->setPixmap(background2);
        ui->BackgroundTheme->setPixmap(background2.scaled(width, height,Qt::IgnoreAspectRatio));
        ui->CelebrationTitle->setStyleSheet("color: #C41703");
        ui->WinnerName->setStyleSheet("color: #C41703");
        ui->PrizeName->setStyleSheet("color: #C41703");

        ui->BackgroundTheme->setScaledContents( true );
        ui->BackgroundTheme->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        break;
    }
    case 2:
    {
        QPixmap background3(":/img/img/PinkBg.jpg");
        ui->BackgroundTheme->setPixmap(background3);
        ui->BackgroundTheme->setPixmap(background3.scaled(width, height,Qt::IgnoreAspectRatio));
        ui->CelebrationTitle->setStyleSheet("color: #C800D6");
        ui->WinnerName->setStyleSheet("color: #C800D6");
        ui->PrizeName->setStyleSheet("color: #C800D6");

        ui->BackgroundTheme->setScaledContents( true );
        ui->BackgroundTheme->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        break;
    }
    case 3:
    {
        QPixmap background4(":/img/img/GreenBg.jpg");
        ui->BackgroundTheme->setPixmap(background4);
        ui->BackgroundTheme->setPixmap(background4.scaled(width, height,Qt::IgnoreAspectRatio));
        ui->CelebrationTitle->setStyleSheet("color: #317E34");
        ui->WinnerName->setStyleSheet("color: #317E34");
        ui->PrizeName->setStyleSheet("color: #317E34");

        ui->BackgroundTheme->setScaledContents( true );
        ui->BackgroundTheme->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        break;
    }
    default:
        QPixmap background5(":/img/img/GoldBg.jpg");
        ui->BackgroundTheme->setPixmap(background5);
        ui->BackgroundTheme->setPixmap(background5.scaled(width, height,Qt::IgnoreAspectRatio));
        ui->CelebrationTitle->setStyleSheet("color: #C49503}");
        ui->WinnerName->setStyleSheet("color: #C49503");
        ui->PrizeName->setStyleSheet("color: #C49503");

        ui->BackgroundTheme->setScaledContents( true );
        ui->BackgroundTheme->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}

void InputForm::on_tbQuit_clicked()
{
    QMessageBox::StandardButton answerQuit = QMessageBox::question(
                this, "Quit", "<font color=\"White\">Recent changes may not have been saved. Are you sure you want to quit?",
                QMessageBox::Yes | QMessageBox::No);

    if (answerQuit == QMessageBox::Yes) {
        qDebug() << true;
//        QApplication::closeAllWindows();
//        qApp->exit();
//        QApplication::quit();
//        QCoreApplication::quit();
//        InputForm::setModal(false);
        exit(1);
    }

}

// Instructions Message Box
void InputForm::on_tbAbout_clicked()
{
    QMessageBox::information(this, "Instructions",
                             "<font color=\"White\"> Input form<br>\t1. Click the text field button to add names and prizes. <br>\t2. Click the \"+\" button to add more participants and prizes.<br>\t3. Click the pencil button to edit, and the trash button to delete.<br>\t4. Click the next button below when you are done, clear button<br>\tto empty all fields and the quit button if you want to exit.<br>\nRaffle Window<br>\t1. Press the start button to begin the hunt. <br>\t2. Click the pencil button to return to the input form and edit details.<br>\t3. Click the trash button to exit. <br> Note: <br> Names limit: 500 <br> Prize limit: 100");

}

//Reboot to clear
void InputForm::on_tbErase_clicked()
{
    QMessageBox::StandardButton answerQuit = QMessageBox::question(
                this, "Clear", "<font color=\"White\">Recent changes may not have been saved. Are you sure you want to clear all fields?",
                QMessageBox::Yes | QMessageBox::No);

    if (answerQuit == QMessageBox::Yes) {
        ui->textEditName->clear();
        ui->textEditPrize->clear();
        ui->lineEditTitle->setText("Sample Text");
        ui->cbFullScreen->setChecked(false);
        ui->PrizeSelectionMode->setCurrentIndex(0);
        ui->themeSelection->setCurrentIndex(0);
        ui->NameCount->setText("0");
        ui->PrizeCount->setText("0");
        ui->btnAddName->setDisabled(true);
        ui->btnAddPrize->setDisabled(true);
        ui->tbStart->setVisible(true);
        ui->tbResume->setVisible(false);
        ui->WinnerName->setText("Juan Dela Cruz");
        ui->PrizeName->setText("House & Lot");
    }
}

//TextEdit Buttons
//Edit button Names
// REMOVE LINE IF EMPTY OR SPACE
void InputForm:: RemoveLines(int whichTextEdit)
{
    qDebug() << "true";
    QStringList lines;
    if (whichTextEdit == 0) {
        lines = ui->textEditName->toPlainText().split("\n");
    } else {
        lines = ui->textEditPrize->toPlainText().split("\n");
    }

    for (int ctr1 = 0; ctr1 < lines.size(); ctr1++) {
        QString line = lines.at(ctr1);
        if (line == "") {
            lines.removeAt(ctr1);
            ctr1--;
            qDebug() << ctr1;
        } else {
             QStringList words = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
            // Convert each word to title case
            for (int i = 0; i < words.size(); ++i) {
                words[i] = words[i].toLower();           // Convert to lowercase
                words[i][0] = words[i][0].toUpper();     // Capitalize first letter
            }
            QString titleCaseText = words.join(" ");

            lines[ctr1] = titleCaseText;
            qDebug() << "line: " << line;
        }
    }

    if (whichTextEdit == 0) {
        ui->textEditName->setPlainText(lines.join("\n"));
        ui->textEditName->show();
    } else {
        ui->textEditPrize->setPlainText(lines.join("\n"));
        ui->textEditPrize->show();
    }

}

void InputForm::on_btnEditName_clicked()
{
    ui->textEditName->setDisabled(false);
    ui->btnAddName->setEnabled(true);

    // SET TEXT COLOR
    ui->textEditName->setStyleSheet(
        "QTextEdit#textEditName"
        "{"
        "border: 2px solid #707070;"
        "padding: 10px;"
        "line-height: 10px;"
        "color: #E4E6EB;"
        "background-color: #242526;"
        "}"

        "QScrollBar:vertical"
        "{"
        "border: none;"
        "background: #E4E6EB;"
        "width: 8px;"
        "margin: 0px 0px 0px 0px;"
        "border-radius: 5px;"
        "padding: 2px;"
        "}"

        "QScrollBar::handle:vertical"
        "{"
        "background: #3A3B3C;"
        "min-height: 0px;"
        "border-radius: 5px;"
        "}"

        "QScrollBar::add-line:vertical"
        "{"
        "background: grey;"
        "height: 0px;"
        "subcontrol-position: bottom;"
        "subcontrol-origin: margin;"
        "border-radius: 2px;"
        "}"

        "QScrollBar::sub-line:vertical"
        "{"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0 rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130));"
        "height: 0 px;"
        "subcontrol-position: top;"
        "subcontrol-origin: margin;"
        "border-radius: 5px;"
        "}");
}

//Add button Names
void InputForm::on_btnAddName_clicked()
{
    // SET TEXT COLOR
    ui->textEditName->setStyleSheet(
        "QTextEdit#textEditName"
        "{"
            "border: 2px solid #707070;"
            "padding: 10px;"
            "line-height: 10px;"
            "color:  #707070;"
            "background-color: #242526;"
        "}"

        "QScrollBar:vertical"
        "{"
            "border: none;"
            "background: #E4E6EB;"
            "width: 8px;"
            "margin: 0px 0px 0px 0px;"
            "border-radius: 5px;"
            "padding: 2px;"
        "}"

        "QScrollBar::handle:vertical"
        "{"
            "background: #3A3B3C;"
            "min-height: 0px;"
            "border-radius: 5px;"
        "}"

        "QScrollBar::add-line:vertical"
        "{"
            "background: grey;"
            "height: 0px;"
            "subcontrol-position: bottom;"
            "subcontrol-origin: margin;"
            "border-radius: 2px;"
        "}"

        "QScrollBar::sub-line:vertical"
        "{"
            "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0 rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130));"
            "height: 0 px;"
            "subcontrol-position: top;"
            "subcontrol-origin: margin;"
            "border-radius: 5px;"
        "}");


    // SET BUTTON VISIBILITY FOR SAVING
    ui->tbResume->setVisible(false);
    ui->tbStart->setVisible(true);

    RemoveLines(0);
    ui->textEditName->setDisabled(true);
    int textEditNameLength = ui->textEditName->document()->blockCount();

    QTextDocument *doc = ui->textEditName->document();
    QTextBlock tb = doc->findBlockByLineNumber(0); // The second line.
    QString s = tb.text(); // returns 'is'
    if ((textEditNameLength == 1) && (s =="")) {
        textEditNameLength = 0;
    }
    ui->NameCount->setText(QString::number(textEditNameLength));
    ui->btnAddName->setEnabled(false);
}

//Edit button Prizes
void InputForm::on_btnEditPrize_clicked()
{
    ui->textEditPrize->setDisabled(false);
    ui->btnAddPrize->setEnabled(true);

    // SET TEXT COLOR
    ui->textEditPrize->setStyleSheet(
        "QTextEdit#textEditPrize"
        "{"
        "border: 2px solid #707070;"
        "padding: 10px;"
        "line-height: 10px;"
        "color: #E4E6EB;"
        "background-color: #242526;"
        "}"

        "QScrollBar:vertical"
        "{"
        "border: none;"
        "background: #E4E6EB;"
        "width: 8px;"
        "margin: 0px 0px 0px 0px;"
        "border-radius: 5px;"
        "padding: 2px;"
        "}"

        "QScrollBar::handle:vertical"
        "{"
        "background: #3A3B3C;"
        "min-height: 0px;"
        "border-radius: 5px;"
        "}"

        "QScrollBar::add-line:vertical"
        "{"
        "background: grey;"
        "height: 0px;"
        "subcontrol-position: bottom;"
        "subcontrol-origin: margin;"
        "border-radius: 2px;"
        "}"

        "QScrollBar::sub-line:vertical"
        "{"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0 rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130));"
        "height: 0 px;"
        "subcontrol-position: top;"
        "subcontrol-origin: margin;"
        "border-radius: 5px;"
        "}");
}

//Add button Prizes
void InputForm::on_btnAddPrize_clicked()
{
    // SET TEXT COLOR
    ui->textEditPrize->setStyleSheet(
        "QTextEdit#textEditPrize"
        "{"
        "border: 2px solid #707070;"
        "padding: 10px;"
        "line-height: 10px;"
        "color:  #707070;"
        "background-color: #242526;"
        "}"

        "QScrollBar:vertical"
        "{"
        "border: none;"
        "background: #E4E6EB;"
        "width: 8px;"
        "margin: 0px 0px 0px 0px;"
        "border-radius: 5px;"
        "padding: 2px;"
        "}"

        "QScrollBar::handle:vertical"
        "{"
        "background: #3A3B3C;"
        "min-height: 0px;"
        "border-radius: 5px;"
        "}"

        "QScrollBar::add-line:vertical"
        "{"
        "background: grey;"
        "height: 0px;"
        "subcontrol-position: bottom;"
        "subcontrol-origin: margin;"
        "border-radius: 2px;"
        "}"

        "QScrollBar::sub-line:vertical"
        "{"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0 rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130));"
        "height: 0 px;"
        "subcontrol-position: top;"
        "subcontrol-origin: margin;"
        "border-radius: 5px;"
        "}");

    // SET BUTTON VISIBILITY FOR SAVING
    ui->tbResume->setVisible(false);
    ui->tbStart->setVisible(true);

    RemoveLines(1);
    ui->textEditPrize->setDisabled(true);
    int textEditPrizeLength = ui->textEditPrize->document()->blockCount();

    QTextDocument *doc = ui->textEditName->document();
    QTextBlock tb = doc->findBlockByLineNumber(0); // The second line.
    QString s = tb.text(); // returns 'is'
    if ((textEditPrizeLength == 1) && (s =="")) {
        textEditPrizeLength = 0;
    }
    ui->PrizeCount->setText(QString::number(textEditPrizeLength));
    ui->btnAddPrize->setEnabled(false);
}

// global variables
QString names[500];
QString prizes[100];

int counterNames = 0;
int counterPrize = 0;

void InputForm::saveAll(){
    // SET FULL SCREEN
    if (!started) {
        started = true;
    }
    if (fullScreen) {
        qDebug() << "notFullScreen";
        QWidget::showFullScreen();

        int h = this->height();
        int w = this->width();

        ui->BackgroundTheme->setGeometry(0, 0, w + 50, h + 50);
        changeBG(w, h);

        ui->tabWidget->setMinimumHeight(h);
        ui->tabWidget->setMinimumWidth(w);

        ui->bgConfetti->setMinimumHeight(h);
        ui->bgConfetti->setMinimumWidth(w);

        ui->bgGoldDrop->setMinimumHeight(h);
        ui->bgGoldDrop->setMinimumWidth(w);

        ui->BackgroundTheme->setMinimumHeight(h);
        ui->BackgroundTheme->setMinimumWidth(w);

        QScreen *screen = QGuiApplication::primaryScreen();
        QRect  screenGeometry = screen->geometry();

        int x = (screenGeometry.width () - ui->wordContainer->width ()) / 2;
        int y = (screenGeometry.height () - ui->wordContainer->height ()) / 2;

        qDebug() << "Screen width: " << screenGeometry.width ();
        qDebug() << "Screen height: " << screenGeometry.height ();
        qDebug() << "x: " << x;
        qDebug() << "y: " << y;

        ui->wordContainer->setGeometry (x, y, 1101, 551);

    } else {
        qDebug() << "notFullScreen";

        int h = this->height();
        int w = this->width();

        ui->BackgroundTheme->setGeometry(0, 0, w + 50, h + 50);
        changeBG(w, h);

        ui->tabWidget->setMinimumHeight(h);
        ui->tabWidget->setMinimumWidth(w);

        ui->bgConfetti->setMinimumHeight(h);
        ui->bgConfetti->setMinimumWidth(w);

        ui->bgGoldDrop->setMinimumHeight(h);
        ui->bgGoldDrop->setMinimumWidth(w);

        ui->BackgroundTheme->setMinimumHeight(h);
        ui->BackgroundTheme->setMinimumWidth(w);

        int x = (1191 - ui->wordContainer->width ()) / 2;
        int y = (695 - ui->wordContainer->height ()) / 2;

        qDebug() << "x: " << x;
        qDebug() << "y: " << y;

        ui->wordContainer->setGeometry (x, y, 1101, 551);
    }
}



//Btn Go
void InputForm::on_tbStart_clicked()
{
    // BUTTON VISIBILITY CHANGE
    ui->tbStart->setVisible(false);
    ui->tbResume->setVisible(true);

    // CALL SAVE PREFERENCES
    saveAll();

    // MOVE TO PRESENTATION TAB
    ui->tabWidget->setCurrentIndex(1);

    // SAVE NAMES AND PRIZES
    //NAME
    //Reset Array Size
    memset( names, 0, sizeof( names ) );
    //qDebug() << names->length() << "line 190";
    int textEditLength = ui->textEditName->document()->blockCount();
    //qDebug() << "textEdit length:" << textEditLength;

    //Array Names append
    for (int i = 0; i < textEditLength; i++) {
        QTextDocument *doc = ui->textEditName->document();
        QTextBlock tb = doc->findBlockByLineNumber(i); // The second line.
        QString s = tb.text();

        if(s.isEmpty()) {
            //qDebug() << "Hey Empty here Line: 126";
        } else if(!s.isEmpty()) {
            //qDebug() << i + 1;
            names[i] = s;
        }
    }

    // Print Name Array
    for (int j = 0; j < names->length(); j++) {
        if (names[j] == "") {
            break;
        } else {
            qDebug() << names[j];
        }
    }

    //Prize
    //Reset Array Size
    memset( prizes, 0, sizeof( prizes ));
    int textEditPrizeLength = ui->textEditPrize->document()->blockCount();
    //qDebug() << textEditPrizeLength;

    //Array Prize append
    for (int i = 0; i < textEditPrizeLength; i++) {
        QTextDocument *doc = ui->textEditPrize->document();
        QTextBlock tb = doc->findBlockByLineNumber(i); // The second line.
        QString s = tb.text();

        if(s.isEmpty()) {
            //qDebug() << "Hey Empty here Line: 126";
        } else if(!s.isEmpty()) {
            //qDebug() << i + 1;
            prizes[i] = s;
        }
    }

    //Display Celebration title
    QString Title = ui->lineEditTitle->text();
    ui->CelebrationTitle->setText(Title);

    // Back to Zero;
    counterNames = 0;
    counterPrize = 0;
}

void InputForm::on_tbResume_clicked()
{
    saveAll();
    //Display Celebration title
    QString Title = ui->lineEditTitle->text();
    ui->CelebrationTitle->setText(Title);

    // MOVE TO PRESENTATION TAB
    ui->tabWidget->setCurrentIndex(1);
}
// Raffle Button Hunt-----------------------------------------------------------------------------------------------------------------

int randNumName = 0;
int randNumPrize = 0;
void InputForm::on_btnRoll_clicked()
{
    // HIDE BUTTON btnRoll
    ui->btnRoll->setVisible(false);
    ui->pushButton->setVisible(false);

    int textEditNameLength = ui->textEditName->document()->blockCount();
    int textEditPrizeLength = ui->textEditPrize->document()->blockCount();
    int descPrize = textEditPrizeLength - 1;
    int ascPrize = 0;
    if (counterNames == textEditNameLength || counterPrize == textEditPrizeLength) {
        QMessageBox::warning(this, "Notice!", "<font color=\"White\">No more Entries");
        ui->btnRoll->setVisible(true);
        ui->pushButton->setVisible(true);
    } else {
        //Flash the random letters
        QString randomNamesFlash[25] = {"dfgrgs sadw dsaf", "aFwwerdsg dsfyvny", "ioierimib ifwiemnsd",
                                        "pewprfj woeromneq", "sdbnlopry xcriopw", "mpyatcdvf aitpmzdtc",
                                        "dfgrgs sadw dsaf", "aFwwerdsg dsfyvny", "ioierimib ifwiemnsd",
                                        "dfgrgs sadw dsaf", "aFwwerdsg dsfyvny", "ioierimib ifwiemnsd",
                                        "pewprfj woeromneq", "sdbnlopry xcriopw", "mpyatcdvf aitpmzdtc",
                                        "dfgrgs sadw dsaf", "aFwwerdsg dsfyvny", "ioierimib ifwiemnsd",
                                        "pewprfj woeromneq", "sdbnlopry xcriopw", "mpyatcdvf aitpmzdtc",
                                        "dfgrgs sadw dsaf"};

        QString randomPrizeFlash[25] = {"ktmnmyuiy sdagarhwqebv", "ahsioudsg sdaghhrpert", "pokfdnbeu asdfioeruntre",
                                        "iouerngfgf sdagiweahut", "fsfefhewry ewgsdgdsfh", "mkbeoopiuosa isdhfgidsg",
                                        "ktmnmyuiy sdagarhwqebv", "ahsioudsg sdaghhrpert", "pokfdnbeu asdfioeruntre",
                                        "iouerngfgf sdagiweahut", "fsfefhewry ewgsdgdsfh", "mkbeoopiuosa isdhfgidsg",
                                        "ktmnmyuiy sdagarhwqebv", "ahsioudsg sdaghhrpert", "pokfdnbeu asdfioeruntre",
                                        "iouerngfgf sdagiweahut", "fsfefhewry ewgsdgdsfh", "mkbeoopiuosa isdhfgidsg",
                                        "ktmnmyuiy sdagarhwqebv", "ahsioudsg sdaghhrpert", "pokfdnbeu asdfioeruntre",
                                        "iouerngfgf sdagiweahut", "fsfefhewry ewgsdgdsfh", "mkbeoopiuosa isdhfgidsg",
                                         "ktmnmyuiy sdagarhwqebv"};

        for (int i = 0; i < 24; i++) {
                this_thread::sleep_for(chrono::milliseconds(0200));
                ui->WinnerName->setText(randomNamesFlash[i]);
                ui->PrizeName->setText(randomPrizeFlash[i]);
                qApp->processEvents();
        }

        // Choose Random Name
        srand(time(0));
        randNumName = 0 + (rand() % (textEditNameLength - counterNames));
        qDebug() << randNumName;
        // SET FONT SIZE
        int id3 = QFontDatabase::addApplicationFont(":/font/fonts/Butler_Regular.otf");
        QString family3 = QFontDatabase::applicationFontFamilies(id3).at(0);

        qDebug() << names[randNumName].length();

        if (fullScreen) {

            if (names[randNumName].length() > 32) {
                QFont butler(family3, 50);
                ui->WinnerName->setFont(butler);
            } else if (names[randNumName].length() > 26) {
                QFont butler(family3, 55);
                ui->WinnerName->setFont(butler);
            } else {
                QFont butler(family3, 65);
                ui->WinnerName->setFont(butler);
            }
        } else {
            if (names[randNumName].length() > 32) {
                QFont butler(family3, 50);
                ui->WinnerName->setFont(butler);
            } else if (names[randNumName].length() > 26) {
                QFont butler(family3, 55);
                ui->WinnerName->setFont(butler);
            } else {
                QFont butler(family3, 65);
                ui->WinnerName->setFont(butler);
            }
        }


        ui->WinnerName->setText(names[randNumName]);



        //qDebug() << "length" << counterNames;

        // Prize
        int prizeSelectionIndex = ui->PrizeSelectionMode->currentIndex();

        switch (prizeSelectionIndex) {
            case 0:
            {
                // Choose Random Prize
                qDebug() << "random";
                srand(time(0));
                randNumPrize = 0 + (rand() % (textEditPrizeLength - counterPrize));
                qDebug() << randNumPrize;
                ui->PrizeName->setText(prizes[randNumPrize]);
                break;

            }
        case 1:
            {
                descPrize -= counterPrize;
                ui->PrizeName->setText(prizes[descPrize]);
                randNumPrize = descPrize;
                break;
            }
         case 2:
            {
                //qDebug() << "ascending";
                randNumPrize = ascPrize;
                ui->PrizeName->setText(prizes[ascPrize]);
                ascPrize += counterPrize;
                break;
            }
        }

            // SHOW CHECK AND CANCEL BUTTON
            ui->btnCheck->setVisible(true);
            ui->btnCancel->setVisible(true);
    }
}

int row = 0;

void InputForm::on_btnCheck_clicked()
{
    // DELETE Name
    int nNames = sizeof(names)/sizeof(names[0]);
    QString xName = names[randNumName];

    // Delete x from names[]
    int iNames;
    for (iNames = 0; iNames < nNames; iNames++)
        if (names[iNames] == xName)
                break;

    if (iNames < nNames)
    {
        nNames = nNames - 1;
        for (int j= iNames; j < nNames; j++)
                names[j] = names[j+1];
    }

    counterNames++;

   // DELETE Prize
    int nPrize = sizeof(prizes)/sizeof(prizes[0]);
    QString xPrize = prizes[randNumPrize];

    // Delete x from prize[]
    int iPrize;
    for (iPrize = 0; iPrize < nPrize; iPrize++)
        if (prizes[iPrize] == xPrize)
            break;

    if (iPrize < nPrize)
    {
        nPrize = nPrize - 1;
        for (int j= iPrize; j < nPrize; j++)
            prizes[j] = prizes[j+1];
    }

    counterPrize++;

    // APPEND DATA TO TABLE IN RESULT TAB
    ui->tableWidget->insertRow ( ui->tableWidget->rowCount() );
    ui->tableWidget->setItem   ( ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(QString("%1").arg(row+1)));
    ui->tableWidget->setItem   ( ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(xName));
    ui->tableWidget->setItem   ( ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(xPrize));

    row+=1;

    // SET BUTTON ROLL VISIBLE. HIDE CHECK AND CANCEL BUTTON
    ui->btnRoll->setVisible(true);
    ui->pushButton->setVisible(true);
    // HIDE CHECK AND CANCEL BUTTON
    ui->btnCheck->setVisible(false);
    ui->btnCancel->setVisible(false);

}

// BTN CANCEL VARIBALES

void InputForm::on_btnCancel_clicked()
{
    int nNames = sizeof(names)/sizeof(names[0]);
    QString xName = names[randNumName];

    // Delete x from names[]
    int iNames;
    for (iNames = 0; iNames < nNames; iNames++)
        if (names[iNames] == xName)
                break;

    if (iNames < nNames)
    {
        nNames = nNames - 1;
        for (int j= iNames; j < nNames; j++)
                names[j] = names[j+1];
    }

    counterNames++;

    // GET THE MISSED PRIZE
    QString xPrize = prizes[randNumPrize];

    // APPEND DATA TO TABLE IN RESULT TAB
    ui->tableWidgetCancel->insertRow ( ui->tableWidgetCancel->rowCount() );
    ui->tableWidgetCancel->setItem   ( ui->tableWidgetCancel->rowCount()-1, 0, new QTableWidgetItem(QString("%1").arg(row+1)));
    ui->tableWidgetCancel->setItem   ( ui->tableWidgetCancel->rowCount()-1, 1, new QTableWidgetItem(xName));
    ui->tableWidgetCancel->setItem   ( ui->tableWidgetCancel->rowCount()-1, 2, new QTableWidgetItem(xPrize));

    // SET BUTTON ROLL VISIBLE. HIDE CHECK AND CANCEL BUTTON
    ui->btnRoll->setVisible(true);
    ui->pushButton->setVisible(true);
    // HIDE CHECK AND CANCEL BUTTON
    ui->btnCheck->setVisible(false);
    ui->btnCancel->setVisible(false);
}

void InputForm::on_tbResult_clicked()
{
    // MOVE TO RESULT TAB
    ui->tabWidget->setCurrentIndex(2);

}

void InputForm::on_cbFullScreen_clicked(bool checked)
{
    if (checked) {
        fullScreen = true;
    } else {
        fullScreen = false;
    }
}

void InputForm::on_pushButton_clicked()
{
    showNormal();
    ui->tabWidget->setCurrentIndex(0);
}

void InputForm::on_tbResultBack_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}

// File Save and Open
void InputForm::on_tbResultSave_clicked()
{
    QXlsx::Document xlsx;

    xlsx.write("A1", "Name");
    xlsx.write("B1", "Prize");
    for (int i = 0; i < row; i++) {
        QString nameRow = ui->tableWidget->item(i,1)->text();
        QString prizeRow = ui->tableWidget->item(i,2)->text();

        QString columnRow2 = QString("A%1").arg(i+2);
        QString columnRow3 = QString("B%1").arg(i+2);
        xlsx.write(columnRow2, nameRow);
        xlsx.write(columnRow3, prizeRow);
    }

    QString path = QFileDialog::getSaveFileName(0, tr("Save File"),".");
    xlsx.saveAs(path + ".xlsx");
}


void InputForm::on_tbOpen_clicked()
{
    QString path = QFileDialog::getOpenFileName(0, tr("Open File"),".");
    Document xlsxR(path);
    qDebug() << path;
    bool isXlsx = ((path.indexOf(".xlsx")) == -1) ? false : true;

    if (xlsxR.load()) // load excel file
    {
        ui->textEditName->clear();
        ui->textEditPrize->clear();
        // qDebug() << "Loaded";

        for (int col = 1; col <= 2; col++) {
            qDebug() << "Goes to loop";
            int row = 1;
            QStringList List;
            while (true) {
                Cell* cell = xlsxR.cellAt(row, col);
                if (cell == NULL) {
                    break;
                }
                QVariant var = cell->readValue();
                qDebug() << var;
                QString qs = var.toString();
                List += qs;
                row++;
            }
            if (col == 1) {
                ui->textEditName->setPlainText(List.join("\n"));
            } else if (col == 2) {
                ui->textEditPrize->setPlainText(List.join("\n"));
            }

        }

        ui->btnAddName->setEnabled(true);
        ui->btnAddPrize->setEnabled(true);
        ui->btnAddName->click();
        ui->btnAddPrize->click();
        ui->btnAddName->setEnabled(false);
        ui->btnAddPrize->setEnabled(false);

    } else {
        if (path == "") {
            QMessageBox::warning(this, "Victor Hunt", "<font color=\"White\">File not open!");
        } else if (!isXlsx) {
            QMessageBox::warning(this, "Victor Hunt", "<font color=\"White\">Invalid File! Please open .xlsx file only");
        }

    }
}

void InputForm::on_tbSave_clicked()
{
    QXlsx::Document xlsx;
    // Name Write
    int textEditNameLength = ui->textEditName->document()->blockCount();
    for (int i = 0; i < textEditNameLength; i++) {
        QTextDocument *doc = ui->textEditName->document();
        QTextBlock tb = doc->findBlockByLineNumber(i);
        QString s = tb.text();
        QString columnRow = QString("A%1").arg(i+1);

        xlsx.write(columnRow , s);
    }

    // PRIZE WRITE
    int textEditPrizeLength = ui->textEditPrize->document()->blockCount();
    for (int i = 0; i < textEditPrizeLength; i++) {
        QTextDocument *doc = ui->textEditPrize->document();
        QTextBlock tb = doc->findBlockByLineNumber(i);
        QString s = tb.text();
        QString columnRow = QString("B%1").arg(i+1);

        xlsx.write(columnRow , s);
    }

    QString path = QFileDialog::getSaveFileName(0, tr("Save File"),".");
    QFile file(path);

    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Victor Hunt", "<font color=\"White\">File not save!");
    } else {
        xlsx.saveAs(path + ".xlsx");
    }
}

// CLOSE OR X BUTTON
void InputForm::closeEvent(QCloseEvent *bar)
{
    bar->ignore();
    on_tbQuit_clicked();
}


