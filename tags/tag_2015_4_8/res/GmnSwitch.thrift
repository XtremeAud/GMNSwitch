/***********************************************************
 * Vss Thrift Script
 * Made By XinyuWang
 * 2015/3/16
 ***********************************************************/

namespace java gmnswitch
namespace cpp gmnswitch
namespace rb GmnSwitch
namespace py gmnswitch
namespace perl GmnSwitch
namespace csharp GmnSwitch

//"required" and "optional" keywords are purely for documentation.

struct TPacket {
  1: required string SrcName,
  2: required string DesName,
  3: required binary Payload
}

struct TEntity {
  1: required string Name,
  2: required string Value,
  3: required string State,
  4: required list<string> Action
}

struct TNamespace {
  1: required string Name,
  2: required string Tag,
  3: required list<string> Policy,
  4: required list<TEntity> Entity
}

service TGmnSwitchService {

  /**
   * Send the TPacket to Switch
   */
  void Send(
    1: required TPacket tPacket
  );
  

  /**
   * Add TNamespace
   */
  void AddNamespace(
    1: required TNamespace tNamespace
  );

  /**
   * Update TNamespace
   */
  void UpdateNamespace(
    1: required list<TNamespace> tNamespaceList 
  );
  
  /**
   * Get a list of TNamespace
   */
  list<TNamespace> ListNamespace();
  
}
