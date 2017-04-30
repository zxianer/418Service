#include <iostream>
#include <cstdio>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

using namespace boost::asio;

class talk_to_client : public boost::enable_shared_from_this<talk_to_client>, boost::noncopyable
{
	typedef talk_to_client self_type;
	talk_to_client();
public:
	typedef boost::shared_ptr<talk_to_client> ptr;
	typedef boost::system::error_code error_code;

	void start();
	void stop();
	void on_read(const error_code& err, size_t bytes);
	void on_write(const error_code& err, size_t bytes);
	void do_read();
	void do_write(const std::string& msg);
	ip::tcp::socket& sock();
	static ptr new_();

private:
	ip::tcp::socket sock_;
	enum { max_msg = 1024 };
	char read_buffer_[max_msg];
	char write_buffer_[max_msg];
	bool started_;	
};

