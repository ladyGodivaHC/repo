#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //------------------------------------------------------------------------------//
    //creating Guitar Table
    GuitarPianoTable = ui->tableWidget;

    GuitarPianoTable->setColumnCount(7);

    GuitarPianoTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Code"));
    GuitarPianoTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Model"));
    GuitarPianoTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Price"));
    GuitarPianoTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Strings"));
    GuitarPianoTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Frets"));
    GuitarPianoTable->setHorizontalHeaderItem(5, new QTableWidgetItem("Shape"));
    GuitarPianoTable->setHorizontalHeaderItem(6, new QTableWidgetItem("WoodType"));

    GuitarPianoTable->setRowCount(0);

    //disabling single cell selection
    //Makes modify easier
    //Selects only full line
    //Selecting a single cell would make modify a little more complex
    GuitarPianoTable->setSelectionMode(QAbstractItemView::SingleSelection);
    GuitarPianoTable->setEditTriggers( QAbstractItemView::NoEditTriggers );
    GuitarPianoTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(GuitarPianoTable->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(allowOperationsSlot()));

    //------------------------------------------------------------------------------//

    //------------------------------------------------------------------------------//
    //setting spinbox and doublespinbox properties

    guitarPriceEdit = ui->doubleSpinBox;
    guitarPriceEdit->setMinimum(100.0);
    guitarPriceEdit->setMaximum(10000.0);

    guitarStringsEdit = ui->spinBox;
    guitarStringsEdit->setMinimum(6);
    guitarStringsEdit->setMaximum(12);

    guitarFretsEdit = ui->spinBox_2;
    guitarFretsEdit->setMinimum(19);
    guitarFretsEdit->setMaximum(24);

    pianoPriceEdit = ui->doubleSpinBox_2;
    pianoPriceEdit->setMinimum(1500);
    pianoPriceEdit->setMaximum(1000000.0);

    pianoGuitarBox = ui->comboBox;
    attributeBox = ui->comboBox_2;

    //--------------------------------------------------//

    guitarModelEdit = ui->lineEdit_2;
    pianoModelEdit = ui->lineEdit_3;
    pianoTailEdit = ui->checkBox;
    pianoWoodEdit = ui->lineEdit_4;

    //------------------------------------------------------------------------------//

    //disabling buttons for first use
    modifyButton = ui->pushButton_3;
    modifyButton->setEnabled(false);

    confirmModify = ui->pushButton_6;
    confirmModify->setEnabled(false);

    searchButton = ui->pushButton_4;
    searchButton->setEnabled(true);

    exitSearch = ui->pushButton_7;
    exitSearch->setEnabled(false);

    removeButton = ui->pushButton_5;
    removeButton->setEnabled(false);

    //assigning the addGuitar and addPiano buttons

    addGuitar = ui->pushButton;
    addPiano = ui->pushButton_2;

    searchEdit = ui->lineEdit;

    connect(addGuitar, SIGNAL(clicked()), this, SLOT(addGuitarSlot()));
    connect(addPiano, SIGNAL(clicked()), this, SLOT(addPianoSlot()));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(searchSlot()));
    connect(exitSearch, SIGNAL(clicked()), this, SLOT(exitSearchSlot()));
    connect(modifyButton, SIGNAL(clicked()), this, SLOT(modifySlot()));
    connect(confirmModify, SIGNAL(clicked()), this, SLOT(confirmModSlot()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeSlot()));

    connect(pianoGuitarBox, SIGNAL(currentIndexChanged(int)), this, SLOT(pianoGuitarBoxChanged()));
    connect(attributeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(attributeBoxChanged()));

    //Creating Menu
    newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a Instrument Table"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

}

//------------------------------------------------------------------------------//
//PUBLIC METHODS IMPLEMENTATION

void MainWindow::resetGuitarFields(){
    ui->lineEdit_2->setText("");
    guitarPriceEdit->setValue(100);
    guitarStringsEdit->setValue(6);
    guitarFretsEdit->setValue(19);
}

void MainWindow::resetPianoFields(){
    ui->lineEdit_3->setText("");
    pianoPriceEdit->setValue(1500);
    ui->checkBox->setChecked(false);
    ui->lineEdit_4->setText("");
}

void MainWindow::disallowOperations(){
    searchButton->setEnabled(false);
    exitSearch->setEnabled(false);
    modifyButton->setEnabled(false);
    confirmModify->setEnabled(false);
    removeButton->setEnabled(false);
}

