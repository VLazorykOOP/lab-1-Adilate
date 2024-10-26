#include "Lab1.h"

template <typename MenuItemType>
void ChangeItemUp(MenuItemType& item, MenuItemType firstItem, MenuItemType lastItem)
{
	item = (item == firstItem) ? lastItem : MenuItemType(int(item) - 1);
}

template <typename MenuItemType>
void ChangeItemDown(MenuItemType& item, MenuItemType firstItem, MenuItemType lastItem)
{
	item = (item == lastItem) ? firstItem : MenuItemType(int(item) + 1);
}

bool ReadTextFromFile(const std::string& filename, std::string& content) 
{
	// Open file:
	std::ifstream fileStream(filename);
	if (!fileStream.is_open())
		return false;

	// Delete previous content:
	content.clear();

	// Read new content from file:
	std::string textLine;

	while (!fileStream.eof())
	{
		std::getline(fileStream, textLine);
		content += (textLine + '\n');
	}

	return true;
}

Lab1& Lab1::GetInstance()
{
	static Lab1 MyLab;
	return MyLab;
}

bool Lab1::IsOpen() const
{
	return OpenLab;
}

void Lab1::HendleInput()
{
	switch (ThisTask)
	{
	case Lab1::TASK::NONE: HendleInputMenuTask();   break;
	default:
		break;
	}
}

void Lab1::Update()
{
		switch (ThisTask)
		{
		case Lab1::TASK::NONE: UpdateMenuTask();break;
		case Lab1::TASK::T1:   Task1();			break;
		case Lab1::TASK::T2:   Task2();			break;
		case Lab1::TASK::T3:   Task3();			break;
		default:
			break;
		}
}

void Lab1::Render() const
{
	Console::ResetCursorPosition();
	switch (ThisTask)
	{
	case Lab1::TASK::NONE: RenderMenuTask();break;
	default:
		break;
	}
}

Lab1::~Lab1()
{
	delete[]A;
	delete[]B;
	delete[]arr;
	delete[]ArR;
}

Lab1::Lab1() : ThisTask(TASK::NONE) , OpenLab(true) , ArrTask(TASK_ARROW::T1)
{
	ReadTextFromFile("menu.txt", MenuContent);

}

void Lab1::HendleInputMenuTask()
{

	if (InputManager::UserPressedKey())
	{
		InputManager::Key key = InputManager::PressedKey();
		switch (key)
		{
		case InputManager::Key::Escape:
			exit(0);
			break;

		case InputManager::Key::Enter:
			switch (ArrTask)
			{
			case Lab1::TASK_ARROW::T1:
				ThisTask = TASK::T1;
				break;
			case Lab1::TASK_ARROW::T2:
				ThisTask = TASK::T2;
				break;
			case Lab1::TASK_ARROW::T3:
				ThisTask = TASK::T3;
				break;
			case Lab1::TASK_ARROW::ESC:
				exit(0);
				break;
			default:
				break;
			}
			break;

		case InputManager::Key::ArrowUp:
			ChangeItemUp(ArrTask, TASK_ARROW::T1, TASK_ARROW::ESC);

			break;
		case InputManager::Key::ArrowDown:
			ChangeItemDown(ArrTask, TASK_ARROW::T1, TASK_ARROW::ESC);
			break;


		default:
			break;
		}
	}
}

bool Lab1::UpdateMenuTask()
{

	RemoveArrowFromSelectedElement(MenuContent);

	size_t selectedItemPosition;

	switch (ArrTask)
	{
	case TASK_ARROW::T1:
		selectedItemPosition = MenuContent.find("Task  1");
		break;
	case TASK_ARROW::T2:
		selectedItemPosition = MenuContent.find("Task  2");
		break;
	case TASK_ARROW::T3:
		selectedItemPosition = MenuContent.find("Task  3");
		break;
	case TASK_ARROW::ESC:
		selectedItemPosition = MenuContent.find("Exit");
		break;
	default:
		return false;
	}

	if (selectedItemPosition == std::string::npos)
		return false;

	MenuContent[selectedItemPosition - 4] = '-';
	MenuContent[selectedItemPosition - 3] = '>';


	return true;
}

void Lab1::RenderMenuTask() const
{
	std::cout << MenuContent;
}

