#include "worksheet.h"
#include "ui_worksheet.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTabWidget>
#include <iostream>
#include <QFile>
#include "testtextinput.h"
#include "base/expression_parser/mathengine.h"

#include "base/expression_parser/lexer/lexer.h"
#include "base/expression_parser/parser/parser.h"
#include "base/expression_parser/interpreter/interpreter.h"

Worksheet::Worksheet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Worksheet)
{
    ui->setupUi(this);

    WorksheetLine* newLine = createLine(0);
    newLine->focus();

    Lexer lexer("2+2*3^24");
    std::vector<Token *> tokens = lexer.tokenize();
    for (size_t i = 0; i < tokens.size(); i++)
    {
        std::cout << tokens[i]->toString() << " ";
    }
    std::cout << std::endl;
    Parser parser = Parser(tokens);
    Expression* expr = parser.parse();
    if (expr->expressionType == ExprType::Literal)
        LiteralExpr p = expr->getLiteral();
    std::cout << std::endl;
    Interpreter::interpret(expr);
}

Worksheet::~Worksheet()
{
    delete ui;
}

WorksheetLine* Worksheet::createLine(int index, LineType type)
{
    std::cout << type << std::endl;

    WorksheetLine *line = new TestTextInput(this);

    QVBoxLayout* parent = (QVBoxLayout*)ui->scrollAreaWidgetContents->layout();

    parent->insertWidget(index,line);
    return line;
}

void Worksheet::evaluateLine(MathLine* line)
{
    MathEngine::AutoParse(line->getText(), &symbolTable, std::bind(&MathLine::onEvaluated,line,std::placeholders::_1));
}

void Worksheet::focusFirst() {}

void Worksheet::focusLast() {}

bool Worksheet::save()
{
    //QString path = QFileDialog::getExistingDirectory (this, tr("Directory"), "");
    QFileDialog::Options options;
    options.setFlag(QFileDialog::Option::DontUseNativeDialog,false);
    QString file = QFileDialog::getSaveFileName(nullptr,tr("Save file"),"",tr("OpenBirch Worksheet File (*.obws);;All Files (*.*)"),nullptr,options);

    if (file.isEmpty())
        return false;

    if (!file.endsWith(".obws"))

    std::cout << file.toStdString() << std::endl;

    QStringList parts = file.split("/");
    QString name = parts.last().split(".").first();

    this->name = name;

    QTabWidget* parent = ((QTabWidget*)this->parentWidget()->parentWidget());
    parent->setTabText(parent->indexOf(this),name);

    // Convert lines array into json data, then save
    QStringList test = {"2x+4=4","Math","x=2","Output","3","Text","4","Text"};

    QFile fileHandle(file);
    fileHandle.open(QFile::WriteOnly);

    fileHandle.write(test.join("\n").toStdString().c_str());

    unsavedChanges = false;
    return true;
}

int Worksheet::close()
{
    if (!this->unsavedChanges) // if we dont have any unsaved changes just close
    {
        this->~Worksheet();
        return 0;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Unsaved Changes");
    msgBox.setText("Are you sure you want to close this?");
    msgBox.setStandardButtons(QMessageBox::Discard);
    msgBox.addButton(QMessageBox::Save);
    msgBox.addButton(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    int reply = msgBox.exec();

    if (reply == QMessageBox::Discard)
        this->~Worksheet();
    else if (reply == QMessageBox::Save)
        this->save();

    return reply;
}