void MainWindow::newTable(){

    //empty the container
    GenericContainer<SmartInstrument>::ContainerIterator beginIT = qModel::Instance()->getContainer()->begin();
    GenericContainer<SmartInstrument>::ContainerIterator endIT = qModel::Instance()->getContainer()->end();
    for(beginIT; beginIT!=endIT; ++beginIT){
        qModel::Instance()->getContainer()->remove((*qModel::Instance()->getContainer())[beginIT]);
    }

    disallowOperations();
    resetGuitarFields();
    resetPianoFields();

    readContainer(qModel::Instance()->getContainer());

    searchEdit->setText("");

    pianoGuitarBox->setCurrentIndex(0);
    //automatic invocation to update attributeBox
}

//reflects the content of GenericContainer in the GUI. Used to keep Model and View separated. It's similar to MVC Design Pattern
void MainWindow::readContainer(GenericContainer<SmartInstrument> *cont){
    GenericContainer<SmartInstrument>::ContainerIterator beginIT = cont->begin();
    GenericContainer<SmartInstrument>::ContainerIterator endIT = cont->end();
    //keep track of how many rows
    int n_rows = 0;
    GuitarPianoTable->setRowCount(0);
    for(beginIT; beginIT != endIT; ++beginIT){

        GuitarPianoTable->insertRow(n_rows);
        GuitarPianoTable->setItem(n_rows, 0, new QTableWidgetItem(QString::fromStdString((*(*cont)[beginIT]).getCode())));
        GuitarPianoTable->setItem(n_rows, 1, new QTableWidgetItem(QString::fromStdString((*(*cont)[beginIT]).getModel())));
        GuitarPianoTable->setItem(n_rows, 2, new QTableWidgetItem(QString::number((*(*cont)[beginIT]).getPrice())));

        Guitar* guitar = dynamic_cast<Guitar*>(&(*(*cont)[beginIT]));
        if(guitar){
            GuitarPianoTable->setItem(n_rows, 3, new QTableWidgetItem(QString::number(guitar->getStrings())));
            GuitarPianoTable->setItem(n_rows, 4, new QTableWidgetItem(QString::number(guitar->getFrets())));
        }
        else{
            Piano* piano = dynamic_cast<Piano*>(&(*(*cont)[beginIT]));
            if(piano->isTail())
                GuitarPianoTable->setItem(n_rows, 5, new QTableWidgetItem("Grand"));
            else
                GuitarPianoTable->setItem(n_rows, 5, new QTableWidgetItem("Upright"));
            GuitarPianoTable->setItem(n_rows, 6, new QTableWidgetItem(QString::fromStdString(piano->getWood())));
        }
    }
    //if after removing an element my table is empty i must disallow buttons
    int rows = GuitarPianoTable->rowCount();
    if(rows==0)
        disallowOperations();
}

void MainWindow::allowOperations(){
    searchButton->setEnabled(true);
    modifyButton->setEnabled(true);
    removeButton->setEnabled(true);
}

//------------------------------------------------------------------------------//

void MainWindow::closeEvent(QCloseEvent *event){
    QMessageBox msgBox;
    msgBox.setText("You are about to exit the application.");
    msgBox.setInformativeText("Are you sure you want to exit?");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

//------------------------------------------------------------------------------//
//SLOTS IMPLEMENTATION

//new file

void MainWindow::newFile(){
    QMessageBox msgBox;
    msgBox.setText("All data will be lost.");
    msgBox.setInformativeText("Do you want to create a new Table?");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Yes)
        newTable();
}

