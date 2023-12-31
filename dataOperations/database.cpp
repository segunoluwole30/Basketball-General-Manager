#include <iostream>
#include <pqxx/pqxx>

int main()
{
    try
    {
        // Set up a connection to the PostgreSQL database
        pqxx::connection conn("dbname=BestGM user=postgres password=jesusislord host=localhost port=5432");

        if (conn.is_open())
        {
            std::cout << "Opened database successfully: " << conn.dbname() << std::endl;
        }
        else
        {
            std::cout << "Failed to open database" << std::endl;
            return 1;
        }

        // Execute a simple SQL query
        pqxx::work txn(conn);
        pqxx::result result = txn.exec("SELECT * FROM teams");
        txn.commit();

        // Print the query results
        for (const auto &row : result)
        {
            for (const auto &field : row)
            {
                std::cout << field.c_str() << " ";
            }
            std::cout << std::endl;
        }

        // Close the connection
        // conn.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}