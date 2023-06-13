// Task6.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <Windows.h>

class Book;
class Stock;
class Sale;

class Publisher
{
public:
    std::string name;
    Wt::Dbo::collection<Wt::Dbo::ptr<Book>> books;

    template<typename Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, name, "name");
        Wt::Dbo::hasMany(a, books, Wt::Dbo::ManyToOne, "publisher");

    }
};

class Book
{
public:
    std::string title;
    Wt::Dbo::ptr<Publisher> publisher;
    Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks;

    template<typename Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, title, "title");
        Wt::Dbo::belongsTo(a, publisher, "publisher");
        Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "book");
    }
};


class Shop
{
public:
    std::string name;
    Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks;

    template<typename Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, name, "name");
        Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "shop");

    }
};

class Stock
{
public:
    int count;
    Wt::Dbo::ptr<Shop> shop;
    Wt::Dbo::ptr<Book> book;
    Wt::Dbo::collection<Wt::Dbo::ptr<Sale>> sales;

    template<typename Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, count, "count");
        Wt::Dbo::belongsTo(a, shop, "shop");
        Wt::Dbo::belongsTo(a, book, "book");
        Wt::Dbo::hasMany(a, sales, Wt::Dbo::ManyToOne, "stock");
    }
};


class Sale
{
public:
    int count;
    std::string date;
    Wt::Dbo::ptr<Stock> stock;

    template<typename Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, count, "count");
        Wt::Dbo::field(a, date, "date");
        Wt::Dbo::belongsTo(a, stock, "stock");
    }
};

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    try
    {
        std::string connectionString =
            "host=localhost "
            "port=5432 "
            "dbname=Lesson6 "
            "user=lesson "
            "password=lesson6 ";

        auto postgres = std::make_unique<Wt::Dbo::backend::Postgres>(connectionString);

       
       

    }
    catch (const Wt::Dbo::Exception& e)
    {
        std::cout << e.what() << std::endl;
    }



    return 0;
}