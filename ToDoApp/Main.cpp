#include <iostream>
#include <string>
#include <vector>
#include <map>

#define Print(msg) std::cout << msg << std::endl

class ToDoList
{
private:
	ToDoList() = delete;
	static std::map<size_t, std::string> todo_list;
	static std::map<size_t, bool> todo_completion;
	static size_t id;
public:
	static void add_todo(const std::string &todo_description)
	{
		todo_list.insert({id, todo_description});
		todo_completion.insert({id, false});
		id++;
	}

	static void remove_todo(uint32_t id)
	{
		todo_list.erase(id);
		todo_completion.erase(id);
		std::map<size_t, bool>::iterator it = todo_completion.find(id);
		it->second = false;
	}

	static void done(uint32_t id)
	{
		std::map<size_t, bool>::iterator it = todo_completion.find(id);
		it->second = true;
		std::cout << "todo with id " << id << " is now marked as 'DONE'" << std::endl;
	}

	static void print_todo_list()
	{

		for (size_t i = 0; i < todo_list.size(); i++)
		{
			auto it_todo_completion = todo_completion.begin();
			auto it_todo_list = todo_list.begin();
			std::advance(it_todo_list, i); 
			std::advance(it_todo_completion, i); 

			std::cout << it_todo_list->first << ": " << it_todo_list->second << " [";
			if(it_todo_completion->second) std::cout << "DONE]" << std::endl;
			else std::cout << "NOT DONE]" << std::endl;
		}
	}
};

std::map<size_t, std::string> ToDoList::todo_list;
std::map<size_t, bool> ToDoList::todo_completion;
size_t ToDoList::id = 0;

int main()
{
	while(true)
	{
		std::string user_input;
		std::getline(std::cin, user_input);

		std::string command = user_input.substr(0, user_input.find(" "));
		
		size_t user_input_len = user_input.length();
		size_t command_len = command.length();
		size_t del = user_input.find(" ");

		std::string command_arg = user_input.substr(del + 1, user_input_len - command_len);
		if (command == "add")
		{
			if (command_arg.empty())
			{
				Print("no command args provided!");
				return 0;
			}

			ToDoList::add_todo(command_arg);
			Print("todo added successfully!");
		}

		if (command == "remove")
		{
			if (command_arg.empty())
			{
				Print("no command args provided!");
				return 0;
			}

			ToDoList::remove_todo(std::stoul(command_arg));
			Print("todo removed successfully!");
		}

		if (command == "done")
		{
			ToDoList::done(std::stoul(command_arg));
		}

		if (command == "list")
		{
			ToDoList::print_todo_list();
		}

		if (command == "help")
		{
			Print("'add \"test\"': add a todo with the description \"test\"");
			Print("'remove 2': remove the todo with id 2");
			Print("'done 2': mark the todo with id 2 as \"done\"");
			Print("'list': list all the todos");
			Print("'help': display all the available commands (this list)");
			Print("'quit': exit the program");
		}

		if (command == "quit")
		{
			return 0;
		}
	}
}
