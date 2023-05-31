#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <Windows.h>

const std::string CONST_CONNECTION_STRING = "host=localhost " "port=5432 " "dbname=LessonSQL5 " "user=lesson5 " "password=lesson5 ";

class DatabaseStorage
{
public:
	DatabaseStorage()
	{
	}

	void SetConnection(std::unique_ptr<pqxx::connection> in_b)
	{
		b = std::move(in_b);
	}

	DatabaseStorage(const DatabaseStorage&) = delete;
	DatabaseStorage& operator=(const DatabaseStorage&) = delete;

	std::vector<std::string> getAllClient()
	{
		if (!b)
		{
			return { };
		}

		std::vector<std::string> result;

		pqxx::work tx{ *b };

		for (std::tuple<std::string> title : tx.query<std::string>("SELECT name FROM client"))
		{
			result.push_back(std::get<0>(title));
		}

		return result;

	}

	void CreateTables()
	{
		pqxx::work tx{ *b };
		tx.exec("CREATE TABLE client( id SERIAL PRIMARY KEY, name text NULL, surname text NULL, email text NULL);");
		tx.exec("CREATE TABLE phones( id SERIAL PRIMARY KEY, number1 text NULL, number2 text NULL, number3 text NULL, client_id int NOT NULL, CONSTRAINT client_fk FOREIGN KEY(client_id) REFERENCES client(id) ON DELETE CASCADE);");
		
		tx.exec("INSERT INTO public.client(id, name, surname, email) VALUES(1, 'Mikhail', 'Ivanov', 'mikivan@gmail.com'); ");
		tx.exec("INSERT INTO public.client(id, name, surname, email) VALUES(2, 'Petr', 'Panin', 'ppan@mail.ru'); ");
		tx.exec("INSERT INTO public.client(id, name, surname, email) VALUES(3, 'Ivan', 'Petrov', 'ivpet@mail.ru'); ");
		tx.exec("INSERT INTO public.phones(id, number1, number2, client_id) VALUES(1, '+79872548978', '88482795845', 1); ");
		tx.exec("INSERT INTO public.phones(id, number1, client_id) VALUES(2, '+79872548978', 2); ");
		tx.exec("INSERT INTO public.phones(id, number1, number2, number3, client_id) VALUES(3, '+79872548978', '88482795845', '+79658217521', 3); ");
		tx.commit();
	}

protected:

	std::unique_ptr<pqxx::connection> b;
};


int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	try {

		DatabaseStorage database;

		std::unique_ptr<pqxx::connection> b = std::make_unique<pqxx::connection>(CONST_CONNECTION_STRING);

		database.SetConnection(std::move(b));

		database.CreateTables();


		auto names = database.getAllClient();

		for (auto name : names)
		{
			std::cout << name << " ";
		}
		std::cout << std::endl;

	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
	return 0;
}