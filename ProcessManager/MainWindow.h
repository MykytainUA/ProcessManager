#pragma once
#include "ProcessContoller.h"

namespace ProcessManager {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading::Tasks;
	using namespace System::Diagnostics;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();

			myProcessController = gcnew ProcessController();

			ProcessesBox->View = View::Details;
			ProcessesBox->FullRowSelect = true;
			ProcessesBox->GridLines = true;

			ProcessesBox->Columns->Add("Name:", 100);
			ProcessesBox->Columns->Add("ID:", 50);
			ProcessesBox->Columns->Add("Priority:", 100);
			ProcessesBox->Columns->Add("State:", 50);
			ProcessesBox->Columns->Add("Server:", 50);
			ProcessesBox->Columns->Add("CreationDate:", 120);
			ProcessesBox->Columns->Add("Path:", 250);

			Task^ myTask = Task::Factory->StartNew(gcnew Action(myProcessController, &ProcessController::GetCurrentProcesses));

			myTask->Wait();

			DebugInfo->Text = myProcessController->GetDebugInfo();

			for each (ProcessInfo^ item in myProcessController->GetProcesses())
			{
				ListViewItem^ item1 = gcnew ListViewItem(item->Name);
				item1->SubItems->Add(Convert::ToString((int)item->ProcessId));
				item1->SubItems->Add(PriorityToString((int)item->Priority));
				item1->SubItems->Add(StateToString((int)item->State));
				item1->SubItems->Add(item->Server);
				item1->SubItems->Add(item->CreationDate);
				item1->SubItems->Add(item->Path);
				ProcessesBox->Items->Add(item1);
			}

		}
	private: System::Windows::Forms::Button^ ClearDebug;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ LoginTextBox;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ PasswordTextBox;

	public:

		int selectedProcessID = -1;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^ ProcessesBox;
	private: System::Windows::Forms::Button^ UpdateProcessTable;
	private: System::Windows::Forms::Button^ TerminateProcessButton;

	private: System::Windows::Forms::TextBox^ ChosenProcessTextBox;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ RemoteComputerName;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ ConnectToRemoteComputer;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::RichTextBox^ DebugInfo;

	protected:

	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->ProcessesBox = (gcnew System::Windows::Forms::ListView());
			this->UpdateProcessTable = (gcnew System::Windows::Forms::Button());
			this->TerminateProcessButton = (gcnew System::Windows::Forms::Button());
			this->ChosenProcessTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->RemoteComputerName = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->ConnectToRemoteComputer = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->DebugInfo = (gcnew System::Windows::Forms::RichTextBox());
			this->ClearDebug = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->LoginTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->PasswordTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// ProcessesBox
			// 
			this->ProcessesBox->HideSelection = false;
			this->ProcessesBox->Location = System::Drawing::Point(363, 12);
			this->ProcessesBox->Name = L"ProcessesBox";
			this->ProcessesBox->Size = System::Drawing::Size(973, 808);
			this->ProcessesBox->TabIndex = 1;
			this->ProcessesBox->UseCompatibleStateImageBehavior = false;
			this->ProcessesBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainWindow::ProcessesBox_SelectedIndexChanged);
			// 
			// UpdateProcessTable
			// 
			this->UpdateProcessTable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->UpdateProcessTable->Location = System::Drawing::Point(12, 12);
			this->UpdateProcessTable->Name = L"UpdateProcessTable";
			this->UpdateProcessTable->Size = System::Drawing::Size(345, 49);
			this->UpdateProcessTable->TabIndex = 2;
			this->UpdateProcessTable->Text = L"Оновити таблицю процесів";
			this->UpdateProcessTable->UseVisualStyleBackColor = true;
			this->UpdateProcessTable->Click += gcnew System::EventHandler(this, &MainWindow::UpdateProcessTable_Click);
			// 
			// TerminateProcessButton
			// 
			this->TerminateProcessButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->TerminateProcessButton->Location = System::Drawing::Point(12, 107);
			this->TerminateProcessButton->Name = L"TerminateProcessButton";
			this->TerminateProcessButton->Size = System::Drawing::Size(345, 49);
			this->TerminateProcessButton->TabIndex = 3;
			this->TerminateProcessButton->Text = L"Завершити процес";
			this->TerminateProcessButton->UseVisualStyleBackColor = true;
			this->TerminateProcessButton->Click += gcnew System::EventHandler(this, &MainWindow::TerminateProcessButton_Click);
			// 
			// ChosenProcessTextBox
			// 
			this->ChosenProcessTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->ChosenProcessTextBox->Location = System::Drawing::Point(184, 67);
			this->ChosenProcessTextBox->Name = L"ChosenProcessTextBox";
			this->ChosenProcessTextBox->ReadOnly = true;
			this->ChosenProcessTextBox->Size = System::Drawing::Size(173, 34);
			this->ChosenProcessTextBox->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::Control;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(0, 73);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(169, 25);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Обраний процес:";
			// 
			// RemoteComputerName
			// 
			this->RemoteComputerName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->RemoteComputerName->Location = System::Drawing::Point(12, 187);
			this->RemoteComputerName->Name = L"RemoteComputerName";
			this->RemoteComputerName->Size = System::Drawing::Size(345, 34);
			this->RemoteComputerName->TabIndex = 6;
			this->RemoteComputerName->Text = L"LocalComputer";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(12, 159);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(306, 25);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Назва віддаленого комп\'ютера:";
			// 
			// ConnectToRemoteComputer
			// 
			this->ConnectToRemoteComputer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->ConnectToRemoteComputer->Location = System::Drawing::Point(12, 357);
			this->ConnectToRemoteComputer->Name = L"ConnectToRemoteComputer";
			this->ConnectToRemoteComputer->Size = System::Drawing::Size(345, 49);
			this->ConnectToRemoteComputer->TabIndex = 8;
			this->ConnectToRemoteComputer->Text = L"Підключитись до віддаленого комп\'ютера";
			this->ConnectToRemoteComputer->UseVisualStyleBackColor = true;
			this->ConnectToRemoteComputer->Click += gcnew System::EventHandler(this, &MainWindow::ConnectToRemoteComputer_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(12, 464);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(298, 25);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Налагоджувальна інформація:";
			// 
			// DebugInfo
			// 
			this->DebugInfo->Location = System::Drawing::Point(17, 492);
			this->DebugInfo->Name = L"DebugInfo";
			this->DebugInfo->Size = System::Drawing::Size(340, 328);
			this->DebugInfo->TabIndex = 10;
			this->DebugInfo->Text = L"";
			// 
			// ClearDebug
			// 
			this->ClearDebug->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ClearDebug->Location = System::Drawing::Point(12, 412);
			this->ClearDebug->Name = L"ClearDebug";
			this->ClearDebug->Size = System::Drawing::Size(345, 49);
			this->ClearDebug->TabIndex = 11;
			this->ClearDebug->Text = L"Видалити текст";
			this->ClearDebug->UseVisualStyleBackColor = true;
			this->ClearDebug->Click += gcnew System::EventHandler(this, &MainWindow::ClearDebug_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(12, 224);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(67, 25);
			this->label4->TabIndex = 12;
			this->label4->Text = L"Логін:";
			// 
			// LoginTextBox
			// 
			this->LoginTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->LoginTextBox->Location = System::Drawing::Point(12, 252);
			this->LoginTextBox->Name = L"LoginTextBox";
			this->LoginTextBox->Size = System::Drawing::Size(345, 34);
			this->LoginTextBox->TabIndex = 13;
			this->LoginTextBox->Text = L"LocalUser";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(12, 289);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(86, 25);
			this->label5->TabIndex = 14;
			this->label5->Text = L"Пароль:";
			// 
			// PasswordTextBox
			// 
			this->PasswordTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->PasswordTextBox->Location = System::Drawing::Point(12, 317);
			this->PasswordTextBox->Name = L"PasswordTextBox";
			this->PasswordTextBox->Size = System::Drawing::Size(345, 34);
			this->PasswordTextBox->TabIndex = 15;
			this->PasswordTextBox->Text = L"LocalPassword";
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1348, 832);
			this->Controls->Add(this->PasswordTextBox);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->LoginTextBox);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->ClearDebug);
			this->Controls->Add(this->DebugInfo);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->ConnectToRemoteComputer);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->RemoteComputerName);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ChosenProcessTextBox);
			this->Controls->Add(this->TerminateProcessButton);
			this->Controls->Add(this->UpdateProcessTable);
			this->Controls->Add(this->ProcessesBox);
			this->Name = L"MainWindow";
			this->Text = L"MainWindow";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	ProcessController^ myProcessController;

	private: System::Void UpdateProcessTable_Click(System::Object^ sender, System::EventArgs^ e) 
	{

		myProcessController->ClearProcesses();
		Task^ myTask = Task::Factory->StartNew(gcnew Action(myProcessController, &ProcessController::GetCurrentProcesses));

		ProcessesBox->Items->Clear();

		myTask->Wait();


		for each (ProcessInfo ^ item in myProcessController->GetProcesses())
		{
			ListViewItem^ item1 = gcnew ListViewItem(item->Name);
			item1->SubItems->Add(Convert::ToString((int)item->ProcessId));
			item1->SubItems->Add(PriorityToString((int)item->Priority));
			item1->SubItems->Add(StateToString((int)item->State));
			item1->SubItems->Add(item->Server);
			item1->SubItems->Add(item->CreationDate);
			item1->SubItems->Add(item->Path);
			ProcessesBox->Items->Add(item1);
		}

		DebugInfo->Text = myProcessController->GetDebugInfo();
	}

