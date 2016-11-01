#include <iostream>
#include "tree.h"


int main()
{
	int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: tree_test <number_of_random_points_to_insert>" << std::endl;
            return 1;
        }
        boost::asio::io_service io_service;


        boost::asio::signal_set signal_set(io_service);
        signal_set.add(SIGINT);
        signal_set.add(SIGTERM);
        signal_set.add(SIGQUIT);
        signal_set.async_wait(boost::bind(&boost::asio::io_service::stop, &io_service));

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "He's Dead Jim" << std::endl;
    }
    return 0;
}

}
