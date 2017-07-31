#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <thread>
#include <functional>
#include <tbb/concurrent_queue.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#pragma GCC diagnostic pop


// вспомогательный класс для предачи данных
template <typename T> union DataUint8_t
{
    DataUint8_t(){}
    T type;
    uint8_t dataUint8_t[sizeof(T) / sizeof(uint8_t)];
};

// обертка над АЗИО для отправки данных
class ServerUDP
{
public:
    ServerUDP(std::string adress, ushort port);
    ~ServerUDP();
    // отправка данных Сырых данных
    template < typename T, size_t N> bool SendData(const std::array<T, N> data)
    {
        boost::system::error_code err;
        m_sock.send_to(boost::asio::buffer(data), m_ep, 0, err);
        return err ? false : true;
    }

    template < typename T> bool SendData(const std::vector<T> data)
    {
        boost::system::error_code err;
        m_sock.send_to(boost::asio::buffer(data), m_ep, 0, err);
        return err ? false : true;
    }   

private:
    boost::asio::io_service m_service;
    // сокет
    boost::asio::ip::udp::socket m_sock;
    // отправка на адрес
    boost::asio::ip::udp::endpoint m_ep;
};

class ClientUDP: public QObject
{
    Q_OBJECT
public:
    // иницилизация сокета для прослушки UDP
    ClientUDP(std::string adress, u_short port, size_t sizeBuffer, QObject *parent, bool multicastAddress = true);
    // Закрытие сокета и завершение работы потока
    ~ClientUDP();
    // получениие данных из сокета
    void PopData(std::vector<uint8_t>& data);
    // Проверка работоспособность сокета
    bool IsStart();
    // запуск прослушки
    void Start();
    // остановка прослушки
    void Stop();
    // Методы установки и получения порта прослушки
    size_t port() const;
    void setPort(const u_short &port);
    // Методы установки и получения ip прослушки
    std::string adress() const;
    void setAdress(const std::string &adress);
    // получение Ip адреса с которого было принято сообщение
    boost::asio::ip::address GetIpAddressSender() const;

public slots:

signals:
    // сигнал готовности данных из парсера
    void PendingData();
    // сигнал полученых данных из буфера
    void PendingReadData();
protected:
    // абстрактный класс для обработки данных
    virtual void CreateData() = 0;
private:
    // Прислушка входящих сообщений по UDP
    void ThreadReceiver();
    // добавление датаграмы в буфер
    void Push(std::vector<uint8_t> &data);
    // ассинхронное чтение даннных из сокета
    void ReadData(const boost::system::error_code &ec, std::size_t bytes_transferred);
    // параметры создания сокета
    std::string m_adress;
    u_short m_port;
    // сокет UDP
    boost::asio::io_service m_service;
    boost::asio::ip::udp::socket m_sock;
    boost::asio::ip::udp::endpoint m_ep;
    // поток для прослушки сокета
    std::thread m_thread;
    // буффер для приема
    std::vector<uint8_t> m_buffer;
    // потоко безопастная очередь сырых данных
    std::list<std::vector<uint8_t>> m_data;
    std::atomic_bool m_isStart;
    bool m_isMulticastAddress;
};

#endif // NETWORK_H
