// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#ifndef __GMN_SWITCH_SERVICE_HANDLER_H__
#define __GMN_SWITCH_SERVICE_HANDLER_H__

#include "TGmnClientService.h"
#include "../inc/GmnClient_constants.h"
#include "../inc/GmnClient_types.h"

#include "TGmnSwitchService.h"
#include "../inc/GmnSwitch_types.h"

#include "ThriftAdapt.h"

#include <thrift/transport/TSocket.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

#define TTL_VALUE 2;    //Global TTL Value

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;
using namespace std;

using namespace  ::gmnswitch;
using namespace  ::gmnclient;

// Lock
bool available;

//The storage for ALL NAMESPACE SETTING
std::vector<TNamespace> NamespaceList;

//The srorgae for ALL ETH (Ports)
//std::vector<EthSimulator> EthList;

ThriftAdapt<TGmnClientServiceClient> lsAdapt;

//In this demo project we use TCP/UDP to simulate the transmission on link-layer.
//So we using this class to define 'Eth Port'

//class EthSimulator
//{

//The packet in progress
class TempTPacket
{
public:
	string SrcName = "";
	string DesName = "";
	string Payload = "";

	int TTL = TTL_VALUE;    //Time to live.  Reduce one when a 'goto' process executed
	int QoS;    //Reserved. For the future QoS Control feature.

	TempTPacket(TPacket tPacket)
	{
		SrcName = tPacket.SrcName;
		DesName = tPacket.DesName;
		Payload = tPacket.Payload;
	}
};

class TGmnSwitchServiceHandler : virtual public TGmnSwitchServiceIf
{
public:

	TGmnSwitchServiceHandler() 
	{

		available=true;
		cout<<"Plesae select a swtich from 0, 1, 2"<<endl;
		int input(0);
		cin>>input;
		

		  TNamespace tN_0, tN_1, tN_2, tN_3, tN_4; 
		  //Initial Namespace List

		  //Data for testing
		  TEntity tE_0, tE_1, tE_2, tE_3, tE_4, tE_5, tE_6;
		  tE_0.__set_State("ONLINE");
		  tE_0.__set_Value("192.168.0.181");
		  tE_0.__set_Name("BobPC");
		  tE_0.Action.push_back("SEND");
		 
		  tE_1.__set_State("OFFLINE");
		  tE_1.__set_Value("192.168.0.180");
		  tE_1.__set_Name("AlicePC");
		  tE_1.Action.push_back("SEND");

		  tE_2.__set_State("OFFLINE");
		  tE_2.__set_Value("192.168.0.179");
		  tE_2.__set_Name("AliceTablet");
		  tE_2.Action.push_back("SEND");

		  tE_3.__set_State("ONLINE");
		  tE_3.__set_Value("");
		  tE_3.__set_Name("Alice");
		  tE_3.Action.push_back("GOTO AliceDeviceList");

		  tE_4.__set_State("ONLINE");
		  tE_4.__set_Value("");
		  tE_4.__set_Name("Bob");
		  tE_4.Action.push_back("GOTO BobDeviceList");

		  tE_5.__set_State("ONLINE");
		  tE_5.__set_Value("192.168.0.100");
		  tE_5.__set_Name("IM-B");
		  tE_5.Action.push_back("FORWARD_TO S0");

		  tE_6.__set_State("ONLINE");
		  tE_6.__set_Value("192.168.0.120");
		  tE_6.__set_Name("IM-A");
		  tE_6.Action.push_back("FORWARD_TO S2");

//////////////////////////////////////////////////////////////////////////////////////////////

		  switch(input)
		  {
		  	//Initial Namespaces in Swithc_0
		  	case 0:
		  	{
		  		//NS: AliceDeviceList
		  	    tN_1.__set_Name("AliceDeviceList");
			    tN_1.__set_Tag("Device");
			    tN_1.Policy.push_back("AliceJMP");
			    tN_1.Entity.push_back(tE_1);
			    tN_1.Entity.push_back(tE_2);
			    NamespaceList.push_back(tN_1);

			    //MS: IM-A
			    tN_3.__set_Name("IM-A");
				tN_3.__set_Tag("Users");
				tN_3.Policy.push_back("*");
			    tN_3.Policy.push_back("BROADCAST");
				tN_3.Entity.push_back(tE_3);
				NamespaceList.push_back(tN_3);

				break;
		  	}

		  	//Switch_1
		  	case 1:
		  	{
		  		//NS: IM
		        tN_0.__set_Name("IM");
		 	    tN_0.__set_Tag("IM");
		        tN_0.Policy.push_back("*");

		        tN_0.Entity.push_back(tE_5);
		        tN_0.Entity.push_back(tE_6);
		        NamespaceList.push_back(tN_0);
				
				break;
		  	}

		  	//Switch_2
		  	case 2:
		  	{
		  		//NS: BobDeviceList
			    tN_2.__set_Name("BobDeviceList");
			    tN_2.__set_Tag("Device");
			    tN_2.Policy.push_back("BobJMP");
			    tN_2.Entity.push_back(tE_0);
			    NamespaceList.push_back(tN_2);

			    //NS: IM-B
			    tN_4.__set_Name("IM-B");
			    tN_4.__set_Tag("Users");
			    tN_4.Policy.push_back("*");
			    tN_4.Policy.push_back("BROADCAST");
			    tN_4.Entity.push_back(tE_4);
			    NamespaceList.push_back(tN_4);

			    break;
		  	}
		  }

		  cout<<"This is Switch"<<"_"<<input<<endl<<endl;

		  cout << "NAMESPACE SETTING VIEW" << endl;
		  for (int indexofNS = 0; indexofNS < NamespaceList.size(); indexofNS++)
		  {
			  cout << "#=======================================================================================" << endl;
			  cout << "Namespace Name:" <<
				  NamespaceList[indexofNS].Name <<
				  "    Tag:" << NamespaceList[indexofNS].Tag <<
				  endl<<"Policy:"<<NamespaceList[indexofNS].Policy[0] <<
				  endl << "Entity List:" << endl;
			  for (int indexofE = 0; indexofE < NamespaceList[indexofNS].Entity.size(); indexofE++)
			  {
				  cout << "No.:" << indexofE;
				  cout << "    Entity Name:" << NamespaceList[indexofNS].Entity[indexofE].Name;
				  cout <<"    Value:" << NamespaceList[indexofNS].Entity[indexofE].Value;
				  cout << "    State:" << NamespaceList[indexofNS].Entity[indexofE].State;
				  cout<<"    Action:" << NamespaceList[indexofNS].Entity[indexofE].Action[0] << endl;
			  }
			  cout << "#=======================================================================================" << endl;
			}
		}