void MainWindow::addGuitarSlot(){

    if(ui->lineEdit_2->text().isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Fields cannot be blank.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else{
        std::string model = ui->lineEdit_2->text().toStdString();
        double price = ui->doubleSpinBox->value();
        int strings = ui->spinBox->value();
        int frets = ui->spinBox_2->value();

        Guitar* newGuitar = new Guitar(price, model, strings, frets);
        SmartInstrument* newGSInstr = new SmartInstrument(newGuitar);
        qModel::Instance()->getContainer()->add(*newGSInstr);

        resetGuitarFields();

        readContainer(qModel::Instance()->getContainer());

    }
}

void MainWindow::addPianoSlot(){

    if(ui->lineEdit_3->text().isEmpty() || ui->lineEdit_4->text().isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Fields cannot be blank.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else{
        std::string model = ui->lineEdit_3->text().toStdString();
        double price = ui->doubleSpinBox_2->value();
        bool tail = ui->checkBox->isChecked();
        std::string wood = ui->lineEdit_4->text().toStdString();

        Piano* newPiano = new Piano(price, model, tail, wood);
        SmartInstrument* newPSInstr = new SmartInstrument(newPiano);
        qModel::Instance()->getContainer()->add(*newPSInstr);

        resetPianoFields();

        readContainer(qModel::Instance()->getContainer());

    }
}

//PRE: i must have at least one line in my table
void MainWindow::modifySlot(){

    //keep track of the row i want to modify
    int selectedRow = GuitarPianoTable->currentRow();
    //getting the code field to identify the row i'm modifying
    QTableWidgetItem* codeItem = GuitarPianoTable->item(selectedRow, 0);
    std::string code = codeItem->text().toStdString();
    //initializing iterator
    GenericContainer<SmartInstrument>::ContainerIterator beginIT = qModel::Instance()->getContainer()->begin();
    GenericContainer<SmartInstrument>::ContainerIterator endIT = qModel::Instance()->getContainer()->end();

    bool found = false;

    for(beginIT; beginIT!=endIT && !found; ++beginIT){
        if(((*(*qModel::Instance()->getContainer())[beginIT]).getCode()) == code){
            //to understand if i am modifying a Guitar object or a Piano one
            Guitar* g = dynamic_cast<Guitar*>(&(*(*qModel::Instance()->getContainer())[beginIT]));
            if (g){
                pianoModelEdit->setEnabled(false);
                guitarModelEdit->setText(g->getModel().c_str());
                guitarPriceEdit->setValue(g->getPrice());
                guitarStringsEdit->setValue(g->getStrings());
                guitarFretsEdit->setValue(g->getFrets());
            }
            else{
                Piano* p = dynamic_cast<Piano*>(&(*(*qModel::Instance()->getContainer())[beginIT]));
                guitarModelEdit->setEnabled(false);
                pianoModelEdit->setText(p->getModel().c_str());
                pianoPriceEdit->setValue(p->getPrice());
                bool grand = p->isTail();
                if(grand)
                    pianoTailEdit->setChecked(true);
                else
                    pianoTailEdit->setChecked(false);
                pianoWoodEdit->setText(p->getWood().c_str());
            }

            //i'm modifying so i disable non related buttons
            addGuitar->setEnabled(false);
            addPiano->setEnabled(false);
            removeButton->setEnabled(false);
            searchButton->setEnabled(false);
            modifyButton->setEnabled(false);

            //enable button to confirm changes
            confirmModify->setEnabled(true);
        }
    }

}

//PRE: my table is not empty -> i have at least one row
void MainWindow::confirmModSlot(){

    SmartInstrument* si;
    //get which object i was modifying
    if(!(guitarModelEdit->text().isEmpty())){
        //if here i was mod a guitar
        std::string model = guitarModelEdit->text().toStdString();
        double price = guitarPriceEdit->value();
        int strings = guitarStringsEdit->value();
        int frets = guitarFretsEdit->value();

        Guitar* guitar = new Guitar(price, model, strings, frets);
        int selectedRow = GuitarPianoTable->currentRow();
        QTableWidgetItem* codeItem = GuitarPianoTable->item(selectedRow, 0);
        std::string code = codeItem->text().toStdString();
        guitar->setCode(code);

        si = new SmartInstrument(guitar);
    }
    else{
        //Piano
        std::string model = pianoModelEdit->text().toStdString();
        double price = pianoPriceEdit->value();
        bool shape = pianoTailEdit->isChecked();
        std::string wood = pianoWoodEdit->text().toStdString();

        Piano* piano = new Piano(price, model, shape, wood);
        int selectedRow = GuitarPianoTable->currentRow();
        QTableWidgetItem* codeItem = GuitarPianoTable->item(selectedRow, 0);
        std::string code = codeItem->text().toStdString();
        piano->setCode(code);

        si = new SmartInstrument(piano);
    }

    //invoking GenericContainer::modify, which will call overloaded modifyFunctor operator()

    qModel::Instance()->getContainer()->modify(*(qModel::Instance()->getContainer()), *si);

    //read the updated container
    readContainer(qModel::Instance()->getContainer());

    //cleaning forms and resetting buttons
    resetGuitarFields();
    resetPianoFields();

    guitarModelEdit->setEnabled(true);
    pianoModelEdit->setEnabled(true);

    addGuitar->setEnabled(true);
    addPiano->setEnabled(true);
    searchButton->setEnabled(true);
    removeButton->setEnabled(true);

    confirmModify->setEnabled(false);

}

//PRE: at least on row in the table
void MainWindow::removeSlot(){
    //get current row
    //this way i can reference the code for each object with item(selectedRow, 0)
    int selectedRow = GuitarPianoTable->currentRow();
    QTableWidgetItem* codeItem = GuitarPianoTable->item(selectedRow, 0);
    std::string code = codeItem->text().toStdString();
    GenericContainer<SmartInstrument>::ContainerIterator beginIT = qModel::Instance()->getContainer()->begin();
    GenericContainer<SmartInstrument>::ContainerIterator endIT = qModel::Instance()->getContainer()->end();

    //bool var to allow unuseful controls since the code is unique
    bool removed = false;
    for(beginIT; beginIT!=endIT && !removed; ++beginIT){
        if(((*(*qModel::Instance()->getContainer())[beginIT]).getCode()) == code){
            qModel::Instance()->getContainer()->remove((*qModel::Instance()->getContainer())[beginIT]);
            removed = true;
        }
    }

    readContainer(qModel::Instance()->getContainer());
}

//PRE: at least one row
void MainWindow::searchSlot(){

    if(searchEdit->text().isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Insert a value to search.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }

    else{

        std::string instr = "";
        std::string attr = "";
        std::string val = "";

        if(pianoGuitarBox->currentIndex()==0){
            instr = "Guitar";
            if(attributeBox->currentIndex()==3)
                attr = "Strings";
            if(attributeBox->currentIndex()==4)
                attr = "Frets";
        }
        else{
            instr = "Piano";
            if(attributeBox->currentIndex()==3)
                attr = "Shape";
            if(attributeBox->currentIndex()==4)
                attr = "Wood";
        }

        if(attributeBox->currentIndex()==0)
            attr = "Code";
        if(attributeBox->currentIndex()==1)
            attr = "Model";
        if(attributeBox->currentIndex()==2)
            attr = "Price";

        //to be shure that val has an appropriate value
        val = searchEdit->text().toStdString();

        GenericContainer<SmartInstrument>* searchContainer = new GenericContainer<SmartInstrument>();
        SearchFunctor* sf = new SearchFunctor(instr, attr, val);

        qModel::Instance()->getContainer()->search(*(qModel::Instance()->getContainer()), *searchContainer, *sf);

        readContainer(searchContainer);

        exitSearch->setEnabled(true);
        searchButton->setEnabled(false);
        removeButton->setEnabled(false);
        modifyButton->setEnabled(false);
        addGuitar->setEnabled(false);
        addPiano->setEnabled(false);
    }
}

//PRE: at least one row in the table
void MainWindow::exitSearchSlot(){
    //reset search form fields
    pianoGuitarBox->setCurrentIndex(0);
    attributeBox->setCurrentIndex(0);
    searchEdit->setText("");

    readContainer(qModel::Instance()->getContainer());

    exitSearch->setEnabled(false);
    searchButton->setEnabled(true);
    if(GuitarPianoTable->rowCount()!=0){
        modifyButton->setEnabled(true);
        removeButton->setEnabled(true);
    }
    addPiano->setEnabled(true);
    addGuitar->setEnabled(true);
}

void MainWindow::allowOperationsSlot(){
    searchButton->setEnabled(true);
    exitSearch->setEnabled(false);
    modifyButton->setEnabled(true);
    confirmModify->setEnabled(false);
    removeButton->setEnabled(true);
}

void MainWindow::pianoGuitarBoxChanged(){
    if(pianoGuitarBox->currentIndex()==0){
        attributeBox->removeItem(4);
        attributeBox->removeItem(3);
        attributeBox->addItem("Strings");
        attributeBox->addItem("Frets");
    }
    else{
        attributeBox->removeItem(4);
        attributeBox->removeItem(3);
        attributeBox->addItem("Shape");
        attributeBox->addItem("Wood");
    }
}

void MainWindow::attributeBoxChanged(){
    //Code and Model are strings and allow every char
    if(attributeBox->currentIndex()==0)
        searchEdit->setValidator(0);
    if(attributeBox->currentIndex()==1)
        searchEdit->setValidator(0);
    if(attributeBox->currentIndex()==2){
        //price selected
        //my compiler gives me a warning for some reason but can be ignored, works correctly
        QRegExp rx("^[1-9][0-9]+$\d+");
        searchEdit->setToolTip("Only numbers are allowed");
        searchEdit->setValidator(new QRegExpValidator (rx, this));
    }
    if(pianoGuitarBox->currentIndex()==0){
        //guitar selected
        if(attributeBox->currentIndex()==3){
            //Strings selected
            QRegExp rx("^[6-9]\d");
            searchEdit->setToolTip("Only numbers ranging for 6 to 9");
            searchEdit->setValidator(new QRegExpValidator(rx, this));
        }
        if(attributeBox->currentIndex()==4){
            //Frets selected
            QRegExp rx("^[1-2][0-5]\d");
            searchEdit->setToolTip("Only numbers from 19 to 25");
            searchEdit->setValidator(new QRegExpValidator(rx, this));
        }
    }
    else{
        //Index==1 -> Piano
        if(attributeBox->currentIndex()==3){
            //Shape
            QRegExp rx("(\W|^)(grand|upright)(\W|$)");
            searchEdit->setToolTip("Choose between grand or upright");
            searchEdit->setValidator(new QRegExpValidator(rx, this));
        }
        //Wood can have any value or char set
        if(attributeBox->currentIndex()==4)
            searchEdit->setValidator(0);
    }
}

//------------------------------------------------------------------------------//


MainWindow::~MainWindow()
{
    delete ui;
}
