#include <iostream>
#include <vector>
#include "Message_class.h"

int main()
{
	Folder default_Folder;
	Folder important_Folder;
	std::vector<Folder> folders{ default_Folder, important_Folder };
	std::vector<Message*> messages;

	int menu;
	int select_folder;
	std::string str;
	while (!std::cin.eof())
	{
		std::cout << "------------------------\n";
		std::cout << "please enter the number for select menu...\n"
			"(1. Check the folder)\n"
			"(2. Make a Message)\n"
			"(3. Copy the Message\n"
			"(4. Copy the Message(using =)\n"
			"(5. Swap the Message)\n"
			"(6. Add to Folder)\n"
			"(7. Remove to Folder)\n"
			"(8. Remove Message)\n"
			"If you enter the another, exit the programs: ";
		std::cin >> menu;

		switch (menu)
		{
		case 1:
			std::cout << "\nSelect the Folders\n"
				"1. Recieved Folder\n"
				"2. Important Folder\n: ";
			std::cin >> select_folder;
			std::cout << std::endl;

			if (folders.at(select_folder - 1).getMessages().size() == 0)
				std::cout << "This folder is empty\n";

			for (auto item : folders.at(select_folder - 1).getMessages())
				std::cout << item->getContents() << std::endl;
			break;
		case 2:
			std::cout << "\nPlease etner the contents in message: ";
			std::cin >> str;

			Message* m = new Message(str);
			m->save(folders.at(0));
			folders.at(0).addMsg(m);
			std::cout << std::endl;
		case 3:

		}
	}

	return 0;
}