	//Forward packet
	int ForwardThisPacket(TempTPacket& tPacket, string target)
	{
		int port;
		if(target=="192.168.0.100"||target=="192.168.0.110"||target=="192.168.0.120")
		{
			port=9090;
		}
		else
		{
			port=9080;
		}
		TClientPacket p_send;
		p_send.__set_DesName(tPacket.DesName);
		p_send.__set_SrcName(tPacket.SrcName);
		p_send.__set_Payload(tPacket.Payload);

		std::cout << "> FORWARDING PACKET TO: " <<target<<endl;

		boost::shared_ptr<TSocket> socket(new TSocket(target, port));
		boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
		boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
		TGmnClientServiceClient client(protocol);
		transport->open();
		client.Send(p_send);
		transport->close();
		cout << "> SENDED" << endl;

		return 0;
	}

	//valueÊÇÓÃÀ´±£´æ·µ»ØÖµµÄ(Ö÷ÒªÊÇÖ¸Ìø×ªµÄNamespaceÃû×Ö), policyÊÇ´«ÈëµÄ¸ÃnamespaceµÄpolicy
	int JSresolution_Namespace(TempTPacket& tPacket, string& value, string policy)
	{

		if ("*" == policy)
		{
			return 1;
		}
		else
		{
			return tPacket.DesName == policy ? 1 : 0;
		}
		
	}

