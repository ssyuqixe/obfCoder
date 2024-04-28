#include "GUI.h"
#include "Parser.h"
#include "Settings.h"
#include "Manager.h"
// replace it later by manager
#include "Comments.h"
#include "Renamer.h"
#include "Looper.h"
#include "Enters.h"
#include "Spaces.h"
#include "FileHandling.h"
#include <QFileDialog>
#include <QProcess>

GUI::GUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.b_LoadFile, SIGNAL(clicked()), this, SLOT(on_loadButton_clicked()));
	connect(ui.b_SaveFile, SIGNAL(clicked()), this, SLOT(on_saveButton_clicked()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_addButton_clicked()));
	connect(ui.cb_Encryption, SIGNAL(clicked(bool)), this, SLOT(on_encBox_changed()));
	connect(ui.cb_deleteComments, SIGNAL(clicked(bool)), this, SLOT(on_delBox_changed()));
	connect(ui.cb_DeleteEnters, SIGNAL(clicked(bool)), this, SLOT(on_delEnters_changed()));
	connect(ui.cb_DeleteSpaces, SIGNAL(clicked(bool)), this, SLOT(on_delSpaces_changed()));
	connect(ui.cb_AddJunk, SIGNAL(clicked(bool)), this, SLOT(on_addJunk_changed()));
	connect(ui.cb_changeLoops, SIGNAL(clicked(bool)), this, SLOT(on_chgLoopBox_changed()));
	connect(ui.cb_ChangeVariables, SIGNAL(clicked(bool)), this, SLOT(on_chgVarBox_changed()));
	connect(ui.b_openFile, SIGNAL(clicked(bool)), this, SLOT(on_openButton_clicked()));
	connect(ui.cb_JunkerSum, SIGNAL(clicked(bool)), this, SLOT(on_JunkerSumBox_changed()));
	connect(ui.cb_JunkerSub, SIGNAL(clicked(bool)), this, SLOT(on_JunkerSubBox_changed()));
	connect(ui.cb_JunkerMul, SIGNAL(clicked(bool)), this, SLOT(on_JunkerMulBox_changed()));
	connect(ui.cb_JunkerConnected, SIGNAL(clicked(bool)), this, SLOT(on_JunkerConnectedBox_changed()));
	connect(ui.cb_JunkerSemiConnected, SIGNAL(clicked(bool)), this, SLOT(on_JunkerSemiConnectedBox_changed()));
	connect(ui.cb_JunkerNonConnected, SIGNAL(clicked(bool)), this, SLOT(on_JunkerNonConnected_changed()));
	connect(ui.cb_JunkerInc, SIGNAL(clicked(bool)), this, SLOT(on_JunkerIncBox_changed()));
}

void GUI::on_loadButton_clicked()
{
	settings::inFileName = QFileDialog::getOpenFileName(this, "Open File", ".//");

	ui.lineEdit->setText(settings::inFileName);
	ui.fileNameLabelIn->setText("Input File Name: " + settings::inFileName.split('/').last());

	file.LoadFile(settings::inFileName.toLocal8Bit().constData());
	ui.textBrowser->clear();

	if (file.IsOpen() == false)
	{
		ui.textBrowser->append("File was empty or not loaded!");
		return;
	}

	// set default settings for the method
	// temporary solution
	manager.DefaultSetup(file.GetContent());
}

void GUI::on_saveButton_clicked()
{
	settings::outFileName = QFileDialog::getExistingDirectory(0, "Select folder to save file", ".//");
	settings::outPath = settings::outFileName.toUtf8();
	if (ui.lineEdit_2->text().isEmpty() == true)
	{
		ui.lineEdit_2->setText("default.cpp");
		settings::outFileName += "/default.cpp";
	}
	else
		settings::outFileName += "/" + ui.lineEdit_2->text();

	ui.fileNameLabelOut->setText("Output File Name: " + settings::outFileName.split('/').last());
}

