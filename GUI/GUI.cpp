#include "GUI.h"
#include "Parser.h"
#include "Settings.h"
#include "TPM.h"


#include <codecvt>


GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(ui.b_LoadFile, SIGNAL(clicked()), this, SLOT(on_loadButton_clicked()));
	connect(ui.b_LoadFile_2, SIGNAL(clicked()), this, SLOT(on_loadButtonTPM_clicked()));
	connect(ui.b_SaveFile, SIGNAL(clicked()), this, SLOT(on_saveButton_clicked()));
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_addButton_clicked()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(on_addButtonTPM_clicked()));
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
	connect(ui.cb_TPM, SIGNAL(clicked(bool)), this, SLOT(on_TPMBox_changed()));
}

void GUI::on_loadButton_clicked() {
	settings::inFileName = QFileDialog::getOpenFileName(this, "Open File", ".//");


	ui.lineEdit->setText(settings::inFileName);
	ui.fileNameLabelIn->setText("Input File Name: " + settings::inFileName.split('/').last());
}

void GUI::on_loadButtonTPM_clicked() {
	settings::inTPMFile = QFileDialog::getOpenFileName(this, "Open File", ".//");


	ui.lineEdit_3->setText(settings::inTPMFile);
}

void GUI::on_addButtonTPM_clicked() {
	if (settings::inTPMFile == "notSelected" || settings::outFileName == "notSelected") {
		ui.textBrowser->append("Error! Wrong path selected!");
		return;
	}
	ui.textBrowser->clear();
	std::string key_contents;
	std::ifstream file(settings::inTPMFile.toLocal8Bit().constData());
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			key_contents += line;
		}
		file.close();
	}
	else {
		ui.textBrowser->append("Error opening TPM key file!");
	}

	std::wstring file_contents;
	std::wifstream file2(settings::inFileName.toLocal8Bit().constData());
	if (file2.is_open()) {
		std::wstring line;
		while (std::getline(file2, line)) {
			file_contents += line;
		}
		file2.close();
	}
	else {
		ui.textBrowser->append("Error load encrypted file!");
	}

	clock_t time = clock();
	TPM* tpm = new TPM();
	std::wstring end;
	end = tpm->DecryptWholeFile(file_contents, key_contents, settings::outFileName.toLocal8Bit().constData());
	time = clock() - time;
	ui.textBrowser->append("Decrypted by TPM - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
	ui.textBrowser->append(QString::fromStdWString(end));
	//ui.textBrowser->append(QString::fromStdString(tpm->getOutputString()));

	delete tpm;

}

void GUI::on_saveButton_clicked() {
	settings::outFileName = QFileDialog::getExistingDirectory(0, "Select folder to save file", ".//");
	settings::outPath = settings::outFileName.toUtf8();
	if (ui.lineEdit_2->text().isEmpty() == true) {
		ui.lineEdit_2->setText("default.cpp");
		settings::outFileName += "/default.cpp";
	}
	else
		settings::outFileName += "/" + ui.lineEdit_2->text();

	ui.fileNameLabelOut->setText("Output File Name: " + settings::outFileName.split('/').last());
}

