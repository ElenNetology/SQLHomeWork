#include <iostream>
#include <string>
#include <pqxx/pqxx>

/*class Client
{
	public:
		void Query ()
		{
			pqxx::work tx{ b };
			std::string author = tx.query_value<std::string>("SELECT name FROM client WHERE id = 2");
			std::cout << "The name client you wanted is: " << name << ".\n";
		};
};*/


int main()
{
	try {
		pqxx::connection b(
			"host=localhost "
			"port=5432 "
			"dbname=LessonSQL5 "
			"user=lesson5 "
			"password=lesson5 "
		);
		pqxx::work tx{ b };
		tx.exec("INSERT INTO telephon(id, number1, number2) "
			"VALUES('4', '+7254851354', '457658')");
		tx.commit();

	}
	catch (pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
	}


	return 0;
}