void GUI::on_addButton_clicked()
{

	if (settings::inFileName == "notSelected" || settings::outFileName == "notSelected")
	{
		ui.textBrowser->append("Error! Wrong path selected!");
		return;
	}

	file.ReloadFile();
	if (file.IsOpen() == false)
	{
		ui.textBrowser->append("File is not loaded!");
		return;
	}
	clock_t sumTimeMain = 0;

	manager.StateComponent("Parser", bool(settings::countOfSettings > 0));
	auto junker = manager.GetComponent("Junker");
	if (junker)
		junker->Update(std::vector<int>({1}));

	clock_t time;
	clock_t sumTime = 0;
	auto components = manager.GetComponents();
	auto status = manager.GetComponentsStatus();
	for (size_t iComponent = 0; iComponent < components->size(); iComponent++)
	{
		std::cout << components->at(iComponent)->GetTag() << " " << status->at(iComponent) << "\n";
		if (status->at(iComponent) == false)
			continue;

		time = clock();
		components->at(iComponent)->DoTechnique();
		time = clock() - time;
		ui.textBrowser->append(QString::fromStdString(components->at(iComponent)->GetTag()) + " - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
		sumTime += time;
	}

	ui.textBrowser->append("Summary: " + QString::number((double)sumTime / CLOCKS_PER_SEC, 'f', 4) + "s.");

	file.SaveFile(settings::outFileName.toLocal8Bit().constData());

	ui.b_openFile->setEnabled(true);
}

void GUI::on_encBox_changed()
{
	if (ui.cb_Encryption->isChecked())
	{
		ui.cb_EncOnlyFor->setEnabled(true);
		ui.cb_EncToFile->setEnabled(true);
		settings::countOfSettings++;
		auto encryption = manager.GetComponent("Encryption");
		if (encryption)
			encryption->Update(std::vector<int>({ui.cb_EncToFile->isChecked(), ui.cb_EncOnlyFor->isChecked()}));
		manager.StateComponent("Encryption", true);
	}
	else
	{
		ui.cb_EncOnlyFor->setEnabled(false);
		ui.cb_EncToFile->setEnabled(false);
		settings::countOfSettings--;
		manager.StateComponent("Encryption", false);
	}
}

void GUI::on_delBox_changed()
{
	if (ui.cb_deleteComments->isChecked())
	{
		ui.cb_DeleteEnters->setEnabled(true);
		manager.StateComponent("Comments", true);
	}
	else
	{
		ui.cb_DeleteEnters->setEnabled(false);
		ui.cb_DeleteEnters->setChecked(false);
		// todo: check if enters is active
		manager.StateComponent("Comments", false);
	}
}

void GUI::on_delEnters_changed()
{
	manager.StateComponent("Enters", ui.cb_DeleteEnters->isChecked());
}

void GUI::on_delSpaces_changed()
{
	manager.StateComponent("Spaces", ui.cb_DeleteSpaces->isChecked());
}
void GUI::on_addJunk_changed()
{
	if (ui.cb_AddJunk->isChecked())
	{
		ui.sp_AmountCodes->setEnabled(true);
		ui.sp_AmountVariables->setEnabled(true);
		settings::countOfSettings++;

		// buttons
		ui.cb_JunkerSum->setEnabled(true);
		ui.cb_JunkerSub->setEnabled(true);
		ui.cb_JunkerMul->setEnabled(true);
		ui.cb_JunkerConnected->setEnabled(true);
		ui.cb_JunkerSemiConnected->setEnabled(true);
		ui.cb_JunkerNonConnected->setEnabled(true);
		ui.cb_JunkerInc->setEnabled(true);
		auto junker = manager.GetComponent("Junker");
		if (junker)
			junker->Update(std::vector<int>({ui.sp_AmountVariables->value(), ui.sp_AmountCodes->value()}));
		manager.StateComponent("Junker", true);
	}
	else
	{
		ui.sp_AmountCodes->setEnabled(false);
		ui.sp_AmountVariables->setEnabled(false);
		settings::countOfSettings--;

		// buttons
		ui.cb_JunkerSum->setEnabled(false);
		ui.cb_JunkerSub->setEnabled(false);
		ui.cb_JunkerMul->setEnabled(false);
		ui.cb_JunkerConnected->setEnabled(false);
		ui.cb_JunkerSemiConnected->setEnabled(false);
		ui.cb_JunkerNonConnected->setEnabled(false);
		ui.cb_JunkerInc->setEnabled(false);
		manager.StateComponent("Junker", false);
	}
}

void GUI::on_chgLoopBox_changed()
{
	if (ui.cb_changeLoops->isChecked())
	{
		settings::countOfSettings++;
		manager.StateComponent("Looper", true);
	}
	else
	{
		settings::countOfSettings--;
		manager.StateComponent("Looper", false);
	}
}

void GUI::on_chgVarBox_changed()
{
	if (ui.cb_ChangeVariables->isChecked())
	{
		settings::countOfSettings++;
		auto renamer = manager.GetComponent("Renamer");
		if (renamer)
		{
			if (renamer->Update(std::vector<int>()))
				manager.StateComponent("Renamer", true);
		}
	}
	else
	{
		settings::countOfSettings--;
		manager.StateComponent("Renamer", false);
	}
}

void GUI::on_openButton_clicked()
{
	ui.textBrowser->append("Debug: setted");
}

void JunkerOption(bool isChecked, int value)
{
	settings::junkerOptions[value] = (isChecked) ? true : false;
}

void GUI::on_JunkerSumBox_changed()
{
	JunkerOption(ui.cb_JunkerSum->isChecked(), 0);
}

void GUI::on_JunkerSubBox_changed()
{
	JunkerOption(ui.cb_JunkerSub->isChecked(), 1);
}

void GUI::on_JunkerMulBox_changed()
{
	JunkerOption(ui.cb_JunkerMul->isChecked(), 2);
}

void GUI::on_JunkerConnectedBox_changed()
{
	JunkerOption(ui.cb_JunkerConnected->isChecked(), 3);
}

void GUI::on_JunkerSemiConnectedBox_changed()
{
	JunkerOption(ui.cb_JunkerSemiConnected->isChecked(), 4);
}

void GUI::on_JunkerNonConnected_changed()
{
	JunkerOption(ui.cb_JunkerNonConnected->isChecked(), 5);
}

void GUI::on_JunkerIncBox_changed()
{
	JunkerOption(ui.cb_JunkerInc->isChecked(), 6);
}