	int JSresolution_Entity(TempTPacket& tPacket, string& name, string& value, string& state, string policy, string& extra_value)
	{
		if(policy == "GOTO AliceDeviceList" && tPacket.DesName == "Alice")
		{
			cout<<"##### RESOLUTION: GOTO AliceDeviceList"<<endl;
			extra_value = "AliceDeviceList";
			tPacket.DesName += "JMP";
			return 2;
		}

		else if(policy == "GOTO BobDeviceList" && tPacket.DesName == "Bob")
		{
			cout<<"##### RESOLUTION: GOTO BobDeviceList"<<endl;
			extra_value = "BobDeviceList";
			tPacket.DesName += "JMP";
			return 2;
		}

		else if(policy == "SEND")
		{
			if(state == "ONLINE")
			{
				cout<<"##### RESOLUTION: SEND"<<endl;
				return 1;
			}
			else
			{
				cout<<"##### RESOLUTION: SEND BUT OFFLINE"<<endl;
				return 0;
			}
		}

		else if(tPacket.SrcName.find("@IM-B")!=std::string::npos && policy == "FORWARD_TO S0")
		{
			cout<<"##### RESOLUTION: FORWARDING TO Switch0"<<endl;
			return 1;
		}

	    else if(tPacket.SrcName.find("@IM-A")!=std::string::npos && policy == "FORWARD_TO S2")
		{
			cout<<"##### RESOLUTION: FORWARDING TO Switch2"<<endl;
			return 1;
		}

		else
		{
			return 0;
		}
	}

	int ExecuteDefault(int indexofTNamespace, TempTPacket tPacket)
	{
		cout<<"> EXECUTE DEFAULT"<<endl;
		if(NamespaceList[indexofTNamespace].Policy.size()>1)
		{
			if(NamespaceList[indexofTNamespace].Policy[1]=="BROADCAST")
			{
				cout<<"> BROADCAST！"<<endl;
				if(tPacket.SrcName=="Alice")
				{
					tPacket.SrcName+="@IM-A";
					ForwardThisPacket(tPacket, "192.168.0.110");
				}
				if(tPacket.SrcName=="Bob")
				{
					tPacket.SrcName+="@IM-B";
					ForwardThisPacket(tPacket, "192.168.0.110");
				}
			}
		}

		return 1;
	}

	int QueryThisEntity(TempTPacket tPacket, int indexofTEntity, int indexofTNamespace)
	{
		cout<<"Entity:"<<NamespaceList[indexofTNamespace].Entity[indexofTEntity].Name<<endl;

		//if TTL <=0 then skip this packet

		if (unlikely(tPacket.TTL <= 0))
		{
			return 0;
		}

		string temp_name;
		string temp_value;    //the name of the target namespace
		string temp_state;
		string temp_action;
		string extra_value;
		temp_name = NamespaceList[indexofTNamespace].Entity[indexofTEntity].Name;
		temp_value = NamespaceList[indexofTNamespace].Entity[indexofTEntity].Value;
		temp_state = NamespaceList[indexofTNamespace].Entity[indexofTEntity].State;
		temp_action = NamespaceList[indexofTNamespace].Entity[indexofTEntity].Action[0];


		int result_flag(0);

		//resolute the policy£¡
		result_flag = JSresolution_Entity(tPacket, temp_name, temp_value, temp_state, temp_action, extra_value);

		// 0 ²»match,skip  1 ·¢³ö 2 Ìø×ª
		
		if (result_flag == 0)
		{
			return 0;
		}
		else if (result_flag == 1)
		{
			ForwardThisPacket(tPacket, temp_value);
			return 0;
		}
		else if (result_flag == 2)
		{
			tPacket.TTL -= 1;    //reduce TTL when 'goto' action executed
								 ////find the index of the target namespace in the list by the particular name of namespace	
			cout<<"> PACKET RESOLUTION >> GOTO NAMESPACE: "<<extra_value<<endl;
			for (int n = 0; n < NamespaceList.size(); n++)
			{
				if (NamespaceList[n].Name == extra_value)
				{
					QueryThisNamespace(tPacket, n);
					//break;
					return 0;
				}
			}
		}

		return 0;
	}

