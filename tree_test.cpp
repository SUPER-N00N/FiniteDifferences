/**
 * sn00n@77k.eu
 */

#include <boost/asio.hpp>
#include <boost/regex.hpp>
#include <string>
#include <stack>
#include <boost/array.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/logic/tribool.hpp>
#include <signal.h>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>

#include "spaces.h"


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
