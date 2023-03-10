/**
 * @file Connection.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The network's connection.
 * @copyright Epitech Rennes 2022
 */

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

/// @cond
#include "NetCommon.hpp"

/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The network's connection.
     * @class Connection
     */
    class Connection : public boost::enable_shared_from_this<Connection>
    {
        private:
            void handleMsgTcp(const boost::system::error_code &error, size_t size);
            void handleMsgUdp(const boost::system::error_code &error, size_t size);
            void open();
            void initConnection();
            bool checkConnection();

            boost::asio::io_context &_ioContext;
            _B_ASIO_UDP::endpoint _udpEndpoint;
            _B_ASIO_TCP::endpoint _tcpEndpoint;
            _B_ASIO_UDP::endpoint _tmpEndpoint;
            _B_ASIO_UDP::socket _udpSocketIn;
            _B_ASIO_UDP::socket _udpSocketOut;
            _B_ASIO_TCP::socket _tcpSocket;
            std::vector<_STORAGE_DATA> _dataOutUdp;
            std::vector<_STORAGE_DATA> _dataOutTcp;
            std::shared_ptr<_QUEUE_TYPE> _dataInUdp;
            std::shared_ptr<_QUEUE_TYPE> _dataInTcp;
            std::thread _threadConnection;
            _STORAGE_DATA _tcpTmpBuffer;
            _STORAGE_DATA _udpTmpBuffer;

        public:
            /**
             * @brief Connection constructor.
             * @fn Connection(boost::asio::io_context &ioContext, std::shared_ptr<_QUEUE_TYPE> &dataInUdp, std::shared_ptr<_QUEUE_TYPE> &dataInTcp)
             * @param ioContext A reference to the input output context.
             * @param dataInTcp A reference to the tcp input data.
             * @param dataInUdp A reference to the udp input data.
             */
            Connection(boost::asio::io_context &ioContext, std::shared_ptr<_QUEUE_TYPE> &dataInTcp, std::shared_ptr<_QUEUE_TYPE> &dataInUdp);
            /**
             * @brief Connection constructor.
             * @fn Connection(std::string ip, uint16_t portTcp, boost::asio::io_context &ioContext, std::shared_ptr<_QUEUE_TYPE> &dataInUdp, std::shared_ptr<_QUEUE_TYPE> &dataInTcp)
             * @param ip The ip of the client.
             * @param portUdp The udp port.
             * @param ioContext A reference to the input output context.
             * @param dataInTcp A reference to the tcp input data.
             * @param dataInUdp A reference to the udp input data.
             */
            Connection(std::string ip, uint16_t portTcp, boost::asio::io_context &ioContext, std::shared_ptr<_QUEUE_TYPE> &dataInTcp, std::shared_ptr<_QUEUE_TYPE> &dataInUdp);
            /**
             * @brief Connection destructor.
             * @fn ~Connection()
             */
            ~Connection();

            /**
             * @brief Run the connection.
             * @fn run()
             */
            void run();
            /**
             * @brief Get the tcp socket.
             * @fn _B_ASIO_TCP::socket &getTcpSocket()
             * @return A reference to the tcp socket
             */
            bool isConnected();
            /**
             * @brief Close the connection.
             * @fn void closeConnection()
             */
            void closeConnection();

            /**
             * @brief Get the thread connection.
             * @fn std::thread &getThreadConnection()
             * @return A reference to the thread connection.
             */
            std::thread &getThreadConnection();
            /**
             * @brief Get the tcp socket.
             * @fn _B_ASIO_TCP::socket &getTcpSocket()
             * @return A reference to the tcp socket.
             */
            _B_ASIO_TCP::socket &getTcpSocket();
            /**
             * @brief Get the udp socket input.
             * @fn _B_ASIO_UDP::socket &getUdpSocketIn()
             * @return A reference to the udp socket.
             */
            _B_ASIO_UDP::socket &getUdpSocketIn();
            /**
             * @brief Get the udp socket output.
             * @fn _B_ASIO_UDP::socket &getUdpSocketOut()
             * @return A reference to the udp socket.
             */
            _B_ASIO_UDP::socket &getUdpSocketOut();

            /**
             * @brief Set the udp endpoint.
             * @fn void setUdpEndpoint(std::string ip, uint16_t port)
             * @param ip The client ip.
             * @param port The client port.
             */
            void setUdpEndpoint(std::string ip, uint16_t port);
            /**
             * @brief Set the tdp endpoint.
             * @fn void setTcpEndpoint(_B_ASIO_TCP::endpoint endpoint)
             * @param endpoint The endpoint to set.
             */
            void setTcpEndpoint(_B_ASIO_TCP::endpoint endpoint);
            /**
             * @brief Get the udp endpoint.
             * @fn _B_ASIO_UDP::endpoint getUdpEndpoint()
             * @return The udp endpoint.
             */
            _B_ASIO_UDP::endpoint getUdpEndpoint();
            /**
             * @brief Get the tdp endpoint.
             * @fn _B_ASIO_TCP::endpoint getTcpEndpoint()
             * @return The tdp endpoint.
             */
            _B_ASIO_TCP::endpoint getTcpEndpoint();

            /**
             * @brief Send a tcp message.
             * @fn void tcpMsg(_STORAGE_DATA data)
             * @param data The data to send through tcp connection.
             */
            void tcpMsg(_STORAGE_DATA data);
            /**
             * @brief Send an udp message.
             * @fn void udpMsg(_STORAGE_DATA data)
             * @param data The data to send through udp connection.
             */
            void udpMsg(_STORAGE_DATA data);

            /**
             * @brief Update the output data.
             * @fn void updateDataOut()
             */
            void updateDataOut();
    };
} // namespace eng

#endif /* !CONNECTION_HPP_ */