private: System::Void ProcessesBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
{

	if (ProcessesBox->SelectedItems->Count > 0) 
	{
		ListViewItem^ selectedItem = ProcessesBox->SelectedItems[0];
		ChosenProcessTextBox->Text = selectedItem->SubItems[0]->Text;
		selectedProcessID = Convert::ToInt32(selectedItem->SubItems[1]->Text);
	}
}

private: System::Void TerminateProcessButton_Click(System::Object^ sender, System::EventArgs^ e) 
{
	try {
		Process^ process = Process::GetProcessById(selectedProcessID);
		process->Kill();
	}
	catch (ArgumentException^) {
		myProcessController->AddDebugInfo(String::Format("Процес з ID {0} не знайдено.\n", selectedProcessID));
	}
	catch (Exception^ ex) {
		myProcessController->AddDebugInfo(String::Format("Помилка №{0}.\n", ex->Message));
	}

	Sleep(1000);

	myProcessController->ClearProcesses();
	Task^ myTask = Task::Factory->StartNew(gcnew Action(myProcessController, &ProcessController::GetCurrentProcesses));
	ProcessesBox->Items->Clear();

	myTask->Wait();


	for each (ProcessInfo ^ item in myProcessController->GetProcesses())
	{
		ListViewItem^ item1 = gcnew ListViewItem(item->Name);
		item1->SubItems->Add(Convert::ToString((int)item->ProcessId));
		item1->SubItems->Add(PriorityToString((int)item->Priority));
		item1->SubItems->Add(StateToString((int)item->State));
		item1->SubItems->Add(item->Server);
		item1->SubItems->Add(item->CreationDate);
		item1->SubItems->Add(item->Path);
		ProcessesBox->Items->Add(item1);
	}
	myProcessController->AddDebugInfo(String::Format("Процес з ID{0} було видалено.\n", selectedProcessID));

	DebugInfo->Text = myProcessController->GetDebugInfo();

}
	 

