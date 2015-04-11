/**
 * Autogenerated by Thrift Compiler (0.9.2)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef GmnClient_TYPES_H
#define GmnClient_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>


namespace gmnclient {

class TClientPacket;


class TClientPacket {
 public:

  static const char* ascii_fingerprint; // = "AB879940BD15B6B25691265F7384B271";
  static const uint8_t binary_fingerprint[16]; // = {0xAB,0x87,0x99,0x40,0xBD,0x15,0xB6,0xB2,0x56,0x91,0x26,0x5F,0x73,0x84,0xB2,0x71};

  TClientPacket(const TClientPacket&);
  TClientPacket& operator=(const TClientPacket&);
  TClientPacket() : SrcName(), DesName(), Payload() {
  }

  virtual ~TClientPacket() throw();
  std::string SrcName;
  std::string DesName;
  std::string Payload;

  void __set_SrcName(const std::string& val);

  void __set_DesName(const std::string& val);

  void __set_Payload(const std::string& val);

  bool operator == (const TClientPacket & rhs) const
  {
    if (!(SrcName == rhs.SrcName))
      return false;
    if (!(DesName == rhs.DesName))
      return false;
    if (!(Payload == rhs.Payload))
      return false;
    return true;
  }
  bool operator != (const TClientPacket &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TClientPacket & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const TClientPacket& obj);
};

void swap(TClientPacket &a, TClientPacket &b);

} // namespace

#endif