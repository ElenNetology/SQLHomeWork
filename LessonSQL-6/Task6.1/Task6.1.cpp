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

        Wt::Dbo::Session session;
        session.setConnection(std::move(postgres));
        session.mapClass<Book>("book");
        session.mapClass<Publisher>("publisher");
        session.mapClass<Shop>("shop");
        session.mapClass<Stock>("stock");
        session.mapClass<Sale>("sale");

        try
        {
            session.createTables();


            Wt::Dbo::Transaction transaction{ session };

            std::unique_ptr<Publisher> p1 = std::make_unique<Publisher>();
            p1->name = "Alpina.Proza";

            std::unique_ptr<Book> b1 = std::make_unique<Book>();
            b1->title = "Atlas Shrugged";

            std::unique_ptr<Shop> s1 = std::make_unique<Shop>();
            s1->name = "Metida";

            std::unique_ptr<Stock> st1 = std::make_unique<Stock>();
            st1->count = 90;

            std::unique_ptr<Sale> sl1 = std::make_unique<Sale>();
            sl1->count = 20;
            sl1->date = "2023-06-20";

            auto publisher_added = session.add(std::move(p1));
            auto book_added = session.add(std::move(b1));
            auto shop_added = session.add(std::move(s1));
            auto stock_added = session.add(std::move(st1));
            auto sale_added = session.add(std::move(sl1));

            book_added.modify()->publisher = publisher_added;

            stock_added.modify()->book = book_added;

            shop_added.modify()->stocks.insert(stock_added);

            sale_added.modify()->stock = stock_added;

            transaction.commit();


        }
        catch (const Wt::Dbo::Exception& e)
        {
            std::cout << "Failed to create tables: " << e.what() << std::endl;
        }
        std::cout << "Enter publisher: ";
        std::string publisherName;

        std::cin >> publisherName;

        Wt::Dbo::Transaction t1{ session };

        Wt::Dbo::ptr<Publisher> publisher = session.find<Publisher>().where("name = ?").bind(publisherName).limit(1);

        if (publisher)
        {
            std::cout << "Publisher found: " << publisher->name << std::endl;

            Wt::Dbo::collection<Wt::Dbo::ptr<Book>> books = publisher->books;

            std::vector<Wt::Dbo::ptr<Stock>> stocks;
            for (auto book : books)
            {

                std::for_each(book->stocks.begin(), book->stocks.end(), [&stocks](Wt::Dbo::ptr<Stock> s) {
                    stocks.push_back(s);
                    });
            }

            for (auto stock : stocks)
            {
                std::cout << "Stock found: " << stock->book->title << " in shop: " << stock->shop->name << std::endl;
            }
        }
        else
        {
            std::cout << "Publisher not found" << std::endl;
        }

        t1.commit();
    }

    catch (const Wt::Dbo::Exception& e)
    {
        std::cout << e.what() << std::endl;
    }



    return 0;
}