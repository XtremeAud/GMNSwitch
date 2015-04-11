/***********************************************************
 * Vss Thrift Script
 * Made By XinyuWang
 * 2015/3/16
 ***********************************************************/

namespace java gmnclient
namespace cpp gmnclient
namespace rb GmnClient
namespace py gmnclient
namespace perl GmnClient
namespace csharp GmnClient

//"required" and "optional" keywords are purely for documentation.

struct TClientPacket {
  1: required string SrcName,
  2: required string DesName,
  3: required binary Payload
}

service TGmnClientService {

  /**
   * Send the TClientPacket to Switch
   */
  void Send(
    1: required TClientPacket tClientPacket
  );
  
}