void GUI::on_addButton_clicked() {
	srand(time(NULL));

	clock_t sumTimeMain = 0;
	//for (int i = 0; i < 100; i++) {
		Parser* newParser = new Parser(settings::inFileName.toLocal8Bit().constData());
		ui.textBrowser->clear();

		if (newParser->Error() == true) {
			ui.textBrowser->append("Cannot open the file!");
			return;
		}

		if (settings::inFileName == "notSelected" || settings::outFileName == "notSelected") {
			ui.textBrowser->append("Error! Wrong path selected!");
			return;
		}

		ui.b_openFile->setEnabled(false);
		clock_t time;
		clock_t sumtime = 0;
		if (ui.cb_deleteComments->isChecked()) {
			time = clock();
			newParser->DeleteComments();
			time = clock() - time;
			ui.textBrowser->append("Deleted comments - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
			sumtime += time;
		}

		if (settings::countOfSettings > 0) {

			time = clock();
			newParser->SpaceOperators();
			time = clock() - time;
			ui.textBrowser->append("Parsered text - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
			sumtime += time;
		}

		if (ui.cb_changeLoops->isChecked()) {
			time = clock();
			newParser->ChangeLoops();
			time = clock() - time;
			ui.textBrowser->append("Changed loops - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
			sumtime += time;
		}

		if (ui.cb_AddJunk->isChecked()) {
			if (settings::junkerOptions.empty() == false) {
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

		if (ui.cb_ChangeVariables->isChecked()) {
			time = clock();
			newParser->FindVariables();
			newParser->ChangeVariables();
			newParser->SpaceOperatorsFix();
			time = clock() - time;
			ui.textBrowser->append("Renamed variables - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
			sumtime += time;
		}

		if (ui.cb_Encryption->isChecked()) {
			time = clock();
			newParser->AddEncryption(ui.cb_EncToFile->isChecked(), ui.cb_EncOnlyFor->isChecked(), ui.cb_TPM_Variables->isChecked());
			time = clock() - time;
			ui.textBrowser->append("Encryption of variables - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
			sumtime += time;
		}


		if (ui.cb_DeleteEnters->isChecked()) {
			time = clock();
			newParser->DeleteEnters();
			time = clock() - time;
			ui.textBrowser->append("Deleted transition to the new line - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
			sumtime += time;
		}

		if (ui.cb_DeleteSpace->isChecked()) {
			time = clock();
			newParser->DeleteUnnecessarySpaces();
			time = clock() - time;
			ui.textBrowser->append("Deleted spaces - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
			sumtime += time;
		}

		newParser->SaveFile(settings::outFileName.toLocal8Bit().constData());
		delete newParser;

		if (ui.cb_TPM->isChecked()) {
			time = clock();
			TPM* tpm = new TPM();
			//tpm->EncryptDecryptSample();
			//ui.textBrowser->append(QString::fromStdString(tpm->getOutputString()));

			//tpm->ArrayParameters();
			//ui.textBrowser->append(QString::fromStdString(tpm->getOutputString()));

			
			std::wstring file_contents = readFileWstring(settings::outFileName.toLocal8Bit().constData());
			if (file_contents == L"") {
				ui.textBrowser->append("Error opening TPM file");
			}

			std::string file12 = tpm->EncryptWholeFile(file_contents, settings::outPath);
			time = clock() - time;
			ui.textBrowser->append("Encrypted by TPM - Time: " + QString::number((double)time / CLOCKS_PER_SEC, 'f', 4) + "s.");
			sumtime += time;
			std::ofstream outFile(settings::outFileName.toLocal8Bit().constData());
			outFile << file12;
			outFile.close();
			delete tpm;
		}


		ui.textBrowser->append("Summary: " + QString::number((double)sumtime / CLOCKS_PER_SEC, 'f', 4) + "s.");
	//	sumTimeMain += sumtime;
		//sumTimeMain += sumtime;
	//}
		
	ui.b_openFile->setEnabled(true);
	//ui.textBrowser->append("Total time: " + QString::number((double)sumTimeMain / CLOCKS_PER_SEC, 'f', 4) + "s.");
	//ui.textBrowser->append("Mean: " + QString::number((double)sumTimeMain / CLOCKS_PER_SEC / 100, 'f', 4) + "s.");
	


}

void GUI::on_encBox_changed() {
	if (ui.cb_Encryption->isChecked()) {
		ui.cb_EncOnlyFor->setEnabled(true);
		ui.cb_EncToFile->setEnabled(true);
		ui.cb_TPM_Variables->setEnabled(true);
		settings::countOfSettings++;
	}
	else {
		ui.cb_EncOnlyFor->setEnabled(false);
		ui.cb_EncToFile->setEnabled(false);
		ui.cb_TPM_Variables->setEnabled(false);
		settings::countOfSettings--;

	}
}

void GUI::on_delBox_changed() {
	if (ui.cb_deleteComments->isChecked()) {
		ui.cb_DeleteEnters->setEnabled(true);
	}
	else {
		ui.cb_DeleteEnters->setEnabled(false);
		ui.cb_DeleteEnters->setChecked(false);
	}
}

void GUI::on_addJunk_changed() {
	if (ui.cb_AddJunk->isChecked()) {
		ui.sp_AmountCodes->setEnabled(true);
		ui.sp_AmountVariables->setEnabled(true);
		settings::countOfSettings++;

		//buttons 
		ui.cb_JunkerSum->setEnabled(true);
		ui.cb_JunkerSub->setEnabled(true);
		ui.cb_JunkerMul->setEnabled(true);
		ui.cb_JunkerConnected->setEnabled(true);
		ui.cb_JunkerSemiConnected->setEnabled(true);
		ui.cb_JunkerNonConnected->setEnabled(true);
		ui.cb_JunkerInc->setEnabled(true);
	}
	else {
		ui.sp_AmountCodes->setEnabled(false);
		ui.sp_AmountVariables->setEnabled(false);
		settings::countOfSettings--;

		//buttons 
		ui.cb_JunkerSum->setEnabled(false);
		ui.cb_JunkerSub->setEnabled(false);
		ui.cb_JunkerMul->setEnabled(false);
		ui.cb_JunkerConnected->setEnabled(false);
		ui.cb_JunkerSemiConnected->setEnabled(false);
		ui.cb_JunkerNonConnected->setEnabled(false);
		ui.cb_JunkerInc->setEnabled(false);
	}
}

void GUI::on_chgLoopBox_changed() {
	if (ui.cb_changeLoops->isChecked()) {
		settings::countOfSettings++;
	}
	else {
		settings::countOfSettings--;
	}
}

void GUI::on_chgVarBox_changed() {
	if (ui.cb_ChangeVariables->isChecked()) {
		settings::countOfSettings++;
	}
	else {
		settings::countOfSettings--;
	}
}

void GUI::on_openButton_clicked() {

	if (QFileInfo::exists(settings::outFileName)) {
		QProcess* proc = new QProcess(this);
		proc->start("notepad.exe " + settings::outFileName);
	}
	else
		ui.textBrowser->append("File doesn't exist!");


}

void JunkerOption(bool isChecked, int value) {
	if (isChecked) {
		settings::junkerOptions.push_back(value);
	}
	else {
		for (int i = 0; i < settings::junkerOptions.size(); i++) {
			if (settings::junkerOptions[i] == value) {

				settings::junkerOptions.erase(settings::junkerOptions.begin() + i);
				break;
			}
		}
	}

}

void GUI::on_JunkerSumBox_changed() {
	JunkerOption(ui.cb_JunkerSum->isChecked(), 1);
}

void GUI::on_JunkerSubBox_changed() {
	JunkerOption(ui.cb_JunkerSub->isChecked(), 2);
}

void GUI::on_JunkerMulBox_changed() {
	JunkerOption(ui.cb_JunkerMul->isChecked(), 3);
}

void GUI::on_JunkerConnectedBox_changed() {
	JunkerOption(ui.cb_JunkerConnected->isChecked(), 4);
}

void GUI::on_JunkerSemiConnectedBox_changed() {
	JunkerOption(ui.cb_JunkerSemiConnected->isChecked(), 5);
}

void GUI::on_JunkerNonConnected_changed() {
	JunkerOption(ui.cb_JunkerNonConnected->isChecked(), 6);
}

void GUI::on_JunkerIncBox_changed() {
	JunkerOption(ui.cb_JunkerInc->isChecked(), 7);
}


void GUI::on_TPMBox_changed() {
	if (ui.cb_TPM->isChecked()) {
		settings::isTPMOn = true;
	}
	else {
		settings::isTPMOn = false;
	}
}