	//Check the namespace
	int QueryThisNamespace(TempTPacket tPacket, int indexofTNamespace)
	{
		cout<<"> NOW SEARCHING IN NS:"<<NamespaceList[indexofTNamespace].Name<<endl;
		//if TTL <=0 then skip this namespace
		if (unlikely(tPacket.TTL <= 0))
		{
			//cout << "50" << endl;
			return 0;
		}

		else
		{
			//cout << "51" << endl;
			string temp_value;    //the name of the target namespace
			int result_flag(0);
			//resolute the policy
			result_flag = JSresolution_Namespace(tPacket, temp_value, NamespaceList[indexofTNamespace].Policy[0]);

			if (result_flag == 0)
			{
				return 0;
			}

			else if (result_flag == 2)
			{
				tPacket.TTL -= 1;    //reduce TTL when 'goto' action executed
								     //find the index of the target namespace in the list by the particular name of namespace
				for (int n = 0; n < NamespaceList.size(); n++)
				{
					if (NamespaceList[n].Name == temp_value)
					{
						QueryThisNamespace(tPacket, n);
						break;
					}
					return 0;
				}
			}

			else if (result_flag == 1)
			{
				for (int n = 0; n < NamespaceList[indexofTNamespace].Entity.size(); n++)
				{
					//cout << "E" <<n<< endl;
					QueryThisEntity(tPacket, n, indexofTNamespace);
				}
				//Run the default policy if exist
				ExecuteDefault(indexofTNamespace, tPacket);
				return 1;
		 	}
		}
		return 0;
	}

//Actually this function is the 
	void Send(const TPacket& tPacket)
	{
		if(available==true)
		{
		    cout << ">>> -->PACKET IS RECEIVING..." << "  |  srcName=" << tPacket.SrcName << "  desName=" << tPacket.DesName << endl;
	  
	  		//Copy the original packet to a temppacket structure
	  		TempTPacket tempPacket(tPacket);
	 		//cout << "1" << endl;
	  		//Process packet
	  		for (int n = 0; n < NamespaceList.size(); n++)
	  		{
			// cout << "2" << endl;
	  			cout << "> START TO PROCESS PACKET..." << endl;
		    	QueryThisNamespace(tempPacket, n);
		    	cout <<"==================================================="<<endl;
			}
			cout<<"<<<"<<endl;
		}
		else
		{
			cout<< "> !!! OUT OF SERVICE !!!"<<endl;
		}
	}

  /**
   * Add TNamespace
   * 
   * @param tNamespace
   */
    void AddNamespace(const TNamespace& tNamespace)
  	{


  		return;

/*

    //Firstly, check if the name of namespace is existed
	  uint32_t flag = 0;
	  for (int n = 0; n < NamespaceList.size(); n++)
	  {
		  if (unlikely(NamespaceList[n].Name == tNamespace.Name))
		  {
			  flag = 1;
			  cout << "> NAMESPACE EXISTED" << endl;
			  break;
		  }
		  else
		  {
			  ;
		  }
	  }
	  if (flag == 0)
	  {
		  //push this item to the list
		  NamespaceList.push_back(tNamespace);
	  }
	  cout <<" > NAMESPACE SETTING UPDATED" << endl;
	  ListNamespace();
*/


	}

  /**
   * Update TNamespace
   * 
   * @param tNamespace
   */
	void UpdateNamespace(const vector<TNamespace> & updated_Namespaces)
	{
		available=false;
		//copy the updated setting to cover that on the switch

		NamespaceList.clear();
		NamespaceList = updated_Namespaces;

		available=true;
		cout << "> NAMESPACE SETTING UPDATED" << endl;
		ListNamespace();
	}
 

 	void ListNamespace(std::vector<TNamespace> & _return) 
	{
		//copy data from the local namespace list to the remote one
		_return = NamespaceList;
		cout <<"> CLIENT REQUESTS THE NAMESPACE LSIT"<< endl<<endl;
	}


	//List all namespace and entities on console
	void ListNamespace()
	{
		cout << "NAMESPACE SETTING VIEW" << endl;
		for (int indexofNS = 0; indexofNS < NamespaceList.size(); indexofNS++)
		{
			cout << "=======================================================================================" << endl;
			cout << "Namespace Name:" <<
				NamespaceList[indexofNS].Name <<
				"    Tag:" << NamespaceList[indexofNS].Tag <<
				endl << "Policy:" << NamespaceList[indexofNS].Policy[0] <<
				endl << "Entity List:" << endl;
			for (int indexofE = 0; indexofE < NamespaceList[indexofNS].Entity.size(); indexofE++)
			{
				cout << "No.:" << indexofE;
				cout << "    Entity Name:" << NamespaceList[indexofNS].Entity[indexofE].Name;
				cout << "    Value:" << NamespaceList[indexofNS].Entity[indexofE].Value;
				cout << "    State:" << NamespaceList[indexofNS].Entity[indexofE].State;
				cout << "    Action:" << NamespaceList[indexofNS].Entity[indexofE].Action[0] << endl;
			}
			cout << "=======================================================================================" << endl;
		}
	}
};

#endif