void Lab1::RemoveArrowFromSelectedElement(std::string& element)
{
	if (size_t arrowPosition = element.find("->"); arrowPosition != std::string::npos)
	{
		element[arrowPosition] = ' ';
		element[arrowPosition + 1] = ' ';
	}
}

void Lab1::Task1()
{
	int N = 1;
	std::string SizeN = "   ";
#pragma region Start
	bool IsNext = false;
	do
	{
		if (InputManager::UserPressedKey())
		{
			InputManager::Key key = InputManager::PressedKey();

			switch (key)
			{
			case InputManager::Key::Back:
				for (int i = 2; i >= 0; i--) if (SizeN[i] != ' ') { SizeN[i] = ' '; break; }	break;
			case InputManager::Key::Enter: if (N > 3) IsNext = true;
				break;
			case InputManager::Key::Escape: ThisTask = Lab1::TASK::NONE;
				return;
			case InputManager::Key::NUM_0: if(SizeN[0] == ' ') break; [[fallthrough]];
			case InputManager::Key::NUM_1: [[fallthrough]];
			case InputManager::Key::NUM_2: [[fallthrough]];
			case InputManager::Key::NUM_3: [[fallthrough]];
			case InputManager::Key::NUM_4: [[fallthrough]];
			case InputManager::Key::NUM_5: [[fallthrough]];
			case InputManager::Key::NUM_6: [[fallthrough]];
			case InputManager::Key::NUM_7: [[fallthrough]];
			case InputManager::Key::NUM_8: [[fallthrough]];
			case InputManager::Key::NUM_9:
				for (int i = 0; i < 3; i++) if (SizeN[i] == ' ') { SizeN[i] = char(key); N = std::stoi(SizeN); break; }break;
			default:
				break;
			}
		}


		Console::ResetCursorPosition();
		std::cout << "#=============================#" << std::endl;
		std::cout << "#           Task  1           #" << std::endl;
		std::cout << "#                             #" << std::endl;
		std::cout << "#           N = " << SizeN << "           #" << std::endl;
		std::cout << "#          Next(Entr)         #" << std::endl;
		std::cout << "#          Exit(esc)          #" << std::endl;
		std::cout << "#=============================#" << std::endl;

	} while (!IsNext);

#pragma endregion

#pragma region ArrayFilling


	A = new int[N];
	B = new int[N];

	int num = N; SizeN = "   "; IsNext = false;

	for (int klk = 0; klk < N;)
	{
		Console::ResetCursorPosition();
		std::cout << "#=============================#" << std::endl;
		for (int i = 0; i < N && i < 25; i++)
			std::cout << "#                             #" << std::endl;
		std::cout << "#=============================#" << std::endl;

		for (int j = 0; j < 25 && klk < N; j++,klk++)
		{
			do
			{
				if (InputManager::UserPressedKey())
				{
					InputManager::Key key = InputManager::PressedKey();

					switch (key)
					{
					case InputManager::Key::Back:
						for (int i = 2; i >= 0; i--) if (SizeN[i] != ' ') { SizeN[i] = ' '; break; }	break;
					case InputManager::Key::Enter: IsNext = true;
						break;
					case InputManager::Key::Escape: ThisTask = Lab1::TASK::NONE;
						return;
					case InputManager::Key::MINUS: if (SizeN[0] == ' ') SizeN[0] = char(key); break;
					case InputManager::Key::NUM_0: [[fallthrough]];
					case InputManager::Key::NUM_1: [[fallthrough]];
					case InputManager::Key::NUM_2: [[fallthrough]];
					case InputManager::Key::NUM_3: [[fallthrough]];
					case InputManager::Key::NUM_4: [[fallthrough]];
					case InputManager::Key::NUM_5: [[fallthrough]];
					case InputManager::Key::NUM_6: [[fallthrough]];
					case InputManager::Key::NUM_7: [[fallthrough]];
					case InputManager::Key::NUM_8: [[fallthrough]];
					case InputManager::Key::NUM_9:
						for (int i = 0; i < 3; i++) if (SizeN[i] == ' ') { SizeN[i] = char(key); num = std::stoi(SizeN); break; }break;
					default:
						break;
					}
				}

				std::string BufSizeN;

				int klkP = 0;
				for (char el : SizeN) if (el == ' ') klkP++;

				switch (klkP)
				{
				case 0: BufSizeN = SizeN; break;
				case 1: BufSizeN = "0" + std::string(1, SizeN[0]) + std::string(1, SizeN[1]); break;
				case 2: BufSizeN = "00" + std::string(1,SizeN[0]); break;
				default: BufSizeN = "000";
					break;
				}



				Console::SetCursorPosition(0, j + 1);
				std::cout << "#        A[" << std::string((N > 99 ? 3 : N > 9 ? 2 : 1) - (klk < 9 ? 1 : klk < 99 ? 2 : 3), '0') << klk + 1 << "] = " << BufSizeN << std::string((N > 99 ? 0 : N > 9 ? 1 : 2), ' ') << "         #" << std::endl;

			} while (!IsNext);
			A[klk] = num; IsNext = false; SizeN = "   "; num = 0;

		}
		Console::ClearScreen();
	}
	num = N; SizeN = "   "; IsNext = false;

	for (int klk = 0; klk < N;)
	{
		Console::ResetCursorPosition();
		std::cout << "#=============================#" << std::endl;
		for (int i = 0; i < N && i < 25; i++)
			std::cout << "#                             #" << std::endl;
		std::cout << "#=============================#" << std::endl;

		for (int j = 0; j < 25 && klk < N; j++, klk++)
		{
			do
			{
				if (InputManager::UserPressedKey())
				{
					InputManager::Key key = InputManager::PressedKey();

					switch (key)
					{
					case InputManager::Key::Back:
						for (int i = 2; i >= 0; i--) if (SizeN[i] != ' ') { SizeN[i] = ' '; break; }	break;
					case InputManager::Key::Enter: IsNext = true;
						break;
					case InputManager::Key::Escape: ThisTask = Lab1::TASK::NONE;
						return;
					case InputManager::Key::MINUS: if (SizeN[0] == ' ') SizeN[0] = char(key); break;
					case InputManager::Key::NUM_0: [[fallthrough]];
					case InputManager::Key::NUM_1: [[fallthrough]];
					case InputManager::Key::NUM_2: [[fallthrough]];
					case InputManager::Key::NUM_3: [[fallthrough]];
					case InputManager::Key::NUM_4: [[fallthrough]];
					case InputManager::Key::NUM_5: [[fallthrough]];
					case InputManager::Key::NUM_6: [[fallthrough]];
					case InputManager::Key::NUM_7: [[fallthrough]];
					case InputManager::Key::NUM_8: [[fallthrough]];
					case InputManager::Key::NUM_9:
						for (int i = 0; i < 3; i++) if (SizeN[i] == ' ') { SizeN[i] = char(key); num = std::stoi(SizeN); break; }break;
					default:
						break;
					}
				}



				std::string BufSizeN;

				int klkP = 0;
				for (char el : SizeN) if (el == ' ') klkP++;

				switch (klkP)
				{
				case 0: BufSizeN = SizeN; break;
				case 1: BufSizeN = "0" + std::string(1, SizeN[0]) + std::string(1, SizeN[1]); break;
				case 2: BufSizeN = "00" + std::string(1, SizeN[0]); break;
				default: BufSizeN = "000";
					break;
				}

				Console::SetCursorPosition(0, j + 1);
				std::cout << "#        B[" << std::string((N > 99 ? 3 : N > 9 ? 2 : 1) - (klk < 9 ? 1 : klk < 99 ? 2 : 3), '0') << klk + 1 << "] = " << BufSizeN << std::string((N > 99 ? 0 : N > 9 ? 1 : 2), ' ') << "         #" << std::endl;

			} while (!IsNext);
			B[klk] = num; IsNext = false; SizeN = "   "; num = 0;

		}
		Console::ClearScreen();
	}

#pragma endregion ArrayFilling

	for (int i = 0; i < N; i++) if (A[i] > 0) A[i] = B[i];

#pragma region 
	for (int klk = 0; klk < N;)
	{
		Console::ResetCursorPosition();
		std::cout << "#=============================#" << std::endl;
		for (int i = 0; i < N && i < 25; i++)
			std::cout << "#                             #" << std::endl;
		std::cout << "#=============================#" << std::endl;

		for (int j = 0; j < 25 && klk < N; j++, klk++)
		{


			Console::SetCursorPosition(0, j + 1);
				std::cout << "#        A[" << std::string((N > 99 ? 3 : N > 9 ? 2 : 1) - (klk < 9 ? 1 : klk < 99 ? 2 : 3), '0') << klk + 1 << "] = " << std::string(A[klk] > 99 ? 0 : A[klk] > 9 ? 1 : A[klk] >= 0 ? 2 : A[klk] > -10 ? 1 : 0, '0') << std::to_string(A[klk]) << std::string((N > 99 ? 0 : N > 9 ? 1 : 2), ' ') << "         #" << std::endl;

		}
		do {
			if (InputManager::UserPressedKey())
			{
				InputManager::Key key = InputManager::PressedKey();

				switch (key)
				{
				case InputManager::Key::Enter: IsNext = true;	break;
				case InputManager::Key::Escape: ThisTask = Lab1::TASK::NONE; return;
				default:
					break;
				}
			}
		} while (!IsNext);
		Console::ClearScreen();
	}
#pragma endregion

}


