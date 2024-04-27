#include "GUI.h"
#include "Parser.h"
#include "Settings.h"
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
	srand(time(NULL));

	clock_t sumTimeMain = 0;
	// for (int i = 0; i < 100; i++) {
	FileHandling file;
	Parser *newParser = new Parser(file.LoadFile(settings::inFileName.toLocal8Bit().constData()));
	ui.textBrowser->clear();

	if (file.IsOpen() == false)
	{
		ui.textBrowser->append("File was empty or not loaded!");
		return;
	}

	if (settings::inFileName == "notSelected" || settings::outFileName == "notSelected")
	{
		ui.textBrowser->append("Error! Wrong path selected!");
		return;
	}

	//ui.b_openFile->setEnabled(false);
	clock_t time;
	clock_t sumtime = 0;
	if (ui.cb_deleteComments->isChecked())
	{
		time = clock();
		newParser->DeleteComments();
		time = clock() - time;
		ui.textBrowser->append("Deleted comments - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
		sumtime += time;
	}

	if (settings::countOfSettings > 0)
	{

		time = clock();
		newParser->SpaceOperators();
		time = clock() - time;
		ui.textBrowser->append("Parsered text - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
		sumtime += time;
	}

	if (ui.cb_changeLoops->isChecked())
	{
		time = clock();
		newParser->ChangeLoops();
		time = clock() - time;
		ui.textBrowser->append("Changed loops - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
		sumtime += time;
	}

	if (ui.cb_AddJunk->isChecked())
	{
		if (settings::junkerOptions.empty() == false)
		{
			time = clock();
			newParser->FindVariables();
			newParser->AddJunks(ui.sp_AmountVariables->value(), ui.sp_AmountCodes->value());
			time = clock() - time;
			ui.textBrowser->append("Added code - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
			sumtime += time;
		}
		else
			ui.textBrowser->append("Adding additional code failed because no options were selected!");
	}

	if (ui.cb_ChangeVariables->isChecked())
	{
		time = clock();
		newParser->FindVariables();
		newParser->ChangeVariables();
		newParser->SpaceOperatorsFix();
		time = clock() - time;
		ui.textBrowser->append("Renamed variables - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
		sumtime += time;
	}

	if (ui.cb_Encryption->isChecked())
	{
		time = clock();
		newParser->AddEncryption(ui.cb_EncToFile->isChecked(), ui.cb_EncOnlyFor->isChecked());
		time = clock() - time;
		ui.textBrowser->append("Encryption of variables - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
		sumtime += time;
	}

	if (ui.cb_DeleteEnters->isChecked())
	{
		time = clock();
		newParser->DeleteEnters();
		time = clock() - time;
		ui.textBrowser->append("Deleted transition to the new line - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
		sumtime += time;
	}

	if (ui.cb_DeleteSpace->isChecked())
	{
		time = clock();
		newParser->DeleteUnnecessarySpaces();
		time = clock() - time;
		ui.textBrowser->append("Deleted spaces - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
		sumtime += time;
	}

	ui.textBrowser->append("Summary: " + QString::number((double)sumtime / CLOCKS_PER_SEC, 'f', 4) + "s.");
	//	sumTimeMain += sumtime;
	file.SaveFile(settings::outFileName.toLocal8Bit().constData());
	// sumTimeMain += sumtime;
	delete newParser;
	//}

	ui.b_openFile->setEnabled(true);
	// ui.textBrowser->append("Total time: " + QString::number((double)sumTimeMain / CLOCKS_PER_SEC, 'f', 4) + "s.");
	// ui.textBrowser->append("Mean: " + QString::number((double)sumTimeMain / CLOCKS_PER_SEC / 100, 'f', 4) + "s.");
}

void GUI::on_encBox_changed()
{
	if (ui.cb_Encryption->isChecked())
	{
		ui.cb_EncOnlyFor->setEnabled(true);
		ui.cb_EncToFile->setEnabled(true);
		settings::countOfSettings++;
	}
	else
	{
		ui.cb_EncOnlyFor->setEnabled(false);
		ui.cb_EncToFile->setEnabled(false);
		settings::countOfSettings--;
	}
}

void GUI::on_delBox_changed()
{
	if (ui.cb_deleteComments->isChecked())
	{
		ui.cb_DeleteEnters->setEnabled(true);
	}
	else
	{
		ui.cb_DeleteEnters->setEnabled(false);
		ui.cb_DeleteEnters->setChecked(false);
	}
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
	}
}

void GUI::on_chgLoopBox_changed()
{
	if (ui.cb_changeLoops->isChecked())
	{
		settings::countOfSettings++;
	}
	else
	{
		settings::countOfSettings--;
	}
}

void GUI::on_chgVarBox_changed()
{
	if (ui.cb_ChangeVariables->isChecked())
	{
		settings::countOfSettings++;
	}
	else
	{
		settings::countOfSettings--;
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