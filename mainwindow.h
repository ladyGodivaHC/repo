#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QString>
#include <QMenu>
#include <QCloseEvent>

#include "qmodel.h"
#include "smartinstrument.h"
#include "guitar.h"
#include "piano.h"
#include "genericcontainer.h"
#include "searchfunctor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void resetGuitarFields();
    void resetPianoFields();

    void newTable();

    //slot needed to disallow operations.
    //When table is empty i cannot perform modify, remove or search operations.
    void disallowOperations();

    void allowOperations();

    //read the searchContainer to display search Results
    void readContainer(GenericContainer<SmartInstrument>*);

protected:
    void closeEvent(QCloseEvent*);


public slots:
    void addGuitarSlot();
    void addPianoSlot();
    void modifySlot();
    void confirmModSlot();
    void removeSlot();
    void searchSlot();
    void exitSearchSlot();
    void newFile();
    //bool saveSlot();
    //bool openSlot();

    //slot needed to allow operations.
    //There must at be 1 item in the table
    void allowOperationsSlot();

    //slots for qcombobox
    void pianoGuitarBoxChanged();
    void attributeBoxChanged();

private:
    Ui::MainWindow *ui;

    QTableWidget* GuitarPianoTable;

    QPushButton* addGuitar;
    QPushButton* addPiano;
    QPushButton* searchButton;
    QPushButton* exitSearch;
    QPushButton* modifyButton;
    QPushButton* confirmModify;
    QPushButton* removeButton;

    QMenu* fileMenu;
    QAction* newAction;
    QAction* exitAction;

    QLabel* tableTitle;

    //---------------------------------//
    //add guitar
    QLabel* guitarModelLabel;
    QLabel* guitarPriceLabel;
    QLabel* guitarStringsLabel;
    QLabel* guitarFretsLabel;

    QLineEdit* guitarModelEdit;
    QDoubleSpinBox* guitarPriceEdit;
    QSpinBox* guitarStringsEdit;
    QSpinBox* guitarFretsEdit;
    //---------------------------------//

    //---------------------------------//
    //add piano
    QLabel* pianoModelLabel;
    QLabel* pianoPriceLabel;
    QLabel* pianoTailLabel;
    QLabel* pianoWoodLabel;

    QLineEdit* pianoModelEdit;
    QDoubleSpinBox* pianoPriceEdit;
    QCheckBox* pianoTailEdit;
    QLineEdit* pianoWoodEdit;
    //---------------------------------//

    //---------------------------------//
    //search bar
    QComboBox* pianoGuitarBox;
    QComboBox* attributeBox;
    QLabel* textLabel;
    QLineEdit* searchEdit;

    //---------------------------------//

};

#endif // MAINWINDOW_H