int findIndex(int arr[], int size, int T1, int T2) {
	int indexT2 = -1;
	int minIndex = -1;
	int minValue = INT_MAX;

	for (int i = 0; i < size; ++i) {
		if (arr[i] == T2) {
			indexT2 = i;
			break;
		}
	}
	if (indexT2 == -1) {
		return -1;
	}

	for (int i = indexT2 + 1; i < size; ++i) {
		if (arr[i] > T1 && (minIndex == -1 || arr[i] < arr[minIndex])) {
			minIndex = i;
		}
	}

	return minIndex;
}

void Lab1::Task2()
{
	int N = 1;

	int T1;
	int T2;

#pragma region Start
	std::string SizeN = "   ";
	bool IsNext = false;
	do
	{
		if (InputManager::UserPressedKey())
		{
			InputManager::Key key = InputManager::PressedKey();

			switch (key)
			{
			case InputManager::Key::Back:
				for (int i = 2; i >= 0; i--) if (SizeN[i] != ' ') { SizeN[i] = ' '; break; }	break;
			case InputManager::Key::Enter: if (N > 3) IsNext = true;
				break;
			case InputManager::Key::Escape: ThisTask = Lab1::TASK::NONE;
				return;
			case InputManager::Key::NUM_0: if (SizeN[0] == ' ') break; [[fallthrough]];
			case InputManager::Key::NUM_1: [[fallthrough]];
			case InputManager::Key::NUM_2: [[fallthrough]];
			case InputManager::Key::NUM_3: [[fallthrough]];
			case InputManager::Key::NUM_4: [[fallthrough]];
			case InputManager::Key::NUM_5: [[fallthrough]];
			case InputManager::Key::NUM_6: [[fallthrough]];
			case InputManager::Key::NUM_7: [[fallthrough]];
			case InputManager::Key::NUM_8: [[fallthrough]];
			case InputManager::Key::NUM_9:
				for (int i = 0; i < 3; i++) if (SizeN[i] == ' ') { SizeN[i] = char(key); N = std::stoi(SizeN); break; }break;
			default:
				break;
			}
		}


		Console::ResetCursorPosition();
		std::cout << "#=============================#" << std::endl;
		std::cout << "#           Task  2           #" << std::endl;
		std::cout << "#                             #" << std::endl;
		std::cout << "#           N = " << SizeN << "           #" << std::endl;
		std::cout << "#          Next(Entr)         #" << std::endl;
		std::cout << "#          Exit(esc)          #" << std::endl;
		std::cout << "#=============================#" << std::endl;

	} while (!IsNext);

	SizeN = "   ";
	IsNext = false;
	do
	{
		if (InputManager::UserPressedKey())
		{
			InputManager::Key key = InputManager::PressedKey();

			switch (key)
			{
			case InputManager::Key::Back:
				for (int i = 2; i >= 0; i--) if (SizeN[i] != ' ') { SizeN[i] = ' '; break; }	break;
			case InputManager::Key::Enter: if (N > 3) IsNext = true;
				break;
			case InputManager::Key::Escape: ThisTask = Lab1::TASK::NONE;
				return;
			case InputManager::Key::NUM_0: if (SizeN[0] == ' ') break; [[fallthrough]];
			case InputManager::Key::NUM_1: [[fallthrough]];
			case InputManager::Key::NUM_2: [[fallthrough]];
			case InputManager::Key::NUM_3: [[fallthrough]];
			case InputManager::Key::NUM_4: [[fallthrough]];
			case InputManager::Key::NUM_5: [[fallthrough]];
			case InputManager::Key::NUM_6: [[fallthrough]];
			case InputManager::Key::NUM_7: [[fallthrough]];
			case InputManager::Key::NUM_8: [[fallthrough]];
			case InputManager::Key::NUM_9:
				for (int i = 0; i < 3; i++) if (SizeN[i] == ' ') { SizeN[i] = char(key); T1 = std::stoi(SizeN); break; }break;
			default:
				break;
			}
		}


		Console::ResetCursorPosition();
		std::cout << "#=============================#" << std::endl;
		std::cout << "#           Task  2           #" << std::endl;
		std::cout << "#                             #" << std::endl;
		std::cout << "#          T1 = " << SizeN << "           #" << std::endl;
		std::cout << "#          Next(Entr)         #" << std::endl;
		std::cout << "#          Exit(esc)          #" << std::endl;
		std::cout << "#=============================#" << std::endl;

	} while (!IsNext);

	SizeN = "   ";
	IsNext = false;
	do
	{
		if (InputManager::UserPressedKey())
		{
			InputManager::Key key = InputManager::PressedKey();

			switch (key)
			{
			case InputManager::Key::Back:
				for (int i = 2; i >= 0; i--) if (SizeN[i] != ' ') { SizeN[i] = ' '; break; }	break;
			case InputManager::Key::Enter: if (N > 3) IsNext = true;
				break;
			case InputManager::Key::Escape: ThisTask = Lab1::TASK::NONE;
				return;
			case InputManager::Key::NUM_0: if (SizeN[0] == ' ') break; [[fallthrough]];
			case InputManager::Key::NUM_1: [[fallthrough]];
			case InputManager::Key::NUM_2: [[fallthrough]];
			case InputManager::Key::NUM_3: [[fallthrough]];
			case InputManager::Key::NUM_4: [[fallthrough]];
			case InputManager::Key::NUM_5: [[fallthrough]];
			case InputManager::Key::NUM_6: [[fallthrough]];
			case InputManager::Key::NUM_7: [[fallthrough]];
			case InputManager::Key::NUM_8: [[fallthrough]];
			case InputManager::Key::NUM_9:
				for (int i = 0; i < 3; i++) if (SizeN[i] == ' ') { SizeN[i] = char(key); T2 = std::stoi(SizeN); break; }break;
			default:
				break;
			}
		}


		Console::ResetCursorPosition();
		std::cout << "#=============================#" << std::endl;
		std::cout << "#           Task  2           #" << std::endl;
		std::cout << "#                             #" << std::endl;
		std::cout << "#          T2 = " << SizeN << "           #" << std::endl;
		std::cout << "#          Next(Entr)         #" << std::endl;
		std::cout << "#          Exit(esc)          #" << std::endl;
		std::cout << "#=============================#" << std::endl;

	} while (!IsNext);

#pragma endregion


#pragma region ArrayFilling


	arr = new int[N];

	int num = N; SizeN = "   "; IsNext = false;

	for (int klk = 0; klk < N;)
	{
		Console::ResetCursorPosition();
		std::cout << "#=============================#" << std::endl;
		for (int i = 0; i < N && i < 25; i++)
			std::cout << "#                             #" << std::endl;
		std::cout << "#=============================#" << std::endl;

		for (int j = 0; j < 25 && klk < N; j++, klk++)
		{
			do
			{
				if (InputManager::UserPressedKey())
				{
					InputManager::Key key = InputManager::PressedKey();

					switch (key)
					{
					case InputManager::Key::Back:
						for (int i = 2; i >= 0; i--) if (SizeN[i] != ' ') { SizeN[i] = ' '; break; }	break;
					case InputManager::Key::Enter: IsNext = true;
						break;
					case InputManager::Key::Escape: ThisTask = Lab1::TASK::NONE;
						return;
					case InputManager::Key::MINUS: if (SizeN[0] == ' ') SizeN[0] = char(key); break;
					case InputManager::Key::NUM_0: [[fallthrough]];
					case InputManager::Key::NUM_1: [[fallthrough]];
					case InputManager::Key::NUM_2: [[fallthrough]];
					case InputManager::Key::NUM_3: [[fallthrough]];
					case InputManager::Key::NUM_4: [[fallthrough]];
					case InputManager::Key::NUM_5: [[fallthrough]];
					case InputManager::Key::NUM_6: [[fallthrough]];
					case InputManager::Key::NUM_7: [[fallthrough]];
					case InputManager::Key::NUM_8: [[fallthrough]];
					case InputManager::Key::NUM_9:
						for (int i = 0; i < 3; i++) if (SizeN[i] == ' ') { SizeN[i] = char(key); num = std::stoi(SizeN); break; }break;
					default:
						break;
					}
				}

				std::string BufSizeN;

				int klkP = 0;
				for (char el : SizeN) if (el == ' ') klkP++;

				switch (klkP)
				{
				case 0: BufSizeN = SizeN; break;
				case 1: BufSizeN = "0" + std::string(1, SizeN[0]) + std::string(1, SizeN[1]); break;
				case 2: BufSizeN = "00" + std::string(1, SizeN[0]); break;
				default: BufSizeN = "000";
					break;
				}



				Console::SetCursorPosition(0, j + 1);
				std::cout << "#        A[" << std::string((N > 99 ? 3 : N > 9 ? 2 : 1) - (klk < 9 ? 1 : klk < 99 ? 2 : 3), '0') << klk + 1 << "] = " << BufSizeN << std::string((N > 99 ? 0 : N > 9 ? 1 : 2), ' ') << "         #" << std::endl;

			} while (!IsNext);
			arr[klk] = num; IsNext = false; SizeN = "   "; num = 0;

		}
		Console::ClearScreen();
	}

#pragma endregion ArrayFilling


	Console::ClearScreen();

	Console::SetCursorPosition(0, 0);

	int result = findIndex(arr, N, T1, T2);
	if (result != -1) {
		std::cout << "Index of the first minimum element, greater than " << T1 << " and located to the right " << T2 << " is: " << result << std::endl;
	}
	else {
		std::cout << "Item Not Found." << std::endl;
	}
	IsNext = false;
	do {
		if (InputManager::UserPressedKey())
		{
			InputManager::Key key = InputManager::PressedKey();

			switch (key)
			{
			case InputManager::Key::Enter: IsNext = true;	break;
			case InputManager::Key::Escape: ThisTask = Lab1::TASK::NONE; return;
			default:
				break;
			}
		}
	} while (!IsNext);
	Console::ClearScreen();
}

