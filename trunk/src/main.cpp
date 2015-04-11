#include "TGmnSwitchService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/server/TThreadedServer.h>
#include <iostream>
#include "TGmnSwitchServiceHandler.h"
//#include <vector>

#define PORT_FOR_MANAGEMENT 9090

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;
using namespace std;

using namespace  ::gmnswitch;
//using namespace ::gmnclient;

int main(int argc, char **argv) 
{
    //Firstly, start the function of management
    int port = PORT_FOR_MANAGEMENT;
    cout << "Server is running..." << endl;
    boost::shared_ptr<TGmnSwitchServiceHandler> handler(new TGmnSwitchServiceHandler());
    boost::shared_ptr<TProcessor> processor(new TGmnSwitchServiceProcessor(handler));
    boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    //TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    TThreadedServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();



  return 0;
}