private: System::Void ClearDebug_Click(System::Object^ sender, System::EventArgs^ e) 
{
	myProcessController->ClearDebugInfo();
	DebugInfo->Text = myProcessController->GetDebugInfo();
}
private: System::Void ConnectToRemoteComputer_Click(System::Object^ sender, System::EventArgs^ e) 
{
	myProcessController->SetNetworkResource(RemoteComputerName->Text);
	myProcessController->SetLogin(LoginTextBox->Text);
	myProcessController->SetPassword(PasswordTextBox->Text);

	Sleep(1000);

	myProcessController->ClearProcesses();
	Task^ myTask = Task::Factory->StartNew(gcnew Action(myProcessController, &ProcessController::GetCurrentProcesses));
	ProcessesBox->Items->Clear();

	myTask->Wait();


	for each (ProcessInfo ^ item in myProcessController->GetProcesses())
	{
		ListViewItem^ item1 = gcnew ListViewItem(item->Name);
		item1->SubItems->Add(Convert::ToString((int)item->ProcessId));
		item1->SubItems->Add(PriorityToString((int)item->Priority));
		item1->SubItems->Add(StateToString((int)item->State));
		item1->SubItems->Add(item->Server);
		item1->SubItems->Add(item->CreationDate);
		item1->SubItems->Add(item->Path);
		ProcessesBox->Items->Add(item1);
	}

	DebugInfo->Text = myProcessController->GetDebugInfo();
}
};
}