#include <unordered_map>

int findMaxUnique(int arr[], int size) {
	std::unordered_map<int, int> frequency;

	// Підрахунок частоти кожного елемента
	for (int i = 0; i < size; ++i) {
		frequency[arr[i]]++;
	}

	int maxUnique = INT_MIN;

	// Пошук максимального унікального елемента
	for (int i = 0; i < size; ++i) {
		if (frequency[arr[i]] == 1 && arr[i] > maxUnique) {
			maxUnique = arr[i];
		}
	}

	return maxUnique;
}

void Lab1::Task3()
{

	int N = 1;
	std::string SizeN = "   ";
#pragma region Start
	bool IsNext = false;
	do
	{
		if (InputManager::UserPressedKey())
		{
			InputManager::Key key = InputManager::PressedKey();

			switch (key)
			{
			case InputManager::Key::Back:
				for (int i = 2; i >= 0; i--) if (SizeN[i] != ' ') { SizeN[i] = ' '; break; }	break;
			case InputManager::Key::Enter: if (N > 3 && N <=400 ) IsNext = true;
				break;
			case InputManager::Key::Escape: ThisTask = Lab1::TASK::NONE;
				return;
			case InputManager::Key::NUM_0: if (SizeN[0] == ' ') break; [[fallthrough]];
			case InputManager::Key::NUM_1: [[fallthrough]];
			case InputManager::Key::NUM_2: [[fallthrough]];
			case InputManager::Key::NUM_3: [[fallthrough]];
			case InputManager::Key::NUM_4: [[fallthrough]];
			case InputManager::Key::NUM_5: [[fallthrough]];
			case InputManager::Key::NUM_6: [[fallthrough]];
			case InputManager::Key::NUM_7: [[fallthrough]];
			case InputManager::Key::NUM_8: [[fallthrough]];
			case InputManager::Key::NUM_9:
				for (int i = 0; i < 3; i++) if (SizeN[i] == ' ') { SizeN[i] = char(key); N = std::stoi(SizeN); break; }break;
			default:
				break;
			}
		}


		Console::ResetCursorPosition();
		std::cout << "#=============================#" << std::endl;
		std::cout << "#           Task  3           #" << std::endl;
		std::cout << "#                             #" << std::endl;
		std::cout << "#           N = " << SizeN << "           #" << std::endl;
		std::cout << "#          Next(Entr)         #" << std::endl;
		std::cout << "#          Exit(esc)          #" << std::endl;
		std::cout << "#=============================#" << std::endl;

	} while (!IsNext);

#pragma endregion

#pragma region ArrayFilling


	ArR = new int[N];

	int num = N; SizeN = "   "; IsNext = false;

	for (int klk = 0; klk < N;)
	{
		Console::ResetCursorPosition();
		std::cout << "#=============================#" << std::endl;
		for (int i = 0; i < N && i < 25; i++)
			std::cout << "#                             #" << std::endl;
		std::cout << "#=============================#" << std::endl;

		for (int j = 0; j < 25 && klk < N; j++, klk++)
		{
			do
			{
				if (InputManager::UserPressedKey())
				{
					InputManager::Key key = InputManager::PressedKey();

					switch (key)
					{
					case InputManager::Key::Back:
						for (int i = 2; i >= 0; i--) if (SizeN[i] != ' ') { SizeN[i] = ' '; break; }	break;
					case InputManager::Key::Enter: IsNext = true;
						break;
					case InputManager::Key::Escape: ThisTask = Lab1::TASK::NONE;
						return;
					case InputManager::Key::MINUS: if (SizeN[0] == ' ') SizeN[0] = char(key); break;
					case InputManager::Key::NUM_0: [[fallthrough]];
					case InputManager::Key::NUM_1: [[fallthrough]];
					case InputManager::Key::NUM_2: [[fallthrough]];
					case InputManager::Key::NUM_3: [[fallthrough]];
					case InputManager::Key::NUM_4: [[fallthrough]];
					case InputManager::Key::NUM_5: [[fallthrough]];
					case InputManager::Key::NUM_6: [[fallthrough]];
					case InputManager::Key::NUM_7: [[fallthrough]];
					case InputManager::Key::NUM_8: [[fallthrough]];
					case InputManager::Key::NUM_9:
						for (int i = 0; i < 3; i++) if (SizeN[i] == ' ') { SizeN[i] = char(key); num = std::stoi(SizeN); break; }break;
					default:
						break;
					}
				}

				std::string BufSizeN;

				int klkP = 0;
				for (char el : SizeN) if (el == ' ') klkP++;

				switch (klkP)
				{
				case 0: BufSizeN = SizeN; break;
				case 1: BufSizeN = "0" + std::string(1, SizeN[0]) + std::string(1, SizeN[1]); break;
				case 2: BufSizeN = "00" + std::string(1, SizeN[0]); break;
				default: BufSizeN = "000";
					break;
				}



				Console::SetCursorPosition(0, j + 1);
				std::cout << "#        A[" << std::string((N > 99 ? 3 : N > 9 ? 2 : 1) - (klk < 9 ? 1 : klk < 99 ? 2 : 3), '0') << klk + 1 << "] = " << BufSizeN << std::string((N > 99 ? 0 : N > 9 ? 1 : 2), ' ') << "         #" << std::endl;

			} while (!IsNext);
			ArR[klk] = num;
			int num = N; SizeN = "   "; IsNext = false;

		}
		Console::ClearScreen();
	}

#pragma endregion ArrayFilling

	Console::ClearScreen();

	Console::SetCursorPosition(0, 0);

	int result = findMaxUnique(ArR, N);
	if (result != INT_MIN) {
		std::cout << "Maximum among unique numbers: " << result << std::endl;
	}
	else {
		std::cout << "No unique numbers found." << std::endl;
	}

	IsNext = false;
	do {
		if (InputManager::UserPressedKey())
		{
			InputManager::Key key = InputManager::PressedKey();

			switch (key)
			{
			case InputManager::Key::Enter: IsNext = true;	break;
			case InputManager::Key::Escape: ThisTask = Lab1::TASK::NONE; return;
			default:
				break;
			}
		}
	} while (!IsNext);
	Console::ClearScreen();
}
