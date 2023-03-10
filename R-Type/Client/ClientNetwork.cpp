#include "ClientNetwork.hpp"

using namespace eng;

ClientNetwork::ClientNetwork(std::string ip, uint16_t portTcp) : _ioContext(), _resolver(_ioContext)
{
    this->_dataInTcp = std::make_shared<_QUEUE_TYPE>();
    this->_dataInUdp = std::make_shared<_QUEUE_TYPE>();

    this->_connection = std::make_unique<Connection>(ip, portTcp, this->_ioContext, this->_dataInTcp, this->_dataInUdp);
    this->initClientNetwork();
}

ClientNetwork::~ClientNetwork()
{
    this->stop();
}

void ClientNetwork::initClientNetwork()
{
    this->_connection->getTcpSocket().connect(this->_connection->getTcpEndpoint());
    if (!this->_connection->getTcpSocket().is_open())
        throw std::runtime_error("TCP socket can't be connected");

    uint16_t portUdp = 0;
    this->_connection->getTcpSocket().read_some(boost::asio::buffer(&portUdp, sizeof(portUdp)));

    uint16_t newPortUdp = this->_connection->getUdpSocketIn().local_endpoint().port();
    this->_connection->getTcpSocket().write_some(boost::asio::buffer(&newPortUdp, sizeof(newPortUdp)));
    this->_connection->setUdpEndpoint(this->_connection->getTcpEndpoint().address().to_string(), portUdp);

    this->_connection->getTcpSocket().read_some(boost::asio::buffer(&_time, sizeof(this->_time)));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    this->_connection->getTcpSocket().read_some(boost::asio::buffer(&_id, sizeof(std::size_t) * 2));

    this->_connection->run();
}

void ClientNetwork::run()
{
    this->_threadContext = std::thread([this]() { this->_ioContext.run(); });
}

void ClientNetwork::stop()
{
    if (this->_connection->isConnected())
        this->_connection->closeConnection();
    if (this->_connection->getThreadConnection().joinable())
        this->_connection->getThreadConnection().join();
    if (!this->_ioContext.stopped())
        this->_ioContext.stop();
    if (this->_threadContext.joinable())
        this->_threadContext.join();
}

bool ClientNetwork::isConnected()
{
    return this->_connection->isConnected();
}

void ClientNetwork::tcpMsg(_STORAGE_DATA data)
{
    this->_connection->tcpMsg(data);
}

void ClientNetwork::udpMsg(_STORAGE_DATA data)
{
    this->_connection->udpMsg(data);
}

_QUEUE_TYPE &ClientNetwork::getQueueInTcp()
{
    return *this->_dataInTcp;
}

_QUEUE_TYPE &ClientNetwork::getQueueInUdp()
{
    return *this->_dataInUdp;
}

void ClientNetwork::updateConnection()
{
    this->_connection->updateDataOut();
}

time_t ClientNetwork::getTime()
{
    return this->_time;
}

std::size_t ClientNetwork::getId()
{
    return this->_id;
}
