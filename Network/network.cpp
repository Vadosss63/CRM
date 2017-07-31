#include "network.h"

ServerUDP::ServerUDP(std::string adress, ushort port):
    m_sock(m_service),
    m_ep(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(adress), port))
{
    m_sock.open(boost::asio::ip::udp::v4());
}

ServerUDP::~ServerUDP()
{
    m_sock.close();
}

ClientUDP::ClientUDP(std::string adress, u_short port, size_t sizeBuffer, QObject *parent, bool multicastAddress):QObject(parent),
    m_adress(adress), m_port(port), m_sock(m_service), m_buffer(sizeBuffer), m_isStart(false), m_isMulticastAddress(multicastAddress)
{}

ClientUDP::~ClientUDP()
{
    Stop();
}

void ClientUDP::Start()
{
    if(IsStart())
        return;

    boost::asio::ip::address_v4 multicastAddress(boost::asio::ip::address_v4::from_string(m_adress));
    boost::asio::ip::udp::endpoint endpoint(multicastAddress, m_port);
    m_sock.open(endpoint.protocol());
    m_sock.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    m_sock.bind(endpoint);
    boost::system::error_code e;
    // подключение мультикаста

    if(m_isMulticastAddress)
        m_sock.set_option(boost::asio::ip::multicast::join_group(multicastAddress), e);

    if(e)
    {
        throw boost::system::system_error(e);
    }

    m_thread = std::thread(&ClientUDP::ThreadReceiver, this);
}

void ClientUDP::Stop()
{
    m_service.stop();
    if(IsStart())
    {
        m_isStart = false;
        if(m_sock.is_open())
            m_sock.close();
        // корректное завершения патока
        if (m_thread.joinable())
            m_thread.join();
    }
}

void ClientUDP::ThreadReceiver()
{
    // принимаем данные из сокета
    m_sock.async_receive_from(boost::asio::buffer(m_buffer),
                              m_ep, boost::bind(&ClientUDP::ReadData,
                                                this, boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
    m_isStart = true;
    m_service.reset();
    m_service.run();

}

void ClientUDP::ReadData(const boost::system::error_code & ec, std::size_t bytes_transferred)
{
    if(!ec)// проверяем сокет на ошибки
    {
        std::vector<uint8_t> reciverDada(bytes_transferred);
        std::copy(m_buffer.begin(), m_buffer.begin() + bytes_transferred, reciverDada.begin());
        Push(reciverDada);
        CreateData();
        // принимаем данные из сокета
        if(m_isStart)
            m_sock.async_receive_from(boost::asio::buffer(m_buffer),
                                      m_ep, boost::bind(&ClientUDP::ReadData,
                                                        this,
                                                        boost::asio::placeholders::error,
                                                        boost::asio::placeholders::bytes_transferred));

    }


}

std::string ClientUDP::adress() const
{
    return m_adress;
}

void ClientUDP::setAdress(const std::string &adress)
{
    m_adress = adress;
}

boost::asio::ip::address ClientUDP::GetIpAddressSender() const
{
    return m_ep.address();
}

size_t ClientUDP::port() const
{
    return m_port;
}

void ClientUDP::setPort(const u_short &port)
{
    m_port = port;
}

void ClientUDP::PopData(std::vector<uint8_t>& data)
{
    data = m_data.back();
    m_data.pop_back();
}

bool ClientUDP::IsStart()
{
    return m_isStart;
}

void ClientUDP::Push(std::vector<uint8_t>& data)
{
    m_data.push_front(std::move(data));
}
