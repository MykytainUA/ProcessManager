#include "MainWindow.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(void) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	ProcessManager::MainWindow form;
	Application::Run(% form);
}

